#include"Tutorial.h"
#include"DxLib.h"
#include"Hit.h"
#include"Main.h"
#include"Game.h"
#define PLAYER_MOV_SPEED	6.0f
#define PLAYER_ROT_SPEED	6.0f

void Tutorial::Init()
{
	//	�v���C���[�̍��W�̏�����
	Player_pos.x = WINDOW_W / 2;
	Player_pos.y = WINDOW_H + 50;
	//	�傫���̏�����
	//(�����蔻��̑傫��)
	Player_size = 5;
	//	�v���C���[�̉摜�̓ǂݍ���
	Player_image = LoadGraph("data/Game/2D/Flog.png");

	//	�v���C���[���ǂ��܂Ői�ނ���ۑ�����ϐ�
	Player_move.x = WINDOW_W / 2;
	Player_move.y = WINDOW_H + 50;
	//	�v���C���[�����@���邩�̃J�E���g
	Player_count = 0;
	//	�v���C���[�������ɓ����Ȃ����邽�߂̕ϐ��̏�����
	move_time = 0;
	//	�����Ă��������肷��ϐ�
	move = true;
	//	�v���C���[�̃S�[������
	goal = false;

	//	��x�g�����S�[���͎g���Ȃ����邽�߂̕ϐ�
	for (int i = 0; i <= 4; i++)
	{
		goal_dead_count[i] = 0;
		//	�S�[�������ۂɃS�[���̐F��ς���
		goal_juge_color[i] = 255;
	}

	//	�S�[���J�E���g�̏�����
	goal_count = 0;

	goal_count_check = 5;

	//	�v���C���[���G�ɂԂ������Ƃ��̏���
	dead = false;

	wood_out = false;

	//	��ɓ������Ƃ��̕ϐ��̏�����
	river_in = false;
	Player_flow = -5.0f;

	//	�������Ԃ̕ϐ��̏�����
	time = 1800;
	time_start = false;


		for (int i = 0; i <= 8; i++)
	{
		//	�E����o�Ă���悤
		Enemy_pos_Right[i].x = WINDOW_W;
		Enemy_pos_Right[i].y = WINDOW_W / 2;
		//	������o�Ă���悤
		Enemy_pos_Left[i].x = WINDOW_W;
		Enemy_pos_Left[i].y = WINDOW_W / 2;

	}

	//	Enemy�̉摜
	Car_red = LoadGraph("data/Game/2D/car_red.png");
	Car_green = LoadGraph("data/Game/2D/car_green.png");
	Car_blue = LoadGraph("data/Game/2D/car_skyblue.png");
	Car_black = LoadGraph("data/Game/2D/car_black.png");
	//	�t����
	Car_red_oppose = LoadGraph("data/Game/2D/car_red_gyaku.png");
	Car_green_oppose = LoadGraph("data/Game/2D/car_green_gyaku.png");
	Car_blue_oppose = LoadGraph("data/Game/2D/car_skyblue_gyaku.png");
	Car_black_oppose = LoadGraph("data/Game/2D/car_black_gyaku.png");


	//	Enemy�̑傫���̏�����
	Enemy_size = 10;

	//	�d�Ȃ��Ă�G�����炷����
	//	�E����o�Ă���G
	Enemy_pos_Right[1].x =+200;
	Enemy_pos_Right[4].x = +200;
	Enemy_pos_Right[7].x = +250;

	Enemy_pos_Right[2].x = +400;
	Enemy_pos_Right[5].x = +400;
	Enemy_pos_Right[8].x = +450;

	//	������o�Ă���G
	Enemy_pos_Left[1].x = +200;
	Enemy_pos_Left[4].x = +200;
	Enemy_pos_Left[7].x = +250;

	Enemy_pos_Left[2].x = +400;
	Enemy_pos_Left[5].x = +400;
	Enemy_pos_Left[8].x = +450;

	//	X���W�����炷���߂̏����@���ꂪ�Ȃ��ƎԂ����ő����Ă���悤�Ɍ�����̂�
	Enemy_pos_Left[0].x += 50;
	Enemy_pos_Left[1].x += 50;
	Enemy_pos_Left[2].x += 50;

	//	��̍��W�̕ϐ���������
	//	�E����̐�
	Enemy_pos_River_Right[0].x = 900;
	Enemy_pos_River_Right[1].x = 0;

	//	������̏�����
	Enemy_pos_River_Left[0].x = 900;
	Enemy_pos_River_Left[1].x = 100;
	//	�E����̐�
	Enemy_pos_River_Right[2].x = 1400;
	Enemy_pos_River_Right[3].x = 500;

	//	�摜��ǂݍ���
	River_image = LoadGraph("data/Game/2D/River.jpg");

	Wood_image = LoadGraph("data/Game/2D/wood.png");
	Wood_image2 = LoadGraph("data/Game/2D/wood_hantai.png");

}
void Tutorial::Update()
{
	//goal_count_check = 5 - goal_count;

	//if (time_start) {
	//	time--;
	//}
	move_time++;
	//	�A�łœ����Ȃ��悤�ɃJ�E���g���Ƃ�
	if (move_time >= 10)
	{
		move = true;
	}

	if (move)
	{
		//	�v���C���[���쏈��
		if (PushHitKey(KEY_INPUT_LEFT))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_RIGHT))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_UP))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_DOWN))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		//	�v���C���[���쏈�� WASD�L�[�p
		if (PushHitKey(KEY_INPUT_A))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_D))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_W))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_S))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}

		//	��ʊO�ɍs���Ȃ��悤�ɂ��鏈��
		if (Player_move.x >= WINDOW_W - 50)
		{
			Player_move.x = WINDOW_H - 50;

		}
		if (Player_move.x <= 50)
		{
			Player_move.x = 50;
		}
		if (Player_move.y >= WINDOW_H - 25)
		{
			Player_move.y = WINDOW_H - 25;
		}
	}
	if (Player_move.x >= Player_pos.x)
	{
		Player_pos.x += 5;
	}
	if (Player_move.y <= Player_pos.y)
	{
		Player_pos.y -= 5;
	}
	if (Player_move.x <= Player_pos.x)
	{
		Player_pos.x -= 5;
	}
	if (Player_move.y >= Player_pos.y)
	{
		Player_pos.y += 5;
	}


	//	��ɓ������Ƃ��̏���

	/*if (Player_pos.y <= 100)
	{
		Player_pos.y = 50;
	}*/

	//	�S�[���������̏���
	if (Player_pos.y <= 50)
	{

		if (Player_pos.x >= WINDOW_W / 2 + 300 && Player_pos.x <= WINDOW_W / 2 + 375)
		{

			//	��x�S�[��������g���Ȃ�����
			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;
			goal_dead_count[0]++;
			goal_juge_color[0] = 0;

		}

		else if (Player_pos.x >= WINDOW_W / 2 + 50 && Player_pos.x <= WINDOW_W / 2 + 125)
		{
			//	��x�S�[��������g���Ȃ�����

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_W + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[1]++;
			goal_juge_color[1] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 2 - 175 && Player_pos.x <= WINDOW_W / 2 - 100)
		{
			//	��x�S�[��������g���Ȃ�����

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[2]++;
			goal_juge_color[2] = 0;
		}


		else if (Player_pos.x >= WINDOW_W / 4 && Player_pos.x <= WINDOW_W / 4 + 75)
		{
			//	��x�S�[��������g���Ȃ�����

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[3]++;
			goal_juge_color[3] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 10 && Player_pos.x <= WINDOW_W / 10 + 75)
		{

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[4]++;
			goal_juge_color[4] = 0;
		}




		else
		{
			dead = true;
		}

	}

	//	���Ԑ؂�ŃQ�[���I�[�o�[�@
	if (time <= -1)
	{
		dead = true;
	}
	if (goal_dead_count[0] >= 2)
	{
		dead = true;

	}

	if (goal_dead_count[1] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[2] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[3] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[4] >= 2)
	{
		dead = true;

	}

	if (goal_count >= 5)
	{
		goal = true;
	}
	//	�G�̍��W(Y���W)
	for (int i = 0; i <= 2; i++) {
		Enemy_pos_Right[i].y = 675;
		Enemy_pos_Left[i].y = 625;
	}
	for (int i = 3; i <= 5; i++)
	{
		Enemy_pos_Right[i].y = 525;
		Enemy_pos_Left[i].y = 575;
	}
	for (int i = 6; i <= 8; i++)
	{
		Enemy_pos_Right[i].y = 425;
		Enemy_pos_Left[i].y = 475;
	}

	//	�G�̍��W�iX���W�j
	for (int i = 0; i <= 8; i++)
	{
		//	�Ԃ̃X�s�[�h�𒲐�����
		Enemy_pos_Right[i].x -= 5;
		Enemy_pos_Left[i].x += 5;
	}

	//	�G����ʊO�ɍs�����甽�Ε�������o�Ă��鏈��
	for (int i = 0; i <= 8; i++)
	{
		if (Enemy_pos_Right[i].x <= -50)
		{
			Enemy_pos_Right[i].x = WINDOW_W;
		}
		if (Enemy_pos_Left[i].x >= WINDOW_W + 50)
		{
			Enemy_pos_Left[i].x = -50;
		}
	}

	//	��̏���
	for (int i = 0; i <= 3; i++)
	{
		Enemy_pos_River_Right[i].x -= 5;
		if (Enemy_pos_River_Right[i].x <= -20)
		{
			Enemy_pos_River_Right[i].x = WINDOW_W + 500;
		}
	}
	for (int i = 0; i <= 1; i++)
	{
		Enemy_pos_River_Left[i].x += 5;
		if (Enemy_pos_River_Left[i].x >= WINDOW_W + 200)
		{
			Enemy_pos_River_Left[i].x = -500;
		}
	}

	//	�����蔻��̏���
	for (int i = 0; i <= 8; i++)
	{
		if (CheckCircleHit(Player_pos, Player_size, Enemy_pos_Right[i], Enemy_size))
		{
			dead = true;
		}
		if (CheckCircleHit(Player_pos, Player_size, Enemy_pos_Left[i], Enemy_size))
		{
			dead = true;
		}
	}

	if (river_in)
	{
		Player_move.x += Player_flow;
	}

	//	��ɂ��鎞�ȊO�͗���Ȃ��悤�ɂ��Ă���
	{
		river_in = false;
	}


	//	��̓����蔻��

	//	�v���C���[���ۑ��̏�ɏ���Ă���Ƃ��̏���
	//	1�{�ڂ̐�
	if (Player_pos.y <= 350 && Player_pos.y >= 250)
	{
		//	�v���C���[����ɗ���鏈��
		river_in = true;
		Player_flow = -5.0f;


		//	�ۑ��̓����蔻��
		if (Player_pos.x >= Enemy_pos_River_Right[0].x - 400 && Player_pos.x <= Enemy_pos_River_Right[0].x + 25)
		{
			wood_out = false;
		}

		if (Player_pos.y <= 350 && Player_pos.y >= 250)
		{
			if (Player_pos.x >= Enemy_pos_River_Right[1].x - 500 && Player_pos.x <= Enemy_pos_River_Right[1].x + 25)
			{
				wood_out = false;
			}
			else if (Player_pos.x >= Enemy_pos_River_Right[0].x - 400 && Player_pos.x <= Enemy_pos_River_Right[0].x + 25)
			{
				wood_out = false;
			}
			else
			{
				wood_out = true;
			}
		}
		//	��{�ڂ̐삱���܂�

	}
	//	��{�ڂ̐�
	if (Player_pos.y <= 250 && Player_pos.y >= 150)
	{
		Player_flow = 5.0f;

		if (Player_pos.x <= Enemy_pos_River_Left[0].x + 500 && Player_pos.x >= Enemy_pos_River_Left[0].x - 25)
		{
			wood_out = false;

		}
		else if (Player_pos.x <= Enemy_pos_River_Left[1].x + 300 && Player_pos.x >= Enemy_pos_River_Left[1].x - 25)
		{
	wood_out = false;

		}
		else
		{
			wood_out = true;
		}

	}

	//	�O�{�ڂ̐�
	if (Player_pos.y <= 150 && Player_pos.y >= 50)
	{
		Player_flow = -5.0f;

		if (Player_pos.x >= Enemy_pos_River_Right[2].x - 400 && Player_pos.x <= Enemy_pos_River_Right[2].x + 25)
		{
			wood_out = false;
		}
		else if (Player_pos.x >= Enemy_pos_River_Right[3].x - 500 && Player_pos.x <= Enemy_pos_River_Right[3].x + 25)
		{
			wood_out = false;
		}
		else
		{
			wood_out = true;
		}
	}


	//	�؂���Ă����Ƃ��̏���
	if (wood_out)
	{
		dead = true;
	}

	//	�v���C���[�����񂾍ۂɃ��X�|�[���n�_�ɖ߂����߂̏���
	if (dead)
	{
		//	��x�S�[��������g���Ȃ�����
		//goal_count++;
		//	�v���C���[�������ʒu�ɖ߂�
		Player_pos.x = WINDOW_W / 2;
		Player_pos.y = WINDOW_H - 25;
		Player_move.x = WINDOW_W / 2;
		Player_move.y = WINDOW_H +50;
		//	�S�[�������琧�����Ԃ�������
		//time = 1800;
		////	�S�[�������琧�����Ԃ��~�߂�
		//time_start = false;
		//goal_dead_count[0]++;
		//goal_juge_color[0] = 0;
		dead = false;

		wood_out = false;

	}

}
void Tutorial::Draw()
{
	//	��ԉ�
	DrawBox(0, 650, WINDOW_W, 700, GetColor(0, 0, 155), TRUE);
	//	������2�Ԗ�
	DrawBox(0, 600, WINDOW_W, 650, GetColor(155, 0, 0), TRUE);
	//	������O�Ԗ�
	DrawBox(0, 550, WINDOW_W, 600, GetColor(0, 155, 0), TRUE);
	//	�ォ��O�Ԗ�
	DrawBox(0, 500, WINDOW_W, 550, GetColor(0, 155, 155), TRUE);
	//	�ォ���Ԗ�
	DrawBox(0, 450, WINDOW_W, 500, GetColor(155, 155, 155), TRUE);
	//	��ԏ�
	DrawBox(0, 400, WINDOW_W, 450, GetColor(0, 0, 0), TRUE);
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------

	//	��̕`��
	DrawRotaGraphF(WINDOW_W / 2, 350 / 2, 2.5f, TO_RADIAN(0), River_image, TRUE);

	////	�ۑ��̕`��
	//DrawRotaGraphF(enemy.Enemy_pos_River_Right[0].x, enemy.Enemy_pos_River_Right[0].y, 0.1f, TO_RADIAN(0), wood_image, TRUE);



	//	�S�[��
	DrawLine(0, -50, WINDOW_W, 50, GetColor(0, 0, 255), TRUE);
	DrawLine(0, 50, WINDOW_W, 50, GetColor(0, 0, 255), TRUE);
	DrawBox(0, -50, WINDOW_W, 50, GetColor(0, 0, 255), TRUE);

	//	�S�[���̏ꏊ��`��

	DrawBox(WINDOW_W / 2 + 375, 25, WINDOW_W / 2 + 300, 50, GetColor(goal_juge_color[0], 255, 255), TRUE);
	DrawBox(WINDOW_W / 2 + 125, 25, WINDOW_W / 2 + 50, 50, GetColor(goal_juge_color[1], 255, 255), TRUE);
	DrawBox(WINDOW_W / 2 - 175, 25, WINDOW_W / 2 - 100, 50, GetColor(goal_juge_color[2], 255, 255), TRUE);
	DrawBox(WINDOW_W / 4, 25, WINDOW_W / 4 + 75, 50, GetColor(goal_juge_color[3], 255, 255), TRUE);
	DrawBox(WINDOW_W / 10, 25, WINDOW_W / 10 + 75, 50, GetColor(goal_juge_color[4], 255, 255), TRUE);


	DrawString(WINDOW_W / 2, 50, "�S�[��", GetColor(0, 255, 0), TRUE);


	for (int i = 0; i <= 8; i++)
	{
		DrawCircle(Enemy_pos_Right[i].x, Enemy_pos_Right[i].y, Enemy_size, GetColor(255, 255, 0), TRUE);
		DrawCircle(Enemy_pos_Left[i].x, Enemy_pos_Left[i].y, Enemy_size, GetColor(255, 255, 0), TRUE);

	}



	//	�Ԃ̕`��i�E����o�Ă�����́j
	for (int i = 0; i < 8; i++) {
		DrawRotaGraphF(Enemy_pos_Right[i].x, Enemy_pos_Right[i].y, 0.25f, TO_RADIAN(0), Car_red, TRUE);

	}
	//DrawRotaGraphF(Enemy_pos_Right[0].x, Enemy_pos_Right[0].y, 0.25f, TO_RADIAN(0), Car_red, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[1].x, Enemy_pos_Right[1].y, 0.25f, TO_RADIAN(0), Car_black, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[2].x, Enemy_pos_Right[2].y, 0.25f, TO_RADIAN(0), Car_blue, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[3].x, Enemy_pos_Right[3].y, 0.25f, TO_RADIAN(0), Car_green, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[7].x, Enemy_pos_Right[7].y, 0.25f, TO_RADIAN(0), Car_red, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[4].x, Enemy_pos_Right[4].y, 0.25f, TO_RADIAN(0), Car_black, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[6].x, Enemy_pos_Right[6].y, 0.25f, TO_RADIAN(0), Car_blue, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[5].x, Enemy_pos_Right[5].y, 0.25f, TO_RADIAN(0), Car_green, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[8].x, Enemy_pos_Right[8].y, 0.25f, TO_RADIAN(0), Car_green, TRUE);

	////	�Ԃ̕`��i������o�Ă�����́j
	//DrawRotaGraphF(Enemy_pos_Left[0].x, Enemy_pos_Left[0].y, 0.25f, TO_RADIAN(0), Car_red_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[1].x, Enemy_pos_Left[1].y, 0.25f, TO_RADIAN(0), Car_black_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[2].x, Enemy_pos_Left[2].y, 0.25f, TO_RADIAN(0), Car_blue_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[3].x, Enemy_pos_Left[3].y, 0.25f, TO_RADIAN(0), Car_green_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[7].x, Enemy_pos_Left[7].y, 0.25f, TO_RADIAN(0), Car_red_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[4].x, Enemy_pos_Left[4].y, 0.25f, TO_RADIAN(0), Car_black_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[6].x, Enemy_pos_Left[6].y, 0.25f, TO_RADIAN(0), Car_blue_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[5].x, Enemy_pos_Left[5].y, 0.25f, TO_RADIAN(0), Car_green_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[8].x, Enemy_pos_Left[8].y, 0.25f, TO_RADIAN(0), Car_green_gyaku, TRUE);

	//	�ۑ��̕`��
	DrawRotaGraphF(Enemy_pos_River_Right[0].x - 200, 300, 0.25f, TO_RADIAN(0), Wood_image, TRUE);
	DrawRotaGraphF(Enemy_pos_River_Right[1].x - 250, 300, 0.3f, TO_RADIAN(0), Wood_image, TRUE);

	DrawRotaGraphF(Enemy_pos_River_Left[0].x + 250, 200, 0.3f, TO_RADIAN(0), Wood_image2, TRUE);
	DrawRotaGraphF(Enemy_pos_River_Left[1].x + 150, 210, 0.25f, TO_RADIAN(0), Wood_image2, TRUE);

	DrawRotaGraphF(Enemy_pos_River_Right[2].x - 200, 100, 0.25f, TO_RADIAN(0), Wood_image, TRUE);
	DrawRotaGraphF(Enemy_pos_River_Right[3].x - 250, 100, 0.3f, TO_RADIAN(0), Wood_image, TRUE);

	DrawCircle(Player_pos.x, Player_pos.y, Player_size, GetColor(0, 0, 255), TRUE);
	DrawRotaGraphF(Player_pos.x, Player_pos.y, 0.035f, TO_RADIAN(0), Player_image, TRUE);
	SetFontSize(20);
	DrawFormatString(WINDOW_W - 350, WINDOW_H - 30, GetColor(0, 0, 255), "�N���A�܂ŕK�v�ȃS�[���񐔂���%d", goal_count_check, true);
	DrawFormatString(0, WINDOW_H - 30, GetColor(0, 0, 255), "�c�莞��%d", time / 60, true);


}
void Tutorial::Exit()
{

}
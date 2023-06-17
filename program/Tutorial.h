#pragma once
#include"Main.h"
#include "Base.h"

class Tutorial : public Base
{
public:
	//	�v���C���[�̍��W�ϐ�
	Vector2 Player_pos;


	//	�v���C���[�̑傫��
	int Player_size;

	//	�v���C���[�̉摜
	int Player_image;

	//	�v���C���[���ǂ��܂Ői�ނ���ۑ�����ϐ�
	Vector2 Player_move;

	//	�v���C���[�̎c�@�J�E���g
	int Player_count;

	//	�v���C���[�̑���𓯎��ɍs���Ȃ����邽�߂̕ϐ�
	int move_time;
	//	�v���C���[�̑���𓯎��ɍs���Ȃ����邽�߂̕ϐ�
	bool move;

	//	���񐔃N���A����ƃQ�[���N���A�ƂȂ�悤�ɂ��邽�߂̕ϐ�
	int goal_count;

	//	�v���C���[�ɂ��Ɖ���S�[������΂����������邽�߂̕ϐ�
	int goal_count_check;

	//	�S�[�������ꏊ�����x���g���Ȃ��悤�ɂ��邽�߂̕ϐ�

	//	���ꂼ��̃S�[���ŃS�[���J�E���g��2��ɂȂ�����Q�[���I�[�o�[�Ƃ���i�����S�[���ɍs���ƃQ�[���I�[�o�[�ƂȂ�j
	int goal_dead_count[5];

	//	���̍ۂɂ킩��₷�����邽�ߐF��ς���
	int goal_juge_color[5];

	//	�S�[������̕ϐ�
	bool goal;

	//	���񂾂Ƃ��̕ϐ�
	//	�c�@��3�Ȃ̂�3�p��
	bool dead;

	//	�v���C���[����ɓ������痬�����p�̕ϐ�
		//	��ɓ��������ǂ����̔���̕ϐ�
	bool river_in;
	//	����邽�߂̕ϐ�
	float Player_flow;


	//	�������Ԃ̕ϐ�
	int time;

	//	�����o�����琧�����Ԃ��n�܂邽�߂̕ϐ�
	bool time_start;

	//	�v���C���[����̏�Ŋۑ��ɏ���Ă���Ƃ��̕ϐ�
	bool wood_out;


	//	��Q��
		//	�E����o�Ă���p�̕ϐ�
	Vector2 Enemy_pos_Right[9];
	//	������o�Ă���G�̕ϐ�
	Vector2 Enemy_pos_Left[9];
	//	��̓����蔻��i��{�I�ɂ͓����蔻��͍L�����Ĉꕔ����������Ȃ����Ă������}���^�Ƃ��Ēʂ点��j
	//	�E���獶�֗���Ă�����
	Vector2 Enemy_pos_River_Right[4];
	//	������E�֗���Ă�����
	Vector2 Enemy_pos_River_Left[2];

	//	�ۑ��i��̒��ŃQ�[���I�[�o�[�ƂȂ�Ȃ����W�j
	//	�E���獶�֗���Ă����ۑ�
	Vector2 Enemy_pos_Safe_Right[2];
	//	������E�֗���Ă����ۑ�
	Vector2 Enemy_pos_Safe_Left;


	//	Enemy(��)�̉摜�p�ϐ�
	struct Color
	{
		int red = 0;
		int green = 0;
		int blue = 0;
		int black = 0;
	};
	Color car_image;
	int Car_red = 0;
	int Car_black = 0;
	int Car_green = 0;
	int Car_blue = 0;
	//	�t�����̂��̂����
	Color car_oppose_image;
	int Car_red_oppose;
	int Car_black_oppose;
	int Car_green_oppose;
	int Car_blue_oppose;

	//	�`���[�g���A���p�̉摜��ǂݍ��ނ��߂̕ϐ�
	
	int Wood_image;
	int Wood_image2;

	int River_image;


	//	Ememy�̑傫����ݒ�
	int Enemy_size;



	void Init();
	void Update();
	void Draw();
	void Exit();
};
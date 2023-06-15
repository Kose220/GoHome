#include <DxLib.h>
#include "Main.h"
#include "Player.h"
#include "WallClass.h"
#include "Timer.h"
#include "Score.h"
#include "Life.h"
#include "UI.h"
#include "Start_camera.h"
#include "UFO.h"
#include "Security.h"
#include "Game.h"
#include"Minimap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"Tutorial.h"
#include<cmath>
using namespace std;

//---------------------------------------------------------------------------
//	Doxygen�@�����T�v
//---------------------------------------------------------------------------
//! @mainpage Go Home
//! @li �Q�[���T�v \n
//! \n
//! @image html "..\..\data\Game\GoHome.png" width = 200px height = 150px
//! \n
//! @ref section_component

//! @page section_control�@�Q�[���̑���



Player   player;
Wall     wall;
Timer    timer;
Score    score;
Life     life;
UI       ui;
Camera   camera;
UFO      ufo;
Seculity seculity;
Minimap minimap;
Tutorial tutorial;

////////////////////////////////
// �萔
////////////////////////////////
constexpr int CAR_NUM = 5;    // �Ԃ̑䐔
constexpr int WOOD_NUM = 10;   // �ۑ��̐�
constexpr int WOOD_START_Z[] = {
	-145,
	-175,
	//  3�Ԗڂ̂��̂����s�v�ɂȂ������߈�U�����Ȃ��Ƃ���ɔz�u
	30000,
	-235,
	-265,
	300,
	-175,
	//  ��L�Ɠ������R
	30000,
	-235,
	-265,
};

//  �����ɂ������Ƃɂ������Ă��������ǉ�����
constexpr int WOOD_START_Z_Re[] = {
	-160,
	-190,
	-30000,
	-250,
	-280,
	30000,
	30000,
	300000,
	-250,
	-280,

};

constexpr int CAR_Z[] = {
	-20,
	-40,
	-60,
	-80,
	-100,

};

//  ���H�̔����̍��W�iZ���W�j
constexpr float WHITE_LINE_1[] = {
	-9,
	-29,
	-49,
	-69,

};
constexpr float WHITE_LINE_2[] = {
	-11,
	-31,
	-51,
	-71,

};   //

void Respawn()
{
	life.life_count -= 1;
	ui.ui_life_count -= 1;
	//  �N���オ��A�j���[�V�������w�����邽�߂̕ϐ�
	player.player_Revival = true;
	//  ���W�������ʒu��
	player.move_z = 20.0f;
	//	player.move_x = 0.0f;
	player.move_y = 1.0f;
	//  �v���C���[�̌�����������
	player.radian_y = 0.0f;
	//  ���W��������
	player.pos_z = 20.0f;
	//	player.pos_x = 0.0f;
	player.pos_y = 1.0f;


	//  �~�j�}�b�v�̃A�C�R����ɖ߂�
	minimap.map_icon_switch = true;

	//  �ォ�畜�������邽�߂�Y���W����ɂ���
	//player.pos_y = 20.0f;
}
//void PlayCount()
//{
//	// 1. �t�@�C�����J��
//// 1-1. fstream�N���X�̃R���X�g���N�^�Ɏw��
//	fstream file("sample.txt", ios::in);
//	// 1-2. fstream�N���X��open�����o�֐��𗘗p
//	//fstream file;
//	//file.open("sample.txt", ios::in);
//	// 1-3. ifstream�N���X���g�p
//	//ifstream file("sample.txt");
//
//	// �G���[����: �t�@�C��������ɊJ�������ǂ����`�F�b�N
//	if (!file.is_open())
//	{
//		cerr << "ERROR: cannot open file." << endl;
//		system("pause");
//		return EXIT_FAILURE;
//	}
//
//	// 2. �t�@�C������f�[�^���擾
//	//int num;
//	//file >> num;
//
//	//float num2;
//	//file >> num2;
//
//	// �t�@�C���I�[�܂łP�s���ǂݍ���
//	vector<string> file_lines;
//	while (true)
//	{
//		string line;
//		getline(file, line);
//		if (file.eof())
//			break;
//
//		file_lines.emplace_back(line);
//	}
//
//	// 3. �t�@�C�������
//	file.close();
//
//	// 4. �擾�����f�[�^������
//	for (const auto& line : file_lines)
//	{
//		cout << line << endl;
//		// �擾�����f�[�^��string�^����int�^�֕ϊ�
//		//int num = line;	// ��肭�����Ȃ�
//		//try
//		//{
//		//	int num = stoi(line);	// stoi�֐�(int�^�ɂ�����string�^�̕ϐ�);
//		//	cout << num << endl;
//		//}
//		//catch (const std::exception&)
//		//{
//		//}
//	}
//
////	system("pause");
//	return EXIT_SUCCESS;
//
//}

void Game::PlayerMove()
{
	// �v���C���[���������Ƃ�
	status_ = STATUS_MOVE;
	next_anim = model_anim_run;
}

void Game::PlayerDie()
{
	if (car_die) {
		PlayerDieToCar();
	}
	if (river_die) {
		PlayerDieToRiver();
	}
}

void Game::PlayerDieToCar()
{
	//  ����ł��܂������̃A�j���[�V�������͑���ł��Ȃ��悤�ɂ���
	// player.player_Revival = false;
	PlaySoundFile("data/Game/SE/�J�[�N���b�V��.mp3", DX_PLAYTYPE_BACK);
	status_ = STATUS_CAR_DAMAGE;
	next_anim = model_anim_car_clash;

}

void Game::PlayerDieToRiver()
{
	//  ����ł��܂������̃A�j���[�V�������͑���ł��Ȃ��悤�ɂ���
	//          player.player_Revival = false;
	PlaySoundFile("data/Game/SE/�����œM���.mp3", DX_PLAYTYPE_BACK);
	status_ = STATUS_RIVER_DAMAGE;
	next_anim = model_anim_river_die;
}

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Game::Init()
{
	//  �^�C�g����UI�����炷���߂̕ϐ�
	Title_Slide = 0;
	//  �^�C�g����UI��X���W
	Title_Slide_x = 0;

	//  �^�C�g���̉摜�p�̕ϐ��̏�����
	Title_Player_x = WINDOW_W - 20;
	Title_Player_y = WINDOW_H - 80;
	Title_Ufo_x = WINDOW_W - 10;
	Title_Ufo_y = 50;
	Title_Ufo_x_plus = -0.5f;
	Title_Ufo_y_plus = 0.3f;
	Title_Ufo_rad = 0.0f;
	Title_Ufo_rad_plus = 0.005f;

	//   �^�C�g���p�̕ϐ��̏�����
	Title_Player = LoadGraph("data/Game/Title/Title_Player.png.crdownload ");
	Title_Ufo = LoadGraph("data/Game/Title/Title_Ufo.png");
	Title_Town = LoadGraph("data/Game/Title/Title_Town.jpg.crdownload");
	Title_House = LoadGraph("data/Game/Title/Title_House.png");

	//  �Q�[���I�[�o�[���̃C���X�g�ϐ��̏�����
	//  ���Ԑ؂ꎞ�̔w�i
	Time_Over_haikei_fire = LoadGraph("data/Game/Title/Fire.png");
	Time_Over_ilust_hansei = LoadGraph("data/Game/Title/hansei_koukai_man.png");
	Time_Over_ilust_sekkyou = LoadGraph("data/Game/Title/pose_mesen_uekara_woman.png");

	River_Over_ilust = LoadGraph("data/Game/Title/oboreru.png");
	River_Over_ilust_safe = LoadGraph("data/Game/Title/kyuujo_ukiwa_tasukaru.png");

	int goal_time = 0;

	// �����f���̓ǂݍ���
	//  �l�Y�~�̃��f���̓ǂݍ��݁H
	model_ = MV1LoadModel("data/Game/Anime/model.mv1");
	//  �P����тQ�̏���
	//  �l�Y�~�̕������f����ǂݍ���
	model_anim_run = MV1LoadModel("data/Game/Anime/Walk.mv1");
	model_anim_idle = MV1LoadModel("data/Game/Anime/Idle.mv1");
	model_anim_car_clash = MV1LoadModel("data/Game/Anime/Dying.mv1");
	model_anim_river_die = MV1LoadModel("data/Game/Anime/River_Dying.mv1");
	model_anim_stand_up = MV1LoadModel("data/Game/Anime/Stand Up.mv1");
	model_anim_happy_dance = MV1LoadModel("data/Game/Anime/Happy.mv1");
	model_anim_security_stand_up = MV1LoadModel("data/Game/Anime/Security_Stand_Up.mv1");
	model_anim_dead_cry = MV1LoadModel("data/Game/Anime/Cry Idle.mv1");
	model_anim_ufo_Out = MV1LoadModel("data/Game/Anime/Ufo_Out.mv1");

	if (anim_index != -1) {
		// ���݂̃A�j���[�V�����̃C���f�b�N�X��-1�i�����l�j�łȂ���΁A
		// ���łɃA�j���[�V�������A�^�b�`����Ă���Ƃ������ƂȂ̂�
		// �f�^�b�`������
		MV1DetachAnim(model_, anim_index);
	}
	anim_index = MV1AttachAnim(model_, 1, model_anim_idle);
	anim_max_frame = MV1GetAttachAnimTotalTime(model_, anim_index);
	MV1SetAttachAnimTime(model_, anim_index, anim_max_frame);
	anim_frame = 0.0f;

	//  ����ł��邩�����Ă��邩�̕ϐ��̏�����
	live = true;
	dead = false;

	//    anim_time = 70.0f;
	player.anim_time = 70.0f;
	//  ��ԗp�ϐ�
	status_ = STATUS_IDLE;

	//	�v�����X���[�̓ǂ݂���
	security_model = MV1LoadModel("data/Game/Seculity/Seculity.mv1");

	//  �v�����X���[�̃A�j���[�V�����̓ǂݍ���
	//seculity_anim_idle =
	//    MV1LoadModel("data/Game/Anime/")
	security_anim_move = MV1LoadModel("data/Game/Anime/Seculity/Seculity_Run.mv1");
	security_anim_attack = MV1LoadModel("data/Game/Anime/Seculity/Seculity_Attack.mv1");
	security_anim_idle = MV1LoadModel("data/Game/Anime/Seculity/Idle.mv1");

	//	����߂��@�t�@�C�������@eof��true�ɂȂ�

		if (seculity_anim_index != -1) {
		MV1DetachAnim(security_model, seculity_anim_index);
	}
	seculity_anim_index = MV1AttachAnim(security_model, 1, security_anim_idle);
	seculity_anim_max_frame = MV1GetAttachAnimTotalTime(security_model, seculity_anim_index);
	MV1SetAttachAnimTime(security_model, seculity_anim_index, seculity_anim_max_frame);

	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------

	//  �N���X�̒��g�̏�����
	player.Init();
	wall.Init();
	timer.Init();
	score.Init();
	life.Init();
	ui.Init();
	camera.Init();
	ufo.Init();
	seculity.Init();
	minimap.Init();
	tutorial.Init();
	//  �Ԃ̕ϐ���������
	for (int i = 0; i < CAR_NUM; i++) {
		//        car_x[i] = GetRand(-200);
		car_z[i] = CAR_Z[i];
	}
	//  �����_�����������΂肪�������邽�߈��΂炯������
	car_x[0] = -50;
	car_x[1] = 30;
	car_x[2] = 90;
	car_x[3] = 60;
	car_x[4] = -100;

	//	�Ԃ𓮂����p�̕ϐ�
	for (int i = 0; i < 6; i++) {
		car_x_plus[i] = 1.5f;
	}
	//  �ۑ��̍��W�̏�����
	//for(int i = 0; i < 5; i++) {
	//    wood_x[i] = 0;
	//}
	//for(int i = 5; i <= 9; i++) {
	//    wood_x[i] = 150;
	//}
	for (int i = 0; i < WOOD_NUM; ++i) {
		//int start_pos_x = (i < 5) ? 0 : 150;
		//wood_x[i]       = start_pos_x;
		int start_pos_x = 0;
		if (i >= 5) {
			start_pos_x = 150;
		}
		wood_x[i] = start_pos_x;
		wood_z[i] = WOOD_START_Z[i];
		wood_x_re[i] = GetRand(-150);
		wood_z_re[i] = WOOD_START_Z_Re[i];
	}

	//  �v���C���[�̓����蔻��
	car_dead = false;

	// �S�[��BGM�����x����Ȃ����߂ɂ���p�̕ϐ�
	goal_adjustment = 0;

	//	���X�|�[���n�_�܂ł̋���
	Respawn_Distance_z = 0.0f;

	//  ���f���̓ǂݍ���
	//  �Ԃ̓ǂݍ���
	car_model[0] = MV1LoadModel("data/Game/Car/Car.mv1");
	//  UFO�̓ǂݍ���
	ufo_model = MV1LoadModel("data/Game/UFO/UFO.mv1");
	//  �v�����X���[�̓ǂݍ���

	for (int i = 1; i < CAR_NUM; i++) {
		car_model[i] = MV1DuplicateModel(car_model[0]);
	}
	//  �R�C���̑f�ނ�ǂݍ���

	coin_model = MV1LoadModel("data/Game/Score/coin.mv1");
	//        coin_model = MV1LoadModel("data/Game/Score/coin.mv1");
		 // �R�C�����f�����R�s�[
	for (int i = 0; i < 5; i++)
	{
		coin_models[i] = MV1DuplicateModel(coin_model);
	}

	//	�R�C���̊p�x�ϐ��̏�����
	Coin_Rota_x = 90;

	//  �R�C���O�Ԗڂ��R�s�[�����₷
	// for(int i = 1; i < COIN_NUM; i++) {
	//    coin_model = MV1DuplicateModel(car_model[0]);
	//}
	//  ��̓����蔻��
	river_dead = false;

	//  �ۑ��̔���
	//  wood_safe���t�@���X�ɂȂ����u�Ԑ�̓����蔻�肪ON�ɂȂ��Ă��܂��B
	//  ����Ă��邤����false����Ă��Ȃ��ꍇ��true
	wood_safe = true;

	//  �Z�[�t�G���A�̐΂̍��W
	safe_stone_x = -90;
	safe_stone_z = -220;


	//  �S�[�����W�̐ݒ�
	goal_line_x = 0;
	goal_line_z = 0;

	//  �Q�[���I�[�o�[��ʂ��x��ďo�Ă��邽�߂̕ϐ�
	over_time = 0;

	//  ��ɓM�ꂽ�Ƃ��ɏ㉺�ɓ������߂̕ϐ�
	river_out_y = 1;
	//  �^�C�g���ϐ��̏�����
	title = true;

	//  �^�C�g����ʂ����ɂ��炷���߂̏���
	title_x = 0;

	title_blend = 0;
	//  �^�C�g���̕������ڂ������߂ɕϐ������炷�p�̂���
	title_blend_hiku = 3;
	//  �Q�[�����n�߂�p�̕ϐ�
	game = false;

	//  �S�[������ϐ��̏�����
	goal = false;

	goal_anim = false;

	goal_count = 0;

	//	�X�e�[�W��ς���ۂ̃J�b�g�C���p�̕ϐ�
	stage_change = false;

	//  ���G��ԗp�̕ϐ�
	no_die = true;

	//	UFO�ɂ������悤�ϐ��i�A�j���[�V�����j
	player_ufo_out = false;
	//	UFO���瓦��邽�߂̕ϐ�
	ufo_rampage = 0;

	consecutive_blocking = 60;

	//  �������p�̕ϐ�
	init = false;

	InitTime = 0;

	//  �G�t�F�N�g�̏�����
	effect_congra = LoadEffekseerEffect("data/Game/Effects/Simple_Turbulence_Fireworks.efkefc");

	//	�^�C�g���̃v���C���[�̑��铮���̂��߂̕ϐ�
	////  �G�t�F�N�g�̈ʒu�̏�����
	//SetPosPlayingEffekseer3DEffect(effect_congra_play, pos_x, pos_y, pos_z - 50);

	//  �J�����̌�����ύX���邽�߂̕ϐ�
	camera_x = 0.0f;
	camera_z = 0.0f;
	//  �J�������ォ�猩���낷�ƋN�p�̕ϐ��i����������j
	camera_y = 25.0f;
	camera_y_radian = 5.0f;
	//  BGM�̏�����
	Title_BGM = LoadSoundMem("data/Game/BGM/Title.mp3");
	Game_BGM = LoadSoundMem("data/Game/BGM/GameMain.mp3");
	Over_BGM = LoadSoundMem("data/Game/BGM/GaneOver.mp3");
	Clear_BGM = LoadSoundMem("data/Game/BGM/Clear.mp3");

	//  SE�̏�����
	Car_Clacshon_SE = LoadSoundMem("data/Game/SE/�Ԃ̃N���N�V����.mp3");
	River_SE = LoadSoundMem("data/Game/SE/�͌�.mp3");
	Car_Clash_SE = LoadSoundMem("data/Game/SE/�J�[�N���b�V��.mp3");
	Car_Slue_SE = LoadSoundMem("data/Game/SE/�Ԓʉ�1.mp3");
	Silen_SE = LoadSoundMem("data/Game/SE/�~�}�ԃT�C����1.mp3");
	River_Die_SE = LoadSoundMem("data/Game/SE/�����œM���.mp3");

	//	�����炬�̉��ʕϐ�
	River_SE_Volume = 0;

	//	�����}��悤�ϐ�
	River_distance = 0.0f;

	//  ���v�̐j�̕ϐ�

	//  BGM���J�n�����邽�߂̕ϐ�
	Title_BGM_Start = true;
	Game_BGM_Start = false;
	Over_BGM_Start = false;
	Clear_BGM_Start = false;

	//  �I�u�W�F�N�g�J�����̍쐬    ���j�ɕ���
	//auto o = Scene::CreateObject<Object>();
	//o->SetName(u8"�e�X�g�J����");14
	SetCameraNearFar(7.5f, 1500.0f);
	//// �J�����R���|�[�l���g��ǉ�
	//auto camera = o->AddComponent<ComponentCamera>();
	//  �J�����̃|�W�V�����Ƃǂ������邩�̐ݒ�
	Title_player_y_gravity = 0.0f;

	//	��̕ϐ��̗p��
	//DxLib_Init();
	//SetDrawScreen(DX_SCREEN_BACK);
	//SetUseZBuffer3D(TRUE);
	//SetWriteZBuffer3D(TRUE);

	//// Set the camera position
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -5), VGet(0, 0, 0));

	//// Create the skybox texture
	//skyBox = MakeBox3D(VGet(-100, -100, -100), VGet(100, 100, 100), TRUE);
	//SetMaterialUseVertNormal(FALSE); // Ignore normals
	//ChangeMaterialParam(skyBox, MATERIALPARAM_DIFFUSERED, 0);
	//ChangeMaterialParam(skyBox, MATERIALPARAM_DIFFUSEGREEN, 0);
	//ChangeMaterialParam(skyBox, MATERIALPARAM_DIFFUSEBLUE, 1);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Game::Update()
{
	Title_player_y_gravity += 0.25f;

	//  �^�C�g�������ɃX���C�h������
	Title_Slide_x += Title_Slide;

	if (title) {

		tutorial.Update();
		////  �^�C�g�������ɃX���C�h������
		//Title_Slide_x += Title_Slide;


		switch (bgm_status) {
		case START_BGM:
			StopSoundMem(Over_BGM);

			ChangeVolumeSoundMem(100, Title_BGM);

			PlaySoundMem(Title_BGM, DX_PLAYTYPE_LOOP);
			Title_BGM_Start = false;
			bgm_status = -1;
			break;
		}

		//if (CheckKeyInput(KEY_INPUT_A))
		//{
		//	Title_player_y_temp = -2.0f;
		//}
		//Title_Player_y += Title_player_y_temp;
		//Title_player_y_temp += 0.2f;

		//if (Title_Player_y <WINDOW_H - 200)
		//{
		//	Title_Player_y = WINDOW_H - 200;
		//}

		PlayCount_Switch = false;

		if (CheckHitKey(KEY_INPUT_I)) {
			PlayCount_Switch = true;
		}

		if (CheckHitKey(KEY_INPUT_SPACE)) {
			//  �X���C�h�̃X�s�[�h
			Title_Slide = 20;
			StopSoundMem(Title_BGM);
			title_rule = true;
			bgm_status = MAIN_BGM;
			//			PlayCount();
					// 1. �t�@�C�����J��
			// 1-1. fstream�N���X�̃R���X�g���N�^�Ɏw��
						//fstream file("sample.txt", ios::in);
						//// 1-2. fstream�N���X��open�����o�֐��𗘗p
						////fstream file;
						////file.open("sample.txt", ios::in);
						//// 1-3. ifstream�N���X���g�p
						////ifstream file("sample.txt");

						//// �G���[����: �t�@�C��������ɊJ�������ǂ����`�F�b�N
						//if (!file.is_open())
						//{
						//	cerr << "ERROR: cannot open file." << endl;
						//	system("pause");
						//	return EXIT_FAILURE;
						//}

						//// 2. �t�@�C������f�[�^���擾
						////int num;
						////file >> num;

						////float num2;
						////file >> num2;

						//// �t�@�C���I�[�܂łP�s���ǂݍ���
						//vector<string> file_lines;
						//while (true)
						//{
						//	string line;
						//	getline(file, line);
						//	if (file.eof())
						//		break;

						//	file_lines.emplace_back(line);
						//}

						//// 3. �t�@�C�������
						//file.close();

						//// 4. �擾�����f�[�^������
						//for (const auto& line : file_lines)
						//{
						//	cout << line << endl;
						//	// �擾�����f�[�^��string�^����int�^�֕ϊ�
						//	//int num = line;	// ��肭�����Ȃ�
						//	//try
						//	//{
						//	//	int num = stoi(line);	// stoi�֐�(int�^�ɂ�����string�^�̕ϐ�);
						//	//	cout << num << endl;
						//	//}
						//	//catch (const std::exception&)
						//	//{
						//	//}
						//}

						////	system("pause");
						//return EXIT_SUCCESS;

		}
		if (Title_Slide_x >= WINDOW_W) {
			title = false;
			//	�X�g�[���[������UI���~�܂��悤�ɂ��Ă����i����Ă����Ȃ��悤�ɂ��Ă����j
			Title_Slide = 0;
		}

		title_blend += title_blend_hiku;
		if (title_blend >= 255) {
			title_blend_hiku *= -1;
		}
		if (title_blend <= 0) {
			title_blend_hiku *= -1;
		}

		//  �^�C�g���̃C���X�g�𓮂����p�̏���
		if (Title_Ufo_y >= 55) {
			Title_Ufo_y_plus *= -1;
		}

		else if (Title_Ufo_y <= 45) {
			Title_Ufo_y_plus *= -1;
		}
		if (Title_Ufo_x <= 0) {
			Title_Ufo_x_plus *= -1;
		}
		else if (Title_Ufo_x >= WINDOW_W) {
			Title_Ufo_x_plus *= -1;
		}
		//  UFO�̃C���X�g
		Title_Ufo_x += Title_Ufo_x_plus;
		Title_Ufo_y += Title_Ufo_y_plus;

		//	�t�e�n�̊p�x��ύX���邽�߂̏���
		Title_Ufo_rad += Title_Ufo_rad_plus;

		if (Title_Ufo_rad >= 0.25f)
		{
			Title_Ufo_rad_plus *= -1;
		}
		if (Title_Ufo_rad <= -0.25f)
		{
			Title_Ufo_rad_plus *= -1;
		}

		//  �v���C���[�̃C���X�g�̏���
		if (Title_Player_x <= 300) {
			Title_Player_x = WINDOW_W + 50;
		}
		//  UFO�̃C���X�g
		Title_Player_x -= 1.0f;
	}

	//  �^�C�g���̎��̉��
	if (title_rule) {
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			title_rule = false;
			game = true;
			PlayCount++;
			stage_status = FIRST_STAGE;
			//	��̂����炬�����ŏ��̒i�K�Ń��[�v����������Ă���
			PlaySoundMem(River_SE,DX_PLAYTYPE_LOOP);
		}

	}

	if (game) {

			ChangeVolumeSoundMem(River_SE_Volume, River_SE);



		//  �G�t�F�N�g�̍Đ�
		//if(CheckHitKey(KEY_INPUT_SPACE) && IsEffekseer3DEffectPlaying(effect_congra_play) == -1) {
		//    //
		//    effect_congra_play = PlayEffekseer3DEffect(effect_congra);
		//    SetPosPlayingEffekseer3DEffect(effect_congra_play, 0, 0, -460);
		//}
		/*    if(player.pos_z <= -470) {
			effect_congra_play = PlayEffekseer3DEffect(effect_congra);
			SetPosPlayingEffekseer3DEffect(effect_congra_play, 0, 0, -460);
		}*/

		switch (bgm_status) {
		case MAIN_BGM:

			ChangeVolumeSoundMem(100, Game_BGM);
			PlaySoundMem(Game_BGM, DX_PLAYTYPE_LOOP);
			//  �P�񂵂��񂳂Ȃ��悤�ɂ���
			bgm_status = -1;
			//	�S�[����������BGM����
			break;
		}
		//  �^�C�g����ʂ��͂�����v���C���[��������悤�ɂ���

		title_x -= 20;
		if (title_x < -WINDOW_W) {
			player.move_juge = true;
		}

		// �����f���̐ݒ�
		MV1SetPosition(model_, { player.pos_x, player.pos_y, player.pos_z });
		MV1SetRotationXYZ(model_, { 0.0f, player.radian_y, 0.0f });
		MV1SetScale(model_, { 0.05f, 0.05f, 0.05f });

		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------
		//  �A�j���[�V�����̍X�V
		//  �A�j���[�V�����̐؂�ւ��p�̎��ԕϐ�
		player.anim_time++;

		//        if(live) {
		int pre_status = status_;   // �ЂƂO�̏�Ԃ�ۑ�
		switch (status_) {
		case STATUS_IDLE:
			// Kanamaru Comment
			//	case���������̂ŒZ�����邱��
			
			//  �ҋ@��ԂɈڂ�����v���C���[�𑀍�ł���悤�ɂ���
			player.Revival_move = true;
			//  �A�j���[�V�������ƂɃt���[���X�s�[�h��ς���
			anim_frame_speed = 0.5f;

			if (player.anim_juge) {
				PlayerMove();
			}
			PlayerDie();

			//  �S�[�����̃n�b�s�[�A�j���[�V����
			if (goal) {
				player.move_juge = false;
				status_ = STATUS_HAPPY_DANCE;
				next_anim = model_anim_happy_dance;
			}

			if (player_ufo_out)
			{
				status_ = STATUS_UFO_OUT;
				next_anim = model_anim_ufo_Out;
			}

			break;
			//  ��L�̏������l�ɍ�����Ă��鏈���ȊO�̕����������̏�����������Ď��ɔ�����
		case STATUS_MOVE:
			//  �A�j���[�V�������ƂɃt���[���X�s�[�h��ς���
			anim_frame_speed = 0.5f;

			if (player.anim_time >= 45.0f) {
				// �A�j���[�V�����I����ɑҋ@��Ԃ�
				status_ = STATUS_IDLE;
				next_anim = model_anim_idle;
			}
			if (car_die) {
				//  ����ł��܂������̃A�j���[�V�������͑���ł��Ȃ��悤�ɂ���
				//     player.player_Revival = false;
				status_ = STATUS_CAR_DAMAGE;
				next_anim = model_anim_car_clash;
				PlaySoundFile("data/Game/SE/�J�[�N���b�V��.mp3", DX_PLAYTYPE_BACK);
			}
			if (river_die) {
				//  ����ł��܂������̃A�j���[�V�������͑���ł��Ȃ��悤�ɂ���
				player.move_juge = false;
				PlaySoundFile("data/Game/SE/�����œM���.mp3", DX_PLAYTYPE_BACK);
				//    player.player_Revival = false;
				status_ = STATUS_RIVER_DAMAGE;
				next_anim = model_anim_river_die;
			}
			//if(player.security_attack) {
			//    status_   = STATUS_CAR_DAMAGE;
			//    next_anim = model_anim_car_clash;
			//}

			if (player.security_attack) {
				//         player.move_juge       = false;
				status_ = STATUS_SECURITY_DAMEGE;
				player.Revival_move = false;
				player.security_attack = false;
				//  �ԂɂЂ��ꂽ�悤�Ɠ|�����悤�A�j���[�V���������p�ɂ���
				next_anim = model_anim_car_clash;
			}
			if (goal) {
				player.move_juge = false;
				status_ = STATUS_HAPPY_DANCE;
				next_anim = model_anim_happy_dance;
			}

			break;
			//  Car�_���[�W�Ƃ��Ă��邪�v�����X���[�ɍU�����ꂽ���̃_���[�W���[�V�����ƈꎞ���p�Ƃ���
		case STATUS_CAR_DAMAGE:
			//  �A�j���[�V�������ƂɃt���[���X�s�[�h��ς���
			anim_frame_speed = 1.0f;
			//  �Q�[���I�[�o�[��ʂ�؂�ւ��i���C�t���c���Ă������ʂ͕ς�炸�j
			over_status = CAR_OVER;

			//  �t���[�������^���ɂȂ�����i�A�j���[�V��������j������ҋ@��Ԃɖ߂�

			if (player.player_Revival) {
				status_ = STATUS_STAND_UP;
				next_anim = model_anim_stand_up;
			}

			break;
		case STATUS_RIVER_DAMAGE:
			//  �A�j���[�V�������ƂɃt���[���X�s�[�h��ς���
			anim_frame_speed = 1.0f;
			//  �Q�[���I�[�o�[��ʂ�؂�ւ��i���C�t���c���Ă������ʂ͕ς�炸�j
			over_status = RIVER_OVER;

			player.move_y -= 0.1f;

			if (player.player_Revival) {
				status_ = STATUS_STAND_UP;
				next_anim = model_anim_stand_up;
			}

			break;

		case STATUS_STAND_UP:
			//  �v���C���[�����X�|�[�����N���オ�������̃A�j���[�V����
			if (anim_frame >= anim_max_frame - 2) {
				if (life.life_over)
				{
					status_ = STATUS_DEAD_CRY;
					next_anim = model_anim_dead_cry;
					//					player.player_Revival = false;

				}
				else {
					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
					player.player_Revival = false;
				}
			}
			break;

		case STATUS_SECURITY_DAMEGE:
			anim_frame_speed = 2.0f;

			if (anim_frame >= anim_max_frame - 2) {
				player.security_attack = false;
				status_ = STATUS_SECURITY_STAND_UP;
				next_anim = model_anim_security_stand_up;
			}
			break;

		case STATUS_SECURITY_STAND_UP:
			anim_frame_speed = 2.0f;

			//  �v�����X���[�ɍU������ė����オ�鎞�̏���
			if (anim_frame >= anim_max_frame - 2) {
				player.security_attack = false;
				status_ = STATUS_IDLE;
				next_anim = model_anim_idle;
				//  �v���C���[���痣���
				seculity.pos_x = GetRand(320) - 150;
			}
			break;
		case STATUS_DEAD_CRY:
			//	���[�v������
			if (anim_frame >= anim_max_frame - 2) {
				anim_frame = 0;
			}
			break;
		case STATUS_HAPPY_DANCE:
			//	�����Ȃ��悤�ɌŒ肷��
			player.move_x = player.pos_x;
			player.move_z = player.pos_z;
			player.move_y = player.pos_y;

			//	�A�j���[�V������1���قǂ�������Idle�ɖ߂�
			if (anim_frame >= anim_max_frame - 2) {
				anim_frame = 0;
			}
			if (CheckHitKey(KEY_INPUT_F)) {
				
					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
				}
		case STATUS_UFO_OUT:

			if (anim_frame >= anim_max_frame - 2) {
				anim_frame = 0;
			}
			if (player.pos_y <= 2.0f)
			{
				//status_ = STATUS_IDLE;
				//next_anim = model_anim_idle;
			}

		}

		if (status_ != pre_status) {
			// �A�j���[�V�������؂�ւ�����P�t���[����
			//  1. �A�j���[�V������Detach
			//  MV1DetachAnim(���f��, ���݂̃A�j���C���f�b�N�X);
			MV1DetachAnim(model_, anim_index);
			//  2. �A�j���[�V������Attach
			//  MV1AttachAnim(���f��, 0/1, �A�j���[�V�������f��);
			MV1AttachAnim(model_, 1, next_anim);
			//  3. �A�j���[�V�����̒����擾
			//  MV1GetAttachAnimTotalTime(���f��, ���݂̃A�j���C���f�b�N�X);
			anim_max_frame = MV1GetAttachAnimTotalTime(model_, anim_index);
			//  4. �A�j���[�V�����̍Đ��b����0�ɂ���
			//  �ϐ���������
			anim_frame = 0;
		}
		MV1SetAttachAnimTime(model_, anim_index, anim_frame);
		anim_frame += anim_frame_speed;
		if (anim_frame >= anim_max_frame) {
			if (car_die) {
				Respawn();
				//	�~�܂��Ă���Ԃ̓������Ăѓ����o������
				for (int i = 0; i < 6; i++) {
					car_x_plus[i] = 1.5f;
				}
				car_die = false;
				//  �Q�[���I�[�o�[�p�̕ϐ��@���C�t���c���Ă����牽���N����Ȃ�
				car_dead = true;
				//status_   = STATUS_MOVE;
				//next_anim = model_anim_run;
			}
			if (river_die) {
				Respawn();
				river_die = false;
				//  �Q�[���I�[�o�[�p�̕ϐ��@���C�t���c���Ă����牽���N����Ȃ�
				river_dead = true;
				//status_    = STATUS_MOVE;
				//next_anim  = model_anim_run;
			}
			anim_frame = 0.0f;
		}

		//  �v�����X���[�̃A�j������

		int security_pre_status = security_status;   // �ЂƂO�̏�Ԃ�ۑ�
		int security_next_anim = -1;                // ���̃A�j���[�V�����p���f��
		if (security_move_juge) {
			security_status = SECULITY_ATTACK;
			security_next_anim = security_anim_attack;
		}

		switch (security_status) {
		case SECULITY_IDLE:
			//			Seculity_Anim_frame = 1.0f;
			Seculity_Anim_frame_speed = 1.0f;
			//if (seculity.radian >= 5.0f) {
			//	security_status = SECULITY_MOVE;
			//	security_next_anim = security_anim_move;
			//}
			//if (security_move_juge)
			//{
			//	security_status = SECULITY_MOVE;
			//	security_next_anim = security_anim_move;
			//}

			break;

			//case SECULITY_MOVE:
			//	Seculity_Anim_frame_speed = 0.25f;

			//	if (player.pos_x <= seculity.pos_x + 2 && player.pos_z < -460 || player.pos_x >= seculity.pos_x - 2 && player.pos_z < -460) {
			//		security_status = SECULITY_ATTACK;
			//		security_next_anim = security_anim_attack;
			//	}
			//	//if (security_move_juge != true)
			//	//{
			//	//	security_status = security_anim_idle;
			//	//	security_next_anim = security_anim_idle;

			//	//}
			//	if (Seculity_Anim_frame >= seculity_anim_max_frame)
			//	{
			//		security_status = security_anim_idle;
			//		security_next_anim = security_anim_idle;

			//	}

			//	break;
		case SECULITY_ATTACK:
			if (Seculity_Anim_frame >= seculity_anim_max_frame / 2)
			{
				security_status = security_anim_idle;
				security_next_anim = security_anim_idle;
				Seculity_Anim_frame = 0;

			}
			break;

		}
		if (security_status != security_pre_status) {
			// �A�j���[�V�������؂�ւ�����P�t���[����
			//  1. �A�j���[�V������Detach
			//  MV1DetachAnim(���f��, ���݂̃A�j���C���f�b�N�X);
			MV1DetachAnim(security_model, seculity_anim_index);
			//  2. �A�j���[�V������Attach
			//  MV1AttachAnim(���f��, 0/1, �A�j���[�V�������f��);
			MV1AttachAnim(security_model, 1, security_next_anim);
			//  3. �A�j���[�V�����̒����擾
			//  MV1GetAttachAnimTotalTime(���f��, ���݂̃A�j���C���f�b�N�X);
			anim_max_frame = MV1GetAttachAnimTotalTime(security_model, seculity_anim_index);
			//  4. �A�j���[�V�����̍Đ��b����0�ɂ���
			//  �ϐ���������
			Seculity_Anim_frame = 0;
		}
		MV1SetAttachAnimTime(security_model, seculity_anim_index, Seculity_Anim_frame);
		Seculity_Anim_frame += Seculity_Anim_frame_speed;


		//  �v���C���[������ł��܂����Ƃ��A�j���[�V�����̃t���[����max�܂ōs�����珉���ʒu�ɖ߂�

		//  �A�j���[�V��������莞�Ԃ�����ҋ@��Ԃ̃A�j���[�V�����ɖ߂�
		//    if(player.anim_time >= 60.0f) {
		//        idle = true;
		//        run  = false;
		//    }
		//    else if(player.anim_time <= 59.0f) {
		//        //            anim_run  = MV1AttachAnim(model_, 1, model_anim, FALSE);
		//        //    //   car_clash = false;
		//        idle = false;
		//        run  = true;
		//    }
		//    //  �ҋ@��Ԃ̏���
		//    if(idle) {
		//        //  �Ђ��ꂽ�ۂ̃A�j���[�V�����̃t���[����߂��Ă���
		//        MV1SetAttachAnimTime(model_, idle_index, anim_idle_frame);
		//        anim_idle_frame += 0.5f;
		//        if(anim_idle_frame >= anim_idle_max) {
		//            anim_idle_frame = 0.0f;
		//        }
		//    }
		//    //            MV1SetAttachAnimTime(model_, model_anim_idle, anim_idle_frame);
		//    //}

		//    if(run) {
		//        MV1SetAttachAnimTime(model_, run_index, anim_run_frame);

		//        anim_run_frame += 0.5f;

		//        // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		//        if(anim_run_frame >= anim_run_max) {
		//            anim_run_frame = 0.0f;
		//        }
		//    }
		//}
		//if(dead)   //  �v���C���[������Ă��܂����Ƃ��̃A�j���[�V����
		//{
		//    //  �ԂɂԂ������Ƃ��̃A�j���[�V�����̏���
		//    if(car_die) {
		//        // �@�Ђ��ꂽ�Ƃ��̃A�j���[�V�����ȊO�͂��ׂĎ~�߂�
		//        idle = false;
		//        run  = false;
		//        anim_car_clash_frame += 1.0f;
		//        MV1SetAttachAnimTime(model_, car_clash_index, anim_car_clash_frame);
		//        if(anim_car_clash_frame >= anim_car_clash_max) {
		//            //  Re�ɂ����W��������
		//            Respawn();
		//            live                 = true;
		//            dead                 = false;
		//            anim_car_clash_frame = 0.0f;
		//            car_dead             = true;
		//        }nfjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
		//    }
		//    if(river_die) {
		//        idle = false;
		//        run  = false;
		//        anim_river_die_frame += 1.0f;
		//        MV1SetAttachAnimTime(model_, anim_river_die_max, anim_car_clash_frame);
		//        if(anim_river_die_frame >= anim_river_die_max) {
		//            Respawn();
		//            live                 = true;
		//            dead                 = false;
		//            anim_car_clash_frame = 0.0f;
		//        }
		//    }

		//  �����Ă���Ƃ��̃A�j���[�V�����̏���
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------

		//  �Ԃ̍��W
		for (int i = 0; i < CAR_NUM; i++) {
			MV1SetPosition(car_model[i], { car_x[i], 0, car_z[i] });
			//MV1SetRotationXYZ(car_model[i], {0, 5, 0});
			MV1SetRotationXYZ(car_model[i], { 0, TO_RADIAN(-90), 0 });
			MV1SetScale(car_model[i], { 0.05f, 0.05f, 0.05f });
		}
		//        MV1SetPosition(coin_model,coin_x, 3, coin_z);
		//  �R�C���̍��W
		//	�R�C��������Ă���悤�Ɍ�����p�̕ϐ�
		Coin_Rota_x+= 3.0f;
		for (int i = 0; i < COIN_NUM; i++) {
			MV1SetPosition(coin_models[i], { score.coin_x[i], 3, score.coin_z[i] });
			MV1SetRotationXYZ(coin_models[i], { 0,TO_RADIAN(Coin_Rota_x), TO_RADIAN(0) });
			MV1SetScale(coin_models[i], { 0.02f, 0.03f, 0.03f });
		}
		MV1SetPosition(coin_model, { score.coin_x[0], 3, score.coin_z[0] });
		MV1SetRotationXYZ(coin_model, { TO_RADIAN(90), 0,TO_RADIAN(90) });
		MV1SetScale(coin_model, { 3.0f, 3.0f, 3.0f });

		//  UFO�̕`��
		MV1SetPosition(ufo_model, { ufo.pos_x, ufo.pos_y - 8, ufo.pos_z });
		MV1SetScale(ufo_model, { 0.5f, 0.5f, 0.5f });

		//  �v�����X���[�̕`��
		MV1SetPosition(security_model, { seculity.pos_x, 0, seculity.pos_z });
		MV1SetRotationXYZ(security_model, { 0.0f, seculity.radian, 0.0f });

		MV1SetScale(security_model, { 0.05f, 0.05f, 0.05f });

		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------
		// SE�p����
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|------------------------------------------------------------

		for (int i = 0; i < CAR_NUM; i++) {
			//  Z���W���ɓ����Ă���(�c)
			if (player.pos_z <= car_z[i] + 10 && player.pos_z >= car_z[i] - 10) {
				//  X���W���ɓ�������Q�[���I�[�o�[�i���j
				if (player.pos_x >= car_x[i] + 99 && player.pos_x <= car_x[i] + 100) {
					PlaySoundFile("data/Game/SE/�Ԃ̃N���N�V����.mp3", DX_PLAYTYPE_BACK);
				}
			}
		}

		////  �R�C���̈ʒu
		//for (int i = 0; i < 5; i++) {
		//    MV1SetRotationXYZ(coin_models[i], {TO_RADIAN(90), 0, TO_RADIAN(90)});

		//    //  �������ő傫�߂ɏo��
		//    MV1SetScale(coin_models[i], {3.0f, 3.0f, 3.0f});
		//}
		//  �ʒu�͂܂����܂��ĂȂ��̂ł�������蓮�ŏꏊ�����߂�

		coin_pos[0] = { car_x[3] + 30, 3, car_z[3] };
		coin_pos[1] = { car_x[0] + 30, 3, car_z[0] };
		coin_pos[2] = { car_x[4] + 30, 3, car_z[4] };
		coin_pos[3] = { wood_x[1], 3, wood_z[1] };
		coin_pos[4] = { wood_x[3], 3, wood_x[3] };

		for (int i = 0; i < COIN_NUM; i++) {
			//MV1SetPosition(coin_model, {coin_pos[i]});
			//             MV1SetPosition(coin_model, {coin_pos[i]});
			//MV1SetPosition(coin_model[3], {0, 3, 0});
			//MV1SetPosition(coin_model[4], {0, 3, 0});*/
		}
		player.time++;

		////  �X�L�b�v�@�\
		if (CheckHitKey(KEY_INPUT_K)) {
			player.move_z = -400;
			player.pos_z = -400;
		}

		//  �N���X�̍X�V
		player.Update();
		wall.Update();
		timer.Update();
		score.Update();
		life.Update();
		ui.Update();
		camera.Update();
		if (stage_status == SECOND_STAGE) {
			ufo.Update();
		}
		seculity.Update();
		minimap.Update();

		//  �R�C�����Ԃ�ۑ��̏�ɕ`�悷�邽�߂̍��W�ϐ��̍X�V
		if (score.coin_swich[0]) {
			score.coin_x[0] = car_x[3] + 30;
			score.coin_z[0] = car_z[3];
		}
		if (score.coin_swich[1]) {
			score.coin_x[1] = car_x[0] + 30;
			score.coin_z[1] = car_z[0];
		}
		if (score.coin_swich[2]) {
			score.coin_x[2] = car_x[4] + 30;
			score.coin_z[2] = car_z[4];
		}
		if (score.coin_swich[3]) {
			score.coin_x[3] = wood_x[1];
			score.coin_z[3] = wood_z[1];
		}
		if (score.coin_swich[4]) {
			score.coin_x[4] = wood_x[3];
			score.coin_x[4] = wood_z[3];
		}

		if (player.pos_y <= 5.0f) {
			//  UFO�ɘA�ꋎ���Ă�r���ɂ�������Ƃ������Ȃ��悤�ɂ��邽��
			//  �R�C����������ۂ̓����蔻��̋y�уX�R�A�̒ǉ�
			for (int i = 0; i < COIN_NUM; i++) {
				if (score.coin_swich[i]) {
					if (score.coin_z[i] - 3 <= player.pos_z && score.coin_z[i] + 3 >= player.pos_z &&
						score.coin_x[i] - 3 <= player.pos_x && score.coin_x[i] + 3 >= player.pos_x) {
						//  �X�R�A���P�O�O�O���₷
						score.score += 1000;
						//  ������R�C���̕`�������
						score.coin_swich[i] = false;
					}
				}
			}
		}

		//  Z���W���O�ɍs���΍s���قǃX�R�A�������Ă��������������đO�ɏo�Ă������Ȃ�
		if (player.move_z < score.score_pos) {
			timer.start_time = true;
			score.score_pos = player.move_z;
			//  ���ɐi�߂ΐi�ނقǃX�R�A�̏オ�蕝�������Ă����悤�ɂ���
			score.score += score.score_pos / -2;
			//            score.score += 10;
		}
		//  �v���C���[����ʒ[�̕ǂ܂ōs�����炻��ȏ�͉��ɍs���Ȃ��悤�ɂ��邽�߂̏���
		if (wall.Wall_left_x <= player.move_x) {
			player.move_x = wall.Wall_left_x - 5;
		}
		if (wall.Wall_right_x >= player.move_x) {
			player.move_x = wall.Wall_right_x + 5;
		}

		//  �ϐ��𑫂������Ĉ��ȏ㐔�l����������Idle�A�j���[�V�����ɂ��Ă���

		//	�X�e�[�W�̏���
	

		switch (stage_status)
		{
		case FIRST_STAGE:
			//  �Ԃ̓����̏���
			for (int i = 0; i < CAR_NUM; i++) {
				//car_x[i] += car_x_plus[i];


				//  ��ʒ[�ɍs�����甽�Α��̉�ʒ[�Ɍ����悤�ɂ��Ă���
				if (car_x[i] >= 200) {
					car_x[i] = -150 + GetRand(-50);

					if (i >= 5) {
						i = 0;
					}
				}
			}



			if (player.pos_y <= 5.0f) {
				//  �����蔻��̏���(�Ԃ̓����蔻��)
				for (int i = 0; i < CAR_NUM; i++) {
					//  Z���W���ɓ����Ă���(�c)
					if (player.pos_z <= car_z[i] + 10 && player.pos_z >= car_z[i] - 10) {
						//  X���W���ɓ�������Q�[���I�[�o�[�i���j
						if (player.pos_x >= car_x[i] - 5 && player.pos_x <= car_x[i] + 5) {
							//  �v���C���[�̍��W�ύX�y�уA�j���[�V�����̍Đ��̋��ϐ���true�ɂ���
							car_x_plus[i] = 0.0f;
							//	������ԉ��o�����(���X�|�[���n�_�܂Ŏ��R�ɔ�΂�)
							//for (int i = 0; i < 15; i++)
							//{
							//	player.move_x++;
							//	player.pos_x = player.move_x;
							//	player.move_y++;
							//}

							//	���X�|�[���n�_�܂ł̋������Ƃ�
							Respawn_Distance_z = player.pos_z - 20.0f;


							for (int i = 0; i >= Respawn_Distance_z; i--)
							{
								player.move_y = i * -1;
								player.move_z -= i;
							}
							//for (int i = 0; i <= 20; i++)
							//{
							//	player.move_y = i;
							//}


	//						player.move_x += player.move_y;
							dead = true;
							live = false;
							car_die = true;
							minimap.map_icon_switch = false;
							bgm_status = OVER_BGM;
							//  �v���C���[�𓮂��Ȃ�����
							player.Revival_move = false;
						}
					}
				}
			}

			if (player.pos_z + 15 >= goal_line_z &&player.pos_z - 15 <= goal_line_z && player.pos_x >= goal_line_x - 15 && player.pos_x <= goal_line_x + 15) {
				goal = true;
				init = true;
				timer.time_clear = false;
				InitTime++;
				goal_count=1;

				if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
					if (init) {

						stage_status = SECOND_STAGE;
						//	���̃X�e�[�W���n�܂����ۂɃA�j���[�V���������Z�b�g����
						status_ = STATUS_IDLE;
						next_anim = model_anim_idle;

						//Game::Init();
						player.Init();
						wall.Init();
						timer.Init();
						score.Init();
						life.Init();
						ui.Init();
						camera.Init();
						ufo.Init();
						seculity.Init();
						minimap.Init();
						camera.pos_z = -700;
						for (int i = 0; i < CAR_NUM; i++) {
							car_z[i] = CAR_Z[i];
						}
						car_x[0] = -50;
						car_x[1] = 30;
						car_x[2] = 90;
						car_x[3] = 60;
						car_x[4] = -100;
						for (int i = 0; i < 6; i++) {
							car_x_plus[i] = 1.5f;
						}
						for (int i = 0; i < WOOD_NUM; ++i) {
							int start_pos_x = 0;
							if (i >= 5) {
								start_pos_x = 150;
							}
							wood_x[i] = start_pos_x;
							wood_z[i] = WOOD_START_Z[i];
							wood_x_re[i] = GetRand(-150);
							wood_z_re[i] = WOOD_START_Z_Re[i];
						}
						car_dead = false;
						Respawn_Distance_z = 0.0f;
						river_dead = false;
						wood_safe = true;
						safe_stone_x = -90;
						safe_stone_z = -220;
						goal_line_x = 0;
						goal_line_z = 0;
						over_time = 0;
						river_out_y = 1;
						//	�^�C�g���ł͂Ȃ����̃X�e�[�W�ւ̃J�b�g�C������������
						//title = true;
						title_x = 0;
						title_blend = 0;
						title_blend_hiku = 3;
						//game = false;
						goal = false;
						goal_anim = false;
						no_die = true;
						init = false;
						camera_x = 0.0f;
						camera_z = 0.0f;
						camera_y = 10.0f;
						//				camera_y = 15.0f;
						camera_y_radian = 5.0f;

						Title_Slide = 10;

						Title_Slide_x = 0;
						stage_change = true;
						StopSoundMem(Clear_BGM);
						//	�A�j���[�V������������������
						InitTime = 0;

						//  BGM���J�n�����邽�߂̕ϐ�
						Title_BGM_Start = true;
						Game_BGM_Start = false;
						Over_BGM_Start = false;
						Clear_BGM_Start = false;

						bgm_status = START_BGM;
					}
				}
			}
			break;

		case SECOND_STAGE:

			//  �Ԃ̓����̏���
			for (int i = 0; i < CAR_NUM; i++) {
				car_x[i] += car_x_plus[i];


				//  ��ʒ[�ɍs�����甽�Α��̉�ʒ[�Ɍ����悤�ɂ��Ă���
				if (car_x[i] >= 200) {
					car_x[i] = -150 + GetRand(-50);

					if (i >= 5) {
						i = 0;
					}
				}
			}



			if (player.pos_y <= 5.0f) {
				//  �����蔻��̏���(�Ԃ̓����蔻��)
				for (int i = 0; i < CAR_NUM; i++) {
					//  Z���W���ɓ����Ă���(�c)
					if (player.pos_z <= car_z[i] + 10 && player.pos_z >= car_z[i] - 10) {
						//  X���W���ɓ�������Q�[���I�[�o�[�i���j
						if (player.pos_x >= car_x[i] - 5 && player.pos_x <= car_x[i] + 5) {
							//  �v���C���[�̍��W�ύX�y�уA�j���[�V�����̍Đ��̋��ϐ���true�ɂ���
							car_x_plus[i] = 0.0f;
							//	������ԉ��o�����(���X�|�[���n�_�܂Ŏ��R�ɔ�΂�)
							//for (int i = 0; i < 15; i++)
							//{
							//	player.move_x++;
							//	player.pos_x = player.move_x;
							//	player.move_y++;
							//}

							//	���X�|�[���n�_�܂ł̋������Ƃ�
							Respawn_Distance_z = player.pos_z - 20.0f;


							for (int i = 0; i >= Respawn_Distance_z; i--)
							{
								player.move_y = i * -1;
								player.move_z -= i;
							}
							//for (int i = 0; i <= 20; i++)
							//{
							//	player.move_y = i;
							//}


	//						player.move_x += player.move_y;
							dead = true;
							live = false;
							car_die = true;
							minimap.map_icon_switch = false;
							bgm_status = OVER_BGM;
							//  �v���C���[�𓮂��Ȃ�����
							player.Revival_move = false;
						}
					}
				}
			}


			//	��ɓ������u�Ԃ̂����炬���̏���
			if (player.pos_z <= -115) {

			}

			River_distance = player.pos_z * -2;


			//  �v���C���[����̃G���A�ɓ������ۂɈړ��ʂ����炷����
			if (player.pos_z <= -119 && player.pos_z >= -279) {
				player.move = 15;
			}
			else
			{
				player.move = 20;
			}

			//  �ۑ��𗬂�����
			wood_x[0]--;
			wood_x[5]--;
			wood_x[1] -= 1.5f;
			wood_x[2]--;
			wood_x[7]--;
			wood_x[3] -= 1.5f;
			wood_x[4]--;
			wood_x[9]--;

			//  �ۑ����t�����ɗ�������
			for (int i = 0; i < 10; i++) {
				wood_x_re[i]++;
			}

			if (player.pos_y <= 5.0f) {
				if (wood_safe != true) {
					//  ��̃G���A�ɓ�����������
					if (player.pos_z <= -130 && player.pos_z >= -279) {
						//  �ۑ��ɏ������v���C���[���ꏏ�ɗ���Ă�������
						//   ��P�{��
						if (player.pos_z <= wood_z[0] + 16 && player.pos_z >= wood_z[0]) {
							player.move_x--;
						}
						else if (player.pos_z <= wood_z[5] + 16 && player.pos_z >= wood_z[5]) {
							player.move_x--;
						}
						//  ��Q�{��
						else if (player.pos_z <= wood_z[1] + 16 && player.pos_z >= wood_z[1]) {
							player.move_x -= 2.0f;
							player.pos_x -= 1.0f;
						}
						//�@��R�{��
						//else if(pos_z <= wood_z[2] + 16 && pos_z >= wood_z[2] - 15) {
						//    move_x--;
						//}
						else if (player.pos_z <= wood_z[7] + 16 && player.pos_z >= wood_z[7]) {
							player.move_x--;
						}
						//  ��S�{��
						else if (player.pos_z <= wood_z[3] + 16 && player.pos_z >= wood_z[3]) {
							player.move_x -= 2.0f;
							player.pos_x -= 1.0f;
						}
						//  ��T�{��
						else if (player.pos_z <= wood_z[4] + 16 && player.pos_z >= wood_z[4] /*- 8*/) {
							player.move_x--;
						}
						else if (player.pos_z <= wood_z[9] + 8 && player.pos_z >= wood_z[9]) {
							player.move_x--;
						}

						for (int i = 0; i < 10; i++) {
							if (player.pos_z <= wood_z_re[i] + 16 && player.pos_z >= wood_z_re[i]) {
								player.move_x++;
								//                            player.pos_x = player.move_x;
								//  �΂̃Z�[�t�G���A��O�̊ۑ��݂̂����Ɏ~�܂��悤�ɂ��Ă���
								//                            if(player.pos_z <= wood_z_re[1] + 16 && player.pos_z >= wood_z_re[1])
								//                          {
								//
								//                           }
							}
						}
					}
				}
			}

			//  ��ʒ[�ɍs������߂��Ă��鏈��	�i�ۑ��p�j
			for (int i = 0; i < WOOD_NUM; i++) {
				if (wood_x[i] <= -400 - 25) {
					wood_x[i] = 400;
				}
				//  �t���������l�ɖ߂�
				if (wood_x_re[i] >= 400) {
					wood_x_re[i] = -150 + GetRand(-150);
				}
			}


			//  �v���C���[���n�ʂɂ��Ă����ꍇ�͔��肪����
			wood_safe = false;
			if (player.pos_y <= 5.0f) {
				//  ��̓����蔻��̓f�t�H���g��ON
				wood_safe = true;

				//  �ۑ��̏���Ă���B����Ă��Ȃ��̓����蔻��
				for (int i = 0; i < WOOD_NUM; i++) {
					if (player.pos_z <= wood_z[i] + 16 && player.pos_z >= wood_z[i] /*- 15*/ &&
						player.pos_x <= wood_x[i] + 100 && player.pos_x >= wood_x[i] - 100) {
						//  false������Ă���Ƃ�
						wood_safe = false;

					}
				}
				//  �t�@�̏���
				for (int i = 0; i < WOOD_NUM; i++) {
					if (player.pos_z <= wood_z_re[i] + 16 && player.pos_z >= wood_z_re[i] /*- 15*/ &&
						player.pos_x <= wood_x_re[i] + 100 && player.pos_x >= wood_x_re[i] - 100) {
						wood_safe = false;
						if (i >= 10) {
							i = 0;
						}
					}
				}
				//}
				//  �΂̏�ɍڂ��Ă���Ƃ��̏���
				if (player.pos_z <= safe_stone_z + 30 && player.pos_z >= safe_stone_z && player.pos_x <= safe_stone_x + 80 &&
					player.pos_x >= safe_stone_x) {
					//move_x++;
					//  ����Ȃ��悤�ɂ���
					//  �v���C���[�������ꏊ���炻��ȏ�i�܂Ȃ��悤�Ɉ�u�Œ肷��i����ȍ~���Ȃ��悤�Ɉ��̂݁j
					int i = 0;
					if (i <= 1) {
						player.move_x = player.move_x;
						i++;
					}

					//    ��ł��ȂȂ��Ȃ�
					wood_safe = false;
				}
			}
			//  �J�����̌�����ύX���邽�߂̏���




			//�@��̃X�e�[�W�ɓ����Ă���̃J�����̕ύX
			/*   if(player.pos_z < -110) {
				if(CheckHitKey(KEY_INPUT_SPACE)) {
					camera_y        = 50.0f;
					camera_y_radian = -25.0f;
				}
				else {
					camera_y        = 10.0f;
					camera_y_radian = 5.0f;
				}
			}*/

			//  ��̔���̏���
			if (wood_safe) {
				if (player.pos_z <= -130 && player.pos_z >= -279) {
					//  �c�@�����炷
					dead = true;
					river_die = true;
					minimap.map_icon_switch = false;

					//  �v���C���[�𓮂��Ȃ�����
					player.Revival_move = false;

					if (life.life_over) {
						river_dead = true;
						//  ����ł��܂����̂ŏ������i���j
						init = true;
					}
				}
			}
			player.pos_x;
			//  �ꏏ�ɗ����悤�ɂ���(�����ۑ��p)
			if (player.pos_z <= wood_z[1] + 16 && player.pos_z >= wood_z[1]) {
				player.move_x += 0.5f;
				player.pos_x += 0.5f;
			}
			if (player.pos_z <= wood_z[3] + 16 && player.pos_z >= wood_z[3] /*- 15*/) {
				player.move_x += 0.5f;
				player.pos_x += 0.5f;
			}


			//  UFO�X�e�[�W�̓�����ɂ���ǂ̓����蔻��
			if (player.pos_z <= -279.0f && player.pos_z >= -285.0f) {
				for (int i = 0; i < 17; i++) {
					if (wall.UFO_STAGE_X[i] + 5 >= player.pos_x && wall.UFO_STAGE_X[i] - 5 <= player.pos_x) {
						player.pos_x = wall.UFO_STAGE_X[i] + 10;
						player.move_x = wall.UFO_STAGE_X[i] + 10;
					}
				}
			}
			//	UFO�̃����_�����W��2����1�Ńv���C���[���W�Ɣ��悤�ɂ��Ă���
			//for (int i = 0; i <= 15; i++)
			//{
			//	if (ufo.pos_no <= i)
			//	{
			//		ufo.pos_x = player.pos_x;
			//	}
			//}
			if (ufo.Tracking)
			{
				if (ufo.pos_x < player.pos_x) {
					ufo.pos_x += 2;
				}
				if (ufo.pos_x > player.pos_x) {
					ufo.pos_x -= 2;
				}
			}
			//	�v���C���[�̍��W�ɂ�����g���b�L���O�����������̏����֌�����
			if (ufo.pos_x == player.pos_x)
			{
				ufo.Tracking = false;
			}

			//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			//	UFO��Z���W�ɂ��Ă̏���
			//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// UFO�ƃv���C���[Z���W�͓����ɂ��Ēǂ��Ă��Ă邢�銴���ɂ��Ă���
			if (player.pos_z <= -320 && player.pos_z >= -439) {
				ufo.pos_z = player.pos_z;
			}
			//  �v���C���[��UFO�G���A���ɂ���Ƃ��̂ݓ����蔻��y��UFO�����Ă���Ƃ������������s����
			if (player.pos_z <= -320 && player.pos_z >= -440) {
				//  UFO�Ƃ̓����蔻��̏���
				if (ufo.ufo_standhing) {
					//  UFO���~�܂�ʒu���}�C�i�X�̍��W�̉\��������̂łQ�p�ӂ���
					if (player.pos_x <= ufo.pos_x + 3 && player.pos_x >= ufo.pos_x - 3 ) {
						//                car_die = true;
						/* no_die = false;
							  ufo.ufo_die = true;*/
							  //car_die = true;
						ufo.ufo_die = true;

					}
				}
			}
			//  �v���C���[�����X�|�[���n�_�܂ŉ^��
			if (ufo.ufo_die) {

				//	UFO�̓������~�߂�
				ufo.ufo_standhing = false;
				//if(ufo.pos_z >= 20.0f) {
				//                if(player.move_y <= 0.0f)
				if (player.move_y <= 20.0f && player.pos_z <= 303.0f) {
					
					//	KEY��A�ł��邱�Ƃɂ�蔲���o�����߂̕ϐ�
					if (CheckHitKey(KEY_INPUT_I))
					{
						consecutive_blocking = 0;
					}
					else
					{
						consecutive_blocking++;
					}
					consecutive_blocking++;
				
					if (consecutive_blocking == 3)
					{
						ufo_rampage += 1;
					}
					if (ufo_rampage >= 10)
					{
						ufo_rampage = 0;
						ufo.ufo_die = false;
						player.move_y = 0.0f;
					}

					//	�v���C���[�̝�����A�j���[�V���������s����
					player_ufo_out = true;
					player.move_y+=0.025;
					player.pos_y += 0.025;
					player.time = 0.0f;
				}

				if (player.pos_y >= 19.0f) {
					player.move_x = ufo.pos_x;
					player.pos_x = ufo.pos_x;
					ufo.Tracking = false;
					ufo.ufo_standhing = true;
					player.move_juge = true;
					if (ufo.UFO_LIGHT >= 0.0f)
					{
						ufo.UFO_LIGHT -= 2.0f;
					}


					//  UFO�G���A�̃X�^�[�g�n�_�܂ŘA��Ă������
					player.move_z = -300.0f;
					//  ufo.pos_no ���̓X�^�[�g�n�_���W��\��
					ufo.pos_no = 0;
				}
				//	�v���C���[��UFO�X�e�[�W�ɂ�����UFO�̃��C�g���W�J�����
				if (player.pos_z <= -299.0f)
				{
					if (ufo.UFO_LIGHT <= 15.0f)
					{
						ufo.UFO_LIGHT += 1.0f;
					}

				}
				//  �v���C���[��Z���W���X�^�[�g�n�_�ɖ߂�����UFO����~�낵�Ď��S�t���O���Ȃ����čŏ�����n�܂�B
				if (player.pos_z >= -302.0f && player.move_y >= 0.0f) {
					//  X���W��UFO�ɂ���Ă��炳��Ȃ��悤�ɂ��邽�߂ɌŒ肷��@UFO����~�肫������FALSE�ɂ��ď������~�߂�
					player.move_x = 0.0f;
					player.pos_x = 0.0f;
					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
					//  UFO��X���W�������_���ɖ߂�ufo_die�̏������I�������͌��̃N���X�̏����ɖ߂�悤�ɂ���
					ufo.pos_no = GetRand(30);
					ufo.ufo_die = false;
				}
			}
			//	�d�͗p�̏���
			//  Z���W-460����x�����X�e�[�W�֓˓�
						//  ��ʒ[�ɍs������߂��Ă��鏈��
			for (int i = 0; i < WOOD_NUM; i++) {
				if (wood_x[i] <= -400 - 25) {
					wood_x[i] = 400;
				}
				//  �t���������l�ɖ߂�
				if (wood_x_re[i] >= 400) {
					wood_x_re[i] = -150 + GetRand(-150);
				}
			}

			//	�v�����X���[�̓����̓f�t�H���g��false�ɂ��A�������Ƃ��̂�true�ɂ���
			security_move_juge = false;

			if (player.pos_x >= seculity.pos_x && seculity.radian >= 4.5f) {
				//  �L�����������Ă���Ƃ��͉�]���~�߂�
				seculity.radian_move_juge = false;
				seculity.pos_x++;
			}
			if (player.pos_x <= seculity.pos_x && seculity.radian <= 1.5f) {
				//  �L�����������Ă���Ƃ��͉�]���~�߂�
				seculity.radian_move_juge = false;
				seculity.pos_x--;
			}

			//  Z���W-450����v�����X���[���ǂ��n�߂�S�[������܂Œǂ��񂳂��
			if (player.pos_z <= -450) {
				//  �O�t���[���ƌ��t���[����������ꍇ�͎��s����i�������Ƃ��j

				if (player.pos_x != player.pos_x_copy || player.pos_z != player.pos_z_copy) {
					if (seculity.pos_x <= player.pos_x && seculity.radian >= 4.3f) {
						seculity.pos_x += 3.0f;
						security_move_juge = true;

					}
					if (seculity.pos_x >= player.pos_x && seculity.radian <= 1.8f) {
						seculity.pos_x -= 3.0f;
						security_move_juge = true;

					}
				}

				//  �v�����X���[�ƃv���C���[�̓����蔻��̏���
				if (player.pos_x + 10.0f >= seculity.pos_x && player.pos_x - 10.0f <= seculity.pos_x) {
					player.security_attack = true;

					//                player.move_y = 20.0f;
				}
				//  Z���W�̓X�e�[�W�ɓ������炸���ƈꏏ
				seculity.pos_z = player.pos_z;
			}

			//}
			//if(ufo.pos_x >= 0)
			//    ufo.pos_x--;
			//player.move_x--;
			//player.pos_x--;

			//if(ufo.pos_x <= 0) {
			//    ufo.pos_x++;
			//    player.move_x++;
			//    player.pos_x++;
			//    player.pos_x--;
			//}
			//if(ufo.pos_z <= 20.0f) {
			//    ufo.pos_z++;
			//    player.move_z++;
			//    player.pos_z++;
			//}

			//if(player.pos_y == 0.0f) {
			//    no_die = false;
			//    Respawn();
			//}

			//	���i�K�ł͂Q�X�e�[�W�ڂ��ŏI�X�e�[�W�Ȃ̂ł�����ɃS�[���̏���������Ă���
			if (player.pos_z + 15 >= goal_line_z &&player.pos_z - 15 <= goal_line_z && player.pos_x >= goal_line_x - 15 && player.pos_x <= goal_line_x + 15) {
				//effect_congra_play = PlayEffekseer3DEffect(effect_congra);
				//SetPosPlayingEffekseer3DEffect(effect_congra_play, player.pos_x, player.pos_y, player.pos_z - 5);
				if (goal_adjustment <= 1)
				{
					bgm_status = CLEAR_BGM;
		//	���x�����[�v���Ȃ����߂ɂ���
					goal_adjustment = 2;
				}

				Clear_BGM_Start = true;
				switch (bgm_status) {
				case CLEAR_BGM:
					StopSoundMem(Game_BGM);
					PlaySoundMem(Clear_BGM, DX_PLAYTYPE_LOOP);
					bgm_status = -1;
					break;
				}
				goal = true;
				init = true;
				timer.time_clear = false;
				InitTime++;
				goal_count = 2;
				if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
					if (init) {

						stage_status = 0;

						//Game::Init();
						player.Init();
						wall.Init();
						timer.Init();
						score.Init();
						life.Init();
						ui.Init();
						camera.Init();
						ufo.Init();
						seculity.Init();
						minimap.Init();
						goal_adjustment = 0;
						for (int i = 0; i < CAR_NUM; i++) {
							car_z[i] = CAR_Z[i];
						}
						car_x[0] = -50;
						car_x[1] = 30;
						car_x[2] = 90;
						car_x[3] = 60;
						car_x[4] = -100;
						for (int i = 0; i < 6; i++) {
							car_x_plus[i] = 1.5f;
						}
						for (int i = 0; i < WOOD_NUM; ++i) {
							int start_pos_x = 0;
							if (i >= 5) {
								start_pos_x = 150;
							}
							wood_x[i] = start_pos_x;
							wood_z[i] = WOOD_START_Z[i];
							wood_x_re[i] = GetRand(-150);
							wood_z_re[i] = WOOD_START_Z_Re[i];
						}
						car_dead = false;
						Respawn_Distance_z = 0.0f;
						river_dead = false;
						wood_safe = true;
						safe_stone_x = -90;
						safe_stone_z = -220;
						goal_line_x = 0;
						goal_line_z = 0;
						over_time = 0;
						river_out_y = 1;
						title = true;
						title_x = 0;
						title_blend = 0;
						title_blend_hiku = 3;
						game = false;
						goal = false;
						goal_anim = false;
						goal_count = 0;
						no_die = true;
						init = false;
						camera_x = 0.0f;
						camera_z = 0.0f;
						camera_y = 10.0f;
						//				camera_y = 15.0f;
						camera_y_radian = 5.0f;

						Title_Slide = 0;

						Title_Slide_x = 0;
						StopSoundMem(Clear_BGM);
						//	�A�j���[�V������������������
						status_ = STATUS_IDLE;
						next_anim = model_anim_idle;

						InitTime = 0;

						//  BGM���J�n�����邽�߂̕ϐ�
						Title_BGM_Start = true;
						Game_BGM_Start = false;
						Over_BGM_Start = false;
						Clear_BGM_Start = false;

						bgm_status = START_BGM;
					}
				}

			}



			break;

		case THIRD_STAGE:

			break;

		case FOURTH_STAGE:

			break;

		case FIFTH_STAGE:

			break;
		}
		if (player.pos_z >= -302.0f && player.move_y >= 0.0f) {
			player.move_y--;
		}


		//  ���Ԑ؂�ŃQ�[���I�[�o�[�ɂȂ������̏���
		if (timer.time_over) {
			//  BGM���Ȃ���
			StopSoundMem(Game_BGM);
			Over_BGM_Start = true;
			switch (bgm_status) {
			case OVER_BGM:
				PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
				bgm_status = -1;
				break;
			}

			//  ���̂܂܂����ʗ��ŎԂɖ����ꑱ���Ă��܂��̂Ŗ�����Ȃ��ꏊ�ɔ�΂�
			player.pos_z = 80000;
			init = true;
			InitTime++;
		}


		//  ���H�̃X�e�[�W�̏ꍇ�̌���
		if (player.pos_z > -110) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				/*      camera_x = -80.0f;
				camera_z = -50.0f;
		  */
				camera_y = 50.0f;
				camera_y_radian = -25.0f;
			}
			else {
				/*    camera_x = 0.0f;
				camera_z = 0.0f;
			*/
				camera_y = 10.0f;
				camera_y_radian = 5.0f;
			}
		}
		//	��X�e�[�W����̓J�������Œ肷��
		if (player.pos_z < -110)
		{
			camera_y = 10.0f;
			camera_y_radian = 5.0f;
		}

		//	�J�������X�^�[�g�ʒu�ɍs���܂Ńv���C���[�𓮂��Ȃ�����

		if (camera.pos_z <= player.pos_z)
		{
			player.pos_x = 0.0f;
			player.pos_z = 20.0f;
			player.move_x = 0.0f;
			player.move_z = 20.0f;
		}


		//  �c�@���s�����Ƃ��̏���
		if (life.life_over) {
			//  �����ꂽ�Ƃ���BGM�J�n�p�̕ϐ���true�ɂ���

			switch (bgm_status) {
			case OVER_BGM:
				StopSoundMem(Game_BGM);
				PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
				bgm_status = -1;
				break;
			}

			//  ���̂܂܂����ʗ��ŎԂɖ����ꑱ���Ă��܂��̂Ŗ�����Ȃ��ꏊ�ɔ�΂�
			//player.pos_z = 80000;
			player.radian_y = 380.0f;


			init = true;
		}


		if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
			if (init) {

				//Game::Init();
				player.Init();
				wall.Init();
				timer.Init();
				score.Init();
				life.Init();
				ui.Init();
				camera.Init();
				ufo.Init();
				seculity.Init();
				minimap.Init();
				for (int i = 0; i < CAR_NUM; i++) {
					car_z[i] = CAR_Z[i];
				}
				car_x[0] = -50;
				car_x[1] = 30;
				car_x[2] = 90;
				car_x[3] = 60;
				car_x[4] = -100;
				for (int i = 0; i < 6; i++) {
					car_x_plus[i] = 1.5f;
				}
				for (int i = 0; i < WOOD_NUM; ++i) {
					int start_pos_x = 0;
					if (i >= 5) {
						start_pos_x = 150;
					}
					wood_x[i] = start_pos_x;
					wood_z[i] = WOOD_START_Z[i];
					wood_x_re[i] = GetRand(-150);
					wood_z_re[i] = WOOD_START_Z_Re[i];
				}
				car_dead = false;
				Respawn_Distance_z = 0.0f;
				river_dead = false;
				wood_safe = true;
				safe_stone_x = -90;
				safe_stone_z = -220;
				goal_line_x = 0;
				goal_line_z = 0;
				over_time = 0;
				river_out_y = 1;
				title = true;
				title_x = 0;
				title_blend = 0;
				title_blend_hiku = 3;
				game = false;
				goal = false;
				goal_anim = false;
				goal_count = 0;
				no_die = true;
				init = false;
				camera_x = 0.0f;
				camera_z = 0.0f;
				camera_y = 10.0f;
				//				camera_y = 15.0f;
				camera_y_radian = 5.0f;

				Title_Slide = 0;

				Title_Slide_x = 0;
				StopSoundMem(Clear_BGM);
				//	�A�j���[�V������������������
				status_ = STATUS_IDLE;
				next_anim = model_anim_idle;

				InitTime = 0;

				//  BGM���J�n�����邽�߂̕ϐ�
				Title_BGM_Start = true;
				Game_BGM_Start = false;
				Over_BGM_Start = false;
				Clear_BGM_Start = false;

				bgm_status = START_BGM;
			}
		}



		//  ��Ŏ��񂾂Ƃ��̏���
		//  +�c�@���Ȃ��Ȃ����Ƃ�

		if (life.life_over) {
			if (river_dead) {
				//    ��ʂ��؂�ւ���Ă���BGM��؂�ւ��邽�߂̏���
				if (over_time == 60) {
					ChangeVolumeSoundMem(200, Over_BGM);

					switch (bgm_status) {
					case OVER_BGM:
						StopSoundMem(Game_BGM);
						PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
						bgm_status = -1;
						break;
					}
					//  ���̂܂܂���M�ꑱ����BGM���n�܂�Ȃ��̂ō��W���ړ�������
					player.pos_z = 8000;
				}
				InitTime++;
				init = true;
				if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
					if (init) {

						//Game::Init();
						player.Init();
						wall.Init();
						timer.Init();
						score.Init();
						life.Init();
						ui.Init();
						camera.Init();
						ufo.Init();
						seculity.Init();
						minimap.Init();
						for (int i = 0; i < CAR_NUM; i++) {
							car_z[i] = CAR_Z[i];
						}
						car_x[0] = -50;
						car_x[1] = 30;
						car_x[2] = 90;
						car_x[3] = 60;
						car_x[4] = -100;
						for (int i = 0; i < 6; i++) {
							car_x_plus[i] = 1.5f;
						}
						for (int i = 0; i < WOOD_NUM; ++i) {
							int start_pos_x = 0;
							if (i >= 5) {
								start_pos_x = 150;
							}
							wood_x[i] = start_pos_x;
							wood_z[i] = WOOD_START_Z[i];
							wood_x_re[i] = GetRand(-150);
							wood_z_re[i] = WOOD_START_Z_Re[i];
						}
						car_dead = false;
						Respawn_Distance_z = 0.0f;
						river_dead = false;
						wood_safe = true;
						safe_stone_x = -90;
						safe_stone_z = -220;
						goal_line_x = 0;
						goal_line_z = 0;
						over_time = 0;
						river_out_y = 1;
						title = true;
						title_x = 0;
						title_blend = 0;
						title_blend_hiku = 3;
						game = false;
						goal = false;
						goal_anim = false;
						goal_count = 0;
						no_die = true;
						init = false;
						camera_x = 0.0f;
						camera_z = 0.0f;
						camera_y = 10.0f;
						//				camera_y = 15.0f;
						camera_y_radian = 5.0f;

						Title_Slide = 0;

						Title_Slide_x = 0;
						StopSoundMem(Clear_BGM);
						//	�A�j���[�V������������������
						status_ = STATUS_IDLE;
						next_anim = model_anim_idle;

						InitTime = 0;

						//  BGM���J�n�����邽�߂̕ϐ�
						Title_BGM_Start = true;
						Game_BGM_Start = false;
						Over_BGM_Start = false;
						Clear_BGM_Start = false;

						bgm_status = START_BGM;
					}
				}
			}
		}

		//  �v���C���[�𓮂��Ȃ�����
		player.move_juge = false;
		////  ��ɗ�����Ȃ��悤�ɂ���
		//player.pos_x++;
		over_time++;
		//            player.pos_y -= river_out_y;
		//  �v���C���[���M�ꂽ�Ƃ��ɐk����
		/* if(life.life_count <= 0) {
				if(player.pos_y <= -5) {
					player.pos_y = GetRand(-3);
				}
			}*/

			//  �~�j�}�b�v�p�̏���
		minimap.map_player_y = 680 + player.pos_z;

		//  ���C�g�̏���
	//    SetUseLighting(true);
		SetLightDirection({ -1.0f, -1.0f,-1.0f });
		//SetLightPosition(VGet(player.pos_x, player.pos_y + 10.0f, player.pos_z + 10.0f));


		// -----------------------------------------------------------------------------------------------------------------
		//  �S�[���������̏���
		// -----------------------------------------------------------------------------------------------------------------
		//	�}���̂��߂���Ł@��񂾂�����łق������߂��̍��W��ʂ����u�Ԃ̂�
		//if (player.pos_z == -599)
		//{
		//	bgm_status = CLEAR_BGM;
		//}


		//if(goal_line_x + 300 >= player.pos_x && goal_line_x - 300 <= player.pos_x && goal_line_z >= player.pos_z) {
		//    StopSoundMem(Game_BGM);
		//    //  �G�t�F�N�g�̍Đ�
		//    //        if(CheckHitKey(KEY_INPUT_SPACE)) {
		//    effect_congra_play = PlayEffekseer3DEffect(effect_congra);
		//    goal_anim          = true;
		//    goal_count++;

		//    //  �G�t�F�N�g�̈ʒu�̏�����
		//    SetPosPlayingEffekseer3DEffect(effect_congra_play, player.pos_x, player.pos_y, player.pos_z + 15);
		//    //        }
		//    if(goal_count >= 240) {
		//        //  ���̂܂܂��ƃS�[����������BGM������Ȃ����ߍ��W�������ɂ����Ă���
		//        player.pos_z = 50000;
		//        switch(bgm_status) {
		//        case SceneFrogger::OVER_BGM:
		//            PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
		//            bgm_status = -1;
		//            break;
		//        }

		//        goal = true;
		//        init = true;
		//    }
		//}
		////  ������
		//  ���C�t���Ȃ��Ȃ����Ƃ��ɏ��������s��
		if (life.life_over) {
			InitTime++;
			timer.time_clear = false;

			if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
				if (init) {
					//Game::Init();
					player.Init();
					wall.Init();
					timer.Init();
					score.Init();
					life.Init();
					ui.Init();
					camera.Init();
					ufo.Init();
					seculity.Init();
					minimap.Init();
					for (int i = 0; i < CAR_NUM; i++) {
						car_z[i] = CAR_Z[i];
					}
					car_x[0] = -50;
					car_x[1] = 30;
					car_x[2] = 90;
					car_x[3] = 60;
					car_x[4] = -100;
					for (int i = 0; i < 6; i++) {
						car_x_plus[i] = 1.5f;
					}
					for (int i = 0; i < WOOD_NUM; ++i) {
						int start_pos_x = 0;
						if (i >= 5) {
							start_pos_x = 150;
						}
						wood_x[i] = start_pos_x;
						wood_z[i] = WOOD_START_Z[i];
						wood_x_re[i] = GetRand(-150);
						wood_z_re[i] = WOOD_START_Z_Re[i];
					}
					car_dead = false;
					Respawn_Distance_z = 0.0f;
					river_dead = false;
					wood_safe = true;
					safe_stone_x = -90;
					safe_stone_z = -220;
					goal_line_x = 0;
					goal_line_z = 0;
					over_time = 0;
					river_out_y = 1;
					title = true;
					title_x = 0;
					title_blend = 0;
					title_blend_hiku = 3;
					game = false;
					goal = false;
					goal_anim = false;
					goal_count = 0;
					no_die = true;
					init = false;
					camera_x = 0.0f;
					camera_z = 0.0f;
					camera_y = 10.0f;
					//				camera_y = 15.0f;
					camera_y_radian = 5.0f;

					Title_Slide = 0;

					Title_Slide_x = 0;

					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
					InitTime = 0;

					//  BGM���J�n�����邽�߂̕ϐ�
					Title_BGM_Start = true;
					Game_BGM_Start = false;
					Over_BGM_Start = false;
					Clear_BGM_Start = false;

					bgm_status = START_BGM;



				}
			}
		}
		//	�J�����������ɖ��܂�Ȃ��悤�ɂ��邽�߂̏���
		/*if (camera_y + 6.0f < 15.0f)
		{
			camera_y = 15.0f;
		}*/
		if (camera.pos_z < -600 && player.pos_z >= 0.0f)
		{
			camera_y = 20.0f;
		}

		//if (camera_y >= 10.0f)
		//{
		//	camera_y -= 0.0025f;
		//}
	//	camera_y = 25.0f;

		//Change_camera_z = camera.pos_z;
		Change_camera_z = 0.0;
		//  �������͂����܂ł������牺�̓J�����̐ݒ�
		SetCameraPositionAndTarget_UpVecY(   //  �ŏI�I�ȃJ������Z���Wplayer.pos_z + 30.0f
			{ player.pos_x, 5.0f + camera_y  , player.pos_z + camera.pos_z },
			{ player.pos_x + camera_x, player.pos_y + camera_y_radian, player.pos_z + Change_camera_z });
		//  SetCameraPositionAndTarget_UpVecY({0.0f,5.0f,30.0f}, {0.0f,-180.0f,0.0f});
		SetupCamera_Perspective(60.0f * DegToRad);
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Game::Draw()
{ 
	//  ���H�̍쐬�i�ԍ��݁j
	if (game) {



		//MakeGraph(500, 100);
		//MakeScreen(500, 100, true);
		//  ���H�̔�����`��
		for (int i = 0; i < 4; i++) {
			DrawCube3D(
				{
					-300,
					-1,
					WHITE_LINE_1[i],
				},
				{ 300, 0.2f, WHITE_LINE_2[i] },
				WHITE,
				WHITE,
				TRUE);
		}
		DrawCube3D(
			{
				-300,
				-1,
				-89.0f,
			},
			{ 300, 0.2f, -91.0f },
			WHITE,
			WHITE,
			TRUE);

		// �����f���̕`��
		//    �v���C���[���f��
		MV1DrawModel(model_);
		for (int i = 0; i < CAR_NUM; i++) {
			MV1DrawModel(car_model[i]);
		}

		//  ���̕`��
		//	���ɏ����Ă��܂���UI���B���Ă��܂����ƂɂȂ�̂ŏ�ɔz�u
		DrawCube3D(
			{
				-300,
				-1.0f,
				500,
			},
			{ 300, -0.9f, -130 },
			GetColor(105, 105, 105),
			GetColor(105, 100, 105),
			TRUE);


		//	�X�e�[�W�̏���
		switch (stage_status)
		{
		case FIRST_STAGE:
		//	�S�[���̏ꏊ��ύX����
			goal_line_x = 0;
			goal_line_z = -130;




			//DrawCube3D({ -10, 0, -100 - 10 }, { 10, 10, -110 - 10 }, GetColor(255, 125, 125), GetColor(125, 0, 0), true);
			//DrawCone3D({ 0,25,-110 - 10 }, { 0,10,-110 - 10 }, 18, 64, GetColor(255, 255, 0), GetColor(255, 255, 0), true);
				//  �S�[����ʂ̕`��
			break;

		case SECOND_STAGE:
			goal_line_x = 0;
			goal_line_z = -600;


			//  UFO�X�e�[�W���n�܂�Ƃ킩��悤�ɂ��邽�߂̐�
			DrawCube3D({ wall.Wall_left_x, 0, -300 }, { wall.Wall_right_x, 1, -305 }, WHITE, WHITE, true);

			//  �Ԃ̕`��i���j

			//  �S�[���̕`��
			// DrawCube3D({goal_line_x + 300, 0, goal_line_z}, {goal_line_x - 300, 30, goal_line_z}, GREEN, GREEN, true);

			//  ��̍쐬�i���j
			DrawCube3D({ 300, -2, -130 }, { -600, -1, -280 }, BLUE, BLUE, TRUE);

			DrawCube3D({ 300,-20,-130 }, { -600,-1,-131 }, BLUE, BLUE, TRUE);

			//  ��̐^�񒆂ɒu���Ώ��̕`��
			//  �΂̍��W������-10����-90�@����-190����-220
			DrawCube3D({ safe_stone_x + 80, 1, safe_stone_z + 30 },
				{ safe_stone_x, 0, safe_stone_z },
				GetColor(105, 105, 105),
				GetColor(105, 105, 105),
				TRUE);

			//  �ۑ��̍쐬�i���j
			//  1�{��
			for (int i = 0; i < 5; i++) {
				DrawCube3D({ wood_x[i] + 100, -1, wood_z[i] + 15 },
					{ wood_x[i] - 100, 0, wood_z[i] },
					GetColor(255, 125, 0),
					GetColor(255, 125, 0),
					true);
				//  �t�����̊ۑ������l�ɗ���
				DrawCube3D({ wood_x_re[i] + 100, -1, wood_z_re[i] + 15 },
					{ wood_x_re[i] - 100, 0, wood_z_re[i] },
					GetColor(255, 125, 0),
					GetColor(255, 125, 0),
					true);
			}

			//  6�{��(5�{�ڂƓ�������)
			DrawCube3D({ wood_x[7] + 100, -1, wood_z[7] + 15 },
				{ wood_x[7] - 100, 0, wood_z[7] },
				GetColor(255, 125, 0),
				GetColor(255, 125, 0),
				true);
			//  6�{��
			DrawCube3D({ wood_x[9] + 100, -1, wood_z[9] + 15 },
				{ wood_x[9] - 100, 0, wood_z[9] },
				GetColor(255, 125, 0),
				GetColor(255, 125, 0),
				true);

			//  UFO�X�e�[�W���Ƃ킩��悤�ɏ���ΐF�ɂ���
			DrawCube3D({ 200, 0, -280 }, { -170, 0.5f, -440 }, GetColor(0, 255, 0), GetColor(0, 255, 0), true);

			//    DrawSphere3D(0,0,0,50.0f)

			//  DrawPolygon3D()
					//  UFO�̕`��
			MV1DrawModel(ufo_model);

			//	UFO�p�̉e��`��
			//DrawSphere3D({ ufo.pos_x,0.5f,ufo.pos_z }, 5.0f, 5.0f, BLACK, BLACK, true);
			//  Z���W-440�`459�̓Z�[�t�G���A
			DrawCube3D({ wall.Wall_left_x, -1, -440 },
				{ wall.Wall_right_x, 0, -450 },
				GetColor(0, 0, 0),
				GetColor(0, 0, 0),
				TRUE);

			//  �v�����X���[�̕`��
			MV1DrawModel(security_model);

			//        MV1DrawModel(coin_model);

				//  �S�[����ʂ̕`��
			if (goal&& goal_count == 2) {
				//		DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
				SetFontSize(40);
				DrawString(WINDOW_W / 3 + 110, WINDOW_H / 2 + 50, "�A��I�I", BLUE, true);
				DrawString(WINDOW_W / 3 + 110 + 3, WINDOW_H / 2 + 50, "�A��I�I", BLACK, true);

				DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "F�������Ă�����x�A��I", GetColor(0, 255, 0), true);
				DrawFormatStringF(WINDOW_W / 2 - 135, WINDOW_H - 115, GetColor(255, 255, 255), "����̃X�R�A��%d", score.score);

			}


			break;

		case THIRD_STAGE:

			break;

		case FOURTH_STAGE:

			break;

		case FIFTH_STAGE:

			break;
		}

		//  �S�[���̉Ƃ�`��
		DrawCube3D({ goal_line_x - 10, 0, goal_line_z + 10 }, { goal_line_x + 10, 10, goal_line_z - 10 }, GetColor(255, 125, 125), GetColor(125, 0, 0), true);
		DrawCone3D({ goal_line_x,25,goal_line_z }, { goal_line_x,10,goal_line_z }, 18, 64, GetColor(255, 255, 0), GetColor(255, 255, 0), true);




		//  �R�C���̕`��
		for (int i = 0; i < COIN_NUM; i++) {
			if (score.coin_swich[i]) {
				//                MV1DrawModel(coin_model);
				//VECTOR scale;
				//scale.x = 1.0f;
				//scale.y = 2.0f;
				//scale.z = 1.0f;
				//MV1SetScale(coin_models[i], scale);
				MV1DrawModel(coin_models[i]);
			}
		}
		//  �R�C���̕`��
		for (int i = 0; i < 5; i++) {
			if (score.coin_swich[i]) {
				//              DrawSphere3D({ score.coin_x[i], 3, score.coin_z[i] }, 3, 5, 5, GetColor(0, 255, 255), true);
			}
		}


		//  �S�[���̉Ƃ�`��
//DrawCube3D({ -10, 0, -600 - 10 }, { 10, 10, -625 - 10 }, GetColor(255, 125, 125), GetColor(125, 0, 0), true);
//DrawCone3D({ 0,25,-615 - 10}, { 0,10,-615 - 10 }, 18, 64, GetColor(255, 255, 0), GetColor(255, 255, 0), true);

//	���C�g�̈ʒu�̈ʒu���m���߂邽�߂ɋ��̂��o��
//	DrawSphere3D({ 1.0f, 1.0f,player.pos_z + 10.0f },5.0f,50.0f,RED,RED,true);




	//  �N���X�̕`��

	//  wall�̕`��
		wall.Draw();
		score.Draw();
		ufo.Draw();
		//  �^�C�}�[�̕`��
		timer.Draw();
		ui.Draw();
//		DrawFormatStringF(WINDOW_W / 2 - 135, WINDOW_H - 135, GetColor(255, 255, 255), "����̃X�R�A��%d", ufo_rampage);

		//if(ufo.ufo_standhing) {
		//    //  ����UFO�̍��W��\��
		//    DrawFormatString(WINDOW_W / 2, WINDOW_H / 2, GetColor(255, 255, 255), "x���W��%f", ufo.pos_x);
		//}
		////  ���Ńv���C���[�̍��W��\��
		//DrawFormatString(WINDOW_W / 2, WINDOW_H / 3, GetColor(255, 255, 255), "���W�A�����W��%f", seculity.radian);
		//DrawFormatString(WINDOW_W / 2, WINDOW_H / 4, GetColor(255, 255, 255), "z���W��%f", player.pos_z);
		//DrawFormatString(WINDOW_W / 2, WINDOW_H / 5, GetColor(255, 255, 255), "y���W��%f", player.pos_y);
		//  DrawString(WINDOW_W / 3, WINDOW_H - 100, "K�L�[�������Ɛ�X�e�[�W���΂��܂�", GetColor(255, 255, 255), true);
		if (timer.time_over) {
			DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 6.0f, 0, Time_Over_haikei_fire, true);
			DrawRotaGraph(WINDOW_W / 3, WINDOW_H / 2 + 50, 1.0f, 0, Time_Over_ilust_hansei, true);
			DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 3.0f, 0, Time_Over_ilust_sekkyou, true);

			DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2, "�{��ꂽ�B�B�B", WHITE, true);
			DrawString(WINDOW_W / 3, WINDOW_H / 2, "�{��ꂽ�B�B�B", RED, true);
			DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2 + 200, "F�������Ē��߂��A��I", GetColor(0, 0, 0), true);
			DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "F�������Ē��߂��A��I", GetColor(0, 255, 0), true);

			DrawFormatStringF(WINDOW_W / 2 - 100,
				timer.result_y / 2 + 50,
				GetColor(255, 255, 255),
				"����̃X�R�A��%d",
				score.score);
		}

		//  �c�@�̏o��
		life.Draw();
		minimap.Draw();

		//DrawFormatStringF(50, 80, GetColor(255, 255, 255), "�v���C��\X���W  %f", player.pos_x);
		//DrawFormatStringF(50, 120, GetColor(255, 255, 255), "�v���C��\X���W  %f", player.pos_z);

		//if(life.life_1) {
		//    //  �c��R�c�@
		//    DrawBox(life.life_x + 30, WINDOW_H - 10, life.life_x + 60, WINDOW_H - 40, GetColor(255, 255, 255), true);
		//    DrawBox(life.life_x + 80, WINDOW_H - 10, life.life_x + 110, WINDOW_H - 40, GetColor(255, 255, 255), true);

		//    DrawBox(life.life_x + 130, WINDOW_H - 10, life.life_x + 160, WINDOW_H - 40, GetColor(255, 255, 255), true);
		//}

		//  �R�C���i���j�̕`��
		//for(int i = 0; i < COIN_NUM;i++) {
		//    DrawCube3D(score.coin_x)
		//}hunterhunterjf
		//        DrawCube3D(0, 0, 5, 5, GetColor(255,0,0), TRUE);

		//  �^�C�g�����
		DrawBox(title_x, 0, title_x + WINDOW_W, WINDOW_H, GetColor(0, 0, 0), true);
		//  ���C�t�����ׂĂȂ��Ȃ����Ƃ�
		if (life.life_over) {
			//  �Q�[���I�[�o�[�̎d���ɂ���ă��U���g��ʂ�ύX����
			switch (over_status) {
			case CAR_OVER:
				//		DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(255, 0, 0), true);
				DrawString(WINDOW_W / 3 + 3, WINDOW_H / 2, "�Ԃ�瀂���ċA��Ȃ������A�A�A�A", BLACK, true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2, "�Ԃ�瀂���ċA��Ȃ������A�A�A", BLUE, true);
				DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2 + 200, "F�������ă^�C�g���֖߂�", GetColor(0, 0, 0), true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "F�������ă^�C�g���֖߂�", GetColor(0, 255, 0), true);

				//DrawFormatStringF(WINDOW_W / 2 - 100,
				//	WINDOW_H - 50,
				//	GetColor(255, 255, 255),
				//	"����̃X�R�A��%d",
				//	score.score);
				break;

			case RIVER_OVER:
				//                if(over_time >= 60) {
				DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 255), true);
				DrawRotaGraph(WINDOW_W / 4, WINDOW_H / 2 + 50, 1.0f, 0, River_Over_ilust, true);
				DrawRotaGraph(WINDOW_W - 200, WINDOW_H / 2 + 50, 1.0f, 0, River_Over_ilust_safe, true);

				DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2, "��ɓM��Ă��܂����B�B�B", BLACK, true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2, "��ɓM��Ă��܂����B�B�B", RED, true);

				DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2 + 200, "F�������Ē��߂��A��I", GetColor(0, 0, 0), true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "F�������Ē��߂��A��I", GetColor(0, 255, 0), true);

				DrawFormatStringF(WINDOW_W / 2 - 100,
					WINDOW_H - 50,
					GetColor(255, 255, 255),
					"����̃X�R�A��%d",
					score.score);
				break;
			}
		}
		if (goal && goal_count == 1) {
			//		DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
			SetFontSize(40);
			DrawString(WINDOW_W / 3 + 110, WINDOW_H / 2 + 50, "�A��I�I", BLUE, true);
			DrawString(WINDOW_W / 3 + 110 + 3, WINDOW_H / 2 + 50, "�A��I�I", BLACK, true);

			DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "F�������Ď��̃X�e�[�W�ցI", GREEN, true);
			DrawFormatStringF(WINDOW_W / 2 - 135, WINDOW_H - 115, BLUE, "����̃X�R�A��%d", score.score);
		}



		//	�X�e�[�W�ύX�p�̃J�b�g�C���̕`��
		if (stage_change)
		{
			DrawBox(0 - Title_Slide_x, 0, WINDOW_W - Title_Slide_x, WINDOW_H, BLACK, true);
		}

	}
	//  �^�C�g����ʂ̍쐬�i���j
	if (title) {

		
			DrawRotaGraph(WINDOW_W / 2 - Title_Slide_x, WINDOW_H / 2 - 50, 7.5f, 0, Title_Town, true);
//			DrawRotaGraph(Title_Player_x - Title_Slide_x, Title_Player_y + Title_Ufo_y, 0.5f, 0, Title_Player, true);
			//																						������łӂ蕝�ύX
			DrawRotaGraphF(Title_Player_x - Title_Slide_x, Title_Player_y - fabs( sinf( Title_player_y_gravity ) ) * 5.0f, 0.5f, 0, Title_Player, true);
			//DrawRotaGraph(Title_Player_x - Title_Slide_x, WINDOW_H - 120 + Title_Ufo_y, 0.5f, 0, Title_Player, true);

			DrawRotaGraph(300 - Title_Slide_x, WINDOW_H - 200, 0.7f, 0, Title_House, true);

			DrawRotaGraph(Title_Ufo_x - Title_Slide_x, Title_Ufo_y, 0.25f, Title_Ufo_rad, Title_Ufo, true);
			//        DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), true);
			SetFontSize(100);
			DrawString(WINDOW_W / 3 + 90 - Title_Slide_x, WINDOW_H / 2 - 100, "Go Home", GetColor(0, 0, 0), true);
			DrawString(WINDOW_W / 3 + 85 - Title_Slide_x, WINDOW_H / 2 - 100, "Go Home", GetColor(255, 255, 0), true);

			SetFontSize(40);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_blend);
			DrawString(WINDOW_W / 3 - Title_Slide_x + 5,
				WINDOW_H / 2 + 200,
				"SPACE�L�[�������ċA��J�n�I",
				GetColor(0, 0, 0),
				true);

			DrawString(WINDOW_W / 3 - Title_Slide_x,
				WINDOW_H / 2 + 200,
				"SPACE�L�[�������ċA��J�n�I",
				GetColor(255, 255, 0),
				true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			if (PlayCount_Switch) {
				DrawFormatString(WINDOW_W - 100, WINDOW_H - 50, GetColor(0, 0, 0), "%d", PlayCount, true);
			}
			
			//
	//	tutorial.Draw();
	}
	if (title_rule) {
		int x = 1250;
		DrawString(WINDOW_W / 2 - 350 - Title_Slide_x + 5 + x,
			WINDOW_H / 2 - 100,
			"�������Q�����I���ʂɋA������x���x���I\n��Ȃ����ǋߓ���˂��؂낤�I",
			GetColor(0, 0, 0),
			true);
		DrawString(WINDOW_W / 2 - 350 - Title_Slide_x + x,
			WINDOW_H / 2 - 100,
			"�������Q�����I���ʂɋA������x���x���I\n��Ȃ����ǋߓ���˂��؂낤�I",
			GetColor(255, 255, 0),
			true);
		DrawString(WINDOW_W / 3 - Title_Slide_x + x,
			WINDOW_H / 2 + 200,
			"ENTER�L�[�������ċA��J�n�I",
			GetColor(255, 255, 0),
			true);
	}

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Game::Exit()
{
	MV1DeleteModel(model_);
	for (int i = 0; i < CAR_NUM; i++) {
		MV1DeleteModel(car_model[i]);
	}
	for (int i = 0; i < COIN_NUM; i++) {
		MV1DeleteModel(coin_models[i]);
	}
}

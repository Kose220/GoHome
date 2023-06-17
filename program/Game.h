#pragma once

//#define WINDOW_W	1500
//#define WINDOW_H	750
#define WINDOW_W	1280
#define WINDOW_H	720

#define BLACK   GetColor(0, 0, 0)
#define WHITE   GetColor(255, 255, 255)
#define RED     GetColor(255, 0, 0)
#define GREEN   GetColor(0, 255, 0)
#define BLUE    GetColor(0, 0, 255)
#define YELLOW  GetColor(255, 255, 0)
#define PINK    GetColor(255, 0, 255)
#define SKYBLUE GetColor(0, 255, 255)

constexpr int COIN_NUM = 5;   //  �R�C���̖���


struct Coin
{
    float x;
    float y;
    float z;
};

class Game
{
private:
    void PlayerMove();

    void PlayerDie();
    void PlayerDieToCar();
    void PlayerDieToRiver();

public:
    //  �v���C���[�ɓ����Ăق����ʒu���w�肷��ϐ�
    //float move_z;
    //float move_x;
    ////  �����蔻��������Ȃ����W�����v���ł���悤��
    //float move_y;
    ////  �v���C���[�̍��W
    //float pos_x;
    //float pos_y;
    //float pos_z;

    ////  �L�����N�^�[�̓������󂯕t���邩�ǂ������肷��ϐ�
    //bool move_juge;

    ////  �v���C���[�̌�����ς���ϐ�
    //float radian_y;

    //  �Q�[�����X�^�[�g���^�C�g�������ɂ��炷���߂̕ϐ�
    int Title_Slide;
    int Title_Slide_x;

    //  �Ԃ𓮂������߂̕ϐ�
    float car_x[6];
    float car_z[6];

    //  �ۑ��̕ϐ�
    float wood_x[10];
    float wood_z[10];
    //  ���Ε������痬��Ă���ۑ��̕ϐ�
    float wood_x_re[10];
    float wood_z_re[10];

    //  ���`�悷��i���j
    float river_x;
    float river_y;

    //  �A���œ����Ȃ��悤�ɂ���
    //    float time;

    //  �v���C���[����Q���ɂԂ������Ƃ����f����ϐ�(�ԂƂԂ�������)
    bool car_dead;

    //  �Ԃ�

    //  ��ɗ������ۂ̏���
    bool river_dead;

    //  �ۑ��̏�ɏ���Ă�ۏ�L��river_dead���������Ȃ��悤�ɂ��邽�߂̕ϐ�
    bool wood_safe;

    //  �^�񒆂̂ق��̃Z�[�t�G���A�i�΂́j���W
    float safe_stone_x;
    float safe_stone_z;

    //  ���ȏ�̉z������N���A�ɂȂ邽�߂̍��W�ϐ�
    float goal_line_x;
    float goal_line_z;

    //  �Q�[���I�[�o�[��ʂ��x��ďo�Ă���悤�ɂ��邽�߂̕ϐ�
    float over_time;

    //��ɓM�ꂽ�Ƃ��Ƀv���C���[���㉺�ɓM��Ă���悤�Ɍ����鏈��
    float river_out_y;

    //  �R�C���p�̕ϐ�
    float coin_z;
    float coin_x;

    int coin_models[5];

    //  �R�C���̊p�x�i����Ă���悤�Ɍ�����悤�ɂ���悤�́j�ϐ�
    int Coin_Rota_x;


    //  �S�[�����W��������p�̕ϐ�
    int goal_adjustment;

    //  �Ԃ𓮂������߂̕ϐ�
    float car_x_plus[6];


    //  �S�[���������ǂ������肷��ϐ�
    bool goal;

    //  �S�[�����̃A�j���[�V�����p�̔���p�ϐ�
    bool goal_anim;

    //  �S�[�������ۂɃv���C���[����яI����Ă��烊�U���g��ʂɔ�Ԃ悤�ɂ��邽�߂̎��Ԃ��Ƃ�J�E���g�ϐ�
    int goal_count;

    //  �^�C�g����ʂ̕ϐ�
    bool title;

    //  �^�C�g���̎��̃y�[�W�̕�������p�̕ϐ�
    bool title_rule;

    //  �^�C�g���̕������ڂ₩���p�̕ϐ�
    int title_blend;
    int title_blend_hiku;

    //  �^�C�g����ʂ����ɃX���C�h���邽�߂̕ϐ�
    float title_x;

    //  �Q�[���{�҂��Ǘ�����ϐ�
    bool game;

    //  ����ł��܂������̏������p�̕ϐ�
    bool init;

    //  �J�����̌�����ς��邽�߂̕ϐ�
    float camera_x;
    float camera_z;
    //  �J������Y���W�p�̕ϐ�(����)
    float camera_y;
    float camera_y_radian;

    // �J�����ŃS�[��������p�̍��W�ϐ�
    //    float goal_pos_x;
    float goal_pos_z;

    //  �Q�[���{�҂��n�܂����^�C�~���O�ŃJ�����^�[�Q�b�g���S�[������v���C���[�ɕς��邽�߂̕ϐ�
    //    float Chenge_camera_x;
    float Change_camera_z;

    //  ���X�|�[���n�_�Ƃ̋�����}�邽�߂̕ϐ�
    float Respawn_Distance_z;

    //  BGM�p�̕ϐ�
    int Title_BGM;
    int Game_BGM;
    int Over_BGM;
    int Clear_BGM;

    //  SE�p�̕ϐ�
    //  �����炬SE
    int River_SE;
    //  �����炬�̉��ʕύX�p�̕ϐ�;
    int River_SE_Volume;
    //  �v���C���[�Ɛ�̋����𑪂邽�߂̕ϐ�
    float River_distance;
    //  �ԂɂЂ��ꂽ����SE
    int Car_Clash_SE;
    //  �Ԃ̃N���N�V������SE
    int Car_Clacshon_SE;
    //  �Ԃ̒ʉ߂�SE
    int Car_Slue_SE;
    //  �ԂɂЂ��ꂽ��̃T�C������SE
    int Silen_SE;
    //  ��ł��ڂꂽ����SE
    int River_Die_SE;

    //  �A�j���[�V�����̕ύX�̒��߂̕ϐ�
    float anim_time;

    ////  �����Ă���Ƃ��̕ϐ�
    //bool run;
    ////  �~�܂��Ă���Ƃ��̕ϐ�
    //bool idle;
    ////  �ԂɂԂ������Ƃ��̃A�j���[�V����
    //bool car_clash;
    ////  ��ɓM�ꂽ�Ƃ��̃A�j���[�V�����̔���ϐ�
    bool river_die;

    bool car_die;

    //  UFO�ɂ����ꂽ�����Ƀ��X�|�[���n�_�܂ŋA���Ă�r���͖��G��Ԃɂ������̂ł���p�̕ϐ�
    bool no_die;

    //  UFO�ɘA�ꋎ���Ă�i�r���j�̃A�j���[�V�����p�̕ϐ�
    bool player_ufo_out;

    //  �v���C���[��UFO�߂܂����ۖ\��邽�߂̕ϐ� 
    //  �Ȃ�炩��KEY��A�ł��邱�ƂŔ����邻�̂��߂̃J�E���g�ϐ���p��
    int ufo_rampage;
    //  �A�ł𒷉����őΏ�����Ȃ����߂̕ϐ�
    int consecutive_blocking;
    //  UFO�ɂ��܂����ۂ̃A�j���[�V�������h��������Ԃɖ߂����߂̕ϐ�
    bool is_ufo_anim;

    //  �X�e�[�W�ύX�p�̉�ʂ��o�����߂̕ϐ�
    bool stage_change;


    //�@BGM�J�n�p�̕ϐ�
    bool Title_BGM_Start;
    bool Game_BGM_Start;
    bool Over_BGM_Start;
    bool Clear_BGM_Start;

    //  �^�C�g���p�̃C���X�g�i�摜�j�̕ϐ�
    int Title_Player;
    int Title_Ufo;
    int Title_Town;
    int Title_House;

    //  �^�C�g���̃C���X�g�p�̕ϐ�
    float Title_Player_x;
    float Title_Player_y;
    float Title_Ufo_x;
    float Title_Ufo_y;
    //  �摜�̍��W�𑫂��p�̕ϐ�
    float Title_Ufo_x_plus;
    float Title_Ufo_y_plus;

    //  UFO�̊p�x��ύX���邽�߂̕ϐ�
    float Title_Ufo_rad;
    float Title_Ufo_rad_plus;

    //  �v���C���[��UFO�ɂ��܂������ǂ������肷�邽�߂̕ϐ�
    bool Player_Catch;

    //  �Q�[���I�[�o�[���̂��炤�Ɨp�̕ϐ�
    int Time_Over_ilust_hansei;
    int Time_Over_ilust_sekkyou;
    int Time_Over_haikei_fire;

    int River_Over_ilust;
    int River_Over_ilust_safe;


    int next_anim = -1;        // ���̃A�j���[�V�����p���f��

    //  ���ȏ�Ń^�C�g���֖߂�悤�ɂ��Ă���
    int InitTime;

    //  �v���C�����J�E���g���邽�߂̕ϐ�
    int PlayCount;
    bool PlayCount_Switch;


    void Init();                //!< ������
    void Update();   //!< �X�V
    void Draw();                //!< �`��
    void Exit();                //!< �I��
    void GUI();                 //!< GUI�\��

private:
    int model_ = -1;   //!< MV1���f���n���h��
    int model_anim_run = -1;   //!< MV1���f���n���h��
    int model_anim_idle = -1;
    int model_anim_car_clash = -1;
    int model_anim_river_die = -1;
    int model_anim_stand_up = -1;   //  �v���C���[�����X�|�[�������ۂɂ���A�j���[�V����
    int model_anim_happy_dance = -1;
    int model_anim_security_dameg = -1;
    int model_anim_security_stand_up = -1;
    int model_anim_dead_cry = -1;
    int model_anim_ufo_Out = -1;


    //  �v�����X���[�̃A�j���[�V�����̏�����
    //  �x�����i�v�����X���[�j�̃��f��
    int security_model;
    int security_anim_idle = -1;
    int security_anim_move = -1;
    int security_anim_attack = -1;

    //  �v�����X���[�������Ă��邩���肷�邽�߂̕ϐ�
    bool security_move_juge;

    //  �A�j���[�V�������f���𓝊�����p�̕ϐ�
    // int anim_managemen;

    //  ��Ԃ̕ϐ�
    //const int STATE_IDLE         = 0;
    //const int STATE_RUN          = 1;
    //const int STATE_CAR_DAMEGE   = 2;
    //const int STATE_RIVER_DAMEGE = 3;
    enum BGM_STATUS
    {
        START_BGM = 0,   //  �^�C�g��BGM
        MAIN_BGM,        //  �Q�[���{��BGM
        OVER_BGM,        //  �Q�[���I�[�o�[BGM
        CLEAR_BGM        //  �N���ABGM

    };
    enum STAGE_STATUS
    {
        FIRST_STAGE = 0,    //  �X�e�[�W�̕ϐ�
        SECOND_STAGE,
        THIRD_STAGE,
        FOURTH_STAGE,
        FIFTH_STAGE



    };
    int bgm_status = START_BGM;
    int stage_status = FIRST_STAGE;
    enum STATUS
    {
        STATUS_IDLE = 0,       // �ҋ@
        STATUS_MOVE,           // �ړ��i����j
        STATUS_CAR_DAMAGE,     // �_���[�W�i�ԁj
        STATUS_RIVER_DAMAGE,   // �_���[�W�i��j
        STATUS_STAND_UP,       //  �N���オ��悤
        STATUS_HAPPY_DANCE,
        STATUS_SECURITY_DAMEGE,
        STATUS_SECURITY_STAND_UP,
        STATUS_DEAD_CRY,        //  �Q�[���I�[�o�[�ɂ��߂��ރA�j���[�V����
        STATUS_UFO_OUT          //  �v���C���[��UFO�ɂ������ۂ̃A�j���[�V����
    };
    int status_ = STATUS_IDLE;   // ��Ԃ��Ǘ�����

    //  ��ł��ڂꂽ���Ԃň����ꂽ�������𔻒肷��p
    enum GAMEOVER
    {
        CAR_OVER = 0,   //  �Ԃň����ꂽ���p
        RIVER_OVER      //  ��ł��ڂꂽ���p

    };
    int over_status = 0;   //  �Ǘ��p
                           //  �������邽�߂̕ϐ�

    int security_status = SECULITY_IDLE;

    enum SECULITY_ACTION_JUGE
    {
        SECULITY_IDLE = 0,
        SECULITY_MOVE,
        SECULITY_ATTACK

    };
    //  int seculity_status_ = SECULITY_IDLE;

    int Seculity_Action_status = SECULITY_IDLE;

    int   seculity_anim_index = -1;
    float seculity_anim_max_frame = -1;   // �A�j���[�V�����̍ő�t���[����

    float Seculity_Anim_frame = -1;
    float Seculity_Anim_frame_speed = 1.0f;

    //  �����Ă��邩����ł��邩���肷��悤�ȕϐ�
    bool live;
    bool dead;
    //  �A�j���[�V�����p�̕ϐ�
    int   anim_index = -1;   // ���݂̃A�j���[�V�����̃C���f�b�N�X
    float anim_max_frame = -1;   // �A�j���[�V�����̍ő�t���[����
    float anim_frame = -1;   // ���݂̃A�j���[�V�����̍Đ��t���[��
    float anim_frame_speed = 1.0f;

    //  �v�����X���[�p�̃A�j���[�V�����ϐ�

    float security_anim_time;

    //  �^�C�g���L�����N�^�[�������Ă��銴���̓�����t���������߂̕ϐ�

    float Title_player_y_gravity;

    //  ���`�悷��悤�ȕϐ�
    int skyBox;

    //int   anim_run = 0;   //  ����A�j���[�V����
    //float anim_run_frame;
    //int   anim_run_max;
    ////  �A�j���[�V�����̖߂�l�p�̕ϐ�
    //int run_index;
    ////  �����~�܂��Ă���Ƃ��̃A�j���[�V�����ϐ�
    //int   anim_idle = 0;
    //float anim_idle_frame;
    //int   anim_idle_max;
    ////  idle�̖߂�l
    //int idle_index;

    ////  �ԂɂԂ������ۂ̃A�j���[�V�����̖߂�l
    //int car_clash_index;

    ////  �ԂɂԂ������Ƃ��̃A�j���[�V�����ϐ�
    //int   anim_car_clash = 0;
    //float anim_car_clash_frame;
    //int   anim_car_clash_max;

    ////  ��ɓM�ꂽ�Ƃ��̃A�j���[�V�����ϐ�

    //int   river_die_index;
    //int   anim_river_die = 0;
    //float anim_river_die_frame;
    //int   anim_river_die_max;

    //  UFO�p�̃��f��
    int ufo_model;

    //  �Ԃ̃��f���p�ϐ�
    int car_model[5];

    //  �X�R�A�̃R�C���p�̉摜�ϐ�
    int  coin_model;
    Coin coin_pos[COIN_NUM];

    //  �G�t�F�N�g
    //  �S�[�������ۂ̉ԉ΂̃G�t�F�N�g
    int effect_congra;

    //  �G�t�F�N�g�̍Đ��n���h��
    int effect_congra_play = -1;
};


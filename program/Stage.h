#pragma once

//  �X�e�[�W�쐬�p�̃w�b�_�[
class Stage
{
public:
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

        //  �^�񒆂̂ق��̃Z�[�t�G���A�i�΂́j���W
    float safe_stone_x;
    float safe_stone_z;

    //  ���ȏ�̉z������N���A�ɂȂ邽�߂̍��W�ϐ�
    float goal_line_x;
    float goal_line_z;


    //  �X�e�[�W�ύX�p�̕ϐ�
    enum STAGE_STATUS
    {
        FIRST_STAGE = 0,    //  �X�e�[�W�̕ϐ�
        SECOND_STAGE,
        THIRD_STAGE,
        FOURTH_STAGE,
        FIFTH_STAGE



    };
    //  �X�e�[�W����̕ϐ�
    int stage_status = FIRST_STAGE;

    void Init();
    void Update();
    void Draw();
    void Exit();

};
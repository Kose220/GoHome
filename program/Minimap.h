#pragma once
class Minimap
{
public:

    //  �~�j�}�b�v��Y���W�p�ϐ�
    float map_y;
    //  �~�j�}�b�v�v���C���[�p�̕ϐ�
    float map_player_y;

    //  �l�Y�~�̃A�C�R���p�̕ϐ�
    int map_icon_player;
    int map_icon_dead;

    //  �~�j�}�b�v�̃A�C�R���̐F��ς��邽�߂̕ϐ�
    bool map_icon_switch;

    void Init();
    void Update();
    void Draw();
    void Exit();

};
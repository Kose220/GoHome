#pragma once

class Player
{
    // Kanamaru Comment
    //  ネストを浅くするための関数化
private:
    bool IsRevivaled() const;   // 復活しきったかどうか
    void Move();                // 移動
    void MoveBack();            // 後ろへ移動
    void MoveFront();           // 前へ移動
    void MoveLeft();            // 左へ移動
    void MoveRight();           // 右へ移動

public:
    float move_z;
    float move_x;

    float move_y;

    float pos_x;
    float pos_y;
    float pos_z;

    float pos_x_copy;
    float pos_z_copy;

    //  プレイヤーの動く大きさを管理する用の変数
    float move;

    bool anim_juge;

    bool move_juge;

    float radian_y;

    float time;

    //  プレイヤーが死んで復活する判定
    bool player_Revival;

    //  プレイヤーが復活しきったら動くことを許可する変数
    bool Revival_move;

    float anim_time;

    bool security_attack;

    float vel;

    float acc;

    void Init(); 
    void Update(); 
    void Draw();  
    void Exit();
};

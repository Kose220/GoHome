#include "DxLib.h"
#include "Player.h"
#include "Score.h"
#include "Timer.h"

// Kanamaru Comment
//  このグローバル変数使っていますか？
//  Game.cppにある変数とかぶってます
Score player_score;
Timer player_time;

// Kanamaru Comment
//  ネストを浅くするための関数化
bool Player::IsRevivaled() const
{
    if (Revival_move != true)
        return false;

    if (move_juge != true)
        return false;

    if (time < 30)
        return false;

    return true;
    //return Revival_move == true && move_juge == true && time >= 30;
}

void Player::Move()
{
    if(CheckHitKey(KEY_INPUT_S)) {
        MoveBack();
    }
    if(CheckHitKey(KEY_INPUT_W)) {
        MoveFront();
    }
    if(CheckHitKey(KEY_INPUT_A)) {
        MoveLeft();
    }
    if(CheckHitKey(KEY_INPUT_D)) {
        MoveRight();
    }
}

void Player::MoveBack()
{
    move_z += move;
    time      = 0;
    radian_y  = 380.0f;
    anim_time = 0;
    anim_juge = true;
}

void Player::MoveFront()
{
    move_z -= move;
    time      = 0;
    radian_y  = 0.0f;
    anim_time = 0;
    anim_juge = true;
}

void Player::MoveLeft()
{
    move_x += 20;
    time      = 0;
    radian_y  = 80.0f;
    anim_time = 0;
    anim_juge = true;
}

void Player::MoveRight()
{
    move_x -= 20;
    time      = 0;
    radian_y  = 190.0f;
    anim_time = 0;
    anim_juge = true;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void Player::Init()
{
    move_x = 10.0f;
    move_y = 1.0f;
    move_z = 20.0f;
    //    -２８０以降がUFO後で消す

    //  川の直前
    // move_z = -460.0f;

    //    move_z = -120.0f;
    pos_x = 10.0f;
    pos_y = 1.0f;
    //    pos_z = 20.0f;
    //  ゴール直前
    pos_z = 20.0f;
    //pos_z = -460.0f;

    //  プレイヤーの移動量の変数
    move = 20.0f;

    //  動いていいか判定する
    move_juge = false;
    //  アニメの判定をする
    anim_juge = false;

    radian_y = 0;

    time = 0.0f;

    player_Revival = false;
    //  復活中に動けないようにするための変数
    Revival_move   = true;
    //  プロレスラーに攻撃された直後すぐに攻撃されないようにするための変数
    security_attack = false;

    vel = 0;
    acc = -0.5;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void Player::Update()
{
    pos_x_copy = pos_x;
    pos_z_copy = pos_z;
    //  キーを押した瞬間一瞬で動いてしまわないようにmove変数を挟む
    if(move_z >= pos_z) {
        pos_z++;
    }
    if(move_z <= pos_z) {
        pos_z--;
    }
    if(move_x >= pos_x) {
        pos_x++;
    }
    if(move_x <= pos_x) {
        pos_x--;
    }
    if(move_y > pos_y) {
        pos_y++;
    }
    if(move_y < pos_y) {
        pos_y -= 1.0f;
    }

    //  デフォルトはtrue復活中の上から降ってきているときは動けなくする
    //if(pos_z == 20.0f) {
    //    player_Revival = true;
    //}
    //if(pos_y >= 0.5f) {
    //    pos_y -= 0.1f;
    //    player_Revival = false;
    //}

    //  動いた時のアニメーションを動かす変数
    //  常にオフにして置き動いた瞬間の一コマのみtrueにする
    anim_juge = false;

    if (pos_z <= -740)
    {
        pos_z = -740 + 1;
    }

    //  プレイヤーは復活しきったら動けるようにする
    if(IsRevivaled()) {
        Move();
    }


    //  タイトルから始まった瞬間に待機アニメーションに入るためにする
    if (CheckHitKey(KEY_INPUT_RETURN)) {
        anim_juge = true;
    }
    //  プレイヤーが一定以上後ろに行かないようにするための処理
    if (pos_z >= 20.0f)
    {
        pos_z = 20.0f;
    }


}

//---------------------------------------------------------------------------------
//!　描画
//---------------------------------------------------------------------------------
void Player::Draw()
{
}

//---------------------------------------------------------------------------------
//!	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}

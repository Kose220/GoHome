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

char KeyBuffer[256];
int KeyFrame[256];
int MouseLeftFrame;
int MouseRightFrame;

int NowMouseX;
int NowMouseY;
int BeforeMouseX;
int BeforeMouseY;

//---------------------------------------------------------------------------------
//	WinMain
//---------------------------------------------------------------------------------
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	int Time;

	SetOutApplicationLogValidFlag( FALSE );
	ChangeWindowMode( FALSE );
	SetMainWindowText( "Go Home" );
	SetBackgroundColor( 100, 100, 100 );

	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );

	SetGraphMode( WINDOW_W, WINDOW_H, 32 );

	SetUseDirect3DVersion( DX_DIRECT3D_9 );

	if( DxLib_Init() == -1 )
		return -1;
	// Effekseer�̏�����
	if (Effekseer_Init(8000) == -1) {
		DxLib_End();
		return -1;
	}
	//
	// ���C�e�B���O�̌v�Z�����Ȃ��悤�ɂ���
	//SetUseLighting(FALSE);
	//SetLightEnable(FALSE);
	//ChangeLightTypePoint(VGet(0.0f, 0.0f, 0.0f), 2000.0f, 0.0f, 0.002f, 0.0f);


	// Effekseer�Ή�
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetDrawScreen( DX_SCREEN_BACK );
	SetTransColor( 255, 0, 255 );
	srand( GetNowCount() % RAND_MAX );

	for( int i = 0; i < 256; i++ ){
		KeyFrame[i] = 0;
	}
	MouseLeftFrame = 0;
	MouseRightFrame = 0;

	SetCameraNearFar( 0.1f, 3000.0f );
	SetupCamera_Perspective( TO_RADIAN( 45.0f ) );

	Game* game = new Game();
	game->Init();

	SetUseZBuffer3D( TRUE ) ;
	SetWriteZBuffer3D( TRUE ) ;

	while( TRUE )
	{
		Time = GetNowCount();
		ClearDrawScreen();

		GetHitKeyStateAll( KeyBuffer );

		for( int i = 0; i < 256; i++ ){
			if( KeyBuffer[i] )	KeyFrame[i]++;
			else				KeyFrame[i] = 0;
		}

		if( CheckMouseInput( MOUSE_INPUT_LEFT ) )	MouseLeftFrame++;
		else										MouseLeftFrame = 0;

		if( CheckMouseInput( MOUSE_INPUT_RIGHT ) )	MouseRightFrame++;
		else										MouseRightFrame = 0;

		NowMouseX = GetMouseX();
		NowMouseY = GetMouseY();

		Effekseer_Sync3DSetting();
		game->Update();
		UpdateEffekseer3D();

		game->Draw();
		DrawEffekseer3D();


		BeforeMouseX = NowMouseX;
		BeforeMouseY = NowMouseY;

		ScreenFlip();
		while( GetNowCount() - Time < 17 ){}
		if( ProcessMessage() )	break;
		if( CheckHitKey( KEY_INPUT_ESCAPE ) )	break;
	}

	game->Exit();

	Effkseer_End();
	DxLib_End();
	return 0;
}

//---------------------------------------------------------------------------------
//	�L�[�������ꂽ�u�Ԃ��擾����
//---------------------------------------------------------------------------------
bool PushHitKey( int key )
{
	if( KeyFrame[key] == 1 ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�}�E�X��������Ă��邩���擾����
//---------------------------------------------------------------------------------
bool CheckMouseInput( int button )
{
	if( GetMouseInput() & button ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�}�E�X�������ꂽ�u�Ԃ��擾����
//---------------------------------------------------------------------------------
bool PushMouseInput( int button )
{
	if( button & MOUSE_INPUT_LEFT ){
		if( MouseLeftFrame == 1 ){
			return true;
		}
	}
	if( button & MOUSE_INPUT_RIGHT ){
		if( MouseRightFrame == 1 ){
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	�}�E�X�̍��W���擾����
//---------------------------------------------------------------------------------
int GetMouseX()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint( &mouse_x, &mouse_y );
	return mouse_x; 
}
int GetMouseY()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint( &mouse_x, &mouse_y );
	return mouse_y;
}
//---------------------------------------------------------------------------------
//	�}�E�X�̈ړ��ʂ��擾����
//---------------------------------------------------------------------------------
int GetMouseMoveX()
{
	return NowMouseX - BeforeMouseX;
}
int GetMouseMoveY()
{
	return NowMouseY - BeforeMouseY;
}

//float DegToRad = 0.017453293f;         //!< Degree��Radian �ϊ��W��

//---------------------------------------------------------------------------------
//	�x�����W�A���ɕϊ�����֐�
//---------------------------------------------------------------------------------
float TO_RADIAN( float degree )
{
	return degree * 3.14159265f / 180.0f;
}
//---------------------------------------------------------------------------------
//	���W�A����x�ɕϊ�����֐�
//---------------------------------------------------------------------------------
float TO_DEGREE( float radian )
{
	return radian * 180.0f / 3.14159265f;
}
//---------------------------------------------------------------------------------
//	�w�y�����ɉ~��`�悷��
//---------------------------------------------------------------------------------
void DrawCircle3D_XZ( Vector3 center, float radius, int color, bool fill )
{
	VECTOR pos1;
	VECTOR pos2;
	for( int i = 0; i < 36; i++ ){
		pos1.x = center.x + radius * sinf( TO_RADIAN( i * 10.0f ) );
		pos1.y = center.y;
		pos1.z = center.z + radius * cosf( TO_RADIAN( i * 10.0f ) );

		pos2.x = center.x + radius * sinf( TO_RADIAN( ( i + 1 ) * 10.0f ) );
		pos2.y = center.y;
		pos2.z = center.z + radius * cosf( TO_RADIAN( ( i + 1 ) * 10.0f ) );

		if( fill ){
			DrawTriangle3D( center.VGet() ,pos1, pos2, color, TRUE );
		}else{
			DrawLine3D( pos1, pos2, color );
		}
	}
}

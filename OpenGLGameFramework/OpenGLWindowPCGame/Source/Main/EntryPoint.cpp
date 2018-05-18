//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_
#include <OpenGLResourceLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_

#ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_
#include <WindowsAPIInputLib.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_

#ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_
#include <OpenALSoundLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_

#ifndef _INCLUDE_GUARD_GAME_H_
#include "../Application/Game/Game.h"
#endif	// #ifndef _INCLUDE_GUARD_GAME_H_



//==================================================================================================================================
// �O���[�o���ϐ�
//==================================================================================================================================

// ���C���N���X
static NS_OpenGLWindowPCGame::BaseApplication* g_pGame = nullptr;



//==================================================================================================================================
// �֐��v���g�^�C�v�錾
//==================================================================================================================================

// �f�B�X�v���C�R�[���o�b�N�֐�
void DISPLAY_CALLBACK();

// �A�C�h���R�[���o�b�N�֐�
void IDLE_CALLBACK();

// exit�֐��ɂ��I������
void AtExit1();



int main( int argc, char *argv[] ) 
{
	// �I�������̊֐���o�^
	atexit( AtExit1 );



	// GLUT��������
	glutInit( &argc, argv ); 

	// �f�B�X�v���C���[�h��������
	glutInitDisplayMode( GLUT_DOUBLE );

	// �E�B���h�E�̈ʒu��������
	glutInitWindowPosition( 0, 0 );

	// �E�B���h�E�̃T�C�Y��������
	glutInitWindowSize( 800, 450 );
//	glutInitWindowSize( 1280, 720 );

	// �E�B���h�E�𐶐�
//	glutCreateWindow( "OpenGLGame" );
	glutCreateWindow( "Game" );



	// �`��֐��̃R�[���o�b�N�֐��o�^
	glutDisplayFunc( DISPLAY_CALLBACK );

	// �A�C�h���֐��̃R�[���o�b�N�֐��o�^
	glutIdleFunc( IDLE_CALLBACK );



	// OpenAL�̏�����
//	NS_Sound::InitializeOpenAL();



	// �Q�[���N���X�𐶐�
	g_pGame = new NS_OpenGLWindowPCGame::Game;

	// �Q�[���̏���������
	g_pGame->Initialize();



	// ���C�����[�v
	glutMainLoop();



	// �Q�[���N���X���L��Δj������
	if ( POINTER_CHECK( g_pGame ) ) 
	{
		// �I������
		g_pGame->Finish();

		SAFE_DELETE( g_pGame );
	}



	return 0;
}



void DISPLAY_CALLBACK() 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( g_pGame );



	// �Q�[���̕`�揈��
	g_pGame->Display();



	// �o�b�t�@���X���b�v
	glutSwapBuffers();
}



void IDLE_CALLBACK() 
{
	// �L�[�{�[�h�̓��͏�Ԃ̍X�V
	NS_Input::NS_Keyboard::UpdateKeyState();

	

	// �w��̓��͂��L��ΏI��
	if ( NS_Input::NS_Keyboard::GetKeyDown( VK_ESCAPE ) ) { exit( 0 ); return; }



	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( g_pGame );



	// �Q�[���̍X�V����
	g_pGame->Update();



	// �`��R�[���o�b�N�֐����Ă�
	glutPostRedisplay();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : exit�֐��ɂ��I������
//
// @note : 
//
// exit�֐��ɂ���ăv���O�������I������ۂɎ��s����I���������s���B
// ���O��atexit�ŏI�������̊֐���o�^���Ă������ŁA
// exit�֐��̌�ɏI�����������s�o����B
//----------------------------------------------------------------------------------------------------------------------------------
void AtExit1() 
{ 
	// �Q�[���N���X��������Ώ������Ȃ�
	if ( !POINTER_CHECK( g_pGame ) ) { return; }

	

	// �I������
	g_pGame->Finish();

	SAFE_DELETE( g_pGame );
}
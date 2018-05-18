//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MAINSCENE_H_
#include "MainScene.h"
#endif	// #ifndef _INCLUDE_GUARD_MAINSCENE_H_

#ifndef _INCLUDE_GUARD_GAMEOVER_H_
#include "../03_GameOver/GameOver.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOVER_H_

#ifndef _INCLUDE_GUARD_CHASECAMERA_H_
#include "../../../Camera/Advanced/ChaseCamera/ChaseCamera.h"
#endif	// #ifndef _INCLUDE_GUARD_CHASECAMERA_H_

#ifndef _INCLUDE_GUARD_PLAYER_H_
#include "../../../GameObject/Element/Player/Player.h"
#endif	// #ifndef _INCLUDE_GUARD_PLAYER_H_

#ifndef _INCLUDE_GUARD_TARGET_H_
#include "../../../GameObject/Element/Target/Target.h"
#endif	// #ifndef _INCLUDE_GUARD_TARGET_H_

#ifndef _INCLUDE_GUARD_STAGE_H_
#include "../../../GameObject/Element/Stage/Stage.h"
#endif	// #ifndef _INCLUDE_GUARD_STAGE_H_

#ifndef _INCLUDE_GUARD_GAMETEXT_H_
#include "../../../GameObject/Element/GameText/GameText.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMETEXT_H_

#ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_
#include <WindowsAPIInputLib.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_

#ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_
#include <OpenALSoundLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_
#include <OpenGLResourceLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// �Q�[�����O���
using namespace NS_OpenGLWindowPCGame;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
MainScene::MainScene() :
	m_pChaseCamera( nullptr ),
	m_pStage( nullptr ),
	m_uiPlayerModelResourceID( ERROR_RESOURCE_ID ),
	m_uiBulletModelResourceID( ERROR_RESOURCE_ID ),
	m_strBGMName( "MainBGM" ),
	m_strSEShotName( "ShotSE" ),
	m_strSEHitName( "HitSE" )
{ 
	VIEWPORT_DESC viewportDesc;
	glGetIntegerv( GL_VIEWPORT, (GLint*)&viewportDesc );

	CAMERA_DESC cameraDesc(
		45.0f,
		( (GLfloat)viewportDesc.width / viewportDesc.height ),
		0.1f,
		10000.0f,
		1,
		false,
		Color4F( 0, 0, 0, 1 ),
//		Color4F( 1, 1, 1, 1 ),
		viewportDesc,
		Vector3DF( 0, 5, 5 ), 
		Vector3DF( 0, 0, 0 ), 
		Vector3DF( 0, 1, 0 )
	);

	CHASE_CAMERA_DESC chaseCameraDesc;
	chaseCameraDesc.distance = 5;
	chaseCameraDesc.verticalAngle = 0;
//	chaseCameraDesc.offset = Vector3DF( 0, 1, 0 );
	
	m_pChaseCamera = new ChaseCamera( cameraDesc, chaseCameraDesc );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
MainScene::~MainScene() 
{
	// �I������
	Finish();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������
//
// @note : 
//
// �������Ɋւ��鏈���͂����ōs���B
// �V�[���J�n��̃V�[���؂�ւ�����1��s�Ȃ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Initialize() 
{ 
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );



	// �Q�[���I�u�W�F�N�g�N���X�𐶐�

	// �v���C���[
	Player* pPlayer	= 
		new Player( 
			m_pChaseCamera, 
			NS_Resource::NS_Model::GetModel( m_uiPlayerModelResourceID ),
			NS_Resource::NS_Model::GetModel( m_uiBulletModelResourceID ),
			m_pGameObjectManager,
			m_strSEShotName,
			m_strSEHitName
		);

	// �I
	for ( int i = 0; i < 7; i++ ) 
	{
		Target* pTarget	= new Target();

		float fScaleSize = Random::RandomFloat( 1, 3 );

		pTarget->Initialize( 
			40, 
			Vector3DF( Random::RandomFloat( -20, 20 ), Random::RandomFloat( 0, 10 ), Random::RandomFloat( -20, 20 ) ), 
			Vector3DF( 0, 0, 0 ), 
//			Vector3DF( Random::RandomFloat( -180, 180 ), Random::RandomFloat( -180, 180 ), Random::RandomFloat( -180, 180 ) ), 
//			Vector3DF( 1, 1, 1 )
			Vector3DF( fScaleSize, fScaleSize, fScaleSize )
		);

		m_pGameObjectManager->AddGameObject( pTarget );
	}

	// �X�e�[�W
	m_pStage	= new Stage();

	// �Q�[���e�L�X�g
	m_pGameText	= new GameText();



	// �Q�[���I�u�W�F�N�g�N���X�̏���������

	// �v���C���[
	pPlayer->Initialize( 
		10, 
		Vector3DF( 0, 2, 30 ), 
		Vector3DF( 0, 180, 0 ), 
		Vector3DF( 0.002f, 0.002f, 0.002f ),
		Vector3DF( 10, 60, 60 )
	);

	// �X�e�[�W
	m_pStage->Initialize();



	// �Q�[���I�u�W�F�N�g��ǉ�

	// �v���C���[
	m_pGameObjectManager->AddGameObject( pPlayer );




	// BGM�̍Đ�
	NS_Sound::Play( m_strBGMName, true );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
// �X�V�Ɋւ��鏈���͂����ōs���B
// �V�[�����p�����Ă���ԁA�`�揈���̑O�ɌJ��Ԃ��s�Ȃ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Update() 
{ 
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );
	ASSERT_POINTER_CHECK( m_pStage );
	ASSERT_POINTER_CHECK( m_pGameText );
	

/*
	if ( NS_Input::NS_Keyboard::GetKeyDown( 'Z' ) ) 
	{
		m_bSceneEndFlg = true;

		// BGM�̒�~
		NS_Sound::Stop( m_strBGMName );
	}
*/	

glDisable( GL_LIGHTING );

	// �Q�[���I�u�W�F�N�g�N���X�̍X�V����
	m_pGameObjectManager->Update();

	// �X�e�[�W
	m_pStage->Update();

	// �Q�[���e�L�X�g
	m_pGameText->Update();



	// �J�����̍X�V����
	m_pChaseCamera->Update();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �`��Ɋւ��鏈���͂����ōs���B
// �V�[�����p�����Ă���ԁA�X�V�����̌�ɌJ��Ԃ��s�Ȃ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Draw() 
{ 
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );
	ASSERT_POINTER_CHECK( m_pStage );
	ASSERT_POINTER_CHECK( m_pGameText );



	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT );

	glEnable( GL_DEPTH_TEST );
	
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );


	

	// �Q�[���e�L�X�g�̕`��
	m_pGameText->Draw();


	



	m_pChaseCamera->Start();
	

	


	
	


	
	m_pGameObjectManager->Draw();

	m_pStage->Draw();



	m_pChaseCamera->End();



	glPopAttrib();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �I������
//
// @note : 
//
// �I���Ɋւ��鏈���͂����ōs���B
// �V�[���I����̃V�[���؂�ւ�����1��s�Ȃ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Finish() 
{ 
	// �Q�[���I�u�W�F�N�g�N���X��j��
	
	// �ǐՃJ����
	SAFE_DELETE( m_pChaseCamera );
	
	// �X�e�[�W
	SAFE_DELETE( m_pStage );
	
	// �Q�[���e�L�X�g
	SAFE_DELETE( m_pGameText );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ɑJ�ڂ���V�[���̐���
//
// @note : 
//
// ���ɑJ�ڂ���V�[���𐶐�����B
// �V�[���؂�ւ������̕K�v�ȃ^�C�~���O�ŌĂяo���悤�ɒ��ӂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::CreateNextScene() 
{
	if ( !POINTER_CHECK( m_pNextScene ) ) 
	{
		m_pNextScene = new GameOver;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���e���c���[�h
//
// @note : 
//
// �R���e���c�̓ǂݍ��ݏ����͂����ōs���B
// �V�[���J�n��̃V�[���؂�ւ�����1��s�Ȃ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::LoadContent() 
{ 
	// �v���C���[���f���̓ǂݍ���

	m_uiPlayerModelResourceID = NS_Resource::NS_Model::LoadModel( "Resource/Graphic/Model/Low Poly Starship-SS01/AF-SS01.obj" );

	if ( m_uiPlayerModelResourceID == ERROR_RESOURCE_ID ) 
	{
		HALT( "���\�[�X�̓ǂݍ��݂Ɏ��s���܂����B" );
	}
	
	
	// �e���f���̓ǂݍ���

	m_uiBulletModelResourceID = NS_Resource::NS_Model::LoadModel( "Resource/Graphic/Model/Missile/missile.obj" );

	if ( m_uiBulletModelResourceID == ERROR_RESOURCE_ID ) 
	{
		HALT( "���\�[�X�̓ǂݍ��݂Ɏ��s���܂����B" );
	}



	// BGM�̓ǂݍ���
	NS_Sound::Load( "Resource/Sound/BGM/Example2.wav", m_strBGMName );

	// ���˂�SE�̓ǂݍ���
	NS_Sound::Load( "Resource/Sound/SE/se_shot.wav", m_strSEShotName );

	// �e�̏Փ˂�SE�̓ǂݍ���
	NS_Sound::Load( "Resource/Sound/SE/se_hit.wav", m_strSEHitName );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���e���c�A�����[�h
//
// @note : 
//
// �R���e���c�̉�������͂����ōs���B
// �V�[���I����̃V�[���؂�ւ�����1��s�Ȃ���B
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::UnloadContent() 
{
	NS_Resource::ClearResource();
}
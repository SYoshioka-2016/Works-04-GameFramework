//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_SCENEMANAGER_H_
#include "SceneManager.h"
#endif	// #ifndef _INCLUDE_GUARD_SCENEMANAGER_H_

#ifndef _INCLUDE_GUARD_BASESCENE_H_
#include "../Scenes/Base/BaseScene.h"
#endif	// #ifndef _INCLUDE_GUARD_BASESCENE_H_



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
SceneManager::SceneManager() :
	m_pCurrentScene( nullptr ),
	m_pNextScene( nullptr )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
SceneManager::~SceneManager() 
{
	// ���݂̃V�[�����L��Δj������
	if ( POINTER_CHECK( m_pCurrentScene ) ) 
	{
		m_pCurrentScene->Finish();

		m_pCurrentScene->UnloadContent();

		SAFE_DELETE( m_pCurrentScene );
	}
/*
	// ���ɑJ�ڂ���V�[�����L��Δj������
	if ( POINTER_CHECK( m_pNextScene ) ) 
	{
		m_pNextScene->Finish();

		SAFE_DELETE( m_pNextScene );
	}
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���s����
//
// @note : 
//
// ���݂̃V�[���̍X�V�������s���B
// ���݂̃V�[�����I�������玟�ɑJ�ڂ���V�[���ɐ؂�ւ���B
//----------------------------------------------------------------------------------------------------------------------------------
void SceneManager::Run() 
{
	// ���݂̃V�[�����L��ꍇ
	if ( POINTER_CHECK( m_pCurrentScene ) ) 
	{
		// ���݂̃V�[�����I�����Ă���΃V�[���؂�ւ�
		if ( m_pCurrentScene->isEndScene() ) 
		{
			// ���݂̃V�[���̏I������
			m_pCurrentScene->Finish();

			// ���݂̃V�[���̃R���e���c�A�����[�h
			m_pCurrentScene->UnloadContent();

			// ���ɑJ�ڂ���V�[���̐؂�ւ�
			ChangeNextScene( m_pCurrentScene->GetNextScene() );

			// ���݂̃V�[�����폜
			SAFE_DELETE( m_pCurrentScene );
		}
		// ���݂̃V�[�����p�����Ă���΃V�[�����X�V
		else 
		{
			// ���݂̃V�[���̍X�V����
			m_pCurrentScene->Update();
		}
	}

	// ���݂̃V�[���������ꍇ
	else 
	{
		// ���ɑJ�ڂ���V�[�����L��ꍇ
		if ( POINTER_CHECK( m_pNextScene ) ) 
		{ 
			// ���݂̃V�[����ݒ�
			m_pCurrentScene = m_pNextScene;

			// ���݂̃V�[���̃R���e���c���[�h
			m_pCurrentScene->LoadContent();

			// ���݂̃V�[���̏���������
			m_pCurrentScene->Initialize();

			// ���ɑJ�ڂ���V�[�����N���A
			m_pNextScene = nullptr;
		}
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// ���݂̃V�[���̕`�揈�����s���B
//----------------------------------------------------------------------------------------------------------------------------------
void  SceneManager::Draw() 
{
	// ���݂̃V�[����������Ώ������Ȃ�
	if ( !POINTER_CHECK( m_pCurrentScene ) ) { return; }



	// �V�[���̕`�揈��
	m_pCurrentScene->Draw();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ɑJ�ڂ���V�[���̐؂�ւ�
//
// @param [in] / BaseScene* pScene : ���ɑJ�ڂ���V�[��
//
// @note : 
//
// ���ɑJ�ڂ���V�[����؂�ւ���B
// ���ۂɃV�[����؂�ւ��鏈����Run�֐��ōs���B
//----------------------------------------------------------------------------------------------------------------------------------
void  SceneManager::ChangeNextScene( BaseScene* pScene )
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pScene );



	// ���ɑJ�ڂ���V�[�����L��΍폜���Ă���
	if ( POINTER_CHECK( m_pNextScene ) ) 
	{
		m_pNextScene->Finish();

		m_pNextScene->UnloadContent();

		SAFE_DELETE( m_pNextScene );
	}



	// ���ɑJ�ڂ���V�[����ݒ�
	m_pNextScene = pScene;
}
//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMEOBJECTMANAGER_H_
#include "GameObjectManager.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECTMANAGER_H_

#ifndef _INCLUDE_GUARD_GAMEOBJECTREMOVE_H_
#include "../Base/GameObjectRemove.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECTREMOVE_H_



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
GameObjectManager::GameObjectManager() : m_GameObjectList( GameObjectList() )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameObjectManager::~GameObjectManager() 
{
	// �S�ẴQ�[���I�u�W�F�N�g���폜����
	for each ( auto pGameObject in m_GameObjectList ) 
	{
		// �Q�[���I�u�W�F�N�g��������Ώ������Ȃ�
		if ( NULL_CHECK( pGameObject ) ) { continue; }



		// �Q�[���I�u�W�F�N�g�̏I������
		pGameObject->End();

		// �Q�[���I�u�W�F�N�g���폜
		SAFE_DELETE( pGameObject );
	}

	// �Q�[���I�u�W�F�N�g���X�g���N���A
	m_GameObjectList.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
void GameObjectManager::Update() 
{
	// �Q�[���I�u�W�F�N�g��j������
	m_GameObjectList.remove_if( GameObjectRemove() );



	// �S�ẴQ�[���I�u�W�F�N�g���X�V����
	for each ( auto pGameObject in m_GameObjectList ) 
	{
		// �Q�[���I�u�W�F�N�g��������Ώ������Ȃ�
		if ( NULL_CHECK( pGameObject ) ) { continue; }



		// �Q�[���I�u�W�F�N�g�̍X�V����
		pGameObject->Update();
	}



	// �S�ẴQ�[���I�u�W�F�N�g�̏Փˏ���
	for each ( auto pGameObject1 in m_GameObjectList ) 
	{
		for each ( auto pGameObject2 in m_GameObjectList ) 
		{
			// �Q�[���I�u�W�F�N�g��������Ώ������Ȃ�
			if ( NULL_CHECK( pGameObject1 ) ) { break; }
			
			// �Q�[���I�u�W�F�N�g��������Ώ������Ȃ�
			if ( NULL_CHECK( pGameObject2 ) ) { continue; }
			
			// �����Q�[���I�u�W�F�N�g�Ȃ珈�����Ȃ�
			if ( pGameObject1 == pGameObject2 ) { continue; }



			// �Q�[���I�u�W�F�N�g�̏Փˏ���
			pGameObject1->CollisionHandling( *pGameObject2 );
		}
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
void GameObjectManager::Draw() 
{
	// �S�ẴQ�[���I�u�W�F�N�g��`�悷��
	for each ( auto pGameObject in m_GameObjectList ) 
	{
		// �Q�[���I�u�W�F�N�g��������Ώ������Ȃ�
		if ( NULL_CHECK( pGameObject ) ) { continue; }


		
		// �Q�[���I�u�W�F�N�g�̕`�揈��
		pGameObject->Draw();
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Q�[���I�u�W�F�N�g�̒ǉ�
//
// @param [in] / GameObject* pGameObject : �Q�[���I�u�W�F�N�g
//
// @note : 
//
// �Q�[���I�u�W�F�N�g���X�g�Ɏw��̃Q�[���I�u�W�F�N�g��ǉ�����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObjectManager::AddGameObject( GameObject* pGameObject ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pGameObject );



	// �Q�[���I�u�W�F�N�g�̊J�n����
	pGameObject->Start();

	// �Q�[���I�u�W�F�N�g���X�g�ɃQ�[���I�u�W�F�N�g��ǉ�����
	m_GameObjectList.push_back( pGameObject );
}
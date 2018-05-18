//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_STARSPRITEMANAGER_H_
#include "StarSpriteManager.h"
#endif	// #ifndef _INCLUDE_GUARD_STARSPRITEMANAGER_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



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
// @param [in] / const SPRITE_DESC& desc		: �X�v���C�g�L�q�q
// @param [in] / const Vector3DF&	vec3Space	: ���X�v���C�g��u�����
// @param [in] / const unsigned int	uiCount		: ���X�v���C�g�̐�
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
StarSpriteManager::StarSpriteManager( 
	const SPRITE_DESC&	desc, 
	const Vector3DF&	vec3Space, 
	const unsigned int	uiCount 
) : m_StarSpriteList( std::list<Sprite*>() ) 
{
	// ���X�v���C�g�̐�������������
	for ( unsigned int i = 0; i < uiCount; i++ ) 
	{
		// �X�v���C�g�L�q�q���R�s�[����
		SPRITE_DESC spriteDesc = desc;

		// ���W����ԓ��̃����_���Ȉʒu�ɐݒ肷��
		spriteDesc.position = 
			Vector3DF( 
				Random::RandomFloat( -vec3Space.x / 2, vec3Space.x / 2 ),
				Random::RandomFloat( -vec3Space.y / 2, vec3Space.y / 2 ),
				Random::RandomFloat( -vec3Space.z / 2, vec3Space.z / 2 )
			);

spriteDesc.scale = Vector3DF( 5, 5, 1 );		
		// ���X�v���C�g���X�g�ɐ��X�v���C�g��ǉ�����
		m_StarSpriteList.push_back( new Sprite( spriteDesc ) );
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
StarSpriteManager::~StarSpriteManager() 
{
	// �S�Ă̐��X�v���C�g���폜����
	for each ( auto pStarSprite in m_StarSpriteList ) 
	{
		SAFE_DELETE( pStarSprite );
	}

	// ���X�v���C�g���X�g���N���A
	m_StarSpriteList.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �S�Ă̐��X�v���C�g��`�悷��B
//----------------------------------------------------------------------------------------------------------------------------------
void StarSpriteManager::Draw() 
{
	glPushAttrib( GL_ENABLE_BIT );



	// �[�x�e�X�g�𖳌��ɂ���
//	glDisable( GL_DEPTH_TEST );

	// ���C�e�B���O�𖳌��ɂ���
	glDisable( GL_LIGHTING );



	// �S�Ă̐��X�v���C�g��`�悷��
	for each ( auto pStarSprite in m_StarSpriteList ) 
	{
		// ���X�v���C�g��������Ώ������Ȃ�
		if( NULL_CHECK( pStarSprite ) ) { continue; }



		// ���X�v���C�g��`��
		pStarSprite->Draw();
	}



	glPopAttrib();
}
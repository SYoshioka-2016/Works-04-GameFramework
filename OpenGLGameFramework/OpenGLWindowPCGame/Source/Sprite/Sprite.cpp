//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_SPRITE_H_
#include "Sprite.h"
#endif	// #ifndef _INCLUDE_GUARD_SPRITE_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @param [in] / const SPRITE_DESC& desc : �X�v���C�g�L�q�q
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Sprite::Sprite( const SPRITE_DESC& desc ) :
	m_Desc( desc )
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Sprite::~Sprite() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �`�揈�����s���B
// �f�t�H���g��XY���ʂɕ��s�Ȏl�p�|���S����`�悷��B
//----------------------------------------------------------------------------------------------------------------------------------
void Sprite::Draw() 
{
	// �e�탌���_�����O���[�h��ޔ�����
	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// �u�����h��ݒ肷��
	glEnable( GL_BLEND );

	glBlendFunc( GL_SRC_ALPHA, GL_ONE );



	// �e�N�X�`�����擾����
	unsigned int uiTexture = NS_Resource::NS_Texture::GetTextureID( m_Desc.textureResourceID );

	// �e�N�X�`�����L��΃e�N�X�`����L���ɂ���
	if ( uiTexture != 0 ) 
	{
		glEnable( GL_TEXTURE_2D );

		glBindTexture( GL_TEXTURE_2D, uiTexture );
	}

	// �e�N�X�`����������΃e�N�X�`���𖳌��ɂ���
	else
	{
		glDisable( GL_TEXTURE_2D );
	}




	// �s���ۑ�
	glPushMatrix();



	// ���s�ړ�
	glTranslatef( m_Desc.position.x, m_Desc.position.y, m_Desc.position.z );

	// ��]
	glRotatef( m_Desc.rotation.x, 1, 0, 0 );
	glRotatef( m_Desc.rotation.y, 0, 1, 0 );
	glRotatef( m_Desc.rotation.z, 0, 0, 1 );

	// �X�P�[�����O
	glScalef( m_Desc.scale.x, m_Desc.scale.y, m_Desc.scale.z );



	// ���݂̃��f���r���[�ϊ��s��
	GLfloat fCurrentModelViewMatrix[16] = { };

	// �r���{�[�h���L���Ȃ�r���{�[�h�s���ݒ肷��
	if ( m_Desc.billboard ) 
	{
		// �s�񃂁[�h�����f���r���[�ɑI��
		glMatrixMode( GL_MODELVIEW );
	
		// ���݂̃��f���r���[�ϊ��s����擾����
		glGetFloatv( GL_MODELVIEW_MATRIX, fCurrentModelViewMatrix );


	
		// �r���{�[�h�s���ݒ�
		Matrix4x4F mat4Billboard = fCurrentModelViewMatrix;

		mat4Billboard[0][0]		= m_Desc.scale.x;
		mat4Billboard[1][1]		= m_Desc.scale.y;
		mat4Billboard[2][2]		= m_Desc.scale.z;

		mat4Billboard[0][1]		= 0;
		mat4Billboard[0][2]		= 0;
		mat4Billboard[1][0]		= 0;
		mat4Billboard[1][2]		= 0;
		mat4Billboard[2][0]		= 0;
		mat4Billboard[2][1]		= 0;

		glLoadMatrixf( (GLfloat*)&mat4Billboard );
	}



	// �X�v���C�g��`�悷��
	glBegin( GL_TRIANGLES );

glColor4fv( (GLfloat*)&m_Desc.color );
//glMaterialfv( GL_FRONT, GL_DIFFUSE, (GLfloat*)&m_Desc.color );


	// ����
	glTexCoord2f( m_Desc.textureOffset.x, m_Desc.textureOffset.y );
	glVertex3f( -0.5f,  0.5f,  0 );

	// ����
	glTexCoord2f( m_Desc.textureOffset.x, m_Desc.textureOffset.y + m_Desc.textureTiling.y );
	glVertex3f( -0.5f, -0.5f,  0 );
	
	// �E��
	glTexCoord2f( m_Desc.textureOffset.x + m_Desc.textureTiling.x, m_Desc.textureOffset.y + m_Desc.textureTiling.y );
	glVertex3f(  0.5f, -0.5f,  0 );
		
	// �E��
	glTexCoord2f( m_Desc.textureOffset.x + m_Desc.textureTiling.x, m_Desc.textureOffset.y + m_Desc.textureTiling.y );
	glVertex3f(  0.5f, -0.5f,  0 );

	// �E��
	glTexCoord2f( m_Desc.textureOffset.x + m_Desc.textureTiling.x, m_Desc.textureOffset.y );
	glVertex3f(  0.5f,  0.5f,  0 );
		
	// ����
	glTexCoord2f( m_Desc.textureOffset.x, m_Desc.textureOffset.y );
	glVertex3f( -0.5f,  0.5f,  0 );

	glEnd();



	// �r���{�[�h���L���Ȃ烂�f���r���[�ϊ��s������ɖ߂�
	if ( m_Desc.billboard ) 
	{
		glMatrixMode( GL_MODELVIEW );
	
		glLoadMatrixf( fCurrentModelViewMatrix );
	}



	// �s���j��
	glPopMatrix();



	// �e�N�X�`�����L��΃e�N�X�`���𖳌��ɂ���
	if ( uiTexture != 0 ) 
	{
		glBindTexture( GL_TEXTURE_2D, 0 );
	}



	// �����_�����O���[�h�𕜋A����
	glPopAttrib();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�v���C�g�L�q�q�̎擾
//
// @return / const SPRITE_DESC& : �X�v���C�g�L�q�q
//
// @note : 
//
// �X�v���C�g�L�q�q�̎Q�Ƃ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const SPRITE_DESC& Sprite::GetDesc() const
{
	return m_Desc;
}
//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLMODEL_H_
#include "OGLModel.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLMODEL_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// ���\�[�X���O���
using namespace NS_Resource;

// ���f�����O���
using namespace NS_Model;

// �e�N�X�`�����O���
using namespace NS_Texture;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLModel::OGLModel() : m_pMesh( nullptr )
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLModel::~OGLModel() 
{
	// ���b�V�����폜
	SAFE_DELETE( m_pMesh );



	// �}�e���A���f�[�^���N���A
	for each ( auto material in m_MaterialData ) 
	{
		SAFE_DELETE( material.second );
	}
	m_MaterialData.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���f���̕`��
//
// @param [in] / const Vector4DF& vec4LightPosition : ���C�g�̈ʒu
// @param [in] / const Matrix4x4F& mat4World		: ���[���h�ϊ��s��
// @param [in] / const Matrix4x4F& mat4View			: �r���[�ϊ��s��
// @param [in] / const Matrix4x4F& mat4Projection	: �v���W�F�N�V�����ϊ��s��
//
// @note : 
//
// ���f����`�悷��B
// ���C�g�̈ʒu��4�����x�N�g���l��xyz�����W�Ƃ��Ĉ����A
// w�̒l��1�Ń|�C���g���C�g( �_���� )�ƂȂ�A
// 0�Ńf�B���N�V���i�����C�g( ���s���� )�ƂȂ�B
// 0�����Ń��C�e�B���O�𖳌��ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void OGLModel::Render( 
	const Vector4DF& vec4LightPosition,
	const Matrix4x4F& mat4World,
	const Matrix4x4F& mat4View, 
	const Matrix4x4F& mat4Projection
) 
{
	// �ޔ�p�J�����g�J���[
	Vector4DF	vec4CurrentColor;

	// �J�����g�J���[���擾
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// �����ݒ�

		if ( 0 > vec4LightPosition.w ) 
		{
			// ���C�e�B���O
			glDisable( GL_LIGHTING );
		}
		


		// �L���ݒ�

		if ( 0 <= vec4LightPosition.w )
		{
			// ���C�e�B���O
			glEnable( GL_LIGHTING );
		
			// ���C�g0
			glEnable( GL_LIGHT0 );
		}

		// �[�x�e�X�g
		glEnable( GL_DEPTH_TEST );

		// �J�����O
		glEnable( GL_CULL_FACE );

		// ���K��
		glEnable( GL_NORMALIZE );



		glPushMatrix();
		{
			// �ϊ��s���P�ʍs��ŏ�����
			glLoadIdentity();	

			// �ˉe�s����s�񉉎Z�^�[�Q�b�g�ɑI��
			glMatrixMode( GL_PROJECTION );

			// �ˉe�ϊ��s���ݒ�
			glLoadMatrixf( (GLfloat*)&mat4Projection );



			// ���f���r���[�s����s�񉉎Z�^�[�Q�b�g�ɑI��
			glMatrixMode( GL_MODELVIEW );

			// �ϊ��s���P�ʍs��ŏ�����
			glLoadIdentity();	
			
			// �s���ݒ�
			glLoadMatrixf( (GLfloat*)&mat4View );
			
			// ���C�g��ݒ�
			glLightfv( GL_LIGHT0, GL_POSITION, (GLfloat*)&vec4LightPosition );
			


			// ���݂̍s��Ƀ��[���h�ϊ��s�����Z
			glMultMatrixf( (GLfloat*)&mat4World );
			


			// �}�e���A�����L��Βʏ�̕`��
			if ( !m_MaterialData.empty() ) 
			{
				// �}�e���A����K�p���ă��b�V����`��
				DrawMesh();
			}

			// �}�e���A����������ΊȈՓI�ȕ`��
			else 
			{
				// �}�e���A�������Ń��b�V����`��
				SimpleDrawMesh( GL_TRIANGLES );
			}
		}
		glPopMatrix();
	}
	glPopAttrib();
	


	// �J�����g�J���[�𕜋A
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���b�V���̎擾
//
// @return / const MESH* : ���b�V��
//	
// @note : 
//
// ���b�V�����擾����B
//----------------------------------------------------------------------------------------------------------------------------------
const MESH* OGLModel::GetMesh() const 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pMesh );



	return m_pMesh;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �}�e���A����K�p���ă��b�V����`��
//
// @note : 
//
// ���b�V����`�悷��B
// �}�e���A�����Ƀ}�e���A���̐ݒ�𔽉f���ă��b�V����`�悷��B
//----------------------------------------------------------------------------------------------------------------------------------
void OGLModel::DrawMesh() const
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pMesh );



	// �ޔ�p

	// �A���r�G���g
	Vector4DF	vec4CurrentAmbient;

	// �f�B�t���[�Y
	Vector4DF	vec4CurrentDiffuse;

	// �X�y�L����
	Vector4DF	vec4CurrentSpecular;

	// ���ʔ��˂̋���
	float		fCurrentShininess	= 0;



	// ���݂̃A���r�G���g���擾
	glGetFloatv( GL_AMBIENT, (GLfloat*)&vec4CurrentAmbient );

	// ���݂̃f�B�t���[�Y���擾
	glGetFloatv( GL_DIFFUSE, (GLfloat*)&vec4CurrentDiffuse );

	// ���݂̃X�y�L�������擾
	glGetFloatv( GL_SPECULAR, (GLfloat*)&vec4CurrentSpecular );

	// ���݂̋��ʔ��˂̋������擾
	glGetFloatv( GL_SHININESS, (GLfloat*)&fCurrentShininess );



	// �}�e���A�����Ƀ��b�V����`�悷��
	for each ( auto material in m_MaterialData ) 
	{
		// �}�e���A��
		MATERIAL* pMaterial = material.second;

		// �}�e���A����������Ώ������Ȃ�
		if ( NULL_CHECK( pMaterial ) ) { continue; }



		// �A���r�G���g��ݒ�
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *)&pMaterial->vec4Ambient );

		// �f�B�t���[�Y��ݒ�
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *)&pMaterial->vec4Diffuse );

		// �X�y�L������ݒ�
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *)&pMaterial->vec4Specular );

		// ���ʔ��˂̋�����ݒ�
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->fShininess );



		// �e�N�X�`��ID���擾
		const unsigned int uiTextureID = GetTextureID( pMaterial->uiTextureResourceID );
		
		// �e�N�X�`�����L��΃e�N�X�`����L���ɂ���
		if ( uiTextureID != 0 ) 
		{
			// �e�N�X�`����L���ɂ���
			glEnable( GL_TEXTURE_2D );

			// �e�N�X�`�����o�C���h����
			glBindTexture( GL_TEXTURE_2D, uiTextureID );
		}

		// �e�N�X�`����������΃e�N�X�`���𖳌��ɂ���
		else 
		{
			// �e�N�X�`���𖳌��ɂ���
			glDisable( GL_TEXTURE_2D );
		}



		// �}�e���A���������_���W�C���f�b�N�X( �|���S�� )�̐������A�|���S����1�����`�悷��
		for ( unsigned int i = 0; i < pMaterial->vertexPositionIndexData.size() ; i++ ) 
		{
			// �O�p�|���S����`�悷��
			glBegin( GL_TRIANGLES );
			{
				// 1�ڂ̒��_��ݒ�

				// �@��
				glNormal3f( 
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->x ].x,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->x ].y,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->x ].z
				);

				// �e�N�X�`�����W
				glTexCoord2f( 
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->x ].x,
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->x ].y
				);

				// ���_���W
				glVertex3f( 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->x ].x, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->x ].y, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->x ].z 
				);


				
				// 2�ڂ̒��_��ݒ�

				// �@��
				glNormal3f( 
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->y ].x,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->y ].y,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->y ].z
				);
				
				// �e�N�X�`�����W
				glTexCoord2f( 
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->y ].x,
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->y ].y
				);
				
				// ���_���W
				glVertex3f( 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->y ].x, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->y ].y, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->y ].z 
				);


				
				// 3�ڂ̒��_��ݒ�

				// �@��
				glNormal3f( 
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->z ].x,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->z ].y,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->z ].z
				);
				
				// �e�N�X�`�����W
				glTexCoord2f( 
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->z ].x,
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->z ].y
				);
								
				// ���_���W
				glVertex3f( 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->z ].x, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->z ].y, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->z ].z 
				);
			}
			glEnd();
		}
	}


	// �e�N�X�`���̃o�C���h����������
	glBindTexture( GL_TEXTURE_2D, 0 );


	
	// �A���r�G���g�𕜋A
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *)&vec4CurrentAmbient );
	
	// �f�B�t���[�Y�𕜋A
if ( vec4CurrentDiffuse.Length() != 0 ) { glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *)&vec4CurrentDiffuse ); }
	
	// �X�y�L�����𕜋A
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *)&vec4CurrentSpecular );
	
	// ���ʔ��˂̋����𕜋A
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, fCurrentShininess );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �}�e���A�������Ń��b�V����`��
//
// @param [in] / const unsigned int uiDrawMode : �`�惂�[�h
//
// @note : 
//
// ���b�V����`�悷��B
// �}�e���A�����g�킸�Ƀ��f�������f�[�^�Ń��b�V����`�悷��B
//----------------------------------------------------------------------------------------------------------------------------------
void OGLModel::SimpleDrawMesh( const unsigned int uiDrawMode ) const
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pMesh );



	// ���_���W�C���f�b�N�X�f�[�^�̃C�e���[�^
	std::multimap<std::string, Vector3DI*>::iterator vertexPositionIndexDataIterator	= m_pMesh->vertexPositionIndexData.begin();
	
	// �@���C���f�b�N�X�f�[�^�̃C�e���[�^
	std::multimap<std::string, Vector3DI*>::iterator normalIndexDataIterator			= m_pMesh->normalIndexData.begin();
	
	// �e�N�X�`�����W�C���f�b�N�X�f�[�^�̃C�e���[�^
	std::multimap<std::string, Vector3DI*>::iterator texcoordIndexDataIterator			= m_pMesh->texcoordIndexData.begin();

	// �J��Ԃ���������p( true : �p�� | false : �I�� )
	bool bIsNotEnd = true;



	// �C�e���[�^�������łȂ���ΌJ��Ԃ�
	bIsNotEnd &= ( m_pMesh->vertexPositionIndexData.end() != vertexPositionIndexDataIterator );
	bIsNotEnd &= ( m_pMesh->normalIndexData.end() != normalIndexDataIterator );
	bIsNotEnd &= ( m_pMesh->texcoordIndexData.end() != texcoordIndexDataIterator );

	while ( bIsNotEnd ) 
	{
		glBegin( uiDrawMode );
		{
/*
			// �|���S���̕\�̕�����@���Ƃ���
			Vector3DF vec3Normal =
				glm::cross(
					m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ] - m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ],
					m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ] - m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ]
			);

			// �@���x�N�g���𐳋K��
			vec3Normal = glm::normalize( vec3Normal );
					
			// �@����ݒ�
			glNormal3f( vec3Normal.x, vec3Normal.y, vec3Normal.z );
*/			


			// 1�ڂ̒��_��ݒ�

			// �@��
			glNormal3f( 
				m_pMesh->normalData[ normalIndexDataIterator->second->x ].x, 
				m_pMesh->normalData[ normalIndexDataIterator->second->x ].y, 
				m_pMesh->normalData[ normalIndexDataIterator->second->x ].z 
			);

			// �e�N�X�`�����W
			glTexCoord2f( 
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->x ].x,
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->x ].y
			);

			// ���_���W
			glVertex3f( 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ].x, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ].y, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ].z 
			);


			
			// 2�ڂ̒��_��ݒ�

			// �@��
			glNormal3f( 
				m_pMesh->normalData[ normalIndexDataIterator->second->y ].x, 
				m_pMesh->normalData[ normalIndexDataIterator->second->y ].y, 
				m_pMesh->normalData[ normalIndexDataIterator->second->y ].z 
			);
			
			// �e�N�X�`�����W
			glTexCoord2f( 
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->y ].x,
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->y ].y
			);
			
			// ���_���W
			glVertex3f( 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ].x, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ].y, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ].z 
			);


			
			// 3�ڂ̒��_��ݒ�

			// �@��
			glNormal3f( 
				m_pMesh->normalData[ normalIndexDataIterator->second->z ].x, 
				m_pMesh->normalData[ normalIndexDataIterator->second->z ].y, 
				m_pMesh->normalData[ normalIndexDataIterator->second->z ].z 
			);

			// �e�N�X�`�����W
			glTexCoord2f( 
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->z ].x,
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->z ].y
			);
			
			// ���_���W
			glVertex3f( 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ].x, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ].y, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ].z 
			);
		}
		glEnd();



		// ���_���W�C���f�b�N�X�f�[�^�̃C�e���[�^��i�߂�
		vertexPositionIndexDataIterator++;

		// �@���C���f�b�N�X�f�[�^�̃C�e���[�^��i�߂�
		normalIndexDataIterator++;

		// �e�N�X�`�����W�C���f�b�N�X�f�[�^�̃C�e���[�^��i�߂�
		texcoordIndexDataIterator++;

		// �C�e���[�^�������łȂ���ΌJ��Ԃ�
		bIsNotEnd &= ( m_pMesh->vertexPositionIndexData.end() != vertexPositionIndexDataIterator );
		bIsNotEnd &= ( m_pMesh->normalIndexData.end() != normalIndexDataIterator );
		bIsNotEnd &= ( m_pMesh->texcoordIndexData.end() != texcoordIndexDataIterator );
	}
}
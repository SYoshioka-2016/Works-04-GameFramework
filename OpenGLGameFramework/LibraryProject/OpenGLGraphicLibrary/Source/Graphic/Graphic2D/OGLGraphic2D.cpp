//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_
#include "OGLGraphic2D.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �_�̕`��
//
// @param [in] / const Vector2DF&	vec2Position		: �_�̍��W
// @param [in] / const Vector4DF&	vec4Color			: �J���[
// @param [in] / const float	fPointSize			: �_�̑傫��
// @param [in] / const float	fOrthoLeft			: ���ˉe��x���̍ŏ��l
// @param [in] / const float	fOrthoRight			: ���ˉe��x���̍ő�l
// @param [in] / const float	fOrthoBottom		: ���ˉe��y���̍ő�l
// @param [in] / const float	fOrthoTop			: ���ˉe��y���̍ŏ��l
// @param [in] / const float	fNear				: Near��
// @param [in] / const float	fFar				: Far��
//
// @note : 
//
// �_��`�悷��B
// ���W�A�J���[�A�_�̑傫���Ɛ��ˉe�ϊ��̐��l���w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawPoint( 
	const Vector2DF&	vec2Position, 
	const Vector4DF&	vec4Color,
	const float		fPointSize,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// �ޔ�p�J�����g�J���[
	Vector4DF vec4CurrentColor;

	

	// �J�����g�J���[���擾
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// �����ݒ�

		// ���C�e�B���O
		glDisable( GL_LIGHTING );
		
		// �e�N�X�`��
		glDisable( GL_TEXTURE );

		// �[�x�e�X�g
		glDisable( GL_DEPTH_TEST );

		// �J�����O
		glDisable( GL_CULL_FACE );
		


		// �L���ݒ�

		// �u�����h
		glEnable( GL_BLEND );



		// �u�����h��ݒ�
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// �`�悷��_�̃T�C�Y��ݒ�
		glPointSize( fPointSize );

		// �ˉe�s����s�񉉎Z�^�[�Q�b�g�ɑI��
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// �ϊ��s���P�ʍs��ŏ�����
			glLoadIdentity();

			// ���ˉe�s���ݒ�
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// ���f���r���[�s����s�񉉎Z�^�[�Q�b�g�ɑI��
			glMatrixMode( GL_MODELVIEW );
		
			// �w��̃J���[��ݒ�
			glColor4fv( (GLfloat*)&vec4Color );
			
			// �_��`��
			glBegin( GL_POINTS );
			{
				glVertex2f( vec2Position.x, vec2Position.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// �J�����g�J���[�𕜋A
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �����̕`��
//
// @param [in] / const Vector2DF&	vec2Position1		: �����̒��_�̍��W1
// @param [in] / const Vector2DF&	vec2Position2		: �����̒��_�̍��W2
// @param [in] / const Vector4DF&	vec4VertexColor1	: �����̒��_�J���[1
// @param [in] / const Vector4DF&	vec4VertexColor2	: �����̒��_�J���[2
// @param [in] / const float	fLineSize			: ���̑���
// @param [in] / const float	fOrthoLeft			: ���ˉe��x���̍ŏ��l
// @param [in] / const float	fOrthoRight			: ���ˉe��x���̍ő�l
// @param [in] / const float	fOrthoBottom		: ���ˉe��y���̍ő�l
// @param [in] / const float	fOrthoTop			: ���ˉe��y���̍ŏ��l
// @param [in] / const float	fNear				: Near��
// @param [in] / const float	fFar				: Far��
//
// @note : 
//
// ������`�悷��B
// ������2�_�̍��W�A�J���[�A���̑����Ɛ��ˉe�ϊ��̐��l���w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawLine( 
	const Vector2DF&	vec2Position1, 
	const Vector2DF&	vec2Position2, 
	const Vector4DF&	vec4VertexColor1,
	const Vector4DF&	vec4VertexColor2,
	const float		fLineSize,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// �ޔ�p�J�����g�J���[
	Vector4DF vec4CurrentColor;

	

	// �J�����g�J���[���擾
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// �����ݒ�

		// ���C�e�B���O
		glDisable( GL_LIGHTING );
		
		// �e�N�X�`��
		glDisable( GL_TEXTURE );

		// �[�x�e�X�g
		glDisable( GL_DEPTH_TEST );

		// �J�����O
		glDisable( GL_CULL_FACE );
		


		// �L���ݒ�

		// �u�����h
		glEnable( GL_BLEND );



		// �u�����h��ݒ�
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// �`�悷����̕���ݒ�
		glLineWidth( fLineSize );

		// �ˉe�s����s�񉉎Z�^�[�Q�b�g�ɑI��
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// �ϊ��s���P�ʍs��ŏ�����
			glLoadIdentity();

			// ���ˉe�s���ݒ�
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// ���f���r���[�s����s�񉉎Z�^�[�Q�b�g�ɑI��
			glMatrixMode( GL_MODELVIEW );

			// ����`��
			glBegin( GL_LINES );
			{
				glColor4fv( (GLfloat*)&vec4VertexColor1 );
				glVertex2f( vec2Position1.x, vec2Position1.y );
				
				glColor4fv( (GLfloat*)&vec4VertexColor2 );
				glVertex2f( vec2Position2.x, vec2Position2.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// �J�����g�J���[�𕜋A
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �����̎O�p�`�̕`��
//
// @param [in] / const Vector2DF&	vec2Position1		: �O�p�`�̒��_�̍��W1
// @param [in] / const Vector2DF&	vec2Position2		: �O�p�`�̒��_�̍��W2
// @param [in] / const Vector2DF&	vec2Position3		: �O�p�`�̒��_�̍��W3
// @param [in] / const Vector4DF&	vec4VertexColor1	: �O�p�`�̒��_�J���[1
// @param [in] / const Vector4DF&	vec4VertexColor1	: �O�p�`�̒��_�J���[2
// @param [in] / const Vector4DF&	vec4VertexColor1	: �O�p�`�̒��_�J���[3
// @param [in] / const float	fLineSize			: ���̑���
// @param [in] / const float	fOrthoLeft			: ���ˉe��x���̍ŏ��l
// @param [in] / const float	fOrthoRight			: ���ˉe��x���̍ő�l
// @param [in] / const float	fOrthoBottom		: ���ˉe��y���̍ő�l
// @param [in] / const float	fOrthoTop			: ���ˉe��y���̍ŏ��l
// @param [in] / const float	fNear				: Near��
// @param [in] / const float	fFar				: Far��
//
// @note : 
//
// ���̎O�p�`��`�悷��B
// 3���_�̍��W�A�J���[�A���̑����Ɛ��ˉe�ϊ��̐��l���w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawLineTriangle( 
	const Vector2DF&	vec2Position1, 
	const Vector2DF&	vec2Position2, 
	const Vector2DF&	vec2Position3,
	const Vector4DF&	vec4VertexColor1,
	const Vector4DF&	vec4VertexColor2,
	const Vector4DF&	vec4VertexColor3,
	const float		fLineSize,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// �ޔ�p�J�����g�J���[
	Vector4DF vec4CurrentColor;

	

	// �J�����g�J���[���擾
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// �����ݒ�

		// ���C�e�B���O
		glDisable( GL_LIGHTING );
		
		// �e�N�X�`��
		glDisable( GL_TEXTURE );

		// �[�x�e�X�g
		glDisable( GL_DEPTH_TEST );

		// �J�����O
		glDisable( GL_CULL_FACE );
		


		// �L���ݒ�

		// �u�����h
		glEnable( GL_BLEND );

		

		// �u�����h��ݒ�
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// �`�悷����̕���ݒ�
		glLineWidth( fLineSize );

		// �ˉe�s����s�񉉎Z�^�[�Q�b�g�ɑI��
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// �ϊ��s���P�ʍs��ŏ�����
			glLoadIdentity();

			// ���ˉe�s���ݒ�
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// ���f���r���[�s����s�񉉎Z�^�[�Q�b�g�ɑI��
			glMatrixMode( GL_MODELVIEW );
		
			// �O�p�`��`��
			glBegin( GL_LINE_LOOP );
			{
				glColor4fv( (GLfloat*)&vec4VertexColor1 );
				glVertex2f( vec2Position1.x, vec2Position1.y );
					
				glColor4fv( (GLfloat*)&vec4VertexColor2 );
				glVertex2f( vec2Position2.x, vec2Position2.y );
				
				glColor4fv( (GLfloat*)&vec4VertexColor3 );
				glVertex2f( vec2Position3.x, vec2Position3.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// �J�����g�J���[�𕜋A
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �h��Ԃ��̎O�p�`�̕`��
//
// @param [in] / const Vector2DF&	vec2Position1		: �O�p�`�̒��_�̍��W1
// @param [in] / const Vector2DF&	vec2Position2		: �O�p�`�̒��_�̍��W2
// @param [in] / const Vector2DF&	vec2Position3		: �O�p�`�̒��_�̍��W3
// @param [in] / const Vector4DF&	vec4VertexColor1	: �O�p�`�̒��_�J���[1
// @param [in] / const Vector4DF&	vec4VertexColor1	: �O�p�`�̒��_�J���[2
// @param [in] / const Vector4DF&	vec4VertexColor1	: �O�p�`�̒��_�J���[3
// @param [in] / const float	fOrthoLeft			: ���ˉe��x���̍ŏ��l
// @param [in] / const float	fOrthoRight			: ���ˉe��x���̍ő�l
// @param [in] / const float	fOrthoBottom		: ���ˉe��y���̍ő�l
// @param [in] / const float	fOrthoTop			: ���ˉe��y���̍ŏ��l
// @param [in] / const float	fNear				: Near��
// @param [in] / const float	fFar				: Far��
//
// @note : 
//
// �h��Ԃ����O�p�`��`�悷��B
// 3���_�̍��W�A�J���[�Ɛ��ˉe�ϊ��̐��l���w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawFilledTriangle( 
	const Vector2DF&	vec2Position1, 
	const Vector2DF&	vec2Position2, 
	const Vector2DF&	vec2Position3,
	const Vector4DF&	vec4VertexColor1,
	const Vector4DF&	vec4VertexColor2,
	const Vector4DF&	vec4VertexColor3,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// �ޔ�p�J�����g�J���[
	Vector4DF vec4CurrentColor;

	

	// �J�����g�J���[���擾
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// �����ݒ�

		// ���C�e�B���O
		glDisable( GL_LIGHTING );
		
		// �e�N�X�`��
		glDisable( GL_TEXTURE );

		// �[�x�e�X�g
		glDisable( GL_DEPTH_TEST );

		// �J�����O
		glDisable( GL_CULL_FACE );
		


		// �L���ݒ�

		// �u�����h
		glEnable( GL_BLEND );

		

		// �u�����h��ݒ�
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// �ˉe�s����s�񉉎Z�^�[�Q�b�g�ɑI��
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// �ϊ��s���P�ʍs��ŏ�����
			glLoadIdentity();

			// ���ˉe�s���ݒ�
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// ���f���r���[�s����s�񉉎Z�^�[�Q�b�g�ɑI��
			glMatrixMode( GL_MODELVIEW );
		
			// �O�p�`��`��
			glBegin( GL_TRIANGLES );
			{
				glColor4fv( (GLfloat*)&vec4VertexColor1 );
				glVertex2f( vec2Position1.x, vec2Position1.y );
					
				glColor4fv( (GLfloat*)&vec4VertexColor2 );
				glVertex2f( vec2Position2.x, vec2Position2.y );
					
				glColor4fv( (GLfloat*)&vec4VertexColor3 );
				glVertex2f( vec2Position3.x, vec2Position3.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// �J�����g�J���[�𕜋A
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}
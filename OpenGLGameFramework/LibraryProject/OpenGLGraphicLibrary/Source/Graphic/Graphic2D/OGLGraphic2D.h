#ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_
#define _INCLUDE_GUARD_OGLGRAPHIC2D_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �O���t�B�b�N���O���
//
// @note : 
//
// �O���t�B�b�N�֘A�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Graphic
{



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2�����O���t�B�b�N���O���
//
// @note : 
//
// �O���t�B�b�N�֘A�̓��A2D�O���t�B�b�N�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Graphic2D
{



	// �_�̕`��
	void DrawPoint( 
		const Vector2DF&	vec2Position, 
		const Vector4DF&	vec4Color,
		const float		fPointSize,
		const float		fOrthoLeft			= -1,
		const float		fOrthoRight			=  1,
		const float		fOrthoBottom		= -1,
		const float		fOrthoTop			=  1,
		const float		fNear				= -1,
		const float		fFar				=  1
	);
	
	// �����̕`��
	void DrawLine( 
		const Vector2DF&	vec2Position1, 
		const Vector2DF&	vec2Position2, 
		const Vector4DF&	vec4VertexColor1,
		const Vector4DF&	vec4VertexColor2,
		const float		fLineSize,
		const float		fOrthoLeft			= -1,
		const float		fOrthoRight			=  1,
		const float		fOrthoBottom		= -1,
		const float		fOrthoTop			=  1,
		const float		fNear				= -1,
		const float		fFar				=  1
	);

	// �����̎O�p�`�̕`��
	void DrawLineTriangle( 
		const Vector2DF&	vec2Position1, 
		const Vector2DF&	vec2Position2, 
		const Vector2DF&	vec2Position3,
		const Vector4DF&	vec4VertexColor1,
		const Vector4DF&	vec4VertexColor2,
		const Vector4DF&	vec4VertexColor3,
		const float		fLineSize,
		const float		fOrthoLeft			= -1,
		const float		fOrthoRight			=  1,
		const float		fOrthoBottom		= -1,
		const float		fOrthoTop			=  1,
		const float		fNear				= -1,
		const float		fFar				=  1
	);

	// �h��Ԃ��̎O�p�`�̕`��
	void DrawFilledTriangle( 
		const Vector2DF&	vec2Position1, 
		const Vector2DF&	vec2Position2, 
		const Vector2DF&	vec2Position3,
		const Vector4DF&	vec4VertexColor1,
		const Vector4DF&	vec4VertexColor2,
		const Vector4DF&	vec4VertexColor3,
		const float		fOrthoLeft			= -1,
		const float		fOrthoRight			=  1,
		const float		fOrthoBottom		= -1,
		const float		fOrthoTop			=  1,
		const float		fNear				= -1,
		const float		fFar				=  1
	);
	


}	// namespace NS_Graphic2D



}	// namespace NS_Graphic



#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_
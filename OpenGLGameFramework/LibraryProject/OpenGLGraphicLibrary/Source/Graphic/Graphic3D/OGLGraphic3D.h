#ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_
#define _INCLUDE_GUARD_OGLGRAPHIC3D_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#define _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_



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
// @purpose : 3�����O���t�B�b�N���O���
//
// @note : 
//
// �O���t�B�b�N�֘A�̓��A3D�O���t�B�b�N�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Graphic3D
{



	void DrawLine(
		const float			fLineWidth,
		const Vector3DF&	vec3Start,
		const Vector3DF&	vec3End
	);



	void DrawLines(
		const float						fLineWidth,
		const std::vector<Vector3DF>&	points
	);



	void DrawWireTriangle(
		const float			fLineWidth,
		const Vector3DF&	vec3Vertex1,
		const Vector3DF&	vec3Vertex2,
		const Vector3DF&	vec3Vertex3
	);



	void DrawWireTriangles(
		const float						fLineWidth,
		const std::vector<Vector3DF>&	points
	);



}	// namespace NS_Graphic3D



}	// namespace NS_Graphic



#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_
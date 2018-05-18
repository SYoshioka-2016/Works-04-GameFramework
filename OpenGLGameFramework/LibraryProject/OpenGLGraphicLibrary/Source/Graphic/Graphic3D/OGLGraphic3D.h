#ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_
#define _INCLUDE_GUARD_OGLGRAPHIC3D_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#define _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : グラフィック名前空間
//
// @note : 
//
// グラフィック関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Graphic
{



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 3次元グラフィック名前空間
//
// @note : 
//
// グラフィック関連の内、3Dグラフィックの関数やクラス等を管理する名前空間。
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
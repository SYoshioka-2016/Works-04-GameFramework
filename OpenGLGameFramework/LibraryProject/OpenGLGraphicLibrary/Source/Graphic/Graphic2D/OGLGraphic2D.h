#ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_
#define _INCLUDE_GUARD_OGLGRAPHIC2D_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



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
// @purpose : 2次元グラフィック名前空間
//
// @note : 
//
// グラフィック関連の内、2Dグラフィックの関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Graphic2D
{



	// 点の描画
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
	
	// 直線の描画
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

	// 直線の三角形の描画
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

	// 塗りつぶしの三角形の描画
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
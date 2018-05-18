#ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_
#define _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_



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
// @purpose : グラフィック数学名前空間
//
// @note : 
//
// グラフィック関連の内、数学系の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_GraphicMathematics
{



	// ベクトルの回転
	Vector3DF RotateVector( 
		const Vector3DF&	vec3Vector, 
		const Vector3DF&	vec3Axis, 
		const float			fDegreesAngle 
	);



QuaternionF RotateToQuaternion( const Vector3DF& vec3Axis, float fAngle );

Matrix4x4F QuaternionToMatrix( const QuaternionF& quat );

Vector3DF MatrixToEulerXYZ( const Matrix4x4F& mat4 );






	// 透視投影変換行列の取得( 右手座標系 )
	Matrix4x4F PerspectiveMatrixRH( 
		const float fFovy,
		const float fAspect,
		const float fZNear,
		const float fZFar
	);



	// 平行投影変換行列の取得( 右手座標系 )
	Matrix4x4F OrthoMatrixRH( 
		const float fLeft,
		const float fRight,
		const float fBottom,
		const float fTop,
		const float fZNear,
		const float fZFar
	);

	

	// 視点変換行列の取得( 右手座標系 )
	Matrix4x4F LookAtMatrixRH( 
		const Vector3DF& vec3Eye,
		const Vector3DF& vec3Center,
		const Vector3DF& vec3Up
	);

	// 視点変換行列の取得( 右手座標系 )
	Matrix4x4F LookAtMatrixRH( 
		const float fEyeX,
		const float fEyeY,
		const float fEyeZ,
		const float fCenterX,
		const float fCenterY,
		const float fCenterZ,
		const float fUpX,
		const float fUpY,
		const float fUpZ
	);



	// 拡大縮小行列の取得
	Matrix4x4F ScaleMatrix( const Vector3DF& vec3Scale );
	
	// 拡大縮小行列の取得
	Matrix4x4F ScaleMatrix( const float fX, const float fY, const float fZ );



	// 平行移動行列の取得( 右手座標系 )
	Matrix4x4F TranslateMatrixRH( const Vector3DF& vec3Translate );

	// 平行移動行列の取得( 右手座標系 )
	Matrix4x4F TranslateMatrixRH( const float fX, const float fY, const float fZ );



	// x軸回転行列の取得( 右手座標系 )
	Matrix4x4F RotateXAxisMatrixRH( const double dDegreesAngle );

	// y軸回転行列の取得( 右手座標系 )
	Matrix4x4F RotateYAxisMatrixRH( const double dDegreesAngle );

	// z軸回転行列の取得( 右手座標系 )
	Matrix4x4F RotateZAxisMatrixRH( const double dDegreesAngle );



}	// namespace NS_GraphicMathematics



}	// namespace NS_Graphic



#endif	// #ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_
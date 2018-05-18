//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#include "Transform.h"
#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
TRANSFORM::TRANSFORM() : 
	TRANSFORM(
		Vector3DF( 0, 0, 0 ),
		Vector3DF( 0, 0, 0 ),
		Vector3DF( 1, 1, 1 )
	)
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const Vector3DF& vec3Position	: 座標
// @param [in] / const Vector3DF& vec3Rotation	: 回転値
// @param [in] / const Vector3DF& vec3Scale		: スケール値
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
TRANSFORM::TRANSFORM( 
	const Vector3DF& vec3Position,
	const Vector3DF& vec3Rotation,
	const Vector3DF& vec3Scale
) : 
	position( vec3Position ),
	rotation( vec3Rotation ),
	scale( vec3Scale )
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 右ベクトルの取得
//
// @return / Vector3DF : 右ベクトル
//
// @note : 
//
// 右方向ベクトルを自身の回転値によって回転したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::GetRight() const 
{
	return RotateVector( Vector3DF( 1, 0, 0 ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 上ベクトルの取得
//
// @return / Vector3DF : 上ベクトル
//
// @note : 
//
// 上方向ベクトルを自身の回転値によって回転したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::GetUp() const 
{
	return RotateVector( Vector3DF( 0, 1, 0 ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 前ベクトルの取得
//
// @return / Vector3DF : 前ベクトル
//
// @note : 
//
// 前方向ベクトルを自身の回転値によって回転したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::GetForward() const 
{
	return RotateVector( Vector3DF( 0, 0, -1 ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ベクトルの回転
//
// @param [in] / const Vector3DF& vec3 : 方向ベクトル
//
// @return / Vector3DF : 回転したベクトル
//
// @note : 
//
// 指定のベクトルを自身の回転値によって回転したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::RotateVector( const Vector3DF& vec3 ) const
{
	Vector3DF vec3Ret;
/*
	// ベクトルをX軸回転する
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3,	VECTOR3DF_RIGHT,	rotation.x );

	// ベクトルをY軸回転する
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret, VECTOR3DF_UP,		rotation.y );

	// ベクトルをZ軸回転する
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret, VECTOR3DF_FORWARD,	rotation.z );
*/
	// ベクトルをY軸回転する
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3, VECTOR3DF_UP,		rotation.y );

	// ベクトルをX軸回転する
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret,	VECTOR3DF_RIGHT,	rotation.x );

	// ベクトルをZ軸回転する
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret, VECTOR3DF_FORWARD,	rotation.z );



	return vec3Ret.Normalized();
}
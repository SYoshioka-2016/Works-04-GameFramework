#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#define _INCLUDE_GUARD_TRANSFORM_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// 構造体定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : トランスフォーム構造体
//
// @note : 
//
// トランスフォーム情報を管理する構造体。
//----------------------------------------------------------------------------------------------------------------------------------
struct TRANSFORM 
{
	// 座標
	Vector3DF position;

	// 回転値
	Vector3DF rotation;

	// スケール値
	Vector3DF scale;


	
	// コンストラクタ
	TRANSFORM();

	// コンストラクタ
	TRANSFORM( 
		const Vector3DF& vec3Position,
		const Vector3DF& vec3Rotation,
		const Vector3DF& vec3Scale
	);


	
	// 右ベクトルの取得
	Vector3DF GetRight() const;

	// 上ベクトルの取得
	Vector3DF GetUp() const;

	// 前ベクトルの取得
	Vector3DF GetForward() const;

	// 右ベクトルプロパティ
	__declspec( property( get = GetRight ) ) Vector3DF right;
	
	// 上ベクトルプロパティ
	__declspec( property( get = GetUp ) ) Vector3DF up;
	
	// 前ベクトルプロパティ
	__declspec( property( get = GetForward ) ) Vector3DF forward;

private:

	// ベクトルの回転
	Vector3DF RotateVector( const Vector3DF& vec3 ) const;
};



//==================================================================================================================================
// 型定義
//==================================================================================================================================

// トランスフォーム型
typedef TRANSFORM Transform;



#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_
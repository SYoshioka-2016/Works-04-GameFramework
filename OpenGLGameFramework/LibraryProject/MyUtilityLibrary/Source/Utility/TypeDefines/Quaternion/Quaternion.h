#ifndef _INCLUDE_GUARD_QUATERNION_H_
#define _INCLUDE_GUARD_QUATERNION_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_FLOAT4_H_
#include "../Numeric/4Dimensions/Float4.h"
#endif	// #ifndef _INCLUDE_GUARD_FLOAT4_H_

#ifndef _INCLUDE_GUARD_VECTOR3DF_H_
#include "../Vector/Vector3DF.h"
#endif	// #ifndef _INCLUDE_GUARD_VECTOR3DF_H_



//==================================================================================================================================
// 構造体定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : クォータニオン構造体
//
// @note : 
//
// 4つの浮動小数値を管理し、クォータニオンを表現する構造体。
//----------------------------------------------------------------------------------------------------------------------------------
struct QUATERNION : public Float4
{
public:

	// コンストラクタ
	QUATERNION();

	// コンストラクタ
	QUATERNION( const float fW, const float fX, const float fY, const float fZ );
	
	// コンストラクタ
	QUATERNION( const float fW, const Vector3DF& vec3 );



	// 共役四元数化
	const QUATERNION& Conjugate();
	
	// 共役四元数
	QUATERNION Conjugated() const;



	// 乗算演算子オーバーロード( クォータニオン×クォータニオン )
	QUATERNION operator * ( const QUATERNION& quat ) const;
};



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline QUATERNION::QUATERNION() : Float4( 0, 0, 0, 0 )
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const float fW : W成分に代入する数値
// @param [in] / const float fX : X成分に代入する数値
// @param [in] / const float fY : Y成分に代入する数値
// @param [in] / const float fZ : Z成分に代入する数値
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline QUATERNION::QUATERNION( const float fW, const float fX, const float fY, const float fZ ) : 
	Float4( fX, fY, fZ, fW )
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const float		fW		: W成分に代入する数値
// @param [in] / const Vector3DF&	vec3	: 3次元ベクトルクラスの参照
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline QUATERNION::QUATERNION( const float fW, const Vector3DF& vec3 ) : 
	Float4( vec3.x, vec3.y, vec3.z, fW )
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 共役四元数化
//
// @return / const QUATERNION& : 自身の共役四元数の参照
//
// @note : 
//
// 自身を自身の共役四元数にする。
//----------------------------------------------------------------------------------------------------------------------------------
inline const QUATERNION& QUATERNION::Conjugate() 
{
	return ( *this = ( *this ).Conjugated() );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 共役四元数
//
// @return / QUATERNION : 自身の共役四元数
//
// @note : 
//
// 自身の共役四元数を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline QUATERNION QUATERNION::Conjugated() const
{
	return QUATERNION( this->w, -this->x, -this->y, -this->z );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 乗算演算子オーバーロード
//
// @param [in] / const QUATERNION& quat : クォータニオンに乗算するクォータニオン
//
// @return / QUATERNION : クォータニオンを乗算したクォータニオン
//
// @note : 
//
// クォータニオン構造体同士の乗算演算を定義する。
// クォータニオンを乗算したクォータニオンを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline QUATERNION QUATERNION::operator * ( const QUATERNION& quat ) const 
{
	Vector3DF	vec3_1( this->x, this->y, this->z );
	Vector3DF	vec3_2( quat.x, quat.y, quat.z );

	float		fW		= ( this->w * quat.w ) - Vector3DF::Dot( vec3_1, vec3_2 );

	Vector3DF	vec3XYZ = vec3_2 * this->w + vec3_1 * quat.w + Vector3DF::Cross( vec3_1, vec3_2 );



	return QUATERNION( fW, vec3XYZ );
}



#endif	// #ifndef _INCLUDE_GUARD_QUATERNION_H_
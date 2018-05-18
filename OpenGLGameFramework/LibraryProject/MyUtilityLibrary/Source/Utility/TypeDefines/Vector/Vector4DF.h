#ifndef _INCLUDE_GUARD_VECTOR4DF_H_
#define _INCLUDE_GUARD_VECTOR4DF_H_



//==================================================================================================================================
// マクロ定義
//==================================================================================================================================

// 1で初期化されたベクトル
#define VECTOR4DF_ONE		Vector4DF( 1, 1, 1, 1 )

// 零ベクトル
#define VECTOR4DF_ZERO		Vector4DF( 0, 0, 0, 0 )



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_CMATH_
#define _INCLUDE_GUARD_CMATH_
#include <cmath>
#endif	// #ifndef _INCLUDE_GUARD_CMATH_
/*
#ifndef _INCLUDE_GUARD_MATRIX4X4F_H_
#include "../Matrix/Matrix4x4F.h"
#endif	// #ifndef _INCLUDE_GUARD_MATRIX4X4F_H_
*/


//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 4次元ベクトルクラス
//
// @note : 
//
// 4次元ベクトルを表現したクラス。
// 4つの浮動小数値を管理し、4次元座標や4次元ベクトルとして扱えるようにする。
//----------------------------------------------------------------------------------------------------------------------------------
class Vector4DF 
{
public:

	// コンストラクタ
	Vector4DF();
	
	// コンストラクタ( ベクトル成分の引数 )
	Vector4DF( const float fX, const float fY, const float fZ, const float fW );
	
//	Vector4DF( const Vector2& vec2 );
	
	// コンストラクタ( コピーコンストラクタ )
	Vector4DF( const Vector4DF& vec4 );



	// ベクトルの正規化
	void Normalize();

	// 零ベクトルに初期化
	void ZeroClear();

	// ベクトルの大きさ
	float Length() const;

	// 2点の4次元座標間の距離
	float Distance( const Vector4DF& vec4 ) const;

	// 2点の4次元座標間の距離( クラス関数 )
	static float Distance( const Vector4DF& vec4A, const Vector4DF& vec4B );

	// 2つの4次元ベクトルの内積
	float Dot( const Vector4DF& vec4 ) const;

	// 2つの4次元ベクトルの内積( クラス関数 )
	static float Dot( const Vector4DF& vec4A, const Vector4DF& vec4B );
/*
	// 2つの4次元ベクトルの成す角度( 度数角 )
	float angle( const Vector4DF& vec4 ) const;

	// 2つの4次元ベクトルの成す角度( 度数角 )( クラス関数 )
	static float angle( const Vector4DF& vec4A, const Vector4DF& vec4B );
*/

	
	// 加算演算子オーバーロード
	Vector4DF operator + () const;
	
	// 加算演算子オーバーロード
	Vector4DF operator + ( const Vector4DF& vec4 ) const;
	
	// 減算演算子オーバーロード
	Vector4DF operator - () const;
	
	// 減算演算子オーバーロード
	Vector4DF operator - ( const Vector4DF& vec4 ) const;
	
	// 乗算演算子オーバーロード
	Vector4DF operator * ( const float fK ) const;
	
	// 乗算演算子オーバーロード
//	Vector4DF operator * ( Matrix4x4F& mat4 );
	
	// 除算演算子オーバーロード
	Vector4DF operator / ( const float fK ) const;

	// 代入演算子オーバーロード
	Vector4DF& operator = ( const Vector4DF& vec4 );

	// 加算代入演算子オーバーロード
	Vector4DF& operator += ( const Vector4DF& vec4 );
	
	// 減算代入演算子オーバーロード
	Vector4DF& operator -= ( const Vector4DF& vec4 );
	
	// 乗算代入演算子オーバーロード
	Vector4DF& operator *= ( const float fK );
	
	// 除算代入演算子オーバーロード
	Vector4DF& operator /= ( const float fK );

	// 等価演算子オーバーロード
	bool operator == ( const Vector4DF& vec4 );

	// 不等価演算子オーバーロード
	bool operator != ( const Vector4DF& vec4 );



float& operator [] ( const unsigned int uiIndex ) 
{
	return this->m[ uiIndex ];
}




public:

union
{
float m[4];
struct
{
	// メンバ変数

	// ベクトルのx成分
	float x;

	// ベクトルのy成分
	float y;

	// ベクトルのz成分
	float z;

	// ベクトルのw成分
	float w;
};
};
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
inline Vector4DF::Vector4DF() : 
	x( 0 ),
	y( 0 ),
	z( 0 ),
	w( 0 )
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const float fX : ベクトルのx成分
// @param [in] / const float fY : ベクトルのy成分
// @param [in] / const float fZ : ベクトルのz成分
// @param [in] / const float fW : ベクトルのw成分
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF::Vector4DF( const float fX, const float fY, const float fZ, const float fW ) : 
	x( fX ),
	y( fY ),
	z( fZ ),
	w( fW )
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF::Vector4DF( const Vector4DF& vec4 ) : 
	x( vec4.x ),
	y( vec4.y ),
	z( vec4.z ),
	w( vec4.w )
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ベクトルの正規化
//
// @note : 
//
// ベクトルを正規化する。
//----------------------------------------------------------------------------------------------------------------------------------
inline void Vector4DF::Normalize() 
{
	float fLength = Length();

	if ( 0.0f < fLength ) 
	{
		*this /= fLength;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 零ベクトルに初期化
//
// @note : 
//
// ベクトルを零ベクトルとして初期化する。
//----------------------------------------------------------------------------------------------------------------------------------
inline void Vector4DF::ZeroClear() 
{
	x = y = z = w = 0.0f;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ベクトルの大きさ
//
// @return / float : ベクトルの大きさ
//
// @note : 
//
// ベクトルの大きさを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::Length() const 
{
	return std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) + ( w * w ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2点の4次元座標間の距離
//
// @param [in] / const Vector4DF& vec4 : 4次元座標
//
// @return / float : 自身の座標と引数の座標の距離
//
// @note : 
//
// 2点の4次元座標間の距離を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::Distance( const Vector4DF& vec4 ) const 
{
	return Distance( *this, vec4 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2点の4次元座標間の距離( クラス関数 )
//
// @param [in] / const Vector4DF& vec4A : 4次元座標1
// @param [in] / const Vector4DF& vec4B : 4次元座標2
//
// @return / float : 2点の4次元座標間の距離
//
// @note : 
//
// 2点の4次元座標間の距離を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::Distance( const Vector4DF& vec4A, const Vector4DF& vec4B ) 
{
	return ( vec4A - vec4B ).Length();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2つの4次元ベクトルの内積
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトル
//
// @return / float : 自身のベクトルと引数のベクトルの内積
//
// @note : 
//
// 2つの4次元ベクトルの内積を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::Dot( const Vector4DF& vec4 ) const 
{
	return Dot( *this, vec4 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2つの4次元ベクトルの内積( クラス関数 )
//
// @param [in] / const Vector4DF& vec4A : 4次元ベクトル1
// @param [in] / const Vector4DF& vec4B : 4次元ベクトル2
//
// @return / float : 2つの4次元ベクトルの内積
//
// @note : 
//
// 2つの4次元ベクトルの内積を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::Dot( const Vector4DF& vec4A, const Vector4DF& vec4B ) 
{
	return ( vec4A.x * vec4B.x ) + ( vec4A.y * vec4B.y ) + ( vec4A.z * vec4B.z ) + ( vec4A.w * vec4B.w );
}


/*
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2つの4次元ベクトルの成す角度( 度数角 )
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトル
//
// @return / float : 自身のベクトルと引数のベクトルの成す角度
//
// @note : 
//
// 2つの4次元ベクトルの成す角度を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::angle( const Vector4DF& vec4 ) const 
{
	return angle( *this, vec4 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 2つの4次元ベクトルの成す角度( 度数角 )( クラス関数 )
//
// @param [in] / const Vector4DF& vec4A : 4次元ベクトル1
// @param [in] / const Vector4DF& vec4B : 4次元ベクトル2
//
// @return / float : 2つの4次元ベクトルの成す角度
//
// @note : 
//
// 2つの4次元ベクトルの成す角度を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline float Vector4DF::angle( const Vector4DF& vec4A, const Vector4DF& vec4B ) 
{
	return  std::acos( ( vec4A.dot( vec4B ) ) / ( vec4A.length * vec4B.length ) );
}
*/


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 加算演算子オーバーロード
//
// @return / Vector4DF : 自身のベクトル
//
// @note : 
//
// 自身のベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator + () const
{
	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 加算演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / Vector4DF : ベクトルの各成分を加算したベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の加算演算を定義する。
// ベクトルの各成分を加算したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator + ( const Vector4DF& vec4 ) const
{
	Vector4DF vec4Ret;

	vec4Ret.x = x + vec4.x;
	vec4Ret.y = y + vec4.y;
	vec4Ret.z = z + vec4.z;
	vec4Ret.w = w + vec4.w;



	return vec4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 減算演算子オーバーロード
//
// @return / Vector4DF : ベクトルの各成分の符号を反転したベクトル
//
// @note : 
//
// ベクトルの各成分の符号を反転したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator - () const
{
	return Vector4DF( -x, -y, -z, -w );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 減算演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / Vector4DF : ベクトルの各成分を減算したベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の減算演算を定義する。
// ベクトルの各成分を減算したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator - ( const Vector4DF& vec4 ) const
{
	Vector4DF vec4Ret;

	vec4Ret.x = x - vec4.x;
	vec4Ret.y = y - vec4.y;
	vec4Ret.z = z - vec4.z;
	vec4Ret.w = w - vec4.w;



	return vec4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 乗算演算子オーバーロード
//
// @param [in] / const float fK : ベクトルに乗算する定数
//
// @return / Vector4DF : ベクトルの各成分を乗算したベクトル
//
// @note : 
//
// 4次元ベクトルクラスと定数の乗算演算を定義する。
// ベクトルの各成分を乗算したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator * ( const float fK ) const
{
	Vector4DF vec4Ret;

	vec4Ret.x = x * fK;
	vec4Ret.y = y * fK;
	vec4Ret.z = z * fK;
	vec4Ret.w = w * fK;



	return vec4Ret;
}


/*
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 乗算演算子オーバーロード
//
// @param [in] / Matrix4x4F& mat4 : ベクトルに乗算する行列
//
// @return / Vector4DF : ベクトルの各成分を乗算したベクトル
//
// @note : 
//
// 4次元ベクトルクラスと4行4列マトリクスクラスの乗算演算を定義する。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator * ( Matrix4x4F& mat4 )
{
	Vector4DF vec4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			vec4Ret[i] += m[j] * mat4[j][i];
		}
	}



	return vec4Ret;
}
*/


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 除算演算子オーバーロード
//
// @param [in] / const float fK : ベクトルに除算する定数
//
// @return / Vector4DF : ベクトルの各成分を除算したベクトル
//
// @note : 
//
// 4次元ベクトルクラスと定数の除算演算を定義する。
// ベクトルの各成分を除算したベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Vector4DF::operator / ( const float fK ) const
{
	Vector4DF vec4Ret;

	vec4Ret.x = x / fK;
	vec4Ret.y = y / fK;
	vec4Ret.z = z / fK;
	vec4Ret.w = w / fK;



	return vec4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 代入演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / Vector4DF& : ベクトルの各成分を代入した自身のベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の代入演算を定義する。
// ベクトルの各成分を自身のベクトルの各成分に代入した自身のベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF& Vector4DF::operator = ( const Vector4DF& vec4 ) 
{
	x = vec4.x;
	y = vec4.y;
	z = vec4.z;
	w = vec4.w;



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 加算代入演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / Vector4DF& : ベクトルの各成分の加算結果を代入した自身のベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の加算代入演算を定義する。
// ベクトルの各成分と自身のベクトルの各成分の加算結果を代入した自身のベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF& Vector4DF::operator += ( const Vector4DF& vec4 )
{
	x += vec4.x;
	y += vec4.y;
	z += vec4.z;
	w += vec4.w;



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 減算代入演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / Vector4DF& : ベクトルの各成分の減算結果を代入した自身のベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の減算代入演算を定義する。
// ベクトルの各成分と自身のベクトルの各成分の減算結果を代入した自身のベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF& Vector4DF::operator -= ( const Vector4DF& vec4 )
{
	x -= vec4.x;
	y -= vec4.y;
	z -= vec4.z;
	w -= vec4.w;



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 乗算代入演算子オーバーロード
//
// @param [in] / const float fK : ベクトルに乗算する定数
//
// @return / Vector4DF& : ベクトルの各成分の乗算結果を代入した自身のベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の乗算代入演算を定義する。
// 自身のベクトルの各成分と定数の乗算結果を代入した自身のベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF& Vector4DF::operator *= ( const float fK ) 
{
	x *= fK;
	y *= fK;
	z *= fK;
	w *= fK;



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 除算代入演算子オーバーロード
//
// @param [in] / const float fK : ベクトルに除算する定数
//
// @return / Vector4DF& : ベクトルの各成分の除算結果を代入した自身のベクトル
//
// @note : 
//
// 4次元ベクトルクラス同士の除算代入演算を定義する。
// 自身のベクトルの各成分と定数の除算結果を代入した自身のベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF& Vector4DF::operator /= ( const float fK ) 
{
	x /= fK;
	y /= fK;
	z /= fK;
	w /= fK;



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 等価演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / bool : 等しいベクトルか?( true : 等しい | false : 異なる )
//
// @note : 
//
// 4次元ベクトルクラス同士が等しいベクトルか比較する。
// 全ての成分が一致すれば等しいベクトルと見なす。
//----------------------------------------------------------------------------------------------------------------------------------
inline bool Vector4DF::operator == ( const Vector4DF& vec4 ) 
{
	return ( x == vec4.x && y == vec4.y && z == vec4.z && w == vec4.w );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 不等価演算子オーバーロード
//
// @param [in] / const Vector4DF& vec4 : 4次元ベクトルクラスのインスタンス
//
// @return / bool : 異なるベクトルか?( true : 異なる | false : 等しい )
//
// @note : 
//
// 4次元ベクトルクラス同士が異なるベクトルか比較する。
// 各成分の内、1つでも異なれば異なるベクトルと見なす。
//----------------------------------------------------------------------------------------------------------------------------------
inline bool Vector4DF::operator != ( const Vector4DF& vec4 ) 
{
	return !( *this == vec4 );
}



#endif	// #ifndef _INCLUDE_GUARD_VECTOR4DF_H_
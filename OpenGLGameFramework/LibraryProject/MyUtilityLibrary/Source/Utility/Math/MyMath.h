#ifndef _INCLUDE_GUARD_MYMATH_H_
#define _INCLUDE_GUARD_MYMATH_H_


//==================================================================================================================================
// マクロ定義
//==================================================================================================================================

#define _USE_MATH_DEFINES



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MATH_H_
#define _INCLUDE_GUARD_MATH_H_
#include <math.h>
#endif	// #ifndef _INCLUDE_GUARD_MATH_H_

#ifndef _INCLUDE_GUARD_RANDOM_H_
#include "Random/Random.h"
#endif	// #ifndef _INCLUDE_GUARD_RANDOM_H_



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 度数角からラジアン角の変換
//
// @param [in] / const double dDegreesAngle : 度数角
//
// @return / double : 度数角を変換したラジアン角
//
// @note : 
//
// 指定の度数角をラジアン角に変換して返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline double DegreeToRadian( const double dDegreesAngle ) 
{
	return dDegreesAngle * ( 3.14 / 180.0 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ラジアン角から度数角の変換
//
// @param [in] / const double dDegreesAngle : 度数角
//
// @return / double : ラジアン角を変換した度数角
//
// @note : 
//
// 指定のラジアン角を度数角に変換して返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline double RadianToDegree( const double dRadiansAngle ) 
{
	return dRadiansAngle * ( 180.0 / M_PI );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 度数角のクランプ( 0〜360度 )
//
// @param [in] / double dDegreesAngle : 度数角
//
// @return / double : 0度以上360度未満の角度
//
// @note : 
//
// 指定の度数角を0から360度までの範囲内にクランプした数値を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline double ClampDegreesAngle0To360( double dDegreesAngle ) 
{
	while ( dDegreesAngle < 0 ) 
	{
		dDegreesAngle += 360;
	}

	while ( dDegreesAngle >= 360 ) 
	{
		dDegreesAngle -= 360.0;
	}



	return dDegreesAngle;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 数値の符号の取得
//
// @param [in] / const double dValue : 数値
//
// @return / int : 数値の符号( 1又は-1 )
//
// @note : 
//
// 指定の数値から符号を取り出して返す。
// 指定の数値が正数なら1、負数なら-1を返す。
// 指定の数値が0なら1を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline int GetSign( const double dValue ) 
{
	return ( 0.0 != dValue ) ? (int)( dValue / abs( dValue ) ) : 1;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 数値のクランプ
//
// @param [in] / const double dValue	: 数値
// @param [in] / const double dMin		: 範囲の最小値
// @param [in] / const double dMax		: 範囲の最大値
//
// @return / double : 指定の範囲内の数値
//
// @note : 
//
// 指定の数値を指定の範囲内にクランプした数値を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline double Clamp( const double dValue, const double dMin, const double dMax ) 
{
	if ( dValue < dMin ) { return dMin; }

	if ( dValue > dMax ) { return dMax; }



	return dValue;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 数値のループ
//
// @param [in] / const double dValue	: 数値
// @param [in] / const double dMin		: 範囲の最小値
// @param [in] / const double dMax		: 範囲の最大値
//
// @return / double : 指定の範囲内の数値
//
// @note : 
//
// 指定の数値が最大値を上回ったら最小値を、
// 最小値を下回ったら最大値を返す。
//----------------------------------------------------------------------------------------------------------------------------------
inline double Loop( const double dValue, const double dMin, const double dMax ) 
{
	if ( dValue < dMin ) { return dMax; }

	if ( dValue > dMax ) { return dMin; }



	return dValue;
}



#endif	// #ifndef _INCLUDE_GUARD_MYMATH_H_
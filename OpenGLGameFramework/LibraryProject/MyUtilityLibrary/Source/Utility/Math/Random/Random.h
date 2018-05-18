#ifndef _INCLUDE_GUARD_RANDOM_H_
#define _INCLUDE_GUARD_RANDOM_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_RANDOM_
#define _INCLUDE_GUARD_RANDOM_
#include <random>
#endif	// #ifndef _INCLUDE_GUARD_RANDOM_



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 乱数クラス
//
// @note : 
//
// 乱数のクラス関数を管理するクラス。
//----------------------------------------------------------------------------------------------------------------------------------
class Random 
{
public:

	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : int型乱数
	//
	// @param [in] / const int iMin : 乱数の範囲の最小値
	// @param [in] / const int iMax : 乱数の範囲の最大値
	//
	// @return / int : int型乱数値
	//
	// @note : 
	//
	// 最小値以上で最大値以下のint型乱数を返す
	//----------------------------------------------------------------------------------------------------------------------------------
	static int RandomInt( const int iMin, const int iMax )
	{
		std::random_device					device;
		std::mt19937						mt( device() );
		std::uniform_int_distribution<int>	uniformIntDistribution( iMin, iMax );

		return uniformIntDistribution( mt );
	}



	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : unsigned int型乱数
	//
	// @param [in] / const unsigned int uiMin : 乱数の範囲の最小値
	// @param [in] / const unsigned int uiMax : 乱数の範囲の最大値
	//
	// @return / unsigned int : unsigned int型乱数値
	//
	// @note : 
	//
	// 最小値以上で最大値以下のunsigned int型乱数を返す
	//----------------------------------------------------------------------------------------------------------------------------------
	static unsigned int RandomUInt( const unsigned int uiMin, const unsigned int uiMax )
	{
		std::random_device							device;
		std::mt19937								mt( device() );
		std::uniform_int_distribution<unsigned int>	uniformIntDistribution( uiMin, uiMax );

		return uniformIntDistribution( mt );
	}



	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : float型乱数
	//
	// @param [in] / const float fMin : 乱数の範囲の最小値
	// @param [in] / const float fMax : 乱数の範囲の最大値
	//
	// @return / float : float型乱数値
	//
	// @note : 
	//
	// 最小値以上で最大値以下のfloat型乱数を返す
	//----------------------------------------------------------------------------------------------------------------------------------
	static float RandomFloat( const float fMin, const float fMax )
	{
		std::random_device						device;
		std::mt19937							mt( device() );
		std::uniform_real_distribution<float>	uniformRealDistribution( fMin, fMax );

		return uniformRealDistribution( mt );
	}



	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : double型乱数
	//
	// @param [in] / const double dMin : 乱数の範囲の最小値
	// @param [in] / const double dMax : 乱数の範囲の最大値
	//
	// @return / double : double型乱数値
	//
	// @note : 
	//
	// 最小値以上で最大値以下のdouble型乱数を返す
	//----------------------------------------------------------------------------------------------------------------------------------
	static double RandomDouble( const double dMin, const double dMax )
	{
		std::random_device						device;
		std::mt19937							mt( device() );
		std::uniform_real_distribution<double>	uniformRealDistribution( dMin, dMax );

		return uniformRealDistribution( mt );
	}

private:

	// コンストラクタ
	Random();

	// デストラクタ
	~Random();
};



#endif	// #ifndef _INCLUDE_GUARD_RANDOM_H_
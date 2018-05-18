#ifndef _INCLUDE_GUARD_RANDOM_H_
#define _INCLUDE_GUARD_RANDOM_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_RANDOM_
#define _INCLUDE_GUARD_RANDOM_
#include <random>
#endif	// #ifndef _INCLUDE_GUARD_RANDOM_



//==================================================================================================================================
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �����N���X
//
// @note : 
//
// �����̃N���X�֐����Ǘ�����N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class Random 
{
public:

	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : int�^����
	//
	// @param [in] / const int iMin : �����͈̔͂̍ŏ��l
	// @param [in] / const int iMax : �����͈̔͂̍ő�l
	//
	// @return / int : int�^�����l
	//
	// @note : 
	//
	// �ŏ��l�ȏ�ōő�l�ȉ���int�^������Ԃ�
	//----------------------------------------------------------------------------------------------------------------------------------
	static int RandomInt( const int iMin, const int iMax )
	{
		std::random_device					device;
		std::mt19937						mt( device() );
		std::uniform_int_distribution<int>	uniformIntDistribution( iMin, iMax );

		return uniformIntDistribution( mt );
	}



	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : unsigned int�^����
	//
	// @param [in] / const unsigned int uiMin : �����͈̔͂̍ŏ��l
	// @param [in] / const unsigned int uiMax : �����͈̔͂̍ő�l
	//
	// @return / unsigned int : unsigned int�^�����l
	//
	// @note : 
	//
	// �ŏ��l�ȏ�ōő�l�ȉ���unsigned int�^������Ԃ�
	//----------------------------------------------------------------------------------------------------------------------------------
	static unsigned int RandomUInt( const unsigned int uiMin, const unsigned int uiMax )
	{
		std::random_device							device;
		std::mt19937								mt( device() );
		std::uniform_int_distribution<unsigned int>	uniformIntDistribution( uiMin, uiMax );

		return uniformIntDistribution( mt );
	}



	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : float�^����
	//
	// @param [in] / const float fMin : �����͈̔͂̍ŏ��l
	// @param [in] / const float fMax : �����͈̔͂̍ő�l
	//
	// @return / float : float�^�����l
	//
	// @note : 
	//
	// �ŏ��l�ȏ�ōő�l�ȉ���float�^������Ԃ�
	//----------------------------------------------------------------------------------------------------------------------------------
	static float RandomFloat( const float fMin, const float fMax )
	{
		std::random_device						device;
		std::mt19937							mt( device() );
		std::uniform_real_distribution<float>	uniformRealDistribution( fMin, fMax );

		return uniformRealDistribution( mt );
	}



	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : double�^����
	//
	// @param [in] / const double dMin : �����͈̔͂̍ŏ��l
	// @param [in] / const double dMax : �����͈̔͂̍ő�l
	//
	// @return / double : double�^�����l
	//
	// @note : 
	//
	// �ŏ��l�ȏ�ōő�l�ȉ���double�^������Ԃ�
	//----------------------------------------------------------------------------------------------------------------------------------
	static double RandomDouble( const double dMin, const double dMax )
	{
		std::random_device						device;
		std::mt19937							mt( device() );
		std::uniform_real_distribution<double>	uniformRealDistribution( dMin, dMax );

		return uniformRealDistribution( mt );
	}

private:

	// �R���X�g���N�^
	Random();

	// �f�X�g���N�^
	~Random();
};



#endif	// #ifndef _INCLUDE_GUARD_RANDOM_H_
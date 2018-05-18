#ifndef _INCLUDE_GUARD_MATRIX4X4F_H_
#define _INCLUDE_GUARD_MATRIX4X4F_H_



//==================================================================================================================================
// �}�N����`
//==================================================================================================================================

// �P�ʍs��
#define MATRIX4X4F_IDENTITY		Matrix4x4F( 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1 )

// ��s��
#define MATRIX4X4F_ZERO			Matrix4x4F( 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0 )



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_VECTOR4DF_H_
#include "../Vector/Vector4DF.h"
#endif	// #ifndef _INCLUDE_GUARD_VECTOR4DF_H_



//==================================================================================================================================
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 4�s4��}�g���N�X�N���X
//
// @note : 
//
// 4�s4��̍s���\�������N���X�B
// 16�̕��������l���Ǘ����A4�~4�s��Ƃ��Ĉ�����悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
class Matrix4x4F 
{
public:

	// �R���X�g���N�^
	Matrix4x4F();
	
	// �R���X�g���N�^
	Matrix4x4F( 
		const float fM11, const float fM12, const float fM13, const float fM14,
		const float fM21, const float fM22, const float fM23, const float fM24,
		const float fM31, const float fM32, const float fM33, const float fM34,
		const float fM41, const float fM42, const float fM43, const float fM44 
	);
	
	// �R���X�g���N�^
	Matrix4x4F( const float ( &fMatrix )[16] );



	// �P�ʍs��
	void Identity();

	// �s��̓]�u
	void Transpose();


	void ConsoleOutPut() const;


	
	// �Y�����Z�q�I�[�o�[���[�h
	float* operator [] ( const unsigned int uiIndex );

	// �P���v���X���Z�q�I�[�o�[���[�h
	Matrix4x4F operator + () const;

	// �P���}�C�i�X���Z�q�I�[�o�[���[�h
	Matrix4x4F operator - () const;
	
	// ���Z���Z�q�I�[�o�[���[�h
	Matrix4x4F operator + ( const Matrix4x4F& mat4 ) const;
	
	// ���Z���Z�q�I�[�o�[���[�h
	Matrix4x4F operator - ( const Matrix4x4F& mat4 ) const;
	
	// ��Z���Z�q�I�[�o�[���[�h( �s��~�萔 )
	Matrix4x4F operator * ( const float fK ) const;

	// ��Z���Z�q�I�[�o�[���[�h( �s��~�s�� )
	Matrix4x4F operator * ( const Matrix4x4F& mat4 ) const;

	// ��Z���Z�q�I�[�o�[���[�h( �s��~�x�N�g�� )
	Vector4DF operator * ( Vector4DF& vec4 ) const;
	
	// ���Z���Z�q�I�[�o�[���[�h( �s�񁀒萔 )
	Matrix4x4F operator / ( const float fK ) const;

	// ������Z�q�I�[�o�[���[�h
	const Matrix4x4F& operator = ( const Matrix4x4F& mat4 );

	// ������Z�q�I�[�o�[���[�h
	const Matrix4x4F& operator = ( const float ( &fMatrix )[16] );

	// ���Z������Z�q�I�[�o�[���[�h
	const Matrix4x4F& operator += ( const Matrix4x4F& mat4 );

	// ���Z������Z�q�I�[�o�[���[�h
	const Matrix4x4F& operator -= ( const Matrix4x4F& mat4 );

	// ��Z������Z�q�I�[�o�[���[�h( �s��~�萔 )
	const Matrix4x4F& operator *= ( const float fK );

	// ���Z������Z�q�I�[�o�[���[�h( �s�񁀒萔 )
	const Matrix4x4F& operator /= ( const float fK );

public:

	// �����o�ϐ�

	union
	{
		float		m[4][4];
		struct
		{
			float	_11, _12, _13, _14;
			float	_21, _22, _23, _24;
			float	_31, _32, _33, _34;
			float	_41, _42, _43, _44;
		};
		float		v[16];
	};
};



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F::Matrix4x4F()
{
	*this = MATRIX4X4F_ZERO;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @param [in] / const float fM11 : 1�s��1��ڂ̐���
// @param [in] / const float fM12 : 1�s��2��ڂ̐���
// @param [in] / const float fM13 : 1�s��3��ڂ̐���
// @param [in] / const float fM14 : 1�s��4��ڂ̐���
// @param [in] / const float fM21 : 2�s��1��ڂ̐���
// @param [in] / const float fM22 : 2�s��2��ڂ̐���
// @param [in] / const float fM23 : 2�s��3��ڂ̐���
// @param [in] / const float fM24 : 2�s��4��ڂ̐���
// @param [in] / const float fM31 : 3�s��1��ڂ̐���
// @param [in] / const float fM32 : 3�s��2��ڂ̐���
// @param [in] / const float fM33 : 3�s��3��ڂ̐���
// @param [in] / const float fM34 : 3�s��4��ڂ̐���
// @param [in] / const float fM41 : 4�s��1��ڂ̐���
// @param [in] / const float fM42 : 4�s��2��ڂ̐���
// @param [in] / const float fM43 : 4�s��3��ڂ̐���
// @param [in] / const float fM44 : 4�s��4��ڂ̐���
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F::Matrix4x4F( 
	const float fM11, const float fM12, const float fM13, const float fM14,
	const float fM21, const float fM22, const float fM23, const float fM24,
	const float fM31, const float fM32, const float fM33, const float fM34,
	const float fM41, const float fM42, const float fM43, const float fM44
) : 
	_11( fM11 ), _12( fM12 ), _13( fM13 ), _14( fM14 ),
	_21( fM21 ), _22( fM22 ), _23( fM23 ), _24( fM24 ),
	_31( fM31 ), _32( fM32 ), _33( fM33 ), _34( fM34 ),
	_41( fM41 ), _42( fM42 ), _43( fM43 ), _44( fM44 )
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @param [in] / const float ( &fMatrix )[16] : 4�~4�s���1�����z��
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F::Matrix4x4F( const float ( &fMatrix )[16] ) : 
	_11( fMatrix[0] ), _12( fMatrix[1] ), _13( fMatrix[2] ), _14( fMatrix[3] ),
	_21( fMatrix[4] ), _22( fMatrix[5] ), _23( fMatrix[6] ), _24( fMatrix[7] ),
	_31( fMatrix[8] ), _32( fMatrix[9] ), _33( fMatrix[10] ), _34( fMatrix[11] ),
	_41( fMatrix[12] ), _42( fMatrix[13] ), _43( fMatrix[14] ), _44( fMatrix[15] )
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �P�ʍs��
//
// @note : 
//
// �s���P�ʍs��ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
inline void Matrix4x4F::Identity() 
{
	*this = MATRIX4X4F_IDENTITY;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �s��̓]�u
//
// @note : 
//
// �s���]�u����B
//----------------------------------------------------------------------------------------------------------------------------------
inline void Matrix4x4F::Transpose() 
{
	int iOffset = 0;

	for ( int i = 0; i < 4 - 1; i++ ) 
	{
		for ( int j = 1 + iOffset; j < 4; j++ ) 
		{
			float fTmp	= m[i][j];
			m[i][j]		= m[j][i];
			m[j][i]		= fTmp;
		}

		iOffset++;
	} 
}



#ifndef _INCLUDE_GUARD_IOSTREAM_H_
#define _INCLUDE_GUARD_IOSTREAM_H_
#include <iostream>
#endif	// #ifndef _INCLUDE_GUARD_IOSTREAM_H_
inline void Matrix4x4F::ConsoleOutPut() const 
{
/*
	for ( int i = 0; i < 16; i++ ) 
	{
		printf( "%f", v[i] );

		if ( ( ( i + 1 ) % 4 ) != 0 ) 
		{ 
			printf( " " ); 
		}
		
		else 
		{
			printf( "\n" );
		}
	}
*/
	for ( int i = 0; i < 4; i++ ) 
	{
		printf( "%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3] );
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Y�����Z�q�I�[�o�[���[�h
//
// @param [in] / const unsigned int uiIndex : �s��̗v�f���i�[����񎟌��z��̍s�C���f�b�N�X
//
// @return / float* :  �s��̗v�f���i�[����񎟌��z��̗�̔z��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X�̓Y�������`����B
//----------------------------------------------------------------------------------------------------------------------------------
inline float* Matrix4x4F::operator [] ( const unsigned int uiIndex )
{
	return m[ ( uiIndex < 4 ) ? uiIndex : 4 - 1 ];
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �P���v���X���Z�q�I�[�o�[���[�h
//
// @return / Matrix4x4F : ���g�̍s��
//
// @note : 
//
// ���g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator + () const
{
	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �P���}�C�i�X���Z�q�I�[�o�[���[�h
//
// @return / Matrix4x4F : �s��̊e�����̕����𔽓]�����s��
//
// @note : 
//
// �s��̊e�����̕����𔽓]�����s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator - () const
{
	Matrix4x4F mat4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			mat4Ret[i][j] = -m[i][j];
		}
	}



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Z���Z�q�I�[�o�[���[�h
//
// @param [in] / const Matrix4x4F& mat4 : 4�s4��}�g���N�X�N���X�̃C���X�^���X
//
// @return / Matrix4x4F : �s��̊e���������Z�����s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X���m�̉��Z���Z���`����B
// �s��̊e���������Z�����s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator + ( const Matrix4x4F& mat4 ) const
{
	Matrix4x4F mat4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			mat4Ret[i][j] = m[i][j] + mat4.m[i][j];
		}
	}



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Z���Z�q�I�[�o�[���[�h
//
// @param [in] / const Matrix4x4F& mat4 : 4�s4��}�g���N�X�N���X�̃C���X�^���X
//
// @return / Matrix4x4F : �s��̊e���������Z�����s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X���m�̌��Z���Z���`����B
// �s��̊e���������Z�����s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator - ( const Matrix4x4F& mat4 ) const
{
	Matrix4x4F mat4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			mat4Ret[i][j] = m[i][j] - mat4.m[i][j];
		}
	}



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ��Z���Z�q�I�[�o�[���[�h( �s��~�萔 )
//
// @param [in] / const float fK : �s��ɏ�Z����萔
//
// @return / Matrix4x4F : �s��̊e��������Z�����s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X�ƒ萔�̏�Z���Z���`����B
// �s��̊e��������Z�����s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator * ( const float fK ) const
{
	Matrix4x4F mat4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			mat4Ret[i][j] = m[i][j] * fK;
		}
	}



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ��Z���Z�q�I�[�o�[���[�h( �s��~�s�� )
//
// @param [in] / const Matrix4x4F& mat4 : �s��ɏ�Z����s��
//
// @return / Matrix4x4F : �s��̊e��������Z�����s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X���m�̏�Z���Z���`����B
// �s��̊e��������Z�����s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator * ( const Matrix4x4F& mat4 ) const
{
	Matrix4x4F mat4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			mat4Ret[i][j] = 
				m[i][0] * mat4.m[0][j] +
				m[i][1] * mat4.m[1][j] +
				m[i][2] * mat4.m[2][j] +
				m[i][3] * mat4.m[3][j];
		}
	}



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ��Z���Z�q�I�[�o�[���[�h( �s��~�x�N�g�� )
//
// @param [in] / Vector4DF& vec4 : �s��ɏ�Z����x�N�g��
//
// @return / Vector4DF : �s�����Z�����x�N�g��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X��4�����x�N�g���N���X�̏�Z���Z���`����B
//----------------------------------------------------------------------------------------------------------------------------------
inline Vector4DF Matrix4x4F::operator * ( Vector4DF& vec4 ) const
{
	Vector4DF vec4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			vec4Ret[i] += m[i][j] * vec4[j];
		}
	}



	return vec4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Z���Z�q�I�[�o�[���[�h( �s�񁀒萔 )
//
// @param [in] / const float fK : �s��ɏ��Z����萔
//
// @return / Matrix4x4F : �s��̊e���������Z�����s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X�ƒ萔�̏��Z���Z���`����B
// �s��̊e���������Z�����s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline Matrix4x4F Matrix4x4F::operator / ( const float fK ) const
{
	Matrix4x4F mat4Ret;

	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			mat4Ret[i][j] = m[i][j] / fK;
		}
	}



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ������Z�q�I�[�o�[���[�h
//
// @param [in] / const Matrix4x4F& mat4 : 4�s4��}�g���N�X�N���X�̃C���X�^���X
//
// @return / const Matrix4x4F& : �s��̊e���������������g�̍s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X���m�̑�����Z���`����B
// �s��̊e���������g�̍s��̊e�����ɑ���������g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline const Matrix4x4F& Matrix4x4F::operator = ( const Matrix4x4F& mat4 ) 
{
	for ( int i = 0; i < 16; i++ ) 
	{
		v[i] = mat4.v[i];
	}



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ������Z�q�I�[�o�[���[�h
//
// @param [in] / const float ( &fMatrix )[16] : 4�~4�s���1�����z��
//
// @return / const Matrix4x4F& : �s��̊e���������������g�̍s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X��4�~4�s���1�����z��̑�����Z���`����B
// �s��̊e���������g�̍s��̊e�����ɑ���������g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline const Matrix4x4F& Matrix4x4F::operator = ( const float ( &fMatrix )[16] ) 
{
	for ( int i = 0; i < 16; i++ ) 
	{
		v[i] = fMatrix[i];
	}



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Z������Z�q�I�[�o�[���[�h
//
// @param [in] / const Matrix4x4F& mat4 : 4�s4��}�g���N�X�N���X�̃C���X�^���X
//
// @return / const Matrix4x4F& : �s��̊e�����̉��Z���ʂ����������g�̍s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X���m�̉��Z������Z���`����B
// �s��̊e�����Ǝ��g�̍s��̊e�����̉��Z���ʂ����������g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline const Matrix4x4F& Matrix4x4F::operator += ( const Matrix4x4F& mat4 )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			m[i][j] += mat4.m[i][j];
		}
	}



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Z������Z�q�I�[�o�[���[�h
//
// @param [in] / const Matrix4x4F& mat4 : 4�s4��}�g���N�X�N���X�̃C���X�^���X
//
// @return / const Matrix4x4F& : �s��̊e�����̌��Z���ʂ����������g�̍s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X���m�̌��Z������Z���`����B
// �s��̊e�����Ǝ��g�̍s��̊e�����̌��Z���ʂ����������g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline const Matrix4x4F& Matrix4x4F::operator -= ( const Matrix4x4F& mat4 )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			m[i][j] -= mat4.m[i][j];
		}
	}



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ��Z������Z�q�I�[�o�[���[�h( �s��~�萔 )
//
// @param [in] / const float fK : �s��ɏ�Z����萔
//
// @return / const Matrix4x4F& : �s��̊e�����̏�Z���ʂ����������g�̍s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X�ƒ萔�̏�Z������Z���`����B
// �s��̊e�����ƒ萔�̏�Z���ʂ����������g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline const Matrix4x4F& Matrix4x4F::operator *= ( const float fK )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			m[i][j] *= fK;
		}
	}



	return *this;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Z������Z�q�I�[�o�[���[�h( �s�񁀒萔 )
//
// @param [in] / const float fK : �s��ɏ��Z����萔
//
// @return / const Matrix4x4F& : �s��̊e�����̏��Z���ʂ����������g�̍s��
//
// @note : 
//
// 4�s4��}�g���N�X�N���X�ƒ萔�̏��Z������Z���`����B
// �s��̊e�����ƒ萔�̏��Z���ʂ����������g�̍s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline const Matrix4x4F& Matrix4x4F::operator /= ( const float fK )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			m[i][j] /= fK;
		}
	}



	return *this;
}



#endif	// #ifndef _INCLUDE_GUARD_MATRIX4X4F_H_
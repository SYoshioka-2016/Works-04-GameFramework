#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#define _INCLUDE_GUARD_TRANSFORM_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// �\���̒�`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �g�����X�t�H�[���\����
//
// @note : 
//
// �g�����X�t�H�[�������Ǘ�����\���́B
//----------------------------------------------------------------------------------------------------------------------------------
struct TRANSFORM 
{
	// ���W
	Vector3DF position;

	// ��]�l
	Vector3DF rotation;

	// �X�P�[���l
	Vector3DF scale;


	
	// �R���X�g���N�^
	TRANSFORM();

	// �R���X�g���N�^
	TRANSFORM( 
		const Vector3DF& vec3Position,
		const Vector3DF& vec3Rotation,
		const Vector3DF& vec3Scale
	);


	
	// �E�x�N�g���̎擾
	Vector3DF GetRight() const;

	// ��x�N�g���̎擾
	Vector3DF GetUp() const;

	// �O�x�N�g���̎擾
	Vector3DF GetForward() const;

	// �E�x�N�g���v���p�e�B
	__declspec( property( get = GetRight ) ) Vector3DF right;
	
	// ��x�N�g���v���p�e�B
	__declspec( property( get = GetUp ) ) Vector3DF up;
	
	// �O�x�N�g���v���p�e�B
	__declspec( property( get = GetForward ) ) Vector3DF forward;

private:

	// �x�N�g���̉�]
	Vector3DF RotateVector( const Vector3DF& vec3 ) const;
};



//==================================================================================================================================
// �^��`
//==================================================================================================================================

// �g�����X�t�H�[���^
typedef TRANSFORM Transform;



#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_
//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#include "Transform.h"
#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
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
// @purpose : �R���X�g���N�^
//
// @param [in] / const Vector3DF& vec3Position	: ���W
// @param [in] / const Vector3DF& vec3Rotation	: ��]�l
// @param [in] / const Vector3DF& vec3Scale		: �X�P�[���l
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
// @purpose : �E�x�N�g���̎擾
//
// @return / Vector3DF : �E�x�N�g��
//
// @note : 
//
// �E�����x�N�g�������g�̉�]�l�ɂ���ĉ�]�����x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::GetRight() const 
{
	return RotateVector( Vector3DF( 1, 0, 0 ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ��x�N�g���̎擾
//
// @return / Vector3DF : ��x�N�g��
//
// @note : 
//
// ������x�N�g�������g�̉�]�l�ɂ���ĉ�]�����x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::GetUp() const 
{
	return RotateVector( Vector3DF( 0, 1, 0 ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �O�x�N�g���̎擾
//
// @return / Vector3DF : �O�x�N�g��
//
// @note : 
//
// �O�����x�N�g�������g�̉�]�l�ɂ���ĉ�]�����x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::GetForward() const 
{
	return RotateVector( Vector3DF( 0, 0, -1 ) );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �x�N�g���̉�]
//
// @param [in] / const Vector3DF& vec3 : �����x�N�g��
//
// @return / Vector3DF : ��]�����x�N�g��
//
// @note : 
//
// �w��̃x�N�g�������g�̉�]�l�ɂ���ĉ�]�����x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF TRANSFORM::RotateVector( const Vector3DF& vec3 ) const
{
	Vector3DF vec3Ret;
/*
	// �x�N�g����X����]����
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3,	VECTOR3DF_RIGHT,	rotation.x );

	// �x�N�g����Y����]����
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret, VECTOR3DF_UP,		rotation.y );

	// �x�N�g����Z����]����
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret, VECTOR3DF_FORWARD,	rotation.z );
*/
	// �x�N�g����Y����]����
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3, VECTOR3DF_UP,		rotation.y );

	// �x�N�g����X����]����
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret,	VECTOR3DF_RIGHT,	rotation.x );

	// �x�N�g����Z����]����
	vec3Ret = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Ret, VECTOR3DF_FORWARD,	rotation.z );



	return vec3Ret.Normalized();
}
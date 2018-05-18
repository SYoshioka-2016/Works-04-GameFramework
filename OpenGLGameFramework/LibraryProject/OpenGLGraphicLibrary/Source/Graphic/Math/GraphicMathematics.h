#ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_
#define _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �O���t�B�b�N���O���
//
// @note : 
//
// �O���t�B�b�N�֘A�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Graphic
{



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �O���t�B�b�N���w���O���
//
// @note : 
//
// �O���t�B�b�N�֘A�̓��A���w�n�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_GraphicMathematics
{



	// �x�N�g���̉�]
	Vector3DF RotateVector( 
		const Vector3DF&	vec3Vector, 
		const Vector3DF&	vec3Axis, 
		const float			fDegreesAngle 
	);



QuaternionF RotateToQuaternion( const Vector3DF& vec3Axis, float fAngle );

Matrix4x4F QuaternionToMatrix( const QuaternionF& quat );

Vector3DF MatrixToEulerXYZ( const Matrix4x4F& mat4 );






	// �������e�ϊ��s��̎擾( �E����W�n )
	Matrix4x4F PerspectiveMatrixRH( 
		const float fFovy,
		const float fAspect,
		const float fZNear,
		const float fZFar
	);



	// ���s���e�ϊ��s��̎擾( �E����W�n )
	Matrix4x4F OrthoMatrixRH( 
		const float fLeft,
		const float fRight,
		const float fBottom,
		const float fTop,
		const float fZNear,
		const float fZFar
	);

	

	// ���_�ϊ��s��̎擾( �E����W�n )
	Matrix4x4F LookAtMatrixRH( 
		const Vector3DF& vec3Eye,
		const Vector3DF& vec3Center,
		const Vector3DF& vec3Up
	);

	// ���_�ϊ��s��̎擾( �E����W�n )
	Matrix4x4F LookAtMatrixRH( 
		const float fEyeX,
		const float fEyeY,
		const float fEyeZ,
		const float fCenterX,
		const float fCenterY,
		const float fCenterZ,
		const float fUpX,
		const float fUpY,
		const float fUpZ
	);



	// �g��k���s��̎擾
	Matrix4x4F ScaleMatrix( const Vector3DF& vec3Scale );
	
	// �g��k���s��̎擾
	Matrix4x4F ScaleMatrix( const float fX, const float fY, const float fZ );



	// ���s�ړ��s��̎擾( �E����W�n )
	Matrix4x4F TranslateMatrixRH( const Vector3DF& vec3Translate );

	// ���s�ړ��s��̎擾( �E����W�n )
	Matrix4x4F TranslateMatrixRH( const float fX, const float fY, const float fZ );



	// x����]�s��̎擾( �E����W�n )
	Matrix4x4F RotateXAxisMatrixRH( const double dDegreesAngle );

	// y����]�s��̎擾( �E����W�n )
	Matrix4x4F RotateYAxisMatrixRH( const double dDegreesAngle );

	// z����]�s��̎擾( �E����W�n )
	Matrix4x4F RotateZAxisMatrixRH( const double dDegreesAngle );



}	// namespace NS_GraphicMathematics



}	// namespace NS_Graphic



#endif	// #ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_
//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_
#include "GraphicMathematics.h"
#endif	// #ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �x�N�g���̉�]
//
// @param [in] / const Vector3DF&	vec3Vector		: ��]������x�N�g��
// @param [in] / const Vector3DF&	vec3Axis		: ��]���鎲
// @param [in] / const float		fAngle			: ��]�p( �x���p )
//
// @return / Vector3DF : ��]�����x�N�g��
//	
// @note : 
//
// �x�N�g����C�ӂ̎��ŔC�ӂ̉�]�p������]���A
// ��]��̃x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Vector3DF NS_Graphic::NS_GraphicMathematics::RotateVector( 
	const Vector3DF&	vec3Vector, 
	const Vector3DF&	vec3Axis, 
	const float			fDegreesAngle 
)
{
	// �w��̉�]���x�N�g���̑傫����0�Ȃ珈�����Ȃ�
	if ( vec3Axis.Length() <= 0 ) { return Vector3DF(); }



	// �x���p�̉�]�p�����W�A���p�ɂ���
	float fTheta = fDegreesAngle * (float)( M_PI / 180 );

	// ��]����x�N�g���̃N�H�[�^�j�I��
	QuaternionF quatP( 0, vec3Vector );

	// �w��̎��Ɏw��̊p�x��]����N�H�[�^�j�I��
	QuaternionF quatQ( 
		(float)( cos( fTheta / 2 ) ),
		( vec3Axis.Normalized() * sin( fTheta / 2 ) )
	);

	// �w��̎��Ɏw��̊p�x��]����N�H�[�^�j�I���̋����l����
	QuaternionF quatR( quatQ.Conjugated() );

	// ��]�����x�N�g���̃N�H�[�^�j�I��
	QuaternionF quatRPQ = quatR * quatP * quatQ;



	return Vector3DF( quatRPQ.x, quatRPQ.y, quatRPQ.z );
}






extern QuaternionF NS_Graphic::NS_GraphicMathematics::RotateToQuaternion( const Vector3DF& vec3Axis, float fAngle )
{

	Vector3DF vec3NormalizedAxis = vec3Axis.Normalized();

QuaternionF quatRet;
float fRadian = (float)( fAngle * ( M_PI / 180.0 ) / 2.0 );
float fSin = sin( fRadian );
quatRet.w = cos( fRadian );
quatRet.x = vec3NormalizedAxis.x * fSin;
quatRet.y = vec3NormalizedAxis.y * fSin;
quatRet.z = vec3NormalizedAxis.z * fSin;
return quatRet;
}

extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::QuaternionToMatrix( const QuaternionF& quat )
{
Vector3DF vec3S( quat.x * quat.x, quat.y * quat.y, quat.z * quat.z );
Vector3DF vec3C( quat.y * quat.z, quat.x * quat.z, quat.x * quat.y );
Vector3DF vec3W( quat.w * quat.x, quat.w * quat.y, quat.w * quat.z );

Matrix4x4F mat4Ret;

mat4Ret._11 = 1.0f - 2.0f * ( vec3S.y + vec3S.z );
mat4Ret._12 = 2.0f * ( vec3C.z + vec3W.z );
mat4Ret._13 = 2.0f * ( vec3C.y - vec3W.y );
mat4Ret._14 = 0.0f;
mat4Ret._21 = 2.0f * ( vec3C.z - vec3W.z );
mat4Ret._22 = 1.0f - 2.0f * ( vec3S.x + vec3S.z );
mat4Ret._23 = 2.0f * ( vec3C.x + vec3W.x );
mat4Ret._24 = 0.0f;
mat4Ret._31 = 2.0f * ( vec3C.y + vec3W.y );
mat4Ret._32 = 2.0f * ( vec3C.x - vec3W.x );
mat4Ret._33 = 1.0f - 2.0f * ( vec3S.x + vec3S.y );
mat4Ret._34 = 0.0f;
mat4Ret._41 = 0.0f;
mat4Ret._42 = 0.0f;
mat4Ret._43 = 0.0f;
mat4Ret._44 = 1.0f;


return mat4Ret;
}


extern Vector3DF NS_Graphic::NS_GraphicMathematics::MatrixToEulerXYZ( const Matrix4x4F& mat4 )
{

	Vector3DF vec3Ret;
	
	vec3Ret.x = atan2f( mat4._23, mat4._33 );

	vec3Ret.y = asinf( -mat4._13 );

	vec3Ret.z = atan2f( mat4._12, mat4._11 );


	vec3Ret *= (float)( 180.0 / M_PI );

	vec3Ret.y = (float)ClampDegreesAngle0To360( vec3Ret.y );
	if ( ( vec3Ret.y > 180 ) && ( vec3Ret.y <= 270 ) ) 
	{
		vec3Ret.x -= 180;
		vec3Ret.y  = 180 - vec3Ret.y;
		vec3Ret.z -= 180;
	}
	else if ( vec3Ret.y > 270 ) 
	{
		vec3Ret.x += 360;
		vec3Ret.z += 360;
	}



	return -vec3Ret;
}







//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �������e�ϊ��s��̎擾( �E����W�n )
//
// @param [in] / const float fFovy		: ����p
// @param [in] / const float fAspect	: �A�X�y�N�g��
// @param [in] / const float fZNear		: Near��
// @param [in] / const float fZFar		: Far��
//
// @return / Matrix4x4F : �E����W�n�̓������e�ϊ��s��
//
// @note : 
//
// �w��̈�������E����W�n�̓������e�ϊ��s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::PerspectiveMatrixRH( 
	const float fFovy,
	const float fAspect,
	const float fZNear,
	const float fZFar
) 
{
	float fRadian	= (float)( 2 * M_PI * fFovy / 360.0 );

	float f			= (float)( 1.0 / tan( fRadian / 2 ) );



	return 
		Matrix4x4F(
			f / fAspect, 0, 0, 0,
			0, f, 0, 0,
			0, 0, ( fZFar + fZNear ) / ( fZNear - fZFar ), -1,
			0, 0, ( 2 * fZFar * fZNear ) / ( fZNear - fZFar ), 0
		);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���s���e�ϊ��s��̎擾( �E����W�n )
//
// @param [in] / const float fLeft		: �X�N���[���̍��[
// @param [in] / const float fRight		: �X�N���[���̉E�[
// @param [in] / const float fBottom	: �X�N���[���̉��[
// @param [in] / const float fTop		: �X�N���[���̏�[
// @param [in] / const float fZNear		: Near��
// @param [in] / const float fZFar		: Far��
//
// @return / Matrix4x4F : �E����W�n�̕��s���e�ϊ��s��
//
// @note : 
//
// �w��̈�������E����W�n�̕��s���e�ϊ��s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::OrthoMatrixRH( 
	const float fLeft,
	const float fRight,
	const float fBottom,
	const float fTop,
	const float fZNear,
	const float fZFar
) 
{
	float fDx = fRight	- fLeft;
	float fDy = fTop	- fBottom;
	float fDz = fZFar	- fZNear;



	return 
		Matrix4x4F(
			2.0f / fDx, 0, 0, 0,
			0, 2.0f / fDy, 0, 0,
			0, 0, -2.0f / fDz, 0,
			-( fRight + fLeft ) / fDx, -( fTop + fBottom ) / fDy, -( fZFar + fZNear ) / fDz, 1.0f
		);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���_�ϊ��s��擾( �E����W�n )
//
// @param [in] / const Vector3DF& vec3Eye		: ���_
// @param [in] / const Vector3DF& vec3Center	: �����_
// @param [in] / const Vector3DF& vec3Up		: ��x�N�g��
//
// @return / Matrix4x4F : �E����W�n�̎��_�ϊ��s��
//
// @note : 
//
// �w��̈�������E����W�n�̎��_�ϊ��s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::LookAtMatrixRH( 
	const Vector3DF& vec3Eye,
	const Vector3DF& vec3Center,
	const Vector3DF& vec3Up
) 
{
	return 
		LookAtMatrixRH( 
			vec3Eye.x, vec3Eye.y, vec3Eye.z, 
			vec3Center.x, vec3Center.y, vec3Center.z, 
			vec3Up.x, vec3Up.y, vec3Up.z
		);
}

	

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���_�ϊ��s��̎擾( �E����W�n )
//
// @param [in] / const float fEyeX		: ���_��x���W
// @param [in] / const float fEyeY		: ���_��y���W
// @param [in] / const float fEyeZ		: ���_��z���W
// @param [in] / const float fCenterX	: �����_��x���W
// @param [in] / const float fCenterY	: �����_��y���W
// @param [in] / const float fCenterZ	: �����_��z���W
// @param [in] / const float fUpX		: ��x�N�g����x����
// @param [in] / const float fUpY		: ��x�N�g����y����
// @param [in] / const float fUpZ		: ��x�N�g����z����
//
// @return / Matrix4x4F : �E����W�n�̎��_�ϊ��s��
//
// @note : 
//
// �w��̈�������E����W�n�̎��_�ϊ��s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::LookAtMatrixRH( 
	const float fEyeX,
	const float fEyeY,
	const float fEyeZ,
	const float fCenterX,
	const float fCenterY,
	const float fCenterZ,
	const float fUpX,
	const float fUpY,
	const float fUpZ
) 
{
	Matrix4x4F mat4Ret;

	float fL;



	float fTx = fEyeX - fCenterX;
	float fTy = fEyeY - fCenterY;
	float fTz = fEyeZ - fCenterZ;

	fL = sqrtf( fTx * fTx + fTy * fTy + fTz * fTz );

	mat4Ret[0][2] = fTx / fL;
	mat4Ret[1][2] = fTy / fL;
	mat4Ret[2][2] = fTz / fL;



	fTx = fUpY * mat4Ret[2][2] - fUpZ * mat4Ret[1][2];
	fTy = fUpZ * mat4Ret[0][2] - fUpX * mat4Ret[2][2];
	fTz = fUpX * mat4Ret[1][2] - fUpY * mat4Ret[0][2];
	
	fL = sqrtf( fTx * fTx + fTy * fTy + fTz * fTz );

	mat4Ret[0][0] = fTx / fL;
	mat4Ret[1][0] = fTy / fL;
	mat4Ret[2][0] = fTz / fL;



	mat4Ret[0][1] = mat4Ret[1][2] * mat4Ret[2][0] - mat4Ret[2][2] * mat4Ret[1][0];
	mat4Ret[1][1] = mat4Ret[2][2] * mat4Ret[0][0] - mat4Ret[0][2] * mat4Ret[2][0];
	mat4Ret[2][1] = mat4Ret[0][2] * mat4Ret[1][0] - mat4Ret[1][2] * mat4Ret[0][0];



	mat4Ret[3][0] = -( fEyeX * mat4Ret[0][0] + fEyeY * mat4Ret[1][0] + fEyeZ * mat4Ret[2][0] );
	mat4Ret[3][1] = -( fEyeX * mat4Ret[0][1] + fEyeY * mat4Ret[1][1] + fEyeZ * mat4Ret[2][1] );
	mat4Ret[3][2] = -( fEyeX * mat4Ret[0][2] + fEyeY * mat4Ret[1][2] + fEyeZ * mat4Ret[2][2] );



	mat4Ret[0][3] = mat4Ret[1][3] = mat4Ret[2][3] = 0.0f;
	mat4Ret[3][3] = 1.0f;



	return mat4Ret;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �g��k���s��̎擾
//
// @param [in] / const Vector3DF& vec3Scale	: �X�P�[���l
//
// @return / Matrix4x4F : �g��k���s��
//
// @note : 
//
// �w��̈�������g��k���s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::ScaleMatrix( const Vector3DF& vec3Scale ) 
{
	return ScaleMatrix( vec3Scale.x, vec3Scale.y, vec3Scale.z );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �g��k���s��̎擾
//
// @param [in] / const float fX	: �X�P�[���l��x����
// @param [in] / const float fY	: �X�P�[���l��y����
// @param [in] / const float fZ	: �X�P�[���l��z����
//
// @return / Matrix4x4F : �g��k���s��
//
// @note : 
//
// �w��̈�������g��k���s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::ScaleMatrix( const float fX, const float fY, const float fZ ) 
{
	return 
		Matrix4x4F(
			fX,  0,  0,  0,
			 0, fY,  0,  0,
			 0,  0, fZ,  0,
			 0,  0,  0,  1
		);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���s�ړ��s��̎擾( �E����W�n )
//
// @param [in] / const Vector3DF& vec3Translate	: ���s�ړ���
//
// @return / Matrix4x4F : �E����W�n�̕��s�ړ��s��
//
// @note : 
//
// �w��̈�������E����W�n�̕��s�ړ��s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::TranslateMatrixRH( const Vector3DF& vec3Translate ) 
{
	return TranslateMatrixRH( vec3Translate.x, vec3Translate.y, vec3Translate.z );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���s�ړ��s��̎擾( �E����W�n )
//
// @param [in] / const float fX	: ���s�ړ��ʂ�x����
// @param [in] / const float fX	: ���s�ړ��ʂ�y����
// @param [in] / const float fX	: ���s�ړ��ʂ�z����
//
// @return / Matrix4x4F : �E����W�n�̕��s�ړ��s��
//
// @note : 
//
// �w��̈�������E����W�n�̕��s�ړ��s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::TranslateMatrixRH( const float fX, const float fY, const float fZ ) 
{
	return 
		Matrix4x4F(
			 1,  0,  0, 0,
			 0,  1,  0, 0,
			 0,  0,  1, 0,
			fX, fY, fZ, 1
		);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : x����]�s��̎擾( �E����W�n )
//
// @param [in] / const double dDegreesAngle	: ��]�p( �x���p )
//
// @return / Matrix4x4F : �E����W�n��x����]�s��
//
// @note : 
//
// �w��̈�������E����W�n��x����]�s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::RotateXAxisMatrixRH( const double dDegreesAngle ) 
{
	float fCos = (float)cos( DegreeToRadian( dDegreesAngle ) );
	float fSin = (float)sin( DegreeToRadian( dDegreesAngle ) );



	return 
		Matrix4x4F(
			1, 0, 0, 0,
			0, fCos, -fSin, 0,
			0, fSin, fCos, 0,
			0, 0, 0, 1
		);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : y����]�s��̎擾( �E����W�n )
//
// @param [in] / const double dDegreesAngle	: ��]�p( �x���p )
//
// @return / Matrix4x4F : �E����W�n��y����]�s��
//
// @note : 
//
// �w��̈�������E����W�n��y����]�s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::RotateYAxisMatrixRH( const double dDegreesAngle ) 
{
	float fCos = (float)cos( DegreeToRadian( dDegreesAngle ) );
	float fSin = (float)sin( DegreeToRadian( dDegreesAngle ) );



	return 
		Matrix4x4F(
			fCos, 0, fSin, 0,
			0, 1, 0, 0,
			-fSin, 0, fCos, 0,
			0, 0, 0, 1
		);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : z����]�s��̎擾( �E����W�n )
//
// @param [in] / const double dDegreesAngle	: ��]�p( �x���p )
//
// @return / Matrix4x4F : �E����W�n��z����]�s��
//
// @note : 
//
// �w��̈�������E����W�n��z����]�s���Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern Matrix4x4F NS_Graphic::NS_GraphicMathematics::RotateZAxisMatrixRH( const double dDegreesAngle ) 
{
	float fCos = (float)cos( DegreeToRadian( dDegreesAngle ) );
	float fSin = (float)sin( DegreeToRadian( dDegreesAngle ) );



	return 
		Matrix4x4F(
			fCos, -fSin, 0, 0,
			fSin, fCos, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
}
//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_STAGE_H_
#include "Stage.h"
#endif	// #ifndef _INCLUDE_GUARD_STAGE_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// �Q�[�����O���
using namespace NS_OpenGLWindowPCGame;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Stage::Stage()
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Stage::~Stage() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������
//
// @note : 
//
// �������������s���B
// �V�[���̏����������ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Stage::Initialize() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
// �X�V�������s���B
// �V�[���̍X�V�����ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Stage::Update() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �`�揈�����s���B
// �V�[���̕`�揈���ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Stage::Draw()
{
	const int iLineWidth			= 1;
	const int iVerticalLineCount	= 71;
	const int iHorizontalLineCount	= 71;


	
	glColor3f( 1.0, 1.0, 1.0 );

	DrawStageVerticalLines( iLineWidth, iVerticalLineCount );

	DrawStageHorizontalLines( iLineWidth, iHorizontalLineCount );
}



void Stage::DrawStageVerticalLines( const float fLineWidth, const unsigned int uiLineCount ) const 
{
	const int iHalfLineCount = static_cast<int>( uiLineCount ) / 2;

	for ( int i = 0; i < static_cast<int>( uiLineCount ); i++ ) 
	{
		float fPositionX = i - iHalfLineCount;

		NS_Graphic::NS_Graphic3D::DrawLine(
			fLineWidth,
			Vector3DF( fPositionX, 0, -iHalfLineCount ),
			Vector3DF( fPositionX, 0,  iHalfLineCount )
		);
	}
}



void Stage::DrawStageHorizontalLines( const float fLineWidth, const unsigned int uiLineCount ) const 
{
	const int iHalfLineCount = static_cast<int>( uiLineCount ) / 2;

	for ( int i = 0; i < static_cast<int>( uiLineCount ); i++ ) 
	{
		float fPositionZ = i - iHalfLineCount;

		NS_Graphic::NS_Graphic3D::DrawLine(
			fLineWidth,
			Vector3DF( -iHalfLineCount, 0, fPositionZ ),
			Vector3DF(  iHalfLineCount, 0, fPositionZ )
		);
	}
}
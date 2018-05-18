#ifndef _INCLUDE_GUARD_STAGE_H_
#define _INCLUDE_GUARD_STAGE_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Q�[�����O���
//
// @note : 
//
// �Q�[���A�v���P�[�V�����֘A�̊֐���N���X���Ǘ����閼�O��ԁB
// �Q�[�����\������N���X�͑S�Ă��̖��O��Ԃɒu���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_OpenGLWindowPCGame
{



//==================================================================================================================================
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�e�[�W�N���X
//
// @note : 
//
// �X�e�[�W���\������N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class Stage 
{
public:

	// �R���X�g���N�^
	Stage();

	// �f�X�g���N�^
	~Stage();



	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

private:

	void DrawStageVerticalLines( const float fLineWidth, const unsigned int uiLineCount ) const;

	void DrawStageHorizontalLines( const float fLineWidth, const unsigned int uiLineCount ) const;

private:

	// �����o�ϐ�
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_STAGE_H_
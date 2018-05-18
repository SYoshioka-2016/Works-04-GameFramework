#ifndef _INCLUDE_GUARD_OALSOUND_H_
#define _INCLUDE_GUARD_OALSOUND_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h���O���
//
// @note : 
//
// �T�E���h�֘A�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Sound 
{


	// OpenAL�̏�����
	void InitializeOpenAL();

	// �T�E���h�̓ǂݍ���
	void Load( const char* pcFileName, const char* pcSetSoundName );

	// �T�E���h�̍Đ�
	void Play( const char* pcSoundName = 0, const bool bIsLoop = false );

	// �T�E���h�̈ꎞ��~
	void Pause( const char* pcSoundName = 0 );

	// �T�E���h�̒�~
	void Stop( const char* pcSoundName = 0 );

	// ���ʂ̕ύX
	void ChangeVolume( const float fVolume );
	
	// ���ʂ̕ύX
	void ChangeVolume( const char* pcSoundName, const float fVolume );

	// �s�b�`�̕ύX
	void ChangePitch( const float fPitch );

	// �s�b�`�̐ݒ�
	void ChangePitch( const char* pcSoundName, const float fPitch );

	// �T�E���h�̃N���A
	void Clear();
	


}	// namespace NS_Sound



#endif	// #ifndef _INCLUDE_GUARD_OALSOUND_H_
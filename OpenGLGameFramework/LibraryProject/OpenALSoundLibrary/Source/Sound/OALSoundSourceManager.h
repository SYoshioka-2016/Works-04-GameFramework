#ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_
#define _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_MAP_
#include <map>
#endif	// #ifndef _INCLUDE_GUARD_MAP_



//==================================================================================================================================
// �O���錾
//==================================================================================================================================

// �T�E���h�\�[�X�N���X
namespace NS_Sound { class OALSoundSource; }



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



//==================================================================================================================================
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�\�[�X�Ǘ��N���X
//
// @extends / Singleton	: �V���O���g���N���X
//
// @note : 
//
// �V���O���g���N���X�B
// �T�E���h�\�[�X���Ǘ�����N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class OALSoundSourceManager : public Singleton<OALSoundSourceManager>
{
private:

	// �t�����h�N���X�w��

	// �V���O���g���N���X
	friend Singleton<OALSoundSourceManager>;

public:

	// �T�E���h�̓ǂݍ���
	void Load( const char* pcFileName, const char* pcSetSoundName );

	// �T�E���h�̍Đ�
	void Play( const char* pcSoundName = NULL, const bool bIsLoop = false );

	// �T�E���h�̈ꎞ��~
	void Pause( const char* pcSoundName = NULL );

	// �T�E���h�̒�~
	void Stop( const char* pcSoundName = NULL );

	// ���ʂ̐ݒ�
	void SetVolume( const float fVolume );

	// ���ʂ̐ݒ�
	void SetVolume( const char* pcSoundName, const float fVolume );

	// �s�b�`�̐ݒ�
	void SetPitch( const float fPitch );

	// �s�b�`�̐ݒ�
	void SetPitch( const char* pcSoundName, const float fPitch );

	// �T�E���h�̃N���A
	void Clear();

private:
	
	// �R���X�g���N�^
	OALSoundSourceManager();

	// �f�X�g���N�^
	~OALSoundSourceManager();

private:
	
	// �����o�ϐ�

	// ����
	float									m_fVolume;

	// �s�b�`
	float									m_fPitch;

	// �T�E���h�\�[�X�}�b�v
	std::map<std::string, OALSoundSource*>	m_SoundSourceMap;
};



}	// namespace NS_Sound 



#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_
#ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_
#define _INCLUDE_GUARD_OALSOUNDSOURCE_H_



//==================================================================================================================================
// �O���錾
//==================================================================================================================================

// �T�E���h�N���b�v���N���X
namespace NS_Sound { class SoundClip; }

// �T�E���h��ԗ�
namespace NS_Sound { enum SOUND_STATE; }



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
// @purpose : �T�E���h�\�[�X�N���X
//
// @note : 
//
// �T�E���h�N���b�v�N���X���Ǘ�����N���X�B
// �T�E���h�̍Đ����~���̑�����s���B
//----------------------------------------------------------------------------------------------------------------------------------
class OALSoundSource 
{
public:

	// �R���X�g���N�^
	OALSoundSource( SoundClip* soundClip );

	// �f�X�g���N�^
	~OALSoundSource();
	


	// �T�E���h�̍Đ�
	void Play( const bool bIsLoop = false );

	// �T�E���h�̈ꎞ��~
	void Pause();

	// �T�E���h�̒�~
	void Stop();

	// ���ʂ̕ύX
	void ChangeVolume( float fVolume ) const;

	// �s�b�`�̕ύX
	void ChangePitch( float fPitch ) const;



	// ���ʂ̎擾
	float GetVolume() const;

	// ���ʂ̐ݒ�
	void SetVolume( const float fVolume );

	// �s�b�`�̎擾
	float GetPitch() const;

	// �s�b�`�̐ݒ�
	void SetPitch( const float fPitch );

private:

	// �o�b�t�@�̐���
	void GenerateBuffer( const SoundClip* soundClip );

	// �\�[�X�̐���
	void GenerateSource();

	// ���݂̍Đ���Ԃ̎擾
	SOUND_STATE GetCurrentState() const;

protected:

	// �����o�ϐ�

	// �o�b�t�@�����t���O( true : �������� | false : �������ĂȂ� )
	bool				m_bIsCreatedBufferFlg;

	// �\�[�X�����t���O( true : �������� | false : �������ĂȂ� )
	bool				m_bIsCreatedSourceFlg;

	// �o�b�t�@
	unsigned int		m_uiBuffer;

	// �\�[�X
	unsigned int		m_uiSource;

	// ����
	float				m_fVolume;

	// �s�b�`
	float				m_fPitch;
};



}	// namespace NS_Sound 



#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_
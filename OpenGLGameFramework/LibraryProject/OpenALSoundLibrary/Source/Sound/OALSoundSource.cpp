//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_
#include "OALSoundSource.h"
#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_

#ifndef _INCLUDE_GUARD_SOUNDCLIP_H_
#include "SoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_SOUNDCLIP_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_ALC_H_
#include "../AL/alc.h"
#endif	// #ifndef _INCLUDE_GUARD_ALC_H_

#ifndef _INCLUDE_GUARD_AL_H_
#include "../AL/al.h"
#endif	// #ifndef _INCLUDE_GUARD_AL_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// �T�E���h���O���
using namespace NS_Sound;



//==================================================================================================================================
// �񋓒�`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h��ԗ�
//
// @note : 
//
// �T�E���h�̍Đ���Ԃ̗񋓁B
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Sound 
{
	enum SOUND_STATE
	{
		STANDBY,				// �ҋ@
		PLAYING,				// �Đ�
		PAUSED,					// �ꎞ��~
		STOPPED,				// ��~

		UNKNOWN_SOUND_STATE,
	};
}



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @param [in] / const SoundClip* soundClip : �T�E���h�N���b�v
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSource::OALSoundSource( SoundClip* soundClip ) :
	m_bIsCreatedBufferFlg( false ),
	m_bIsCreatedSourceFlg( false ),
	m_fVolume( 1.0f ),
	m_fPitch( 1.0f )
{ 
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( soundClip );



	// �o�b�t�@�̐���
	GenerateBuffer( soundClip );

	// �\�[�X�̐���
	GenerateSource();

	// ���ʂ̐ݒ�
	SetVolume( m_fVolume );

	// �s�b�`�̐ݒ�
	SetPitch( m_fPitch );



SAFE_DELETE( soundClip );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSource::~OALSoundSource() 
{
	// �T�E���h�̒�~
	Stop();

	// �\�[�X���폜
	alDeleteSources( 1, &m_uiSource );

	// �o�b�t�@���폜
	alDeleteBuffers( 1, &m_uiBuffer );

	

m_bIsCreatedBufferFlg = m_bIsCreatedSourceFlg = false;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̍Đ�
//
// @param [in] / const bool bIsLoop : ���[�v���邩?( true : ���[�v���� | false : ���[�v���Ȃ� )
//
// @note : 
//
// �T�E���h��1��Đ�����B
// �����Ŗ������[�v�Đ���ݒ�o����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::Play( const bool bIsLoop ) 
{
	// �Đ���ԂȂ珈�����Ȃ�
	if ( SOUND_STATE::PLAYING == GetCurrentState() ) { return; }



	// �\�[�X�̃��[�v�ݒ�
	alSourcei( m_uiSource, AL_LOOPING, ( bIsLoop ) ? AL_TRUE : AL_FALSE );

	// �\�[�X�̍Đ�
	alSourcePlay( m_uiSource );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̈ꎞ��~
//
// @note : 
//
// �T�E���h���ꎞ��~����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::Pause() 
{
	// �Đ���ԂłȂ��Ȃ珈�����Ȃ�
	if ( SOUND_STATE::PLAYING != GetCurrentState() ) { return; }



	// �\�[�X�̈ꎞ��~
	alSourcePause( m_uiSource );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̒�~
//
// @note : 
//
// �T�E���h���~����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::Stop() 
{
	// �Đ���ԂłȂ��Ȃ珈�����Ȃ�
	if ( SOUND_STATE::PLAYING != GetCurrentState() ) { return; }



	// �\�[�X�̒�~
	alSourceStop( m_uiSource );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ʂ̕ύX
//
// @param [in] / float fVolume : �ݒ肷�鉹��( �͈͂�0.0�`1.0 )
//
// @note : 
//
// ���ʂ��\�[�X�ɔ��f����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::ChangeVolume( float fVolume ) const
{
	// �\�[�X����������Ă��Ȃ���Ώ������Ȃ�
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// ���ʂ𒲐�
	if ( 0.0f > fVolume )		{ fVolume = 0.0f; }
	else if ( 1.0f < fVolume )	{ fVolume = 1.0f; }



	// �\�[�X�̉��ʂ�ݒ�
	alSourcef( m_uiSource, AL_GAIN, fVolume );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �s�b�`�̕ύX
//
// @param [in] / float fPitch : �ݒ肷��s�b�`( 0.0�ȏ� )
//
// @note : 
//
// �s�b�`���\�[�X�ɔ��f����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::ChangePitch( float fPitch ) const
{
	// �\�[�X����������Ă��Ȃ���Ώ������Ȃ�
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// �s�b�`�𒲐�
	if ( 0.0f > fPitch ) { fPitch = 0.0f; }



	// �\�[�X�̃s�b�`��ݒ�
	alSourcef( m_uiSource, AL_PITCH, fPitch );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ʂ̎擾
//
// @note : 
//
// ���ʂ��擾����B
//----------------------------------------------------------------------------------------------------------------------------------
float OALSoundSource::GetVolume() const 
{
	return m_fVolume;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ʂ̐ݒ�
//
// @param [in] / const float fVolume : �ݒ肷�鉹��( �͈͂�0.0�`1.0 )
//
// @note : 
//
// ���ʂ�ݒ肷��B
// �\�[�X�ւ̔��f���s���B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::SetVolume( const float fVolume ) 
{
	// �\�[�X����������Ă��Ȃ���Ώ������Ȃ�
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// ���ʂ�ݒ�
	if ( 0.0f > fVolume )		{ m_fVolume = 0.0f; }
	else if ( 1.0f < fVolume )	{ m_fVolume = 1.0f; }
	else						{ m_fVolume = fVolume; }

	// ���ʂ̕ύX
	ChangeVolume( m_fVolume );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �s�b�`�̎擾
//
// @note : 
//
// �s�b�`���擾����B
//----------------------------------------------------------------------------------------------------------------------------------
float OALSoundSource::GetPitch() const 
{
	return m_fPitch;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �s�b�`�̐ݒ�
//
// @param [in] / const float fPitch : �ݒ肷��s�b�`( 0.0�ȏ� )
//
// @note : 
//
// �s�b�`��ݒ肷��B
// �\�[�X�ւ̔��f���s���B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::SetPitch( const float fPitch ) 
{
	// �\�[�X����������Ă��Ȃ���Ώ������Ȃ�
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// �s�b�`�𒲐�
	if ( 0.0f > fPitch )	{ m_fPitch = 0.0f; }
	else					{ m_fPitch = fPitch; }

	// �s�b�`�̕ύX
	ChangePitch( m_fPitch );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �o�b�t�@�̐���
//
// @param [in] / const SoundClip* soundClip : �T�E���h�N���b�v
//
// @note : 
//
// �T�E���h�N���b�v�̃f�[�^����o�b�t�@�𐶐�����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::GenerateBuffer( const SoundClip* soundClip ) 
{
	// ���Ƀo�b�t�@����������Ă���Ώ������Ȃ�
	if ( m_bIsCreatedBufferFlg ) { return; }

	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( soundClip );



	// �t�H�[�}�b�g��ݒ�
	ALenum format;
	switch ( soundClip->GetFormat() )
	{
	case SOUND_FORMAT::MONAURAL_8:	format = AL_FORMAT_MONO8;		break;

	case SOUND_FORMAT::MONAURAL_16: format = AL_FORMAT_MONO16;		break;

	case SOUND_FORMAT::STEREO_8:	format = AL_FORMAT_STEREO8;		break;

	case SOUND_FORMAT::STEREO_16:	format = AL_FORMAT_STEREO16;	break;

	default: 

		HALT( "�Ή����Ȃ��t�H�[�}�b�g�ł��B" ); 
		SAFE_DELETE( soundClip );
		break;
	}



	// �o�b�t�@���쐬
	alGenBuffers( 1, &m_uiBuffer );

	// �o�b�t�@�ɔg�`�f�[�^���Z�b�g
	alBufferData(
		m_uiBuffer,
		format,
		soundClip->GetWaveData(),
		soundClip->GetWaveDataSize(),
		soundClip->GetSamplingRate()
	);



	// �o�b�t�@�����t���O�𗧂Ă�
	m_bIsCreatedBufferFlg = true;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �\�[�X�̐���
//
// @note : 
//
// �o�b�t�@����\�[�X�𐶐�����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::GenerateSource() 
{
	// ���Ƀ\�[�X����������Ă���Ώ������Ȃ�
	if ( m_bIsCreatedSourceFlg ) { return; }

	// �o�b�t�@����������Ă��Ȃ���Ώ������Ȃ�
	if ( !m_bIsCreatedBufferFlg ) { return; }



	// �\�[�X���쐬
	alGenSources( 1, &m_uiSource );

	// �\�[�X��ݒ�
	alSourcei( m_uiSource, AL_BUFFER, m_uiBuffer );



	// �\�[�X�����t���O�𗧂Ă�
	m_bIsCreatedSourceFlg = true;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���݂̍Đ���Ԃ̎擾
//
// @return / SOUND_STATE : ���݂̍Đ����
//	
// @note : 
//
// �T�E���h�̌��݂̍Đ���Ԃ��擾����B
//----------------------------------------------------------------------------------------------------------------------------------
SOUND_STATE OALSoundSource::GetCurrentState() const
{
	STRONG_ASSERT( m_bIsCreatedSourceFlg && "�\�[�X����������Ă��܂���B" );



	// �\�[�X�̏�Ԃ��擾
	int state = 0;
	alGetSourcei( m_uiSource, AL_SOURCE_STATE, &state );
	
	// �\�[�X�̏�ԕʂɏ���
	switch ( state )
	{

	// �ҋ@���
	case AL_INITIAL:	return SOUND_STATE::STANDBY;

	// �Đ����
	case AL_PLAYING:	return SOUND_STATE::PLAYING;

	// �ꎞ��~���
	case AL_PAUSED:		return SOUND_STATE::PAUSED;

	// ��~���
	case AL_STOPPED:	return SOUND_STATE::STOPPED;



	default:			return SOUND_STATE::UNKNOWN_SOUND_STATE;
	}
}
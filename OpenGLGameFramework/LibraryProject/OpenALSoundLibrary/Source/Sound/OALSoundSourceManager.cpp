//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_
#include "OALSoundSourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_

#ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_
#include "OALSoundSource.h"
#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_

#ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_
#include "WavSoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// �T�E���h���O���
using namespace NS_Sound;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSourceManager::OALSoundSourceManager() :
	m_fVolume( 1.0f ),
	m_fPitch( 1.0f )
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSourceManager::~OALSoundSourceManager() 
{
	// �T�E���h�̃N���A
	Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̓ǂݍ���
//
// @param [in] / const char* pcFileName		: �f�B���N�g���Ɗg���q���܂ރT�E���h�t�@�C����
// @param [in] / const char* pcSetSoundName : �}�b�v�R���e�i�ɓo�^����L�[�ƂȂ�T�E���h��
//
// @note : 
//
// �T�E���h�t�@�C����ǂݍ��݁A�T�E���h�𐶐�����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Load( const char* pcFileName, const char* pcSetSoundName ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pcFileName );
	ASSERT_POINTER_CHECK( pcSetSoundName );



	// ���ɃL�[���o�^����Ă���( �T�E���h���ǂݍ��܂�Ă��� )�Ȃ珈�����Ȃ�
	if ( m_SoundSourceMap.count( pcSetSoundName ) >= 1 ) { HALT( "���ɓǂݍ��܂�Ă��܂��B" ); return; }



	// �t�@�C�����\����
	FILE_NAME_STRUCTURE filename( pcFileName );

	// ��������T�E���h�N���b�v
	SoundClip*			pSoundClip		= NULL;

	// �R���e�i�ɒǉ�����T�E���h�\�[�X
	OALSoundSource*		pSoundSource	= NULL;



	// �t�H�[�}�b�g�ʂɃT�E���h�N���b�v�𐶐�

	// WAVE�t�@�C���̏ꍇ
	if ( strcmp( filename.GetExtensions().c_str(), ".wav" ) == 0 ) 
	{
		// WAVE�t�H�[�}�b�g�T�E���h�N���b�v�𐶐�
		pSoundClip = new WavSoundClip;
	}

	// �Ή����Ă��Ȃ��t�H�[�}�b�g�͓ǂݍ��܂Ȃ�
	else 
	{
		HALT( "�Ή����Ă��Ȃ��t�H�[�}�b�g�ł��B" ); return;
	}



	// �T�E���h��ǂݍ���
	if ( FAILED( pSoundClip->Load( pcFileName ) ) ) 
	{
		SAFE_DELETE( pSoundClip );
		HALT( "�T�E���h�̓ǂݍ��݂Ɏ��s���܂����B" ); return;
	};

	// �T�E���h�\�[�X�𐶐�
	pSoundSource = new OALSoundSource( pSoundClip );

	// �T�E���h�\�[�X�̉��ʂ�ύX
	pSoundSource->ChangeVolume( m_fVolume * pSoundSource->GetVolume() );

	// �T�E���h�\�[�X�̃s�b�`��ύX
	pSoundSource->ChangePitch( m_fPitch * pSoundSource->GetPitch() );

	// �R���e�i�ɃT�E���h�\�[�X��ǉ�
	m_SoundSourceMap[ pcSetSoundName ] = pSoundSource;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̍Đ�
//
// @param [in] / const char*	pcSoundName	: �}�b�v�R���e�i�ɂ���v�f���w�肷��L�[�ƂȂ�T�E���h��
// @param [in] / const bool		bIsLoop		: ���[�v���邩?( true : ���[�v���� | false : ���[�v���Ȃ� )( �ȗ������false�ɂȂ� )
//
// @note : 
//
// ( �w��� )�T�E���h���Đ�����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Play( const char* pcSoundName, const bool bIsLoop ) 
{
	// �w��̃T�E���h���L��ꍇ
	if ( POINTER_CHECK( pcSoundName ) ) 
	{
		// �R���e�i�Ɏw��̗v�f��������Ώ������Ȃ�
		if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "�w��̃T�E���h������܂���B" ); return; }



		// �w��̃T�E���h���Đ�
		m_SoundSourceMap.at( pcSoundName )->Play( bIsLoop );
	}
	// �w��̃T�E���h�������ꍇ
	else 
	{
		// �R���e�i���̑S�ẴT�E���h���Đ�
		std::for_each( 
			m_SoundSourceMap.begin(), 
			m_SoundSourceMap.end(), 
			[&] ( std::pair<std::string, OALSoundSource*> pair ) { pair.second->Play( bIsLoop ); }
		);
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̈ꎞ��~
//
// @param [in] / const char* pcSoundName	: �}�b�v�R���e�i�ɂ���v�f���w�肷��L�[�ƂȂ�T�E���h��
//
// @note : 
//
// ( �w��� )�T�E���h���ꎞ��~����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Pause( const char* pcSoundName ) 
{
	// �w��̃T�E���h���L��ꍇ
	if ( POINTER_CHECK( pcSoundName ) ) 
	{
		// �R���e�i�Ɏw��̗v�f��������Ώ������Ȃ�
		if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "�w��̃T�E���h������܂���B" ); return; }



		// �w��̃T�E���h���ꎞ��~
		m_SoundSourceMap.at( pcSoundName )->Pause();
	}
	// �w��̃T�E���h�������ꍇ
	else 
	{
		// �R���e�i���̑S�ẴT�E���h���ꎞ��~
		std::for_each( 
			m_SoundSourceMap.begin(), 
			m_SoundSourceMap.end(), 
			[&] ( std::pair<std::string, OALSoundSource*> pair ) { pair.second->Pause(); }
		);
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̒�~
//
// @param [in] / const char* pcSoundName	: �}�b�v�R���e�i�ɂ���v�f���w�肷��L�[�ƂȂ�T�E���h��
//
// @note : 
//
// ( �w��� )�T�E���h���~����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Stop( const char* pcSoundName ) 
{
	// �w��̃T�E���h���L��ꍇ
	if ( POINTER_CHECK( pcSoundName ) ) 
	{
		// �R���e�i�Ɏw��̗v�f��������Ώ������Ȃ�
		if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "�w��̃T�E���h������܂���B" ); return; }



		// �w��̃T�E���h���~
		m_SoundSourceMap.at( pcSoundName )->Stop();
	}
	// �w��̃T�E���h�������ꍇ
	else 
	{
		// �R���e�i���̑S�ẴT�E���h���~
		std::for_each( 
			m_SoundSourceMap.begin(), 
			m_SoundSourceMap.end(), 
			[&] ( std::pair<std::string, OALSoundSource*> pair ) { pair.second->Stop(); }
		);
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ʂ̐ݒ�
//
// @param [in] / const float fVolume : �ݒ肷�鉹��( �͈͂�0.0�`1.0 )
//
// @note : 
//
// �T�E���h�\�[�X�S�̂̉��ʂ�ݒ肷��B
// �e�T�E���h�\�[�X�̉��ʂ̕ύX���s���B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetVolume( const float fVolume ) 
{
	// ���ʂ�ݒ�
	if ( 0.0f > fVolume )		{ m_fVolume = 0.0f; }
	else if ( 1.0f < fVolume )	{ m_fVolume = 1.0f; }
	else						{ m_fVolume = fVolume; }



	// �e�T�E���h�\�[�X�̉��ʂɑS�̂̉��ʂ𔽉f����
	std::for_each( 
		m_SoundSourceMap.begin(), 
		m_SoundSourceMap.end(), 
		[&] ( std::pair<std::string, OALSoundSource*> pair ) 
		{ 
			pair.second->ChangeVolume( m_fVolume * pair.second->GetVolume() ); 
		}
	);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ʂ̐ݒ�
//
// @param [in] / const char* pcSoundName	: �}�b�v�R���e�i�ɂ���v�f���w�肷��L�[�ƂȂ�T�E���h��
// @param [in] / const float fVolume		: �ݒ肷�鉹��( �͈͂�0.0�`1.0 )
//
// @note : 
//
// �w��̃T�E���h�\�[�X�̉��ʂ�ݒ肷��B
// �w��̃T�E���h�\�[�X�̉��ʂ̕ύX���s���B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetVolume( const char* pcSoundName, const float fVolume ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pcSoundName );



	// �R���e�i�Ɏw��̗v�f��������Ώ������Ȃ�
	if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "�w��̃T�E���h������܂���B" ); return; }

	

	// �w��̃T�E���h�\�[�X�̉��ʂ�ݒ�
	m_SoundSourceMap.at( pcSoundName )->SetVolume( fVolume );

	// �w��̃T�E���h�\�[�X�̉��ʂ�ύX
	m_SoundSourceMap.at( pcSoundName )->ChangeVolume( m_fVolume * m_SoundSourceMap.at( pcSoundName )->GetVolume() );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �s�b�`�̐ݒ�
//
// @param [in] / const float fPitch : �ݒ肷��s�b�`( 0.0�ȏ� )
//
// @note : 
//
// �T�E���h�\�[�X�S�̂̃s�b�`��ݒ肷��B
// �e�T�E���h�\�[�X�̃s�b�`�̕ύX���s���B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetPitch( const float fPitch ) 
{
	// �s�b�`��ݒ�
	if ( 0.0f > fPitch )	{ m_fPitch = 0.0f; }
	else					{ m_fPitch = fPitch; }



	// �e�T�E���h�\�[�X�̃s�b�`�ɑS�̂̃s�b�`�𔽉f����
	std::for_each( 
		m_SoundSourceMap.begin(), 
		m_SoundSourceMap.end(), 
		[&] ( std::pair<std::string, OALSoundSource*> pair ) 
		{ 
			pair.second->ChangePitch( m_fPitch * pair.second->GetPitch() ); 
		}
	);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �s�b�`�̐ݒ�
//
// @param [in] / const char* pcSoundName	: �}�b�v�R���e�i�ɂ���v�f���w�肷��L�[�ƂȂ�T�E���h��
// @param [in] / const float fPitch			: �ݒ肷��s�b�`( 0.0�ȏ� )
//
// @note : 
//
// �w��̃T�E���h�\�[�X�̃s�b�`��ݒ肷��B
// �w��̃T�E���h�\�[�X�̃s�b�`�̕ύX���s���B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetPitch( const char* pcSoundName, const float fPitch ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pcSoundName );



	// �R���e�i�Ɏw��̗v�f��������Ώ������Ȃ�
	if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "�w��̃T�E���h������܂���B" ); return; }

	

	// �w��̃T�E���h�\�[�X�̃s�b�`��ݒ�
	m_SoundSourceMap.at( pcSoundName )->SetPitch( fPitch );

	// �w��̃T�E���h�\�[�X�̃s�b�`��ύX
	m_SoundSourceMap.at( pcSoundName )->ChangePitch( m_fPitch * m_SoundSourceMap.at( pcSoundName )->GetPitch() );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �T�E���h�̃N���A
//
// @note : 
//
// �R���e�i���̃T�E���h���N���A����B
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Clear() 
{
	std::for_each( 
		m_SoundSourceMap.begin(), 
		m_SoundSourceMap.end(), 
		[&] ( std::pair<std::string, OALSoundSource*> pair ) { SAFE_DELETE( pair.second ); }
	);

	m_SoundSourceMap.clear();
}
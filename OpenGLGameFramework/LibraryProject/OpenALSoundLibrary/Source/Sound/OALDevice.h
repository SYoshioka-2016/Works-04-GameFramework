#ifndef _INCLUDE_GUARD_OALDEVICE_H_
#define _INCLUDE_GUARD_OALDEVICE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_

#ifndef _INCLUDE_GUARD_ALC_H_
#include "../AL/alc.h"
#endif	// #ifndef _INCLUDE_GUARD_ALC_H_

#ifndef _INCLUDE_GUARD_AL_H_
#include "../AL/al.h"
#endif	// #ifndef _INCLUDE_GUARD_AL_H_



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
// @purpose : OpenAL�f�o�C�X�Ǘ��N���X
//
// @extends / Singleton	: �V���O���g���N���X
//
// @note : 
//
// �V���O���g���N���X�B
// OpenAL�̃f�o�C�X��R���e�L�X�g���Ǘ�����B
//----------------------------------------------------------------------------------------------------------------------------------
class OALDevice : public Singleton<OALDevice>
{
private:

	// �t�����h�N���X�w��

	// �V���O���g���N���X
	friend Singleton<OALDevice>;

public:

	// OpenAL�f�o�C�X�̏�����
	HRESULT Initialize();

	// �������
	void Release();

	// �R���e�L�X�g�̗L���ݒ�
	void Activate();

	// �R���e�L�X�g�̖����ݒ�
	void Deactivate();

private:

	// �R���X�g���N�^
	OALDevice();

	// �f�X�g���N�^
	~OALDevice();



	// OpenAL�̃G���[���m
	bool IsError();

private:

	// �����o�ϐ�

	// �f�o�C�X�����t���O( true : �������� | false : �������ĂȂ� )
	bool				m_bIsCreatedFlg;

	// OpenAL�f�o�C�X
	ALCdevice*			m_pDevice;

	// OpenAL�R���e�L�X�g
	ALCcontext*			m_pContext;
};



}	// namespace NS_Sound 



#endif	// #ifndef _INCLUDE_GUARD_OALDEVICE_H_
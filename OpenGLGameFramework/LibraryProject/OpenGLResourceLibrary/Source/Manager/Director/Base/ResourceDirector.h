#ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
#define _INCLUDE_GUARD_RESOURCEDIRECTOR_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_RESOURCEDATA_H_
#include "../../../ResourceInfo/ResourceData.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDATA_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X���O���
//
// @note : 
//
// ���\�[�X�֘A�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Resource
{



//==================================================================================================================================
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�f�B���N�^�N���X
//
// @note : 
//
// ���\�[�X���Ǘ�����N���X�B
// �e�N�X�`����T�E���h�Ȃǂ̃f�B���N�^�N���X�̃x�[�X�ƂȂ�B
//----------------------------------------------------------------------------------------------------------------------------------
class ResourceDirector
{
public:

	// �R���X�g���N�^
	ResourceDirector( const eRESOURCE_TYPE& resourceType );

	// �f�X�g���N�^
	virtual ~ResourceDirector();



	// ���\�[�X�̓ǂݍ���
	virtual const unsigned int Load( const char* strPath ) = 0;

	// ���\�[�X�̃N���A
	void Clear();

	// ���\�[�X�̃N���A
	void Clear( const unsigned int uiResourceID );

	

	// ���\�[�X�̎擾
	const void* GetResource( const unsigned int uiResourceID, const bool bEnableLog = true ) const;

	// ���\�[�XID�̎擾
	const unsigned int GetResourceID( const char* strPath, const bool bEnableLog = true ) const;

protected:

	// ���\�[�X�̒ǉ�
	const unsigned int PushResource( const char* strPath, void* pResource );

protected:

	// ���\�[�X�}�b�v�^
	typedef std::map<const unsigned int, RESOURCE_DATA*> ResourceMap;
	


	// �����o�ϐ�

	// ���\�[�X�^�C�v
	eRESOURCE_TYPE		m_ResourceType;

	// ���\�[�X�}�b�v
	ResourceMap			m_ResourceMap;
};



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
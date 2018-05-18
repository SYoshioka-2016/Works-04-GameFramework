#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#define _INCLUDE_GUARD_RESOURCEMANAGER_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
#include "Director/Base/ResourceDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_



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
// @purpose : ���\�[�X�Ǘ��N���X
//
// @extends / Singleton	: �V���O���g���N���X
//
// @note : 
//
// �V���O���g���N���X�B
// ���\�[�X�f�B���N�^�N���X���Ǘ�����N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class ResourceManager : public Singleton<ResourceManager>
{
private:

	// �t�����h�N���X�w��

	// �V���O���g���N���X
	friend Singleton<ResourceManager>;

public:

	// ���\�[�X�f�B���N�^�̎擾
	ResourceDirector* GetResourceDirector( const eRESOURCE_TYPE& resourceType );

	// ���\�[�XID�̔��s
	const unsigned int IssueResourceID();

	// ���\�[�X�̃N���A
	void ClearResource();

private:

	// �R���X�g���N�^
	ResourceManager();

	// �f�X�g���N�^
	~ResourceManager();



	// �����̔��s
	static const unsigned int IssueRandomNumber();

private:

	// ���\�[�X�}�b�v�^
	typedef std::map<eRESOURCE_TYPE, ResourceDirector*> ResourceDirectorMap;
	


	// �����o�ϐ�
	
	// ���\�[�X�f�B���N�^�}�b�v
	ResourceDirectorMap m_ResourceDirectorMap;
};



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
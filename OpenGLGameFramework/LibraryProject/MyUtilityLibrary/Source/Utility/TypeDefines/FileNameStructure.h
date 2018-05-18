#ifndef _INCLUDE_GUARD_FILENAMESTRUCTURE_H_
#define _INCLUDE_GUARD_FILENAMESTRUCTURE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_STROPERATE_H_
#include "StrOperate.h"
#endif	// #ifndef _INCLUDE_GUARD_STROPERATE_H_



//==================================================================================================================================
// �\���̒�`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �t�@�C�����\����
//
// @note : 
//
// �t�@�C�������Ǘ�����\���́B
//----------------------------------------------------------------------------------------------------------------------------------
struct FILE_NAME_STRUCTURE
{
public:

	FILE_NAME_STRUCTURE( const char* pcFileName ) : 
		strFileDirectory( GetFileDirectory( pcFileName ) ),
		strFileName( GetFileNameWithoutDirectoryAndExtensions( pcFileName ) ),
		strFileExtensions( GetFileExtensions( pcFileName ) ) 
	{
		strFullPath = strFileDirectory + strFileName + strFileExtensions;
	}

	// �f�B���N�g���̎擾
	const std::string& GetDirectory() const { return strFileDirectory; }
	
	// �t�@�C�����̎擾
	const std::string& GetFileName() const { return strFileName; }
	
	// �g���q�̎擾
	const std::string& GetExtensions() const { return strFileExtensions; }

	// ���S�p�X�̎擾
	const std::string& GetFullPath() const { return strFullPath; }

private:

	std::string		strFileDirectory;
	std::string		strFileName;
	std::string		strFileExtensions;
	std::string		strFullPath;
};



#endif	// #ifndef _INCLUDE_GUARD_FILENAMESTRUCTURE_H_
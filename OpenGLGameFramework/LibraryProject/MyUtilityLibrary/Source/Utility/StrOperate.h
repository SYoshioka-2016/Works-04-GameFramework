#ifndef _INCLUDE_GUARD_STROPERATE_H_
#define _INCLUDE_GUARD_STROPERATE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_LOCALE_H_
#define _INCLUDE_GUARD_LOCALE_H_
#include <locale.h>
#endif	// #ifndef _INCLUDE_GUARD_LOCALE_H_

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#define _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_

#ifndef _INCLUDE_GUARD_STRING_
#define _INCLUDE_GUARD_STRING_
#include <string>
#endif	// #ifndef _INCLUDE_GUARD_STRING_



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�B���N�g���̎擾
//
// @param [in] / const std::string& strPath : �t�@�C�������܂ރp�X
//
// @return / std::string : �t�@�C�������O�܂ł̃f�B���N�g��
//
// @note : 
//
// �t�@�C�������܂ރp�X����A
// �t�@�C�������O�܂ł̃f�B���N�g���𒊏o���ĕԂ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline std::string GetFileDirectory( const std::string& strPath ) 
{
	size_t pos1 = 0;
 
    pos1 = strPath.rfind( '\\' );
    if ( pos1 != std::string::npos ) 
	{
        return strPath.substr( 0, pos1 + 1 );
    }
 
    pos1 = strPath.rfind( '/' );
    if ( pos1 != std::string::npos ) 
	{
        return strPath.substr( 0, pos1 + 1 );
    }
 


    return "";
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �g���q�t���t�@�C�����̎擾
//
// @param [in] / const std::string& strPath : �t�@�C�������܂ރp�X
//
// @return / std::string : �f�B���N�g�����������g���q�t���t�@�C����
//
// @note : 
//
// �t�@�C�������܂ރp�X����A
// �t�@�C�������O�܂ł̃f�B���N�g������菜���ĕԂ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline std::string GetFileNameWithExtensions( const std::string& strPath ) 
{
	size_t pos1;
 
    pos1 = strPath.rfind( '\\' );
    if ( pos1 != std::string::npos ) 
	{
        return strPath.substr( pos1 + 1, strPath.size() - pos1 - 1 );
    }
 
    pos1 = strPath.rfind( '/' );
    if ( pos1 != std::string::npos ) 
	{
        return strPath.substr( pos1 + 1, strPath.size() - pos1 - 1 );
    }
 


    return strPath;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �t�@�C�����̎擾
//
// @param [in] / const std::string& strPath : �t�@�C�������܂ރp�X
//
// @return / std::string : �f�B���N�g���Ɗg���q���������t�@�C����
//
// @note : 
//
// �t�@�C�������܂ރp�X����A
// �t�@�C�������O�܂ł̃f�B���N�g����
// �t�@�C��������̊g���q����菜���ĕԂ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline std::string GetFileNameWithoutDirectoryAndExtensions( const std::string& strPath ) 
{
	size_t pos1, pos2;
 
    pos1 = strPath.rfind( '\\' );
    if ( pos1 != std::string::npos ) 
	{
		pos2 = strPath.rfind( '.' );
		if ( pos2 != std::string::npos ) 
		{
			return strPath.substr( pos1 + 1, pos2 - pos1 - 1 );
		}
    }
 
    pos1 = strPath.rfind( '/' );
    if ( pos1 != std::string::npos ) 
	{
		pos2 = strPath.rfind( '.' );
		if ( pos2 != std::string::npos ) 
		{
			return strPath.substr( pos1 + 1, pos2 - pos1 - 1 );
		}
    }

	pos1 = strPath.rfind( '.' );
    if ( pos1 != std::string::npos ) 
	{	
		return strPath.substr( 0, pos1 );
    }
 


    return strPath;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �t�@�C���̊g���q�̎擾
//
// @param [in] / const std::string& strPath : �t�@�C�������܂ރp�X
//
// @return / std::string : �f�B���N�g���ƃt�@�C�������������g���q
//
// @note : 
//
// �t�@�C�������܂ރp�X����A
// �t�@�C�������O�܂ł̃f�B���N�g����
// �t�@�C��������菜���ĕԂ��B
//----------------------------------------------------------------------------------------------------------------------------------
inline std::string GetFileExtensions( const std::string& strPath ) 
{
	size_t pos1;

	pos1 = strPath.rfind( '.' );
    if ( pos1 != std::string::npos ) 
	{
		return strPath.substr( pos1, strPath.length() );
    }



    return strPath;
}


/*
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �q���������p�X�̎擾
//
// @param [in] / const std::string& pathForDirectory	: �f�B���N�g���𒊏o����p�X
// @param [in] / const std::string& pathForFileName	: �t�@�C�����𒊏o����p�X
//
// @return / std::string : ���o�����f�B���N�g���ƃt�@�C�������q�����p�X
//
// @note : 
//
// �p�X����f�B���N�g���ƃt�@�C�����𒊏o���Čq�����킹��B
//----------------------------------------------------------------------------------------------------------------------------------
inline std::string GetReconnectedPath( const std::string& pathForDirectory, const std::string& pathForFileName ) 
{
	return GetDirectory( pathForDirectory ) + GetFileNameWithExtensions( pathForFileName );
}
*/


#endif	// #ifndef _INCLUDE_GUARD_STROPERATE_H_
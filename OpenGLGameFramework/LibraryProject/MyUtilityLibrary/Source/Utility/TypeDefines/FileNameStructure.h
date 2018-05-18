#ifndef _INCLUDE_GUARD_FILENAMESTRUCTURE_H_
#define _INCLUDE_GUARD_FILENAMESTRUCTURE_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_STROPERATE_H_
#include "StrOperate.h"
#endif	// #ifndef _INCLUDE_GUARD_STROPERATE_H_



//==================================================================================================================================
// 構造体定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ファイル名構造体
//
// @note : 
//
// ファイル名を管理する構造体。
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

	// ディレクトリの取得
	const std::string& GetDirectory() const { return strFileDirectory; }
	
	// ファイル名の取得
	const std::string& GetFileName() const { return strFileName; }
	
	// 拡張子の取得
	const std::string& GetExtensions() const { return strFileExtensions; }

	// 完全パスの取得
	const std::string& GetFullPath() const { return strFullPath; }

private:

	std::string		strFileDirectory;
	std::string		strFileName;
	std::string		strFileExtensions;
	std::string		strFullPath;
};



#endif	// #ifndef _INCLUDE_GUARD_FILENAMESTRUCTURE_H_
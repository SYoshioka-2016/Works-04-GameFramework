#ifndef _INCLUDE_GUARD_STROPERATE_H_
#define _INCLUDE_GUARD_STROPERATE_H_



//==================================================================================================================================
// インクルード
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
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ディレクトリの取得
//
// @param [in] / const std::string& strPath : ファイル名を含むパス
//
// @return / std::string : ファイル名直前までのディレクトリ
//
// @note : 
//
// ファイル名を含むパスから、
// ファイル名直前までのディレクトリを抽出して返す。
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
// @purpose : 拡張子付きファイル名の取得
//
// @param [in] / const std::string& strPath : ファイル名を含むパス
//
// @return / std::string : ディレクトリを除いた拡張子付きファイル名
//
// @note : 
//
// ファイル名を含むパスから、
// ファイル名直前までのディレクトリを取り除いて返す。
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
// @purpose : ファイル名の取得
//
// @param [in] / const std::string& strPath : ファイル名を含むパス
//
// @return / std::string : ディレクトリと拡張子を除いたファイル名
//
// @note : 
//
// ファイル名を含むパスから、
// ファイル名直前までのディレクトリと
// ファイル名直後の拡張子を取り除いて返す。
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
// @purpose : ファイルの拡張子の取得
//
// @param [in] / const std::string& strPath : ファイル名を含むパス
//
// @return / std::string : ディレクトリとファイル名を除いた拡張子
//
// @note : 
//
// ファイル名を含むパスから、
// ファイル名直前までのディレクトリと
// ファイル名を取り除いて返す。
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
// @purpose : 繋ぎかえたパスの取得
//
// @param [in] / const std::string& pathForDirectory	: ディレクトリを抽出するパス
// @param [in] / const std::string& pathForFileName	: ファイル名を抽出するパス
//
// @return / std::string : 抽出したディレクトリとファイル名を繋いだパス
//
// @note : 
//
// パスからディレクトリとファイル名を抽出して繋ぎ合わせる。
//----------------------------------------------------------------------------------------------------------------------------------
inline std::string GetReconnectedPath( const std::string& pathForDirectory, const std::string& pathForFileName ) 
{
	return GetDirectory( pathForDirectory ) + GetFileNameWithExtensions( pathForFileName );
}
*/


#endif	// #ifndef _INCLUDE_GUARD_STROPERATE_H_
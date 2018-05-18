#ifndef _INCLUDE_GUARD_RESOURCELIB_H_
#define _INCLUDE_GUARD_RESOURCELIB_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_
#include "Texture/TextureResourceLibrary.h"
#endif	// #ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_

#ifndef _INCLUDE_GUARD_MODELRESOURCELIBRARY_H_
#include "Model/ModelResourceLibrary.h"
#endif	// #ifndef _INCLUDE_GUARD_MODELRESOURCELIBRARY_H_



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソース名前空間
//
// @note : 
//
// リソース関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Resource
{



	// リソースのクリア
	void ClearResource();



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCELIB_H_
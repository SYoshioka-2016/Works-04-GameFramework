#ifndef _INCLUDE_GUARD_OGLMODEL_H_
#define _INCLUDE_GUARD_OGLMODEL_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_MATERIAL_H_
#include "Material.h"
#endif	// #ifndef _INCLUDE_GUARD_MATERIAL_H_

#ifndef _INCLUDE_GUARD_MESH_H_
#include "Mesh.h"
#endif	// #ifndef _INCLUDE_GUARD_MESH_H_



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソース名前空間
//
// @note : 
//
// リソース関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Resource
{


	
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : モデル名前空間
//
// @note : 
//
// リソース関連の内、モデル関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Model
{



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : モデルクラス
//
// @note : 
//
// 各フォーマットのモデルクラスのベースとなるクラス。
// モデルファイルから読み込んだデータを管理する。
//----------------------------------------------------------------------------------------------------------------------------------
class OGLModel 
{
public:

	// コンストラクタ
	OGLModel();

	// デストラクタ
	virtual ~OGLModel();


	
	// モデルの読み込み
	virtual HRESULT Load( const char* pcFileName ) = 0;

	// モデルの描画
	void Render( 
		const Vector4DF&	vec4LightPosition,
		const Matrix4x4F&	mat4World,
		const Matrix4x4F&	mat4View, 
		const Matrix4x4F&	mat4Projection
	);



	// マテリアルを適用してメッシュを描画
	void DrawMesh() const;
	
	// マテリアル無しでメッシュを描画
	void SimpleDrawMesh( const unsigned int uiDrawMode ) const;



	// メッシュの取得
	const MESH* GetMesh() const;

protected:

	// メンバ変数

	// メッシュ
	MESH*								m_pMesh;

	// マテリアルデータ
	std::map<std::string, MATERIAL*>	m_MaterialData;
};



}	// namespace NS_Model



}	// namespace NS_Resource



#endif	// #ifndef _INCLUDE_GUARD_OGLMODEL_H_
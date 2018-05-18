//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLOBJMODEL_H_
#include "OGLObjModel.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLOBJMODEL_H_

#ifndef _INCLUDE_GUARD_MATERIAL_H_
#include "../../Base/Material.h"
#endif	// #ifndef _INCLUDE_GUARD_MATERIAL_H_

#ifndef _INCLUDE_GUARD_MESH_H_
#include "../../Base/Mesh.h"
#endif	// #ifndef _INCLUDE_GUARD_MESH_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// リソース名前空間
using namespace NS_Resource;

// モデル名前空間
using namespace NS_Model;

// テクスチャ名前空間
using namespace NS_Texture;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLObjModel::OGLObjModel()
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLObjModel::~OGLObjModel() 
{
	// メッシュを削除
	SAFE_DELETE( m_pMesh );



	// マテリアルデータをクリア
	for each ( auto material in m_MaterialData ) 
	{
		SAFE_DELETE( material.second );
	}
	m_MaterialData.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : モデルの読み込み
//
// @param [in] / const char* pcFileName : OBJフォーマットファイル名
//
// @return / HRESULT : モデルの読み込みに成功したか
//	
// @note : 
//
// OBJフォーマットファイルからデータの読み込み処理を行う。
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLObjModel::Load( const char* pcFileName ) 
{
	// メッシュが有れば処理しない
	if ( POINTER_CHECK( m_pMesh ) ) 
	{
		DEBUG_CONSOLE_LOG( "既に読み込まれています。" );

		return S_OK;
	}



	// ファイルを開く
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, pcFileName, "rt" ) != 0 ) 
	{
		DEBUG_CONSOLE_LOG( "objファイルのファイルオープンに失敗しました。" );

		return E_FAIL;
	}



	// 文字列保存用
	char		strBuffer[ 256 ]		= { 0 };

	// マテリアル名保存用
	char		strMaterialName[ 256 ]	= { 0 };

	// ベクトル保存用
	Vector3DF	vec3Buffer;



	// メッシュを生成する
	m_pMesh = new MESH;

	

	// ファイルポインタの位置をファイルの先頭に移動する
	fseek( pFile, SEEK_SET, 0 );

	// ファイルからデータを読み込む
	while ( !feof( pFile ) ) 
	{
		// ファイルから1行( キーワード )読み込む
		ZeroMemory( strBuffer, sizeof(strBuffer) );
		fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );



		// マテリアルファイルを読み込む
		if ( strcmp( strBuffer, "mtllib" ) == 0 ) 
		{ 
			// マテリアルファイル名を読み込んでバッファに保存
			fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );

			// マテリアルファイル名にディレクトリを繋ぎ合わせる
			char fullPath[ 256 ] = "";
			strcpy_s( fullPath, GetFileDirectory( pcFileName ).c_str() );
			strcat_s( fullPath, strBuffer );

			// マテリアルファイルを読み込む
			LoadMaterial( fullPath );
		}

		// 頂点座標を読み込む
		if ( strcmp( strBuffer, "v" ) == 0 ) 
		{ 
			// 頂点座標を読み込んでバッファに保存
			fscanf_s( pFile, "%f %f %f", &vec3Buffer.x, &vec3Buffer.y, &vec3Buffer.z );

			 m_pMesh->vertexPositionData.push_back( vec3Buffer );
		}

		// 法線を読み込む
		if ( strcmp( strBuffer, "vn" ) == 0 ) 
		{
			// 法線を読み込んでバッファに保存
			fscanf_s( pFile, "%f %f %f", &vec3Buffer.x, &vec3Buffer.y, &vec3Buffer.z );
			
			m_pMesh->normalData.push_back( vec3Buffer );
		}

		// テクスチャ座標を読み込む
		if ( strcmp( strBuffer, "vt" ) == 0 ) 
		{ 	
			// テクスチャ座標を読み込んでバッファに保存
			fscanf_s( pFile, "%f %f", &vec3Buffer.x, &vec3Buffer.y );

			// objファイルはy成分が逆なので合わせる
			m_pMesh->texCoordData.push_back( Vector2DF( vec3Buffer.x, 1 - vec3Buffer.y ) );
		}	

		// マテリアル名を読み込む
		if ( strcmp( strBuffer, "usemtl" ) == 0 ) 
		{
			// マテリアル名を読み込んでバッファに保存
			fscanf_s( pFile, "%s ", strMaterialName, sizeof(strMaterialName) );
		}

		// インデックスを読み込む
		if ( strcmp( strBuffer, "f" ) == 0 ) 
		{ 
			// 頂点座標インデックス保存用
			Vector3DI	ivec3VertexPositionIndex;
			
			// テクスチャ座標インデックス保存用
			Vector3DI	ivec3TexcoordIndex;
			
			// 法線インデックス保存用
			Vector3DI	ivec3NormalIndex;

			// インデックスのポインタ
			Vector3DI* pivec3Index		= nullptr;
	
			// マテリアル参照用
			MATERIAL*	pMaterial		= nullptr;



			// 現在のマテリアルを参照する
			try 
			{
				pMaterial = m_MaterialData.at( strMaterialName );
			}
//			catch ( std::exception &e ) { }
			catch ( ... ) { }



			// インデックスを読み込んでバッファに保存
			fscanf_s( 
				pFile, "%d/%d/%d %d/%d/%d %d/%d/%d", 
				&ivec3VertexPositionIndex.x, &ivec3TexcoordIndex.x, &ivec3NormalIndex.x, 
				&ivec3VertexPositionIndex.y, &ivec3TexcoordIndex.y, &ivec3NormalIndex.y, 
				&ivec3VertexPositionIndex.z, &ivec3TexcoordIndex.z, &ivec3NormalIndex.z 
			);



			// 保存する頂点座標インデックスを調整
			pivec3Index		= new Vector3DI;
			*pivec3Index	= ivec3VertexPositionIndex - Vector3DI( 1, 1, 1 );

			// 頂点座標インデックスデータにインデックスを保存する
			m_pMesh->vertexPositionIndexData.insert( std::pair<std::string, Vector3DI*>( strMaterialName, pivec3Index ) );

			// 現在のマテリアルが有れば、そのマテリアルにインデックスを保存する
			if ( POINTER_CHECK( pMaterial ) ) 
			{
				pMaterial->vertexPositionIndexData.push_back( pivec3Index );
			}


			
			// 保存するテクスチャ座標インデックスを調整
			pivec3Index		= new Vector3DI;
			*pivec3Index	= ivec3TexcoordIndex - Vector3DI( 1, 1, 1 );
			
			// テクスチャ座標インデックスデータにインデックスを保存する
			m_pMesh->texcoordIndexData.insert( std::pair<std::string, Vector3DI*>( strMaterialName, pivec3Index ) );
			
			// 現在のマテリアルが有れば、そのマテリアルにインデックスを保存する
			if ( POINTER_CHECK( pMaterial ) ) 
			{
				pMaterial->texcoordIndexData.push_back( pivec3Index );
			}


						
			// 保存する法線座標インデックスを調整
			pivec3Index		= new Vector3DI;
			*pivec3Index	= ivec3NormalIndex - Vector3DI( 1, 1, 1 );
			
			// 法線インデックスデータにインデックスを保存する
			m_pMesh->normalIndexData.insert( std::pair<std::string, Vector3DI*>( strMaterialName, pivec3Index ) );
			
			// 現在のマテリアルが有れば、そのマテリアルにインデックスを保存する
			if ( POINTER_CHECK( pMaterial ) ) 
			{
				pMaterial->normalIndexData.push_back( pivec3Index );
			}
		}
	}



	// ファイルを閉じる
	if ( POINTER_CHECK( pFile ) ) { fclose( pFile ); }



	return S_OK;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : マテリアルの読み込み
//
// @param [in] / const char* pcFileName : mtlフォーマットファイル名
//
// @return / HRESULT : マテリアルの読み込みに成功したか
//	
// @note : 
//
// mtlフォーマットファイルからマテリアルの読み込み処理を行う。
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLObjModel::LoadMaterial( const char* pcFileName ) 
{
	// ファイルを開く
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, pcFileName, "rt" ) != 0 ) 
	{
		DEBUG_CONSOLE_LOG( "mtlファイルのファイルオープンに失敗しました。" );

		return E_FAIL;
	}
	


	// 文字列保存用
	char		strBuffer[ 256 ]	= { 0 };

	// ベクトル保存用
	Vector4DF	vec4Buffer;

	// マテリアル保存用
	MATERIAL*	pMaterial			= nullptr;



	// ファイルポインタの位置をファイルの先頭に移動する
	fseek( pFile, SEEK_SET, 0 );

	// ファイルからデータを読み込む
	while ( !feof( pFile ) ) 
	{
		// ファイルから1行( キーワード )読み込む
		ZeroMemory( strBuffer, sizeof(strBuffer) );
		fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );



		// マテリアル名を読み込む
		if ( strcmp( strBuffer, "newmtl" ) == 0 ) 
		{ 
			// 既にマテリアルが生成されていれば保存しておく
			if ( POINTER_CHECK( pMaterial ) ) 
			{ 
				m_MaterialData.insert( std::pair<std::string, MATERIAL*>( pMaterial->strMaterialName, pMaterial ) ); 
			}



			// マテリアルを生成
			pMaterial = new MATERIAL;

			// マテリアル名を読み込んでバッファに保存
			fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );
			pMaterial->strMaterialName = strBuffer;
		}

		// アンビエントを読み込む
		if ( strcmp( strBuffer, "Ka" ) == 0 ) 
		{
			// アンビエントを読み込んでバッファに保存
			fscanf_s( pFile, "%f %f %f", &vec4Buffer.x, &vec4Buffer.y, &vec4Buffer.z );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->vec4Ambient = vec4Buffer; }
		}

		// ディフューズを読み込む
		if ( strcmp( strBuffer, "Kd" ) == 0 ) 
		{
			// ディフューズを読み込んでバッファに保存
			fscanf_s( pFile, "%f %f %f", &vec4Buffer.x, &vec4Buffer.y, &vec4Buffer.z );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->vec4Diffuse = vec4Buffer; }
		}

		// スペキュラを読み込む
		if ( strcmp( strBuffer, "Ks" ) == 0 ) 
		{
			// スペキュラを読み込んでバッファに保存
			fscanf_s( pFile, "%f %f %f", &vec4Buffer.x, &vec4Buffer.y, &vec4Buffer.z );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->vec4Specular = vec4Buffer; }
		}

		// 鏡面反射の強さを読み込む
		if ( strcmp( strBuffer, "Ns" ) == 0 ) 
		{
			// 鏡面反射の強さを読み込んでバッファに保存
			fscanf_s( pFile, "%f", &vec4Buffer.x );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->fShininess = vec4Buffer.x; }
		}

		// テクスチャを読み込む
		if ( strcmp( strBuffer, "map_Kd" ) == 0 ) 
		{
			// テクスチャ名を読み込んでバッファに保存
			fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );
			
			// テクスチャ名にディレクトリを繋ぎ合わせる
			char fullPath[ 256 ] = "";
			strcpy_s( fullPath, GetFileDirectory( pcFileName ).c_str() );
			strcat_s( fullPath, strBuffer );

			// テクスチャを読み込む
			if ( POINTER_CHECK( pMaterial ) )
			{
				pMaterial->uiTextureResourceID = LoadTexture( fullPath );
			}
/*
			// テクスチャ名を保存する
			if ( POINTER_CHECK( pMaterial ) ) 
			{ 
				pMaterial->strTextureName = fullPath;
			}
*/
		}
	}

	// ファイルを閉じる
	if ( POINTER_CHECK( pFile ) ) { fclose( pFile ); }



	// マテリアルが生成されていれば保存しておく
	if ( POINTER_CHECK( pMaterial ) ) 
	{ 
		m_MaterialData.insert( std::pair<std::string, MATERIAL*>( pMaterial->strMaterialName, pMaterial ) ); 

		pMaterial = nullptr;
	}



	return S_OK;
}
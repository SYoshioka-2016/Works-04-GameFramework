//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLMODEL_H_
#include "OGLModel.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLMODEL_H_

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
OGLModel::OGLModel() : m_pMesh( nullptr )
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLModel::~OGLModel() 
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
// @purpose : モデルの描画
//
// @param [in] / const Vector4DF& vec4LightPosition : ライトの位置
// @param [in] / const Matrix4x4F& mat4World		: ワールド変換行列
// @param [in] / const Matrix4x4F& mat4View			: ビュー変換行列
// @param [in] / const Matrix4x4F& mat4Projection	: プロジェクション変換行列
//
// @note : 
//
// モデルを描画する。
// ライトの位置は4次元ベクトル値でxyzを座標として扱い、
// wの値が1でポイントライト( 点光源 )となり、
// 0でディレクショナルライト( 平行光源 )となる。
// 0未満でライティングを無効にする。
//----------------------------------------------------------------------------------------------------------------------------------
void OGLModel::Render( 
	const Vector4DF& vec4LightPosition,
	const Matrix4x4F& mat4World,
	const Matrix4x4F& mat4View, 
	const Matrix4x4F& mat4Projection
) 
{
	// 退避用カレントカラー
	Vector4DF	vec4CurrentColor;

	// カレントカラーを取得
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// 無効設定

		if ( 0 > vec4LightPosition.w ) 
		{
			// ライティング
			glDisable( GL_LIGHTING );
		}
		


		// 有効設定

		if ( 0 <= vec4LightPosition.w )
		{
			// ライティング
			glEnable( GL_LIGHTING );
		
			// ライト0
			glEnable( GL_LIGHT0 );
		}

		// 深度テスト
		glEnable( GL_DEPTH_TEST );

		// カリング
		glEnable( GL_CULL_FACE );

		// 正規化
		glEnable( GL_NORMALIZE );



		glPushMatrix();
		{
			// 変換行列を単位行列で初期化
			glLoadIdentity();	

			// 射影行列を行列演算ターゲットに選択
			glMatrixMode( GL_PROJECTION );

			// 射影変換行列を設定
			glLoadMatrixf( (GLfloat*)&mat4Projection );



			// モデルビュー行列を行列演算ターゲットに選択
			glMatrixMode( GL_MODELVIEW );

			// 変換行列を単位行列で初期化
			glLoadIdentity();	
			
			// 行列を設定
			glLoadMatrixf( (GLfloat*)&mat4View );
			
			// ライトを設定
			glLightfv( GL_LIGHT0, GL_POSITION, (GLfloat*)&vec4LightPosition );
			


			// 現在の行列にワールド変換行列を乗算
			glMultMatrixf( (GLfloat*)&mat4World );
			


			// マテリアルが有れば通常の描画
			if ( !m_MaterialData.empty() ) 
			{
				// マテリアルを適用してメッシュを描画
				DrawMesh();
			}

			// マテリアルが無ければ簡易的な描画
			else 
			{
				// マテリアル無しでメッシュを描画
				SimpleDrawMesh( GL_TRIANGLES );
			}
		}
		glPopMatrix();
	}
	glPopAttrib();
	


	// カレントカラーを復帰
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : メッシュの取得
//
// @return / const MESH* : メッシュ
//	
// @note : 
//
// メッシュを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const MESH* OGLModel::GetMesh() const 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pMesh );



	return m_pMesh;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : マテリアルを適用してメッシュを描画
//
// @note : 
//
// メッシュを描画する。
// マテリアル毎にマテリアルの設定を反映してメッシュを描画する。
//----------------------------------------------------------------------------------------------------------------------------------
void OGLModel::DrawMesh() const
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pMesh );



	// 退避用

	// アンビエント
	Vector4DF	vec4CurrentAmbient;

	// ディフューズ
	Vector4DF	vec4CurrentDiffuse;

	// スペキュラ
	Vector4DF	vec4CurrentSpecular;

	// 鏡面反射の強さ
	float		fCurrentShininess	= 0;



	// 現在のアンビエントを取得
	glGetFloatv( GL_AMBIENT, (GLfloat*)&vec4CurrentAmbient );

	// 現在のディフューズを取得
	glGetFloatv( GL_DIFFUSE, (GLfloat*)&vec4CurrentDiffuse );

	// 現在のスペキュラを取得
	glGetFloatv( GL_SPECULAR, (GLfloat*)&vec4CurrentSpecular );

	// 現在の鏡面反射の強さを取得
	glGetFloatv( GL_SHININESS, (GLfloat*)&fCurrentShininess );



	// マテリアル毎にメッシュを描画する
	for each ( auto material in m_MaterialData ) 
	{
		// マテリアル
		MATERIAL* pMaterial = material.second;

		// マテリアルが無ければ処理しない
		if ( NULL_CHECK( pMaterial ) ) { continue; }



		// アンビエントを設定
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *)&pMaterial->vec4Ambient );

		// ディフューズを設定
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *)&pMaterial->vec4Diffuse );

		// スペキュラを設定
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *)&pMaterial->vec4Specular );

		// 鏡面反射の強さを設定
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->fShininess );



		// テクスチャIDを取得
		const unsigned int uiTextureID = GetTextureID( pMaterial->uiTextureResourceID );
		
		// テクスチャが有ればテクスチャを有効にする
		if ( uiTextureID != 0 ) 
		{
			// テクスチャを有効にする
			glEnable( GL_TEXTURE_2D );

			// テクスチャをバインドする
			glBindTexture( GL_TEXTURE_2D, uiTextureID );
		}

		// テクスチャが無ければテクスチャを無効にする
		else 
		{
			// テクスチャを無効にする
			glDisable( GL_TEXTURE_2D );
		}



		// マテリアルが持つ頂点座標インデックス( ポリゴン )の数だけ、ポリゴンを1枚ずつ描画する
		for ( unsigned int i = 0; i < pMaterial->vertexPositionIndexData.size() ; i++ ) 
		{
			// 三角ポリゴンを描画する
			glBegin( GL_TRIANGLES );
			{
				// 1つ目の頂点を設定

				// 法線
				glNormal3f( 
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->x ].x,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->x ].y,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->x ].z
				);

				// テクスチャ座標
				glTexCoord2f( 
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->x ].x,
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->x ].y
				);

				// 頂点座標
				glVertex3f( 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->x ].x, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->x ].y, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->x ].z 
				);


				
				// 2つ目の頂点を設定

				// 法線
				glNormal3f( 
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->y ].x,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->y ].y,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->y ].z
				);
				
				// テクスチャ座標
				glTexCoord2f( 
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->y ].x,
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->y ].y
				);
				
				// 頂点座標
				glVertex3f( 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->y ].x, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->y ].y, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->y ].z 
				);


				
				// 3つ目の頂点を設定

				// 法線
				glNormal3f( 
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->z ].x,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->z ].y,
					m_pMesh->normalData[ pMaterial->normalIndexData[i]->z ].z
				);
				
				// テクスチャ座標
				glTexCoord2f( 
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->z ].x,
					m_pMesh->texCoordData[ pMaterial->texcoordIndexData[i]->z ].y
				);
								
				// 頂点座標
				glVertex3f( 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->z ].x, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->z ].y, 
					m_pMesh->vertexPositionData[ pMaterial->vertexPositionIndexData[i]->z ].z 
				);
			}
			glEnd();
		}
	}


	// テクスチャのバインドを解除する
	glBindTexture( GL_TEXTURE_2D, 0 );


	
	// アンビエントを復帰
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *)&vec4CurrentAmbient );
	
	// ディフューズを復帰
if ( vec4CurrentDiffuse.Length() != 0 ) { glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *)&vec4CurrentDiffuse ); }
	
	// スペキュラを復帰
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *)&vec4CurrentSpecular );
	
	// 鏡面反射の強さを復帰
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, fCurrentShininess );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : マテリアル無しでメッシュを描画
//
// @param [in] / const unsigned int uiDrawMode : 描画モード
//
// @note : 
//
// メッシュを描画する。
// マテリアルを使わずにモデルが持つデータでメッシュを描画する。
//----------------------------------------------------------------------------------------------------------------------------------
void OGLModel::SimpleDrawMesh( const unsigned int uiDrawMode ) const
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pMesh );



	// 頂点座標インデックスデータのイテレータ
	std::multimap<std::string, Vector3DI*>::iterator vertexPositionIndexDataIterator	= m_pMesh->vertexPositionIndexData.begin();
	
	// 法線インデックスデータのイテレータ
	std::multimap<std::string, Vector3DI*>::iterator normalIndexDataIterator			= m_pMesh->normalIndexData.begin();
	
	// テクスチャ座標インデックスデータのイテレータ
	std::multimap<std::string, Vector3DI*>::iterator texcoordIndexDataIterator			= m_pMesh->texcoordIndexData.begin();

	// 繰り返し条件判定用( true : 継続 | false : 終了 )
	bool bIsNotEnd = true;



	// イテレータが末尾でなければ繰り返す
	bIsNotEnd &= ( m_pMesh->vertexPositionIndexData.end() != vertexPositionIndexDataIterator );
	bIsNotEnd &= ( m_pMesh->normalIndexData.end() != normalIndexDataIterator );
	bIsNotEnd &= ( m_pMesh->texcoordIndexData.end() != texcoordIndexDataIterator );

	while ( bIsNotEnd ) 
	{
		glBegin( uiDrawMode );
		{
/*
			// ポリゴンの表の方向を法線とする
			Vector3DF vec3Normal =
				glm::cross(
					m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ] - m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ],
					m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ] - m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ]
			);

			// 法線ベクトルを正規化
			vec3Normal = glm::normalize( vec3Normal );
					
			// 法線を設定
			glNormal3f( vec3Normal.x, vec3Normal.y, vec3Normal.z );
*/			


			// 1つ目の頂点を設定

			// 法線
			glNormal3f( 
				m_pMesh->normalData[ normalIndexDataIterator->second->x ].x, 
				m_pMesh->normalData[ normalIndexDataIterator->second->x ].y, 
				m_pMesh->normalData[ normalIndexDataIterator->second->x ].z 
			);

			// テクスチャ座標
			glTexCoord2f( 
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->x ].x,
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->x ].y
			);

			// 頂点座標
			glVertex3f( 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ].x, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ].y, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->x ].z 
			);


			
			// 2つ目の頂点を設定

			// 法線
			glNormal3f( 
				m_pMesh->normalData[ normalIndexDataIterator->second->y ].x, 
				m_pMesh->normalData[ normalIndexDataIterator->second->y ].y, 
				m_pMesh->normalData[ normalIndexDataIterator->second->y ].z 
			);
			
			// テクスチャ座標
			glTexCoord2f( 
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->y ].x,
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->y ].y
			);
			
			// 頂点座標
			glVertex3f( 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ].x, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ].y, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->y ].z 
			);


			
			// 3つ目の頂点を設定

			// 法線
			glNormal3f( 
				m_pMesh->normalData[ normalIndexDataIterator->second->z ].x, 
				m_pMesh->normalData[ normalIndexDataIterator->second->z ].y, 
				m_pMesh->normalData[ normalIndexDataIterator->second->z ].z 
			);

			// テクスチャ座標
			glTexCoord2f( 
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->z ].x,
				m_pMesh->texCoordData[ texcoordIndexDataIterator->second->z ].y
			);
			
			// 頂点座標
			glVertex3f( 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ].x, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ].y, 
				m_pMesh->vertexPositionData[ vertexPositionIndexDataIterator->second->z ].z 
			);
		}
		glEnd();



		// 頂点座標インデックスデータのイテレータを進める
		vertexPositionIndexDataIterator++;

		// 法線インデックスデータのイテレータを進める
		normalIndexDataIterator++;

		// テクスチャ座標インデックスデータのイテレータを進める
		texcoordIndexDataIterator++;

		// イテレータが末尾でなければ繰り返す
		bIsNotEnd &= ( m_pMesh->vertexPositionIndexData.end() != vertexPositionIndexDataIterator );
		bIsNotEnd &= ( m_pMesh->normalIndexData.end() != normalIndexDataIterator );
		bIsNotEnd &= ( m_pMesh->texcoordIndexData.end() != texcoordIndexDataIterator );
	}
}
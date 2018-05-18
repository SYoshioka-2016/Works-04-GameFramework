//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_STARSPRITEMANAGER_H_
#include "StarSpriteManager.h"
#endif	// #ifndef _INCLUDE_GUARD_STARSPRITEMANAGER_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// ゲーム名前空間
using namespace NS_OpenGLWindowPCGame;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const SPRITE_DESC& desc		: スプライト記述子
// @param [in] / const Vector3DF&	vec3Space	: 星スプライトを置く空間
// @param [in] / const unsigned int	uiCount		: 星スプライトの数
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
StarSpriteManager::StarSpriteManager( 
	const SPRITE_DESC&	desc, 
	const Vector3DF&	vec3Space, 
	const unsigned int	uiCount 
) : m_StarSpriteList( std::list<Sprite*>() ) 
{
	// 星スプライトの数だけ生成する
	for ( unsigned int i = 0; i < uiCount; i++ ) 
	{
		// スプライト記述子をコピーする
		SPRITE_DESC spriteDesc = desc;

		// 座標を空間内のランダムな位置に設定する
		spriteDesc.position = 
			Vector3DF( 
				Random::RandomFloat( -vec3Space.x / 2, vec3Space.x / 2 ),
				Random::RandomFloat( -vec3Space.y / 2, vec3Space.y / 2 ),
				Random::RandomFloat( -vec3Space.z / 2, vec3Space.z / 2 )
			);

spriteDesc.scale = Vector3DF( 5, 5, 1 );		
		// 星スプライトリストに星スプライトを追加する
		m_StarSpriteList.push_back( new Sprite( spriteDesc ) );
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
StarSpriteManager::~StarSpriteManager() 
{
	// 全ての星スプライトを削除する
	for each ( auto pStarSprite in m_StarSpriteList ) 
	{
		SAFE_DELETE( pStarSprite );
	}

	// 星スプライトリストをクリア
	m_StarSpriteList.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 描画処理
//
// @note : 
//
// 全ての星スプライトを描画する。
//----------------------------------------------------------------------------------------------------------------------------------
void StarSpriteManager::Draw() 
{
	glPushAttrib( GL_ENABLE_BIT );



	// 深度テストを無効にする
//	glDisable( GL_DEPTH_TEST );

	// ライティングを無効にする
	glDisable( GL_LIGHTING );



	// 全ての星スプライトを描画する
	for each ( auto pStarSprite in m_StarSpriteList ) 
	{
		// 星スプライトが無ければ処理しない
		if( NULL_CHECK( pStarSprite ) ) { continue; }



		// 星スプライトを描画
		pStarSprite->Draw();
	}



	glPopAttrib();
}
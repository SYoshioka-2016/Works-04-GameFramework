//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_SPRITE_H_
#include "Sprite.h"
#endif	// #ifndef _INCLUDE_GUARD_SPRITE_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const SPRITE_DESC& desc : スプライト記述子
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Sprite::Sprite( const SPRITE_DESC& desc ) :
	m_Desc( desc )
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Sprite::~Sprite() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 描画処理
//
// @note : 
//
// 描画処理を行う。
// デフォルトでXY平面に平行な四角ポリゴンを描画する。
//----------------------------------------------------------------------------------------------------------------------------------
void Sprite::Draw() 
{
	// 各種レンダリングモードを退避する
	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// ブレンドを設定する
	glEnable( GL_BLEND );

	glBlendFunc( GL_SRC_ALPHA, GL_ONE );



	// テクスチャを取得する
	unsigned int uiTexture = NS_Resource::NS_Texture::GetTextureID( m_Desc.textureResourceID );

	// テクスチャが有ればテクスチャを有効にする
	if ( uiTexture != 0 ) 
	{
		glEnable( GL_TEXTURE_2D );

		glBindTexture( GL_TEXTURE_2D, uiTexture );
	}

	// テクスチャが無ければテクスチャを無効にする
	else
	{
		glDisable( GL_TEXTURE_2D );
	}




	// 行列を保存
	glPushMatrix();



	// 平行移動
	glTranslatef( m_Desc.position.x, m_Desc.position.y, m_Desc.position.z );

	// 回転
	glRotatef( m_Desc.rotation.x, 1, 0, 0 );
	glRotatef( m_Desc.rotation.y, 0, 1, 0 );
	glRotatef( m_Desc.rotation.z, 0, 0, 1 );

	// スケーリング
	glScalef( m_Desc.scale.x, m_Desc.scale.y, m_Desc.scale.z );



	// 現在のモデルビュー変換行列
	GLfloat fCurrentModelViewMatrix[16] = { };

	// ビルボードが有効ならビルボード行列を設定する
	if ( m_Desc.billboard ) 
	{
		// 行列モードをモデルビューに選択
		glMatrixMode( GL_MODELVIEW );
	
		// 現在のモデルビュー変換行列を取得する
		glGetFloatv( GL_MODELVIEW_MATRIX, fCurrentModelViewMatrix );


	
		// ビルボード行列を設定
		Matrix4x4F mat4Billboard = fCurrentModelViewMatrix;

		mat4Billboard[0][0]		= m_Desc.scale.x;
		mat4Billboard[1][1]		= m_Desc.scale.y;
		mat4Billboard[2][2]		= m_Desc.scale.z;

		mat4Billboard[0][1]		= 0;
		mat4Billboard[0][2]		= 0;
		mat4Billboard[1][0]		= 0;
		mat4Billboard[1][2]		= 0;
		mat4Billboard[2][0]		= 0;
		mat4Billboard[2][1]		= 0;

		glLoadMatrixf( (GLfloat*)&mat4Billboard );
	}



	// スプライトを描画する
	glBegin( GL_TRIANGLES );

glColor4fv( (GLfloat*)&m_Desc.color );
//glMaterialfv( GL_FRONT, GL_DIFFUSE, (GLfloat*)&m_Desc.color );


	// 左上
	glTexCoord2f( m_Desc.textureOffset.x, m_Desc.textureOffset.y );
	glVertex3f( -0.5f,  0.5f,  0 );

	// 左下
	glTexCoord2f( m_Desc.textureOffset.x, m_Desc.textureOffset.y + m_Desc.textureTiling.y );
	glVertex3f( -0.5f, -0.5f,  0 );
	
	// 右下
	glTexCoord2f( m_Desc.textureOffset.x + m_Desc.textureTiling.x, m_Desc.textureOffset.y + m_Desc.textureTiling.y );
	glVertex3f(  0.5f, -0.5f,  0 );
		
	// 右下
	glTexCoord2f( m_Desc.textureOffset.x + m_Desc.textureTiling.x, m_Desc.textureOffset.y + m_Desc.textureTiling.y );
	glVertex3f(  0.5f, -0.5f,  0 );

	// 右上
	glTexCoord2f( m_Desc.textureOffset.x + m_Desc.textureTiling.x, m_Desc.textureOffset.y );
	glVertex3f(  0.5f,  0.5f,  0 );
		
	// 左上
	glTexCoord2f( m_Desc.textureOffset.x, m_Desc.textureOffset.y );
	glVertex3f( -0.5f,  0.5f,  0 );

	glEnd();



	// ビルボードが有効ならモデルビュー変換行列を元に戻す
	if ( m_Desc.billboard ) 
	{
		glMatrixMode( GL_MODELVIEW );
	
		glLoadMatrixf( fCurrentModelViewMatrix );
	}



	// 行列を破棄
	glPopMatrix();



	// テクスチャが有ればテクスチャを無効にする
	if ( uiTexture != 0 ) 
	{
		glBindTexture( GL_TEXTURE_2D, 0 );
	}



	// レンダリングモードを復帰する
	glPopAttrib();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : スプライト記述子の取得
//
// @return / const SPRITE_DESC& : スプライト記述子
//
// @note : 
//
// スプライト記述子の参照を返す。
//----------------------------------------------------------------------------------------------------------------------------------
const SPRITE_DESC& Sprite::GetDesc() const
{
	return m_Desc;
}
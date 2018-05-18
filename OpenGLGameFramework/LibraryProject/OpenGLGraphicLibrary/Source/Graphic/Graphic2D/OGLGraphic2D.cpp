//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_
#include "OGLGraphic2D.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 点の描画
//
// @param [in] / const Vector2DF&	vec2Position		: 点の座標
// @param [in] / const Vector4DF&	vec4Color			: カラー
// @param [in] / const float	fPointSize			: 点の大きさ
// @param [in] / const float	fOrthoLeft			: 正射影のx軸の最小値
// @param [in] / const float	fOrthoRight			: 正射影のx軸の最大値
// @param [in] / const float	fOrthoBottom		: 正射影のy軸の最大値
// @param [in] / const float	fOrthoTop			: 正射影のy軸の最小値
// @param [in] / const float	fNear				: Near面
// @param [in] / const float	fFar				: Far面
//
// @note : 
//
// 点を描画する。
// 座標、カラー、点の大きさと正射影変換の数値を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawPoint( 
	const Vector2DF&	vec2Position, 
	const Vector4DF&	vec4Color,
	const float		fPointSize,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// 退避用カレントカラー
	Vector4DF vec4CurrentColor;

	

	// カレントカラーを取得
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// 無効設定

		// ライティング
		glDisable( GL_LIGHTING );
		
		// テクスチャ
		glDisable( GL_TEXTURE );

		// 深度テスト
		glDisable( GL_DEPTH_TEST );

		// カリング
		glDisable( GL_CULL_FACE );
		


		// 有効設定

		// ブレンド
		glEnable( GL_BLEND );



		// ブレンドを設定
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// 描画する点のサイズを設定
		glPointSize( fPointSize );

		// 射影行列を行列演算ターゲットに選択
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// 変換行列を単位行列で初期化
			glLoadIdentity();

			// 正射影行列を設定
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// モデルビュー行列を行列演算ターゲットに選択
			glMatrixMode( GL_MODELVIEW );
		
			// 指定のカラーを設定
			glColor4fv( (GLfloat*)&vec4Color );
			
			// 点を描画
			glBegin( GL_POINTS );
			{
				glVertex2f( vec2Position.x, vec2Position.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// カレントカラーを復帰
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 直線の描画
//
// @param [in] / const Vector2DF&	vec2Position1		: 線分の頂点の座標1
// @param [in] / const Vector2DF&	vec2Position2		: 線分の頂点の座標2
// @param [in] / const Vector4DF&	vec4VertexColor1	: 線分の頂点カラー1
// @param [in] / const Vector4DF&	vec4VertexColor2	: 線分の頂点カラー2
// @param [in] / const float	fLineSize			: 線の太さ
// @param [in] / const float	fOrthoLeft			: 正射影のx軸の最小値
// @param [in] / const float	fOrthoRight			: 正射影のx軸の最大値
// @param [in] / const float	fOrthoBottom		: 正射影のy軸の最大値
// @param [in] / const float	fOrthoTop			: 正射影のy軸の最小値
// @param [in] / const float	fNear				: Near面
// @param [in] / const float	fFar				: Far面
//
// @note : 
//
// 直線を描画する。
// 線分の2点の座標、カラー、線の太さと正射影変換の数値を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawLine( 
	const Vector2DF&	vec2Position1, 
	const Vector2DF&	vec2Position2, 
	const Vector4DF&	vec4VertexColor1,
	const Vector4DF&	vec4VertexColor2,
	const float		fLineSize,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// 退避用カレントカラー
	Vector4DF vec4CurrentColor;

	

	// カレントカラーを取得
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// 無効設定

		// ライティング
		glDisable( GL_LIGHTING );
		
		// テクスチャ
		glDisable( GL_TEXTURE );

		// 深度テスト
		glDisable( GL_DEPTH_TEST );

		// カリング
		glDisable( GL_CULL_FACE );
		


		// 有効設定

		// ブレンド
		glEnable( GL_BLEND );



		// ブレンドを設定
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// 描画する線の幅を設定
		glLineWidth( fLineSize );

		// 射影行列を行列演算ターゲットに選択
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// 変換行列を単位行列で初期化
			glLoadIdentity();

			// 正射影行列を設定
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// モデルビュー行列を行列演算ターゲットに選択
			glMatrixMode( GL_MODELVIEW );

			// 線を描画
			glBegin( GL_LINES );
			{
				glColor4fv( (GLfloat*)&vec4VertexColor1 );
				glVertex2f( vec2Position1.x, vec2Position1.y );
				
				glColor4fv( (GLfloat*)&vec4VertexColor2 );
				glVertex2f( vec2Position2.x, vec2Position2.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// カレントカラーを復帰
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 直線の三角形の描画
//
// @param [in] / const Vector2DF&	vec2Position1		: 三角形の頂点の座標1
// @param [in] / const Vector2DF&	vec2Position2		: 三角形の頂点の座標2
// @param [in] / const Vector2DF&	vec2Position3		: 三角形の頂点の座標3
// @param [in] / const Vector4DF&	vec4VertexColor1	: 三角形の頂点カラー1
// @param [in] / const Vector4DF&	vec4VertexColor1	: 三角形の頂点カラー2
// @param [in] / const Vector4DF&	vec4VertexColor1	: 三角形の頂点カラー3
// @param [in] / const float	fLineSize			: 線の太さ
// @param [in] / const float	fOrthoLeft			: 正射影のx軸の最小値
// @param [in] / const float	fOrthoRight			: 正射影のx軸の最大値
// @param [in] / const float	fOrthoBottom		: 正射影のy軸の最大値
// @param [in] / const float	fOrthoTop			: 正射影のy軸の最小値
// @param [in] / const float	fNear				: Near面
// @param [in] / const float	fFar				: Far面
//
// @note : 
//
// 線の三角形を描画する。
// 3頂点の座標、カラー、線の太さと正射影変換の数値を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawLineTriangle( 
	const Vector2DF&	vec2Position1, 
	const Vector2DF&	vec2Position2, 
	const Vector2DF&	vec2Position3,
	const Vector4DF&	vec4VertexColor1,
	const Vector4DF&	vec4VertexColor2,
	const Vector4DF&	vec4VertexColor3,
	const float		fLineSize,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// 退避用カレントカラー
	Vector4DF vec4CurrentColor;

	

	// カレントカラーを取得
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// 無効設定

		// ライティング
		glDisable( GL_LIGHTING );
		
		// テクスチャ
		glDisable( GL_TEXTURE );

		// 深度テスト
		glDisable( GL_DEPTH_TEST );

		// カリング
		glDisable( GL_CULL_FACE );
		


		// 有効設定

		// ブレンド
		glEnable( GL_BLEND );

		

		// ブレンドを設定
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// 描画する線の幅を設定
		glLineWidth( fLineSize );

		// 射影行列を行列演算ターゲットに選択
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// 変換行列を単位行列で初期化
			glLoadIdentity();

			// 正射影行列を設定
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// モデルビュー行列を行列演算ターゲットに選択
			glMatrixMode( GL_MODELVIEW );
		
			// 三角形を描画
			glBegin( GL_LINE_LOOP );
			{
				glColor4fv( (GLfloat*)&vec4VertexColor1 );
				glVertex2f( vec2Position1.x, vec2Position1.y );
					
				glColor4fv( (GLfloat*)&vec4VertexColor2 );
				glVertex2f( vec2Position2.x, vec2Position2.y );
				
				glColor4fv( (GLfloat*)&vec4VertexColor3 );
				glVertex2f( vec2Position3.x, vec2Position3.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// カレントカラーを復帰
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 塗りつぶしの三角形の描画
//
// @param [in] / const Vector2DF&	vec2Position1		: 三角形の頂点の座標1
// @param [in] / const Vector2DF&	vec2Position2		: 三角形の頂点の座標2
// @param [in] / const Vector2DF&	vec2Position3		: 三角形の頂点の座標3
// @param [in] / const Vector4DF&	vec4VertexColor1	: 三角形の頂点カラー1
// @param [in] / const Vector4DF&	vec4VertexColor1	: 三角形の頂点カラー2
// @param [in] / const Vector4DF&	vec4VertexColor1	: 三角形の頂点カラー3
// @param [in] / const float	fOrthoLeft			: 正射影のx軸の最小値
// @param [in] / const float	fOrthoRight			: 正射影のx軸の最大値
// @param [in] / const float	fOrthoBottom		: 正射影のy軸の最大値
// @param [in] / const float	fOrthoTop			: 正射影のy軸の最小値
// @param [in] / const float	fNear				: Near面
// @param [in] / const float	fFar				: Far面
//
// @note : 
//
// 塗りつぶした三角形を描画する。
// 3頂点の座標、カラーと正射影変換の数値を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Graphic::NS_Graphic2D::DrawFilledTriangle( 
	const Vector2DF&	vec2Position1, 
	const Vector2DF&	vec2Position2, 
	const Vector2DF&	vec2Position3,
	const Vector4DF&	vec4VertexColor1,
	const Vector4DF&	vec4VertexColor2,
	const Vector4DF&	vec4VertexColor3,
	const float		fOrthoLeft,
	const float		fOrthoRight,
	const float		fOrthoBottom,
	const float		fOrthoTop,
	const float		fNear,
	const float		fFar
)
{
	// 退避用カレントカラー
	Vector4DF vec4CurrentColor;

	

	// カレントカラーを取得
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );



	glPushAttrib( GL_ENABLE_BIT );
	{
		// 無効設定

		// ライティング
		glDisable( GL_LIGHTING );
		
		// テクスチャ
		glDisable( GL_TEXTURE );

		// 深度テスト
		glDisable( GL_DEPTH_TEST );

		// カリング
		glDisable( GL_CULL_FACE );
		


		// 有効設定

		// ブレンド
		glEnable( GL_BLEND );

		

		// ブレンドを設定
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// 射影行列を行列演算ターゲットに選択
		glMatrixMode( GL_PROJECTION );

		glPushMatrix();
		{
			// 変換行列を単位行列で初期化
			glLoadIdentity();

			// 正射影行列を設定
			glOrtho( fOrthoLeft, fOrthoRight, fOrthoBottom, fOrthoTop, fNear, fFar );

			// モデルビュー行列を行列演算ターゲットに選択
			glMatrixMode( GL_MODELVIEW );
		
			// 三角形を描画
			glBegin( GL_TRIANGLES );
			{
				glColor4fv( (GLfloat*)&vec4VertexColor1 );
				glVertex2f( vec2Position1.x, vec2Position1.y );
					
				glColor4fv( (GLfloat*)&vec4VertexColor2 );
				glVertex2f( vec2Position2.x, vec2Position2.y );
					
				glColor4fv( (GLfloat*)&vec4VertexColor3 );
				glVertex2f( vec2Position3.x, vec2Position3.y );
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();



	// カレントカラーを復帰
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}
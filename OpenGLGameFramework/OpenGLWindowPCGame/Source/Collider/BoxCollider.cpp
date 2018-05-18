//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_BOXCOLLIDER_H_
#include "BoxCollider.h"
#endif	// #ifndef _INCLUDE_GUARD_BOXCOLLIDER_H_

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



BoxCollider::BoxCollider( const Vector3DF* pvec3VertexPositionData, const unsigned int uiVertexPositionCount, const Transform& transform ) :
	m_vec3Center( 0, 0, 0 ),
	m_vec3Size( 0, 0, 0 ),
	m_Transform( transform )
{ 
	CreateBox( pvec3VertexPositionData, uiVertexPositionCount );
}



BoxCollider::~BoxCollider() 
{

}



const Vector3DF& BoxCollider::GetCenter() const 
{
	return m_vec3Center;
}
	
const Vector3DF& BoxCollider::GetSize() const
{
	return m_vec3Size;
}

void BoxCollider::SetCenter( const Vector3DF& vec3Center )
{
	m_vec3Center = vec3Center;
}

void BoxCollider::SetSize( const Vector3DF& vec3Size )
{
	m_vec3Size = 
		Vector3DF(
			(float)Clamp( vec3Size.x, 0.0f, abs( vec3Size.x ) ),
			(float)Clamp( vec3Size.y, 0.0f, abs( vec3Size.y ) ),
			(float)Clamp( vec3Size.z, 0.0f, abs( vec3Size.z ) )
		);
}






bool BoxCollider::CollisionDetection( const BoxCollider* pBoxCollider ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pBoxCollider );



	// ボックスの距離ベクトル
//	Vector3DF vec3Distance = pMeshB->vPos - pMeshA->vPos;
return false;
}




void BoxCollider::DrawBox() 
{

	Vector4DF vec4Color( 0, 1, 0, 1 );




	// 退避用カレントカラー
	Vector4DF vec4CurrentColor;

	// カレントカラーを取得
	glGetFloatv( GL_CURRENT_COLOR, (GLfloat*)&vec4CurrentColor );

	
	
	glPushAttrib( GL_ENABLE_BIT );
	{
		// 無効設定

		// テクスチャ
		glDisable( GL_TEXTURE_2D );

		// ライティング
		glDisable( GL_LIGHTING );

		// 有効設定

		// 深度テスト
		glEnable( GL_DEPTH_TEST );



		glPushMatrix();
		{
			// カラーを設定
			glColor4fv( (GLfloat*)&vec4Color );




			glTranslatef( m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );
	glRotatef( m_Transform.rotation.y, 0, 1, 0 );
	glRotatef( m_Transform.rotation.z, 0, 0, 1 );
	glRotatef( m_Transform.rotation.x, 1, 0, 0 );

	glScalef( m_Transform.scale.x, m_Transform.scale.y, m_Transform.scale.z );

//glTranslatef( m_vec3Center.x, m_vec3Center.y, m_vec3Center.z );

			Vector3DF vec3VertexPositionData[] = 
			{
				// 左上奥
				Vector3DF( m_vec3Center.x - ( m_vec3Size.x / 2 ), m_vec3Center.y + ( m_vec3Size.y / 2 ), m_vec3Center.z - ( m_vec3Size.z / 2 ) ),

				// 左上前
				Vector3DF( m_vec3Center.x - ( m_vec3Size.x / 2 ), m_vec3Center.y + ( m_vec3Size.y / 2 ), m_vec3Center.z + ( m_vec3Size.z / 2 ) ),

				// 右上前
				Vector3DF( m_vec3Center.x + ( m_vec3Size.x / 2 ), m_vec3Center.y + ( m_vec3Size.y / 2 ), m_vec3Center.z + ( m_vec3Size.z / 2 ) ),

				// 右上奥
				Vector3DF( m_vec3Center.x + ( m_vec3Size.x / 2 ), m_vec3Center.y + ( m_vec3Size.y / 2 ), m_vec3Center.z - ( m_vec3Size.z / 2 ) ),
				
				// 左下奥
				Vector3DF( m_vec3Center.x - ( m_vec3Size.x / 2 ), m_vec3Center.y - ( m_vec3Size.y / 2 ), m_vec3Center.z - ( m_vec3Size.z / 2 ) ),
				
				// 左下前
				Vector3DF( m_vec3Center.x - ( m_vec3Size.x / 2 ), m_vec3Center.y - ( m_vec3Size.y / 2 ), m_vec3Center.z + ( m_vec3Size.z / 2 ) ),
				
				// 右下前
				Vector3DF( m_vec3Center.x + ( m_vec3Size.x / 2 ), m_vec3Center.y - ( m_vec3Size.y / 2 ), m_vec3Center.z + ( m_vec3Size.z / 2 ) ),
				
				// 右下奥
				Vector3DF( m_vec3Center.x + ( m_vec3Size.x / 2 ), m_vec3Center.y - ( m_vec3Size.y / 2 ), m_vec3Center.z - ( m_vec3Size.z / 2 ) ),
			};

			unsigned char ucVertexPositionIndexData[] = 
			{
				0, 1,
				1, 2,
				2, 3,
				3, 0,

				0, 4,
				1, 5,
				2, 6,
				3, 7,

				4, 5,
				5, 6,
				6, 7,
				7, 4,
			};



			glEnableClientState( GL_VERTEX_ARRAY );

			glVertexPointer( 3, GL_FLOAT, 0, vec3VertexPositionData );

			glDrawElements( GL_LINES, ARRAYSIZE( ucVertexPositionIndexData ), GL_UNSIGNED_BYTE, ucVertexPositionIndexData );
		}
		glPopMatrix();
	}
	glPopAttrib();
	


	// カレントカラーを復帰
	glColor4fv( (GLfloat*)&vec4CurrentColor );
}



void BoxCollider::CreateBox( const Vector3DF* pvec3VertexPositionData, const unsigned int uiVertexPositionCount ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pvec3VertexPositionData );



	// ボックスの最大点( XYZ軸の各成分が最も大きい座標、比較用に最小値で初期化する )
	Vector3DF vec3MaxPoint( -FLT_MAX, -FLT_MAX, -FLT_MAX );

	// ボックスの最小点( XYZ軸の各成分が最も小さい座標、比較用に最大値で初期化する )
	Vector3DF vec3MinPoint = -vec3MaxPoint;



	// 頂点座標データからボックスの最大点と最小点を求める
	for ( unsigned int i = 0; i < uiVertexPositionCount; i++ ) 
	{
		// 調べる頂点座標を1つ取り出す
		Vector3DF vec3 = pvec3VertexPositionData[i];
		
		// 各軸の最大の成分を検出して保存する
		if ( vec3.x > vec3MaxPoint.x ) { vec3MaxPoint.x = vec3.x; }
		if ( vec3.y > vec3MaxPoint.y ) { vec3MaxPoint.y = vec3.y; }
		if ( vec3.z > vec3MaxPoint.z ) { vec3MaxPoint.z = vec3.z; }
		
		// 各軸の最小の成分を検出して保存する
		if ( vec3.x < vec3MinPoint.x ) { vec3MinPoint.x = vec3.x; }
		if ( vec3.y < vec3MinPoint.y ) { vec3MinPoint.y = vec3.y; }
		if ( vec3.z < vec3MinPoint.z ) { vec3MinPoint.z = vec3.z; }
	}


	SetSize(
		Vector3DF(
			vec3MaxPoint.x - vec3MinPoint.x,
			vec3MaxPoint.y - vec3MinPoint.y,
			vec3MaxPoint.z - vec3MinPoint.z
		)
	);



	SetCenter( 
		Vector3DF(
			vec3MinPoint.x + ( m_vec3Size.x / 2 ),
			vec3MinPoint.y + ( m_vec3Size.y / 2 ),
			vec3MinPoint.z + ( m_vec3Size.z / 2 )
		)
	);
}





Matrix4x4F BoxCollider::GetWorldMatrix() const 
{
	Matrix4x4F mat4Ret = 
		NS_Graphic::NS_GraphicMathematics::TranslateMatrixRH( m_Transform.position ) *
		NS_Graphic::NS_GraphicMathematics::RotateXAxisMatrixRH( m_Transform.rotation.x ) *
		NS_Graphic::NS_GraphicMathematics::RotateYAxisMatrixRH( m_Transform.rotation.y ) *
		NS_Graphic::NS_GraphicMathematics::RotateZAxisMatrixRH( m_Transform.rotation.z ) *
		NS_Graphic::NS_GraphicMathematics::ScaleMatrix( m_Transform.scale );

	return mat4Ret;
	return
		NS_Graphic::NS_GraphicMathematics::TranslateMatrixRH( m_Transform.position ) *
		NS_Graphic::NS_GraphicMathematics::RotateXAxisMatrixRH( m_Transform.rotation.x ) *
		NS_Graphic::NS_GraphicMathematics::RotateYAxisMatrixRH( m_Transform.rotation.y ) *
		NS_Graphic::NS_GraphicMathematics::RotateZAxisMatrixRH( m_Transform.rotation.z ) *
		NS_Graphic::NS_GraphicMathematics::ScaleMatrix( m_Transform.scale );
}
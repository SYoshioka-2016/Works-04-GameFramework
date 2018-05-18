#ifndef _INCLUDE_GUARD_BOXCOLLIDER_H_
#define _INCLUDE_GUARD_BOXCOLLIDER_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#include "../Transform/Transform.h"
#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ゲーム名前空間
//
// @note : 
//
// ゲームアプリケーション関連の関数やクラスを管理する名前空間。
// ゲームを構成するクラスは全てこの名前空間に置くようにする。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_OpenGLWindowPCGame
{



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ボックスコライダクラス
//
// @note : 
//
// 箱状のコライダを表現するクラス。
// OBBの衝突判定を行う。
//----------------------------------------------------------------------------------------------------------------------------------
class BoxCollider
{
public:

	// コンストラクタ
	BoxCollider( const Vector3DF* pvec3VertexPositionData, const unsigned int uiVertexPositionCount, const Transform& transform );

	// デストラクタ
	~BoxCollider();

	
	const Vector3DF& GetCenter() const;
	
	const Vector3DF& GetSize() const;

	void SetCenter( const Vector3DF& vec3Center );

	void SetSize( const Vector3DF& vec3Size );



	bool CollisionDetection( const BoxCollider* pBoxCollider );



	void DrawBox();

private:

	void CreateBox( const Vector3DF* pvec3VertexPositionData, const unsigned int uiVertexPositionCount );

	Matrix4x4F GetWorldMatrix() const;

private:
	
	// メンバ変数

	Vector3DF m_vec3Center;

	Vector3DF m_vec3Size;


	const Transform& m_Transform;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_BOXCOLLIDER_H_
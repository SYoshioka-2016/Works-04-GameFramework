#ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
#define _INCLUDE_GUARD_GAMEOBJECT_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#include "../../Transform/Transform.h"
#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_

#ifndef _INCLUDE_GUARD_SPHERECOLLIDER_H_
#include "../../Collider/SphereCollider.h"
#endif	// #ifndef _INCLUDE_GUARD_SPHERECOLLIDER_H_



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
// @purpose : ゲームオブジェクトクラス
//
// @note : 
//
// ゲームシーンに置くオブジェクトのベースとなるクラス。
//----------------------------------------------------------------------------------------------------------------------------------
class GameObject 
{
public:

	// コンストラクタ
	GameObject();

	// デストラクタ
	virtual ~GameObject();



	// 開始処理
	virtual void Start();

	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw();

	// 終了処理
	virtual void End();


	
	// 衝突処理
	void CollisionHandling( const GameObject& gameObject );



	// 破棄するか?
	bool IsDestroy() const;
	


	// トランスフォームの取得
	const Transform& GetTransform() const;

	// スフィアコライダの取得
	const SphereCollider& GetSphereCollider() const;

	// 名前の取得
	const char* GetName() const;

	// 名前の設定
	void SetName( const char* strName );

protected:

	// 衝突中処理
	virtual void OnColliding( const GameObject& gameObject );

protected:

	// メンバ変数

	// トランスフォーム
	Transform			m_Transform;

	// スフィアコライダ
	SphereCollider		m_SphereCollider;

	// 衝突フラグ
	bool				m_bCollisionFlg;
	
	// 直前の衝突フラグ
	bool				m_bPrevCollisionFlg;

	// 破棄フラグ
	bool				m_bDestroyFlg;

	// 名前
	std::string			m_strName;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
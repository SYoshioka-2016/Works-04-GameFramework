#ifndef _INCLUDE_GUARD_PLAYER_H_
#define _INCLUDE_GUARD_PLAYER_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
#include "../../Base/GameObject.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECT_H_



//==================================================================================================================================
// 前方宣言
//==================================================================================================================================

// 追跡カメラクラス
namespace NS_OpenGLWindowPCGame { class ChaseCamera; }

// モデルクラス
namespace NS_Resource 
{
	namespace NS_Model 
	{ 
		class OGLModel;
	}
}

// ゲームオブジェクト管理クラス
namespace NS_OpenGLWindowPCGame { class GameObjectManager; }



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ゲーム名前空間
//
// @extends / GameObject : ゲームオブジェクトクラス
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
// @purpose : プレイヤークラス
//
// @note : 
//
// プレイヤーを構成するクラス。
//----------------------------------------------------------------------------------------------------------------------------------
class Player : public GameObject
{
public:

	// コンストラクタ
	Player( 
		ChaseCamera*							pChaseCamera,
		const NS_Resource::NS_Model::OGLModel*	pPlayerModel,
		const NS_Resource::NS_Model::OGLModel*	pBulletModel,
		GameObjectManager*						pGameObjectManager,
		const char*								strSEShotName,
		const char*								strSEHitName
	);

	// デストラクタ
	~Player();
	


	// 更新処理
	void Update();

	// 描画処理
	void Draw();



	// 初期化処理
	void Initialize(
		const float			fMoveSpeed, 
		const Vector3DF&	vec3Position,
		const Vector3DF&	vec3Rotation, 
		const Vector3DF&	vec3Scale,
		const Vector3DF&	vec3RotationAngleSpeed
	);

private:
	
	// 衝突中処理
	void OnColliding( const GameObject& gameObject );



	// 前に移動する入力があったか?
	bool IsInputMoveForward() const;

	// 後ろに移動する入力があったか?
	bool IsInputMoveBack() const;

	// 右にヨー回転する入力があったか?
	bool IsInputYawRotationRight() const;
	
	// 左にヨー回転する入力があったか?
	bool IsInputYawRotationLeft() const;
	
	// 上にピッチ回転する入力があったか?
	bool IsInputPitchRotationUp() const;
	
	// 下にピッチ回転する入力があったか?
	bool IsInputPitchRotationDown() const;

	
	
	// 弾を発射する入力があったか?
	bool IsInputShoot() const;



	// 移動処理
	void Move();

	// 弾発射開始処理
	void ShootStart();

private:

	// メンバ変数

	// 移動の速さ
	float										m_fMoveSpeed;

	// 各回転軸の回転の速さ
	Vector3DF									m_vec3RotationAngleSpeed;

	// 移動方向ベクトル
	Vector3DF									m_vec3MoveDirection;

	// プレイヤーのモデル
	const NS_Resource::NS_Model::OGLModel*		m_pPlayerModel;

	// 弾のモデル
	const NS_Resource::NS_Model::OGLModel*		m_pBulletModel;

	// 追跡カメラ
	ChaseCamera*								m_pChaseCamera;

	// ゲームオブジェクト管理クラス
	GameObjectManager*							m_pGameObjectManager;

	// 発射のSE名
	const char*									m_strSEShotName;

	// 弾の衝突のSE名
	const char*									m_strSEHitName;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_PLAYER_H_
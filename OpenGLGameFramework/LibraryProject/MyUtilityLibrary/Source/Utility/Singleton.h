#ifndef _INCLUDE_GUARD_SINGLETON_H_
#define _INCLUDE_GUARD_SINGLETON_H_



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : シングルトンクラス
//
// @note : 
//
// 継承先をシングルトンクラスにする。
//
// 継承先の作成には以下の要件を要請する。
// 
// 1.継承先のクラス定義で、継承先クラスをテンプレート引数に指定して
//   このクラスを継承する。
//
//   ex) class A : public Singleton<A> { 〜
//
// 2.継承先のクラス定義内で、このクラスをフレンドクラスに指定する
//   (継承先クラスのコンストラクタをprivateにしつつ、
//   このクラスでそのコンストラクタを呼ぶ為)。
//
//   ex) friend Singleton<A>;
//
// 3.継承先クラスのコンストラクタ、デストラクタのアクセス修飾子を
//   privateにする。
//   またコンストラクタ、デストラクタに引数が有ってはならない。
//----------------------------------------------------------------------------------------------------------------------------------
template<class T>
class Singleton
{
public:

	//----------------------------------------------------------------------------------------------------------------------------------
	// @purpose : インスタンスゲッタ
	//
	// @return / T* : インスタンスのアドレス
	//
	// @note : 
	//
	// 継承先クラスのインスタンスを生成し、そのアドレスを返す。
	// 継承先クラスで定義したメンバを外部から利用するには、
	// これを使って継承先クラスのインスタンスを取得し、メンバを参照する。
	//
	// ex) 継承先クラス::Instance()->メンバ
	//----------------------------------------------------------------------------------------------------------------------------------
	static T* Instance() 
	{ 
		static T instance;

		return &instance;
	}

protected:

	Singleton() { }

	virtual ~Singleton() { }

private:
	
	Singleton( const T& r ) { }

	Singleton& operator=( const Singleton& r ) { }
};



#endif	// #ifndef _INCLUDE_GUARD_SINGLETON_H_
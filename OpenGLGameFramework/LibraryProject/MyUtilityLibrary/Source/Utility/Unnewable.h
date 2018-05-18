#ifndef _INCLUDE_GUARD_UNNEWABLE_H_
#define _INCLUDE_GUARD_UNNEWABLE_H_



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 生成不能クラス
//
// @note : 
//
// このクラスの継承先のクラスを生成不可能にする。
// private継承で継承する。
//----------------------------------------------------------------------------------------------------------------------------------
class Unnewable
{
protected:
	
	// デストラクタ
	~Unnewable() { }

private:

	// コンストラクタ
	Unnewable() { }



	// コピーコンストラクタ
	Unnewable( const Unnewable& );

	// コピー代入演算子
	Unnewable& operator=( const Unnewable& );
};



#endif	// #ifndef _INCLUDE_GUARD_UNNEWABLE_H_
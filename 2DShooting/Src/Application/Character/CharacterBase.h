#pragma once


//キャラクターの親クラス
class CharacterBase
{
public:
	// 初期設定
	virtual void Init() = 0;

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw2D() = 0;


	//キャラの画像をアドレスでセット
	void SetTex(KdTexture* tex) { m_charaTex = tex; }


	//キャラの切り取り範囲設定
	//float x...X方向の長さ
	//float y...Y方向の高さ 
	void SetRec(float x, float y) { m_rec = { 0,0,x,y }; }


protected:

	//画像アドレス
	KdTexture* m_charaTex = nullptr;

	//キャラの座標
	Math::Vector2 m_pos;

	//キャラの切り取り範囲
	Math::Rectangle m_rec;

	//キャラのスピード


	//合成行列
	Math::Matrix m_mat;

	//移動行列
	Math::Matrix m_transMat;

	//拡大行列
	Math::Matrix m_scaleMat;

	//回転行列
	Math::Matrix m_rotationMat;




private:

};


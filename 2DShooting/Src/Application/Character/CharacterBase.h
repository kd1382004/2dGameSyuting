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

	Math::Vector2 GetPos() { return m_pos; }

	//当たり判定用変数(直径)を返す
	float GetHitDetection() { return HitDetection; }

	//生存フラグを返す
	bool GetAliveFlg() { return m_aliveFlg; }

protected:

	// 解放
	virtual void Release() = 0;

	//画像アドレス
	KdTexture* m_charaTex = nullptr;

	//キャラの座標
	Math::Vector2 m_pos;

	//キャラの切り取り範囲
	Math::Rectangle m_rec;

	//キャラのスピード
	Math::Vector2 m_speed;

	//キャラの移動量
	Math::Vector2 m_move;
	//合成行列
	Math::Matrix m_mat;

	//移動行列
	Math::Matrix m_transMat;

	//拡大行列
	Math::Matrix m_scaleMat;

	//回転行列
	Math::Matrix m_rotationMat;

	//生存フラグ
	bool m_aliveFlg;

	//円当たり判定用変数(直径を入れる)
	float HitDetection;


private:

};


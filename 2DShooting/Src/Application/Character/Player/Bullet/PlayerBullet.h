#pragma once

class PlayerBullet
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};


	// 初期設定
	//pos...プレイヤーの座標を入れる
	//deg...プレイヤーの角度を入れる
	void Init(Math::Vector2 pos,float rad);

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	//敵と当たってからの処理
	void Hit();

	//キャラの画像をアドレスでセット
	void SetTex(KdTexture* tex) { m_bulletTex = tex; }

	Math::Vector2 GetPos() { return m_pos; }

	//当たり判定用変数(直径)を返す
	float GetHitDetection() { return HitDetection; }

	//生存フラグを返す
	bool GetAliveFlg() { return m_aliveFlg; }
private:

	KdTexture* m_bulletTex = nullptr;

	Math::Vector2 m_pos = Math::Vector2(0, 0);

	float m_speed = 10.0f;

	Math::Vector2 m_move = Math::Vector2(0, 0);

	Math::Matrix m_mat;

	Math::Rectangle m_rec = { 0,0,16,16 };

	float HitDetection = 0.0f;
	bool m_aliveFlg = false;	
	float m_rad = 0.0f;
};

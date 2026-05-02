#pragma once

class PlayerBullet
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};


	// 初期設定
	//pos...プレイヤーの座標を入れる
	//deg...プレイヤーの角度を入れる
	void Init(Math::Vector2 pos, float rad);

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

	//弾の貫通回数を返す
	int GetBulletPene() { return m_buletPene; }

	//弾の貫通回数を1減らす
	void DownBulletPene() {  m_buletPene--; }

	//どの番号の敵と当たったか
	void SetEnemyNum(int Num) { m_enemuNum = Num; }

	//どの番号の敵と最後に当たったか
	int GetEnemyNum() { return m_enemuNum ; }

	//攻撃力ゲッター
	int GetAtk() { return m_atk; }

	void SetSliveFlg(bool flg) { m_aliveFlg = flg; }
private:

	KdTexture* m_bulletTex = nullptr;

	Math::Vector2 m_pos = Math::Vector2(0, 0);

	float m_speed = 10.0f;

	Math::Vector2 m_move = Math::Vector2(0, 0);

	float m_deg;

	Math::Vector2 m_siz;

	Math::Matrix m_mat;

	Math::Rectangle m_rec = { 0,0,32,32 };

	float HitDetection = 16.0f;
	bool m_aliveFlg = false;
	float m_rad = 0.0f;

	//弾の貫通回数
	int m_buletPene;

	//何番目の敵に最後当たったか
	int m_enemuNum;

	//攻撃力
	int m_atk=0;
};

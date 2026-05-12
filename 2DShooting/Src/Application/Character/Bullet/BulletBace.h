#pragma once
class CharacterInfo;
class CharacterInfo;

//弾のType
enum BulletType
{
	NORMAL,
	FIRE,
};

class BulletBace
{
public:
	BulletBace() {};
	~BulletBace() {};

	// 初期設定
	//pos...プレイヤーの座標を入れる
	//deg...プレイヤーの角度を入れる
	//Info...PlayerPowerUpInfonのアドレス
	virtual void Init(Math::Vector2 pos, float rad, CharacterInfo* Info, BulletType type = NORMAL) {};

	// 更新処理
	virtual	void Update() {};

	// 描画処理
	virtual	void Draw2D() {};

	//敵と当たってからの処理
	virtual	void Hit() {};

	//キャラの画像をアドレスでセット
	void SetTex(KdTexture* tex) { m_bulletTex = tex; }

	Math::Vector2 GetPos() { return m_pos; }
	void SetPos(Math::Vector2 pos) { m_pos = pos; }

	//当たり判定用変数(直径)を返す
	float GetHitDetection() { return HitDetection; }

	//生存フラグを返す
	bool GetAliveFlg() { return m_aliveFlg; }

	//弾の貫通回数を返す
	int GetBulletPeneNum() { return m_buletPeneNum; }

	//弾の貫通回数を1減らす
	void DownBulletPeneNum() { m_buletPeneNum--; }

	//どの番号の敵と当たったか
	void SetEnemyNum(int Num) { m_enemuNum = Num; }

	//どの番号の敵と最後に当たったか
	int GetEnemyNum() { return m_enemuNum; }

	//攻撃力ゲッター
	int GetAtk() { return m_atk; }

	void SetSliveFlg(bool flg) { m_aliveFlg = flg; }

	virtual void MatConfirmed(float scroll) {};

	//v...壁の法線ベクトル
	virtual void MapHit(Math::Vector2 v1) {};



	BulletType GetBulletType() { return  m_bullettype; }
protected:
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

	//何番目の敵に最後当たったか
	int m_enemuNum;

	//弾の貫通回数
	int m_buletPeneNum = 0;

	//弾のバウンド回数
	int m_boundNum = 0;

	//攻撃力
	int m_atk = 0;

	BulletType m_bullettype = BulletType::NORMAL;
};

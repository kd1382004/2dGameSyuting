#pragma once
#include "../CharacterBase.h"

class BulletBace;
class  PlayerHpBer;
class  CharacterInfo;
class  SoundBase;
class  Playerheel;

class Player : public CharacterBase
{
public:

	Player() {};
	~Player() override { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

	void MatConfirmed(float scroll) override;

	//アニメーションモードの変更
	void AnimeRec();

	int GetBulletNum() { return m_bullet.size(); }
	BulletBace* GetBullet(int num);

	//num番目の弾が当たった後の処理
	void PlayerBulletHit(int num);

	//弾の消去
	void ReleseBuleet(int num);


	void ReleseBuleet();

	void SetShadowTex(KdTexture* tex) { m_shadowTex = tex; }

	CharacterInfo* GetPlayerPlayerPowerUpInfo() { return m_info; }

	int GetHP() { return m_HP; }
	int GetMaxHP() { return m_MaxHP; }

	int GetEnemyDehHeelLv() { return m_enemyDehHeelLv; }
	void SetEnemyDehHeelLv(int lv) { m_enemyDehHeelLv += lv; if (m_enemyDehHeelLv > 99) { m_enemyDehHeelLv = 99; }}

	float EnemyDehHeelAmount();

	void HPHeel(float heel);

	void SetFireArrow(int lv) { m_fireArrowLv += lv; if (m_fireArrowLv > 99) { m_fireArrowLv = 99; } }
	int GetFireArrow() { return m_fireArrowLv; }

	void SetScoreUpLV(int lv) { m_scoreUpLV += lv; if (m_scoreUpLV > 99) { m_scoreUpLV = 99; } }
	int GetScoreUpLV() { return m_scoreUpLV; }

	void ResetDeg() { m_deg = 0; }
	void ResetSiz() {m_siz = { 3,3 };}

	//プレイヤー移動関数
	void Move();

	void SetHPHeel(Math::Vector2 pos);

	void HPDown(int dmg)override;
private:

	KdTexture* m_shadowTex;

	Math::Matrix m_shadowMat;

	enum PlayerAniemMode
	{
		Nomar,
		MoveMode,//移動
		ATKMode, //攻撃
	};

	void Release()override;

	//プレイヤーキー操作

	//上移動
	int m_moveUp;
	//下移動
	int m_moveDown;
	//左移動
	int m_moveLeft;
	//右移動
	int m_moveRight;

	//弾
	//弾発射
	void Shot();
	void Shot(bool _3WShotFlg, bool m_3LRShotFlg);
	void BulletUpdata();
	void BulletDraw();

	//撃つかどうか
	bool m_shotFlg;

	KdTexture m_bulletTex;

	std::vector< BulletBace*> m_bullet;
	float m_shotInterval = 0;			//弾の発射間隔管理
	float m_shotIntervalMax = 0.5f * 60;	//弾の発射間隔(インターバル秒×FPS(60))


	std::vector< Playerheel*> m_playerHeel;

	////////////////////////////////
	PlayerAniemMode m_animeMode = Nomar;

	PlayerHpBer* m_hpBer;

	//敵を倒す度回復Lv
	int m_enemyDehHeelLv = 0;


	//炎の矢
	int m_fireArrowLv = 0;

	//scoreアップ量
	int m_scoreUpLV = 0;

	//音
	SoundBase* m_bowSE;
	SoundBase* m_fireSE;
	SoundBase* m_HitSE;
};


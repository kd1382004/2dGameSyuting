#pragma once
#include "../CharacterBase.h"

class BulletBace;
class SoundBase;
class Player;

enum Mode
{
	MOVE,
	ATK,
	Def,
};

class EnemyBase :public CharacterBase
{
public:
	EnemyBase() { BaseInit(); }
	~EnemyBase() override { Release(); }

	// 初期設定
	virtual void Init() {}

	// 更新処理
	virtual void Update() {}

	// 描画処理
	virtual void Draw2D() {}

	virtual void MatConfirmed(float scroll) {}


	virtual void SetStatus(int Stage) {};

	//追跡用等にプレイヤー座標セット
	void SetPlayerPos(Math::Vector2 playerPos) { m_plaeyrPos = playerPos; };


	void PlayerBulletHit(BulletBace* bullet);


	virtual void BlockHit() {};

	int GetBulletNum() { return  m_bullet.size(); }

	BulletBace* GetBullet(int i) { return   m_bullet[i]; }

	void BulletHit(BulletBace* bullet);

	virtual void EnemyHit() {}

	void StateTypeManager();

	//状態変化
	//type...状態を入れる
	//Time...時間を入れる
	//dmg...ダメージを与える系統なら1回当たりのダメージを入れる
	void StateTypeChange(StateType type, int Time = 0, int  dmg = 0);


	void ChangeMode(Mode mode);

	//生きてる敵の数
	void SetEnemyNum(int num) { m_enemyNum = num; }

	bool GetDefAnimeFinshFlg() { return m_defAnimeFinshFlg; }
	void SetDefAnimeFinshFlg(bool flg) { m_defAnimeFinshFlg = flg; }
protected:

	int m_enemyNum = -1;

	// 解放
	virtual void Release();

	//追跡用等のプレイヤー座標
	Math::Vector2 m_plaeyrPos = { 0,0 };

	std::vector< BulletBace*> m_bullet;

	virtual void MODEMove() {};
	virtual void MODEATK() {};
	virtual void MODEDef() {};


	Mode m_mode = MOVE;
	bool m_defAnimeFinshFlg = false;
private:




	void BaseInit();

	void StateTypeFire();

	////////////////////////////////////////
	//炎ドットダメージ

	//クールタイムMax
	static const int m_firemDMGCoolTimMax = 60;

	//クールタイムM
	int m_firemDMGCoolTim = 0;

	//一回当たりのダメージ
	int m_fireDmg = 0;

	//音
	SoundBase* m_fireSE;
	SoundBase* m_HitSE;
	SoundBase* m_DownSE;
};


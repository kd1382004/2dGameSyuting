#pragma once
#include "../CharacterBase.h"

class BulletBace;

enum Mode
{
	MOVE,
	ATK,
	Def,
};

class EnemyBase :public CharacterBase
{
public:
	EnemyBase() { m_speed = { 1, 1 }; }
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
	void StateTypeChange(StateType type, int Time = 0);


	void ChangeMode(Mode mode);
protected:

	// 解放
	virtual void Release() {}

	//追跡用等のプレイヤー座標
	Math::Vector2 m_plaeyrPos = { 0,0 };

	std::vector< BulletBace*> m_bullet;

	virtual void MODEMove() {};
	virtual void MODEATK() {};
	virtual void MODEDef() {};


	Mode m_mode = MOVE;
	
private:


	void StateTypeFire();

	////////////////////////////////////////
	//炎ドットダメージ

	//クールタイムMax
	static const int m_firemDMGCoolTimMax = 60;

	//クールタイムM
	int m_firemDMGCoolTim = 0;
};


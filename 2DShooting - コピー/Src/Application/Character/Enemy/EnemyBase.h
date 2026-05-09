#pragma once
#include "../CharacterBase.h"

class BulletBace;

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


	//追跡用等にプレイヤー座標セット
	void SetPlayerPos(Math::Vector2 playerPos) { m_plaeyrPos = playerPos; };


	void PlayerBulletHit(BulletBace* bullet);


	virtual void BlockHit() {};

	int GetBulletNum() { return  m_bullet.size(); }

	BulletBace* GetBullet(int i) { return   m_bullet[i]; }

	void BulletHit(BulletBace* bullet);
protected:

	// 解放
	virtual void Release() {}

	//追跡用等のプレイヤー座標
	Math::Vector2 m_plaeyrPos = { 0,0 };

	std::vector< BulletBace*> m_bullet;
private:

};


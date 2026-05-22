#pragma once

class CharacterInfo;
#include"../../../Bullet/BulletBace.h"

class SkeletonBullet :public BulletBace
{
public:
	SkeletonBullet() {}
	~SkeletonBullet() {};

	// 初期設定
	//pos...座標を入れる
	//deg...角度を入れる
	//Info...PlayerPowerUpInfonのアドレス
	void Init(Math::Vector2 pos, float rad, CharacterInfo* Info, BulletType type = NORMAL)override;


	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

	//敵と当たってからの処理
	void Hit()override;

	void MatConfirmed(float scroll)override;

	//v...壁の法線ベクトル
	void MapHit(Math::Vector2 v1)override;


private:
	int aliveTime = 500;
};
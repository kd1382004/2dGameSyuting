#pragma once

class CharacterInfo;
#include"../../Bullet/BulletBace.h"

class PlayerBullet:public BulletBace
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};


	// 初期設定
	//pos...プレイヤーの座標を入れる
	//deg...プレイヤーの角度を入れる
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

	//炎のアニメーション
	float m_fierAnime = 0;
};

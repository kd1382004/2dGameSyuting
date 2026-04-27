#pragma once
#include "../CharacterBase.h"

class PlayerBullet;

class Player: public CharacterBase
{
public:

	Player() {};
	~Player() { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;


	int GetBulletNum() { return m_bullet.size(); }
	PlayerBullet* GetBullet(int num);

private:

	void Release()override;

	//プレイヤー角度
	float m_deg = 0.0f;

	//プレイヤー移動関数
	void Move();

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
	void BulletUpdata();
	void BulletDraw();

	KdTexture m_bulletTex;

	 std::vector< PlayerBullet*> m_bullet;
	 float m_shotInterval = 0;			//弾の発射間隔管理
	 float m_shotIntervalMax = 0.5f*60;	//弾の発射間隔(インターバル秒×FPS(60))

};


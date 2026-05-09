#pragma once

#include"../EnemyBase.h"
class SkeletonBullet;
class CharacterInfo;

class Skeleton :public EnemyBase
{
public:
	Skeleton() {}
	~Skeleton() {};

	// ‰Šúİ’è
	void Init()override;

	// XVˆ—
	void Update()override;

	// •`‰æˆ—
	void Draw2D()override;

	void MatConfirmed(float scroll)override;

	void BlockHit()override;

	void SetStatus(int stage)override;

	void EnemyHit()override;
private:

	// ‰ğ•ú
	void Release()override;

	//’e‚ğŒ‚‚Â
	void shot();
	void Shot(bool _3WShotFlg, bool m_3LRShotFlg);

	KdTexture m_bulletTex;

	int m_shotInterval;
	bool m_shotFlg;
	float m_shotIntervalMax = 0.5f * 100;
};
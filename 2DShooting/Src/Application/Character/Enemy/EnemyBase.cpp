#include"EnemyBase.h"
#include"../Bullet/BulletBace.h"
#include"../Bullet/BulletBace.h"

void EnemyBase::PlayerBulletHit(BulletBace* bullet)
{
	m_HP -= bullet->GetAtk();

	if (m_HP <= 0)
	{
		m_aliveFlg = false;
		m_anime = 0;
	}
}

void EnemyBase::BulletHit(BulletBace* bullet)
{
	bullet->DownBulletPeneNum();

	if (bullet->GetBulletPeneNum() < 0)
	{
		bullet->SetSliveFlg(false);
	}
}


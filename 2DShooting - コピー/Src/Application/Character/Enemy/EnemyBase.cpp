#include"EnemyBase.h"
#include"../Bullet/BulletBace.h"
#include"../Bullet/BulletBace.h"

void EnemyBase::PlayerBulletHit(BulletBace* bullet)
{

	if (m_HPDownCoolTime == m_HPDownCoolTimeMax)
	{
		m_HPDownCoolTime = 0;
		m_HP -= bullet->GetAtk();
	}

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


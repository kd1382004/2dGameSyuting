#include"EnemyBase.h"
#include"../Player/PlayerBullet/PlayerBullet.h"


void EnemyBase::PlayerBulletHit(PlayerBullet* bullet)
{
	m_HP -= bullet->GetAtk();

	if (m_HP <= 0)
	{
		m_aliveFlg = false;
		m_anime = 0;
	}
}


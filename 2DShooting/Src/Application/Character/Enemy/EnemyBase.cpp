#include"EnemyBase.h"
#include"../Bullet/BulletBace.h"
#include"../../Particle/Fire/Fire.h"
#include"../../Sound/Game/Player/Bow/FireSE.h"

void EnemyBase::PlayerBulletHit(BulletBace* bullet)
{

	if (m_HPDownCoolTime == m_HPDownCoolTimeMax)
	{
		m_HPDownCoolTime = 0;
		m_HP -= bullet->GetAtk();

		if (m_HP > 0)
		{
			//ノックバック
			Math::Vector2 enemyiPos = m_pos;
			enemyiPos += bullet->GetMove() * 1.5;
			m_pos = enemyiPos;
		}
	}

	if (m_HP <= 0)
	{
		ChangeMode(Mode::Def);
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

void EnemyBase::StateTypeManager()
{


	if (m_statetype != TypeNORMAL)
	{
		m_stateTime += 1 / 60.0f;

		if (m_stateTime > m_stateTimeMax)
		{
			StateTypeChange(StateType::TypeNORMAL);
		}
	}


	switch (m_statetype)
	{
	case TypeNORMAL:
		break;
	case TypeFIRE:
		StateTypeFire();
		break;
	default:
		break;
	}

}



void EnemyBase::StateTypeChange(StateType type, int Time, int  dmg)
{
	for (int i = 0; i < m_praticle.size(); i++)
	{
		delete m_praticle[i];
		m_praticle.erase(m_praticle.begin() + i);
		i--;
	}

	switch (type)
	{
	case TypeNORMAL:

		break;
	case TypeFIRE:

		m_praticle.push_back(new Fire());
		m_praticle.back()->Emit({ 0,0 }, { 0,0 }, 0, Math::Color{ 0,0,0,0 }, 0, true, -1);
		m_praticle.back()->SetdefSiz({ 0.5,0.7 });
		m_fireDmg = dmg;
		m_fireSE->Play();
		break;
	default:
		break;
	}

	m_stateTime = 0;
	m_stateTimeMax = Time;
	m_statetype = type;
}


void EnemyBase::BaseInit()
{
	m_speed = { 1, 1 };
	m_fireSE = new FireSE();
}

void EnemyBase::StateTypeFire()
{
	m_firemDMGCoolTim++;


	if (m_firemDMGCoolTim > m_firemDMGCoolTimMax)
	{
		m_firemDMGCoolTim = 0;
		m_HP -= m_fireDmg;

		if (m_HP <= 0)
		{
			ChangeMode(Mode::Def);
			m_aliveFlg = false;
		}
	}

}

void EnemyBase::ChangeMode(Mode mode)
{
	switch (mode)
	{
	case MOVE:
		m_mode = MOVE;
		break;
	case ATK:
		m_mode = ATK;
		break;

	case Def:
		m_mode = Def;
	default:
		break;
	}

	m_anime = 0;
}

void EnemyBase::Release()
{
	delete m_fireSE;
}

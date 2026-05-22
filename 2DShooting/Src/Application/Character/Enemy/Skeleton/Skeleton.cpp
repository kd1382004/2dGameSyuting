#include "Skeleton.h"
#include"SkeletonBullet/SkeletonBullet.h"
#include"../../Info/CharacterInfoBace.h"
#include"../../../Particle/Fire/Fire.h"

void Skeleton::Init()
{
	m_aliveFlg = true;
	HitDetection = 64;
	m_pos = {};
	m_HP = 10;
	m_speed.y = 1;
	m_move.y = m_speed.y;
	m_bulletTex.Load("Tex/Character/Enemy/Skeleton/Bullet/Bullet.png");
	m_info = new CharacterInfo();
	m_rec = { 32 * (int)m_anime, 32,32,32 };
	m_info->SetATKLV(1);
	m_siz = { 2,2 };
}

void Skeleton::Update()
{
	if (!m_drawFlg)
	{
		if (m_bullet.size() == 0 || m_enemyNum == 0)
		{
			m_deleteFlg = true;
		}
	}


	if (m_aliveFlg)
	{
		StateTypeManager();
		HPCoolTimeManager();
	}


	switch (m_mode)
	{
	case MOVE:

		MODEMove();

		break;
	case ATK:

		MODEATK();

		break;

	case Def:

		MODEDef();

	default:
		break;
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{

		if (m_bullet[i]->GetAliveFlg())
		{
			m_bullet[i]->Update();
		}
		else
		{
			delete m_bullet[i];
			m_bullet.erase(m_bullet.begin() + i);
			i--;
		}

	}
}

void Skeleton::Draw2D()
{
	if (!m_deleteFlg)
	{
		for (int i = 0; i < m_bullet.size(); i++)
		{
			m_bullet[i]->Draw2D();
		}

		if (m_drawFlg)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat);
			if (m_charaAlpha != 1)
			{
				SHADER.m_spriteShader.DrawColorTex(m_charaTex, m_rec, &Math::Color{ 1,0,0,m_charaAlpha });
			}
			else
			{
				SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, m_charaAlpha);
			}

			if (m_aliveFlg)
			{
				for (int i = 0; i < m_praticle.size(); i++)
				{
					m_praticle[i]->Draw();
				}
			}
		}
	}
}

void Skeleton::MatConfirmed(float scroll)
{
	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->MatConfirmed(scroll);
	}

	for (int i = 0; i < m_praticle.size(); i++)
	{
		m_praticle[i]->Update(m_pos, scroll);
	}

	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat = m_scaleMat * /*m_rotationMat **/ m_transMat;
}

void Skeleton::BlockHit()
{
	m_move.y *= -1;
}

void Skeleton::SetStatus(int stage)
{
	int HPUp = 0;
	int bound = 0;
	if (stage != 0)
	{
		HPUp = stage / 3 * 10;
		bound = stage / 5;
	}

	m_HP = 5 + HPUp;

	int atkLv = stage * 0.1;


	int num;
	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	int siz = 100 - stage;
	std::uniform_int_distribution<int> dist(60, 60 + siz);
	num = dist(rand_engine);

	m_shotIntervalMax = 1.0f * num;
	m_info->SetBoundNum(bound);
	m_info->SetATKLV(atkLv);
}

void Skeleton::EnemyHit()
{
	BlockHit();
}

void Skeleton::Release()
{
	m_bulletTex.Release();
}

void Skeleton::shot()
{
	m_shotInterval--;

	if (m_shotInterval <= 0 && !m_shotFlg)
	{
		m_anime = 0;
		m_shotFlg = true;
		ChangeMode(ATK);
	}

}

void Skeleton::Shot(bool _3WShotFlg, bool _3LRShotFlg)
{
	m_bullet.push_back(new SkeletonBullet);
	m_bullet.back()->Init(m_pos, m_deg, m_info);
	m_bullet.back()->SetTex(&m_bulletTex);

	if (_3WShotFlg)
	{
		float deg = m_deg;
		deg -= 45;
		for (int i = 0; i < 2; i++)
		{
			ChangeMode(ATK);
			m_bullet.push_back(new SkeletonBullet);
			m_bullet.back()->Init(m_pos, deg, m_info);
			m_bullet.back()->SetTex(&m_bulletTex);
			deg += 90;
		}
	}

	if (_3LRShotFlg)
	{
		float deg = m_deg;
		deg -= 90;
		for (int i = 0; i < 2; i++)
		{
			m_bullet.push_back(new SkeletonBullet);
			m_bullet.back()->Init(m_pos, deg, m_info);
			m_bullet.back()->SetTex(&m_bulletTex);
			deg += 180;
		}
	}
}

void Skeleton::MODEMove()
{
	shot();
	m_pos.y += m_move.y;

	float moveX = m_plaeyrPos.x - m_pos.x;
	float moveY = m_plaeyrPos.y - m_pos.y;
	float rad = atan2(moveY, moveX);
	if (fabs(moveX) < 0.0001f && fabs(moveY) < 0.0001f)
	{
		int a = 0;
	}
	else
	{
		float deg = DirectX::XMConvertToDegrees(rad);

		if (deg < 0)
		{
			deg += 360;
		}

		m_deg = deg;
	}

	//アニメーション
	m_anime += 0.1;
	if (m_anime > 6)
	{
		m_anime = 0;
	}
	m_rec = { 32 * (int)m_anime, 0,32,32 };

}

void Skeleton::MODEATK()
{
	//アニメーション
	m_anime += 0.1;
	if (m_anime > 6)
	{
		m_anime = 0;

		if (m_shotFlg)
		{
			m_shotFlg = false;
			m_shotInterval = m_shotIntervalMax;
			Shot(m_info->Get3WShotFlg(), m_info->GetLRShotFlg());
			ChangeMode(MOVE);
		}

	}

	if (m_deg >= 0 && m_deg <= 90 || m_deg >= 270 && m_deg <= 360)
	{
		m_siz.x = 2;
	}
	else
	{
		m_siz.x = -2;

	}

	m_rec = { 32 * (int)m_anime, 32,32,32 };

}

void Skeleton::MODEDef()
{//アニメーション
	m_anime += 0.1;
	if (m_anime > 6)
	{
		m_anime = 0;
		if (!m_aliveFlg)
		{
			m_drawFlg = false;
		}
	}

	m_rec = { 32 * (int)m_anime, 32 * 6,32,32 };
}

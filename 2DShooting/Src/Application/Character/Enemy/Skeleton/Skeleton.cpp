#include "Skeleton.h"
#include"SkeletonBullet/SkeletonBullet.h"
#include"../../Info/CharacterInfoBace.h"

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
	shot();



	if (m_aliveFlg)
	{
		HPCoolTimeManager();

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


		shot();
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Update();
	}
	//アニメーション
	m_anime += 0.1;
	if (m_anime > 6)
	{
		m_anime = 0;
		if (!m_aliveFlg)
		{
			m_deleteFlg = true;
		}

		if (m_shotFlg)
		{
			m_shotFlg = false;
			m_shotInterval = m_shotIntervalMax;
			Shot(m_info->Get3WShotFlg(), m_info->GetLRShotFlg());
		}

	}

	if (m_aliveFlg)
	{

		if (m_shotFlg)
		{
			if (m_deg >= 0 && m_deg <= 90 || m_deg >= 270 && m_deg <= 360)
			{
				m_siz.x = 2;
			}
			else
			{
				m_siz.x = -2;

			}

			m_rec = { 32 * (int)m_anime, 0,32,32 };
		}
		else
		{

			m_rec = { 32 * (int)m_anime, 32,32,32 };
		}


	}
	else
	{
		m_rec = { 32 * (int)m_anime, 32 * 6,32,32 };
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

		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, m_charaAlpha);
	}
}

void Skeleton::MatConfirmed(float scroll)
{
	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->MatConfirmed(scroll);
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

	m_HP = 20 + HPUp;

	int atkLv = 0;
	atkLv = stage * 0.8;



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

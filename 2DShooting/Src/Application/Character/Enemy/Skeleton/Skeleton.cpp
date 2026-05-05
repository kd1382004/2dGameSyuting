#include "Skeleton.h"

void Skeleton::Init()
{
	m_aliveFlg = true;
	HitDetection = 64;
	m_pos = { (float)(rand() % 640 - 320),(float)(rand() % 720 / 2 - 360 / 2) };
	m_HP = 10;
	m_speed.y = 1;
	m_move.y = m_speed.y;
}

void Skeleton::Update()
{
	shot();



	if (m_aliveFlg)
	{
		m_pos.y += m_move.y;

		float moveX = m_plaeyrPos.x - m_pos.x;
		float moveY = m_plaeyrPos.y - m_pos.y;
		float rad = atan2(moveY, moveX);
		float deg = DirectX::XMConvertToDegrees(rad);

		if (deg < 0)
		{
			deg += 360;
		}

		m_deg = deg;
	}
	

	//アニメーション
	m_anime += 0.3;
	if (m_anime > 6)
	{
		m_anime = 0;
		if (!m_aliveFlg)
		{
			m_deleteFlg = true;
		}
	}

	if (!m_aliveFlg)
	{
		m_rec = { 32 * (int)m_anime, 32*6,32,32 };
	}
	else
	{
		m_rec = { 32 * (int)m_anime, 0,32,32 };
	}
	

}

void Skeleton::Draw2D()
{
	if (!m_deleteFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
	}
}

void Skeleton::MatConfirmed(float scroll)
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(2, 2, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat = m_scaleMat * /*m_rotationMat **/ m_transMat;
}

void Skeleton::BlockHit()
{
	m_move.y *= -1;
}

void Skeleton::Release()
{

}

void Skeleton::shot()
{

}

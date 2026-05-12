#include "SkeletonBullet.h"
#include"../../../Info/CharacterInfoBace.h"

void SkeletonBullet::Init(Math::Vector2 pos, float deg, CharacterInfo* Info, BulletType type)
{
	m_enemuNum = -999;
	m_buletPeneNum = Info->GetBuletPeneNum();
	m_boundNum = Info->GetBoundNum();
	m_atk = Info->GetATK() + Info->GetATKLV() * 2;
	m_deg = deg;
	m_siz = { 1,1 };
	m_pos = pos;
	HitDetection = 15.0f;
	m_aliveFlg = true;
	m_rec = { 0,0,21,15 };
	m_speed = 1.0f;

	//角度から移動量を求める
	m_move.x = cos(DirectX::XMConvertToRadians(deg)) * m_speed;
	m_move.y = sin(DirectX::XMConvertToRadians(deg)) * m_speed;
	m_mat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0) * Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg)) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void SkeletonBullet::Update()
{
	if (!m_aliveFlg) { return; }


	//座標更新
	m_pos += m_move;
}

void SkeletonBullet::Draw2D()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_bulletTex, m_rec, 1.0f);
	}
}

void SkeletonBullet::Hit()
{

}

void SkeletonBullet::MatConfirmed(float scroll)
{
	//行列合成
	//行列作成
	m_mat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0) * Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg)) * Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
}

void SkeletonBullet::MapHit(Math::Vector2 v)
{

	m_boundNum--;

	if (m_boundNum < 0)
	{
		m_aliveFlg = false;
	}
	else
	{
		m_pos -= m_move * 1.5;

		float dot = v.x * m_move.x + v.y * m_move.y;
		m_move = { m_move.x - 2 * dot * v.x, m_move.y - 2 * dot * v.y };


		Math::Vector2 FuturePos = m_pos + m_move;
		float moveX = FuturePos.x - m_pos.x;
		float moveY = FuturePos.y - m_pos.y;

		m_move = FuturePos - m_pos;
		m_move.Normalize();
		m_move *= m_speed;
		float rad = atan2(m_move.y, m_move.x);
		m_deg = DirectX::XMConvertToDegrees(rad);

		if (m_deg < 0)
		{
			m_deg += 360;
		}

		m_pos += m_move;
	}

}

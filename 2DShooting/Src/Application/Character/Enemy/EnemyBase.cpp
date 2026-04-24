#include"EnemyBase.h"

void EnemyBase::Init()
{
	m_aliveFlg = true;
	HitDetection = 64;
}

void EnemyBase::Update()
{
	PlayerTrackingMove();
}

void EnemyBase::Draw2D()
{

	if (m_aliveFlg)
	{
		m_rec = { 64,64 };
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
	}


}

void EnemyBase::Release()
{
}

void EnemyBase::PlayerTrackingMove()
{

	float moveX = m_plaeyrPos.x - m_pos.x;
	float moveY = m_plaeyrPos.y - m_pos.y;
	float rad = atan2(moveY, moveX);
	float deg = DirectX::XMConvertToDegrees(rad);

	if (deg < 0)
	{
		deg += 360;
	}

	m_move.x = cos(DirectX::XMConvertToRadians(deg)) * m_speed.x;
	m_move.y = sin(DirectX::XMConvertToRadians(deg)) * m_speed.y;

	m_pos += m_move;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}
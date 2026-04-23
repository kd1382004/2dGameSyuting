#include"EnemyBase.h"

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	Move();
}

void EnemyBase::Draw2D()
{

	m_rec = { 64,64 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
}

void EnemyBase::Release()
{
}

void EnemyBase::Move()
{




	m_pos += {1, 1};
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}
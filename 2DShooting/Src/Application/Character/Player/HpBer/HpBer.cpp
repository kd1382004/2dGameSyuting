#include"HpBer.h"

PlayerHpBer::PlayerHpBer()
{

}

PlayerHpBer::~PlayerHpBer()
{
	m_tex.Release();
}

void PlayerHpBer::Init()
{
	m_tex.Load("Tex/Character/Player/HPBar/HPBer.png");
}

void PlayerHpBer::Update()
{

}

void PlayerHpBer::Drow2D()
{
	SHADER.m_spriteShader.SetMatrix(m_HPMaxMat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_HPMaxRec);

	SHADER.m_spriteShader.SetMatrix(m_HPNowMat);


	SHADER.m_spriteShader.DrawColorTex(&m_tex, m_HPNowRec, &m_HpBerColor);
}

void PlayerHpBer::SetHPPercent(float Percent)
{

	m_playerPos.y -= 60;

	m_HPMaxRec = { 0,0,96,32 };
	m_HPNowRec = { 96,0,int(96 * Percent),32 };

	m_HPMaxPos = m_playerPos;
	m_HPNowPos = m_playerPos;

	m_HPNowPos.x -= (96 - (96 * Percent)) / 2;

	if (Percent * 100 < 50)
	{
		m_alpha += m_alphaPus;
		if (m_alpha > 1)
		{
			m_alpha = 1;
			m_alphaPus *= -1;
		}
		else if (m_alpha < 0.3)
		{
			m_alpha = 0.3;
			m_alphaPus *= -1;
		}

		m_HpBerColor = { 1,0,0, m_alpha };
	}
	else if (Percent * 100 < 70)
	{
		m_alpha = 1.0f;
		m_HpBerColor = { 1,0,0, m_alpha };
	}
	else
	{
		m_alpha = 1.0f;
		m_HpBerColor = { 0,1,0, m_alpha };
	}



}

void PlayerHpBer::MatConfirmed(float scllor)
{
	m_HPMaxMat = Math::Matrix::CreateTranslation(m_HPMaxPos.x - scllor, m_HPMaxPos.y, 0);
	m_HPNowMat = Math::Matrix::CreateTranslation(m_HPNowPos.x - scllor, m_HPNowPos.y, 0);
}

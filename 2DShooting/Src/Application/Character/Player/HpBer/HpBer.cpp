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


	m_playerRec = { 0,0,100,100 };
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

	SHADER.m_spriteShader.SetMatrix(m_playerMat);
	SHADER.m_spriteShader.DrawTex(m_playerTex, m_playerRec,m_playerAlpha);
}

void PlayerHpBer::SetHPPercent(float Percent)
{

	m_HPMaxRec = { 0,0,192,64 };
	m_HPNowRec = { 192,0,int(192 * Percent),64 };

	m_HPMaxPos = { 500,-280 };
	m_HPNowPos = { 500,-280 };

	m_HPNowPos.x -= (192 - (192 * Percent)) / 2.0f;

	if (Percent * 100 < 30)
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
	else if (Percent * 100 < 50)
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
	m_HPMaxMat = Math::Matrix::CreateTranslation(m_HPMaxPos.x, m_HPMaxPos.y, 0);
	m_HPNowMat = Math::Matrix::CreateTranslation(m_HPNowPos.x, m_HPNowPos.y, 0);
	m_playerMat = Math::Matrix::CreateScale(3, 3, 0) * Math::Matrix::CreateTranslation(m_HPMaxPos.x - 96, m_HPMaxPos.y, 0);
}

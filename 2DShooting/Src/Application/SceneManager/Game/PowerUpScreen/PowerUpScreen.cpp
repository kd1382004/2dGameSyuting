#include "PowerUpScreen.h"
#include"PowerUp3WShot/PowerUp3WShot.h"
#include"PowerupRLShot/PowerupRLShot.h"
#include"PowerupBound/PowerupBound.h"
#include"PowerupPeneShot/PowerupPeneShot.h"
#include"../../../Info/InfoKey/InfoKey.h"


PowerUpScreen::PowerUpScreen()
{
	m_backTex.Load("Tex/PowerUpScreen/PowerUpScreen.png");
	m_selectTex.Load("Tex/PowerUpScreen/Select.png");
	m_backMat = Math::Matrix::CreateTranslation(0, 0, 0);
	for (int i = 0; i < m_powerUpMax; i++)
	{
		m_powerUpPos[i] = { -340 + i * 225.0f ,90 };
	}

	m_selectPos = m_powerUpPos[0];
	m_selectSiz = 1.2;
}

void PowerUpScreen::Init()
{
	std::shared_ptr<Powerup3WShot> p3WS;
	p3WS = std::make_shared<Powerup3WShot>();
	m_powerUPSlect.push_back(p3WS);


	std::shared_ptr<PowerupRLShot> pRLS;
	pRLS = std::make_shared<PowerupRLShot>();
	m_powerUPSlect.push_back(pRLS);


	std::shared_ptr<PowerupBound> pBou;
	pBou = std::make_shared<PowerupBound>();
	m_powerUPSlect.push_back(pBou);


	std::shared_ptr<PowerupPeneShot> pPenS;
	pPenS = std::make_shared<PowerupPeneShot>();
	m_powerUPSlect.push_back(pPenS);


	for (int i = 0; i < m_powerUpMax; i++)
	{
		int num;

		std::random_device rand_dev{};
		std::mt19937 rand_engine(rand_dev());
		int siz = m_powerUPSlect.size();
		siz -= 1;
		std::uniform_int_distribution<int> dist(0, siz);
		num = dist(rand_engine);

		m_powerUp[i] = m_powerUPSlect[num];
		m_powerUp[i]->Init(m_powerUpPos[i]);

		m_powerUPSlect.erase(m_powerUPSlect.begin() + num);;
	}
}

void PowerUpScreen::Update(CharacterInfo* playerInfo)
{
	if (InfoKeyAPP.KeyPush('A', true) || InfoKeyAPP.KeyPush(VK_LEFT, true))
	{
		m_selectNum--;
		if (m_selectNum <= 0)
		{
			m_selectNum = 0;
		}
	}


	if (InfoKeyAPP.KeyPush('D', true) || InfoKeyAPP.KeyPush(VK_RIGHT, true))
	{
		m_selectNum++;
		if (m_selectNum >= m_powerUpMax)
		{
			m_selectNum = m_powerUpMax - 1;
		}
	}

	for (int i = 0; i < m_powerUpMax; i++)
	{
		if (i == m_selectNum)
		{
			m_selectPos = m_powerUpPos[m_selectNum];
			m_powerUp[i]->SetSelectSiz(m_selectSiz);

			if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
			{
				if (!m_powerUp[i]->GetSelectFlg())
				{
					m_powerUp[i]->Update(playerInfo);
					m_powerUp[i]->SetSelectFlg(true);
				}

			}
		}
		else
		{
			m_powerUp[i]->SetSelectSiz(1);
		}
	}
	m_selectMat = Math::Matrix::CreateScale(m_selectSiz, m_selectSiz, 0) * Math::Matrix::CreateTranslation(m_selectPos.x, m_selectPos.y, 0);
}

void PowerUpScreen::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_backMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle{ 0,0,900,500 });

	SHADER.m_spriteShader.SetMatrix(m_selectMat);
	SHADER.m_spriteShader.DrawTex(&m_selectTex, Math::Rectangle{ 0,0,156,221 });

	for (int i = 0; i < m_powerUpMax; i++)
	{
		if (m_powerUp[i])
		{
			m_powerUp[i]->Draw2D();
		}
	}

	m_powerUp[m_selectNum]->DrawEX();
}

void PowerUpScreen::Release()
{
	m_selectTex.Release();
	m_backTex.Release();
}

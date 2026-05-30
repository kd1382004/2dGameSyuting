#include "PowerUpScreen.h"
#include"PowerUp3WShot/PowerUp3WShot.h"
#include"PowerupRLShot/PowerupRLShot.h"
#include"PowerupBound/PowerupBound.h"
#include"PowerupPeneShot/PowerupPeneShot.h"
#include"HPHeel/HPHeel.h"
#include"ATKUP/ATKUP.h"
#include"PlayerHeel/PlayerHeel.h"
#include"PowerupFireArrow/PowerupFireArrow.h"
#include"PowerUPScore/PowerUPScore.h"

#include"../../../Character/Info/CharacterInfoBace.h"
#include"../../../Info/InfoKey/InfoKey.h"
#include"../Game.h"

#include"../../../Sound/Button/ButtonSelectionSE.h"
#include"../../../Sound/Game/PowerUp/PowerUpSE.h"

PowerUpScreen::PowerUpScreen()
{
	//‰¹
	m_buttonSelectionSE = new ButtonSelectionSE();
	m_powerUpSE = new PowerUpSE();

	m_backTex.Load("Tex/PowerUpScreen/PowerUpScreen.png");
	m_selectTex.Load("Tex/PowerUpScreen/Select.png");
	m_backMat = Math::Matrix::CreateTranslation(0, 0, 0);
	for (int i = 0; i < m_powerUpMax; i++)
	{
		m_powerUpPos[i] = { -340 + i * 225.0f ,90 };
	}

	m_selectPos = m_powerUpPos[0];
	m_selectSiz = 1.2f;
}

void PowerUpScreen::Init(CharacterInfo* playerInfo, Game* game)
{

	if (m_powerUPSlect.size() > 0)
	{
		m_powerUPSlect.clear();

	}



	if (!playerInfo->Get3WShotFlg())
	{
		std::shared_ptr<Powerup3WShot> p3WS;
		p3WS = std::make_shared<Powerup3WShot>();
		m_powerUPSlect.push_back(p3WS);
	}



	if (!playerInfo->GetLRShotFlg())
	{
		std::shared_ptr<PowerupRLShot> pRLS;
		pRLS = std::make_shared<PowerupRLShot>();
		m_powerUPSlect.push_back(pRLS);
	}


	std::shared_ptr<PowerupBound> pBou;
	pBou = std::make_shared<PowerupBound>();
	m_powerUPSlect.push_back(pBou);


	std::shared_ptr<PowerupPeneShot> pPenS;
	pPenS = std::make_shared<PowerupPeneShot>();
	m_powerUPSlect.push_back(pPenS);

	std::shared_ptr<HPHeel> pHPH;
	pHPH = std::make_shared<HPHeel>();
	m_powerUPSlect.push_back(pHPH);

	std::shared_ptr<ATKUP> pATKUP;
	pATKUP = std::make_shared<ATKUP>();
	m_powerUPSlect.push_back(pATKUP);


	std::shared_ptr<PlayerHeel> pPHH;
	pPHH = std::make_shared<PlayerHeel>();
	m_powerUPSlect.push_back(pPHH);

	std::shared_ptr<PowerupFireArrow> pPFireA;
	pPFireA = std::make_shared<PowerupFireArrow>();
	m_powerUPSlect.push_back(pPFireA);

	for (int i = 0; i < m_powerUpMax - 1; i++)
	{
		int num;

		std::random_device rand_dev{};
		std::mt19937 rand_engine(rand_dev());
		int siz = m_powerUPSlect.size();
		siz -= 1;
		std::uniform_int_distribution<int> dist(0, siz);
		num = dist(rand_engine);

		m_powerUp[i] = m_powerUPSlect[num];
		m_powerUp[i]->Init(m_powerUpPos[i], playerInfo, game->GetPlayer());

		m_powerUPSlect.erase(m_powerUPSlect.begin() + num);
	}


	std::shared_ptr<PowerUPScore> pPSC;
	pPSC = std::make_shared<PowerUPScore>();
	m_powerUp[m_powerUpMax - 1] = pPSC;
	m_powerUp[m_powerUpMax - 1]->Init(m_powerUpPos[m_powerUpMax - 1], playerInfo, game->GetPlayer());
}

void PowerUpScreen::Update(CharacterInfo* playerInfo, Game* game)
{
	if (InfoKeyAPP.KeyPush('A', true) || InfoKeyAPP.KeyPush(VK_LEFT, true))
	{
		m_selectNum--;
		if (m_selectNum <= 0)
		{
			m_selectNum = 0;
		}
		m_buttonSelectionSE->Stop();
		m_buttonSelectionSE->Play();
	}


	if (InfoKeyAPP.KeyPush('D', true) || InfoKeyAPP.KeyPush(VK_RIGHT, true))
	{
		m_selectNum++;
		if (m_selectNum >= m_powerUpMax)
		{
			m_selectNum = m_powerUpMax - 1;
		}
		m_buttonSelectionSE->Stop();
		m_buttonSelectionSE->Play();
	}

	for (int i = 0; i < m_powerUpMax; i++)
	{
		if (i == m_selectNum)
		{
			if (m_powerUp[i])
			{
				m_selectPos = m_powerUpPos[m_selectNum];
				m_powerUp[i]->SetSelectSiz(m_selectSiz);

				if (InfoKeyAPP.KeyPush(VK_SPACE, true, true))
				{
					if (!m_powerUp[i]->GetSelectFlg())
					{
						m_powerUp[i]->Update(playerInfo);
						m_powerUp[i]->Update(game->GetPlayer());
						m_powerUp[i]->SetSelectFlg(true);
						game->PowerUpScreenFlg();
						m_powerUpSE->Play();
					}

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
	delete m_buttonSelectionSE;
	delete m_powerUpSE;
}

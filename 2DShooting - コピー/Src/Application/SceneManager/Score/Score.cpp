#include "Score.h"
#include "../SceneManager.h"
#include"../../Button/TitleButton/TitleButton.h"
#include"../../Info/InfoKey/InfoKey.h"

void Score::Init()
{
	////////////////
	//ボタン
	m_slect = 0;
	std::shared_ptr<TitleButton> titleButton;
	titleButton = std::make_shared<TitleButton>();
	titleButton->SetOwner(m_owner);
	titleButton->Init(Math::Vector2{ 0,-300 });
	titleButton->SetDefaultSiz(3);
	titleButton->SetSelectSiz(1.5);
	m_button.push_back(titleButton);
}

void Score::Update()
{
	//////////////////////////
	//ボタン
	if (InfoKeyAPP.KeyPush(VK_LEFT, true))
	{
		m_slect--;

		if (m_slect < 0)
		{
			m_slect = 0;
		}
	}

	if (InfoKeyAPP.KeyPush(VK_RIGHT, true))
	{
		m_slect++;

		if (m_slect >= m_button.size())
		{
			m_slect = m_button.size() - 1;
		}
	}


	for (int i = 0; i < m_button.size(); i++)
	{
		if (m_button[i])
		{
			if (i == m_slect)
			{
				m_button[i]->SetSelectFlg(true);
				if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
				{
					m_button[i]->Update();
				}
			}
			else
			{
				m_button[i]->SetSelectFlg(false);
			}
		}
	}
}

void Score::Draw2D()
{
	//ボタン
	for (int i = 0; i < m_button.size(); i++)
	{
		if (m_button[i])
		{
			m_button[i]->Draw2D();
		}
	}
}

void Score::Release()
{
}

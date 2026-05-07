#include "TitleButton.h"
#include"../../SceneManager/SceneManager.h"

void TitleButton::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/Button/TitleButton.png");
	m_pos = pos;
	SetSelectFlg(false);
}

void TitleButton::Update()
{
	if (m_owner)
	{
		m_owner->SetNextSceneType(SceneType::TITLE);
	}
}

void TitleButton::Release()
{
	m_tex.Release();
}

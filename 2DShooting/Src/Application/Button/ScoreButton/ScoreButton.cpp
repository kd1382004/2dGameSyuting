#include "ScoreButton.h"
#include"../../SceneManager/SceneManager.h"

void ScoreButton::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/Button/ScoreButton.png");
	m_pos = pos;
	SetSelectFlg(false);
}

void ScoreButton::Update()
{
	if (m_owner)
	{
		m_owner->SetNextSceneType(SceneType::SCORE);
		SoundPlay();
	}
}

void ScoreButton::Release()
{
	m_tex.Release();
}

#include "PlayButton.h"
#include"../../SceneManager/SceneManager.h"

void PlayButton::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/Button/PlayButton.png");
	m_pos = pos;
	SetSelectFlg(false);
}

void PlayButton::Update()
{
	if (m_owner)
	{
		m_owner->SetNextSceneType(SceneType::GAME);
		SoundPlay();
	}
}

void PlayButton::Release()
{
	m_tex.Release();
}

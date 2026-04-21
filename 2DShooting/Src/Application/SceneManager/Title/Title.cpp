#include "Title.h"
#include "Application/SceneManager/SceneManager.h"


void Title::Init()
{
}

void Title::Update()
{
	//シーン切り替え
	if (GetAsyncKeyState('G') & 0x8000)
	{
		m_owner->ChangeScene(GAME);
	}
}

void Title::Draw2D()
{
	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "タイトル Gで変更", Math::Vector4(1, 1, 0, 1));
}

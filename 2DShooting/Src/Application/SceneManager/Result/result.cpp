#include "result.h"
#include "Application/SceneManager/SceneManager.h"

void Result::Init()
{
}

void Result::Update()
{



	//シーン切り替え
	if (GetAsyncKeyState('T') & 0x8000)
	{
		m_owner->ChangeScene(TITLE);
	}
}

void Result::Draw2D()
{
	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "リザルト Tで変更", Math::Vector4(1, 1, 0, 1));
}

void Result::Release()
{
}

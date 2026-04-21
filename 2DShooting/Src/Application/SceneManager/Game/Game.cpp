#include "Game.h"
#include "Application/SceneManager/SceneManager.h"

void Game::Init()
{

}

void Game::Update()
{
	
	
	
	
	
	//シーン切り替え
	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_owner->ChangeScene(RESULT);
	}
}

void Game::Draw2D()
{
	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "ゲーム Rで変更", Math::Vector4(1, 1, 0, 1));
}
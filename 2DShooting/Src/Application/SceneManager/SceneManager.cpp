#include "SceneManager.h"
#include"Title/Title.h"
#include"Game/Game.h"
#include"Result/result.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	if (m_nowScene != nullptr)
	{
		delete m_nowScene;
		m_nowScene = nullptr;
	}
}

void SceneManager::Init()
{
	ChangeScene(TITLE);	
}

void SceneManager::Draw2D()
{
	//////////////////
	//各シーンの描画//
	//////////////////
	if (m_nowScene)
	{
		m_nowScene->Draw2D();
	}

}

void SceneManager::Update()
{
	//////////////////
	//各シーンの更新//
	//////////////////
	if (m_nowScene)
	{
		m_nowScene->Update();
	}
}

void SceneManager::ChangeScene(SceneType type)
{

	if (m_nowScene != nullptr)
	{
		delete m_nowScene;
		m_nowScene = nullptr;
	}


	if (m_nowScene == nullptr)
	{
		//引数で指定されたシーンをセットする
		switch (type)
		{
		case TITLE:
			m_nowScene = new Title();
			break;
		case GAME:
			m_nowScene = new Game();
			break;
		case RESULT:
			m_nowScene = new Result();
			break;
		}

		m_nowScene->SetOwner(this);
		m_nowScene->Init();
	}
}
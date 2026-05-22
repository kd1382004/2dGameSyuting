#include "SceneManager.h"
#include"Title/Title.h"
#include"Game/Game.h"
#include"Result/result.h"
#include"Score/Score.h"
#include"../Map/Map.h"
#include"../Sound/Titel/TitelBGM.h"

SceneManager::~SceneManager()
{
	if (m_nowScene != nullptr)
	{
		delete m_nowScene;
		m_nowScene = nullptr;
	}


	m_titleBgm->Stop();
	delete m_titleBgm;
}

void SceneManager::Init()
{
	MAPAPP.Init(0);
	ChangeScene(TITLE);	

	//音
	m_titleBgm = new TitelBGM();
	m_titleBgm->Play();
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
	//シーン切り替え//
	//////////////////
	if (m_nowSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}



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

			if (m_nowSceneType == RESULT)
			{
				MAPAPP.Init(0);
				m_titleBgm->Play();
			}

			m_nowScene = new Title();
			break;
		case GAME:
			m_titleBgm->Stop();
			if (m_nowSceneType == RESULT)
			{
				MAPAPP.Init(0);
			}

			m_nowScene = new Game();
			break;
		case RESULT:
			m_nowScene = new Result();
			break;
		case SCORE:			
			m_nowScene = new Score();
			break;
		}

		m_nowScene->SetOwner(this);
		m_nowScene->Init();

		m_nowSceneType = type;
	}
}
#include "SceneManager.h"
#include"Application/SceneManager/Title/Title.h"
#include"Application/SceneManager/Game/Game.h"
#include"Application/SceneManager/Result/result.h"

#include"Application/SceneManager/SceneBase.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{

	if (m_title)
	{
		delete m_title;
	}

	if (m_game)
	{
		delete m_game;
	}

	if (m_result)
	{
		delete m_result;
	}

}

void SceneManager::Init()
{
	m_title = new Title();
	m_game = new Game();
	m_result = new Result();

	m_title->SetOwner(this);
	m_game->SetOwner(this);
	m_result->SetOwner(this);


	m_nowScene = m_title;
	m_nowScene->Init();
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
	//引数で指定されたシーンをセットする
	switch (type)
	{
	case TITLE:
		m_nowScene = m_title;
		break;
	case GAME:
		m_nowScene = m_game;
		m_nowScene->Init();
		break;
	case RESULT:
		m_nowScene = m_result;
		break;
	}
}
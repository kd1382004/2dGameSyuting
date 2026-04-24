#pragma once

class SceneBase;

//シーンの種類
enum SceneType
{
	TITLE,
	GAME,
	RESULT
};

class SceneManager
{
public:

	~SceneManager();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	void SetNextSceneType(SceneType _nextTepy) { m_nextSceneType = _nextTepy; }
private:

	//シーン切り替え関数
	//引数...TITLE GAME RESULT
	void ChangeScene(SceneType type);

	// 初期設定
	void Init();

	SceneType m_nowSceneType = TITLE;
	SceneType m_nextSceneType = m_nowSceneType;

	//現在のシーン
	SceneBase* m_nowScene = nullptr;

private:

	SceneManager() { Init(); }

public:
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}
};

//シーンを管理するクラスにアクセスするためのマクロ
#define SManager SceneManager::GetInstance()


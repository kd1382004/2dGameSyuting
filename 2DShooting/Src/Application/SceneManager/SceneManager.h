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

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	//シーン切り替え関数
	//引数...TITLE GAME RESULT
	void ChangeScene(SceneType type);
private:

	//現在のシーン
	SceneBase* m_nowScene = nullptr;

private:

	SceneManager();

public:
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}
};

//シーンを管理するクラスにアクセスするためのマクロ
#define SManager SceneManager::GetInstance()


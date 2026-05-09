#pragma once
#include"../SceneBase.h"

class ButtonBase;

class Score :public SceneBase
{
public:

	Score() {};
	~Score() { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

private:

	// 解放
	void Release()override;


	//ボタン
	std::vector<std::shared_ptr<ButtonBase>> m_button;
	int m_slect;
};

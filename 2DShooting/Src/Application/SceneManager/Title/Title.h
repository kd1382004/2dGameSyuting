#pragma once
#include"../SceneBase.h"

class ButtonBase;
class Map;
class SoundBase;

class Title :public SceneBase
{
public:

	Title() {};
	~Title()override { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

private:

	// 解放
	void Release()override;

	//ゲーム名
	KdTexture m_titleTex;
	Math::Vector2 m_titlePos;
	Math::Matrix m_titleMat;

	//ボタン
	std::vector<std::shared_ptr<ButtonBase>> m_button;
	int m_slect;

	//プレイヤー
	KdTexture m_playerTex;
	Math::Vector2 m_playerPos;
	Math::Matrix m_playerMat;
	bool m_aliveFlg = false;
	float m_playerAnime = 0;

	SoundBase *m_buttonSelectionSE;
};

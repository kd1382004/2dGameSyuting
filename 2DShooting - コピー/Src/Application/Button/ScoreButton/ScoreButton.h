#pragma once
#include"../ButtonBase.h"

class SceneManager;

class ScoreButton :public ButtonBase
{
public:
	ScoreButton() {}
	~ScoreButton()override { Release(); }

	// ‰Šúİ’è
	void Init(Math::Vector2 pos)override;

	// XVˆ—
	void Update()override;

	void SetOwner(SceneManager* manager) { m_owner = manager; }
private:

	SceneManager* m_owner = nullptr;

	void Release()override;
};
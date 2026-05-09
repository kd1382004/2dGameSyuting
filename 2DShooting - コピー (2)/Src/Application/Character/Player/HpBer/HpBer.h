#pragma once

class PlayerHpBer
{
public:
	PlayerHpBer();
	~PlayerHpBer();

	void Init();

	void Update();

	void Drow2D();

	void SetHPPercent(float Percent);

	//プレイヤー座標セッター
	void SetPlayerPos(Math::Vector2 playerPos) { m_playerPos = playerPos; }

	void MatConfirmed(float scllor);
private:

	KdTexture m_tex;

	Math::Vector2 m_HPMaxPos;
	Math::Matrix m_HPMaxMat;
	Math::Rectangle m_HPMaxRec;


	Math::Vector2 m_HPNowPos;
	Math::Matrix m_HPNowMat;
	Math::Rectangle m_HPNowRec;

	//最大HPに対する現在HPの割合
	float m_HPPercent;

	//プレイヤー座標
	Math::Vector2 m_playerPos;

	//HPBer
	Math::Color m_HpBerColor = { 0,1,0,1 };
	float m_alpha = 1.0f;
	float m_alphaPus = 0.05f;
};



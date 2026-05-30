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

	void MatConfirmed(float scllor);
private:

	KdTexture m_tex;

	Math::Vector2 m_HPMaxPos;
	Math::Matrix m_HPMaxMat;
	Math::Rectangle m_HPMaxRec;


	Math::Vector2 m_HPNowPos;
	Math::Matrix m_HPNowMat;
	Math::Rectangle m_HPNowRec;

	//ç≈ëÂHPÇ…ëŒÇ∑ÇÈåªç›HPÇÃäÑçá
	float m_HPPercent;

	//HPBer
	Math::Color m_HpBerColor = { 0,1,0,1 };
	float m_alpha = 1.0f;
	float m_alphaPus = 0.05f;


	float m_playerAlpha = 1.0f;
	Math::Matrix m_playerMat;
	Math::Rectangle  m_playerRec;
	KdTexture* m_playerTex;
};



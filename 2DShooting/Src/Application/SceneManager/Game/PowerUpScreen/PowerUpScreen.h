#pragma once

class PowerUpBase;

class PowerUpScreen
{
public:
	PowerUpScreen();
	~PowerUpScreen() { Release(); }

	void Init();
	void Update();
	void Draw2D();

private:
	void Release();

	KdTexture m_backTex;
	Math::Matrix m_backMat;

	std::vector<std::shared_ptr<PowerUpBase>> m_powerUPSlect;

	static const int m_powerUpMax = 4;
	std::shared_ptr<PowerUpBase> m_powerUp[m_powerUpMax];
	Math::Vector2 m_powerUpPos[m_powerUpMax];

	KdTexture m_selectTex;
	Math::Vector2 m_selectPos;
	float m_selectSiz = 1.2;
	Math::Matrix m_selectMat;

	int m_selectNum = 0;
};

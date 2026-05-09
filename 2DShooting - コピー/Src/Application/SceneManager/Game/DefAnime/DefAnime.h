#pragma once

class Game;

class DefAnime
{
public:
	DefAnime() {}
	~DefAnime() { Release(); }

	void Init();
	void Update(Game*m_owner);
	void Draw2D();

private:

	KdTexture m_playerTex;
	Math::Matrix m_pkayerTexMat;
	Math::Rectangle m_playerTexRec;
	float m_PlayerDefAnime = 0;
	const int m_PlayerDefAnimeMax = 3;


	bool m_nextStageFlg = false;


	KdTexture m_backTex;
	Math::Matrix m_backTexMat;

	void Release();
};

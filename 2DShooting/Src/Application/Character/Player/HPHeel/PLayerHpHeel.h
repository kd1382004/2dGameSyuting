#pragma once

class Player;
class  SoundBase;

class Playerheel
{
public:
	Playerheel() {};
	~Playerheel() {
		m_tex.Release(); delete m_hpheel;
	};


	void Init(Math::Vector2 pos);
	void Update(Player*player);
	void Drow2D();

	void MatConfirmed(float scroll);

	bool GetDeleteFlg() { return m_deleteFlg; }
private:

	KdTexture m_tex;

	Math::Vector2 m_pos;
	
	Math::Matrix m_mat;

	Math::Vector2 m_move;

	float m_speed;

	bool m_deleteFlg = false;

	SoundBase *m_hpheel;
};


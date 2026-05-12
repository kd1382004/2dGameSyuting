#pragma once
class CharacterInfo;
class Player;

class PowerUpBase
{
public:
	PowerUpBase() {};
	virtual ~PowerUpBase() { Release(); };

	//表示場所をセット
	virtual void Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player) {};
	virtual void Update(CharacterInfo* playerInfo) {};
	virtual void Update(Player* player) {};
	virtual void Draw2D() {};


	virtual void DrawEX() {};


	bool GetSelectFlg() { return m_selectFlg; }
	void SetSelectFlg(bool flg) { m_selectFlg = flg; }


	void SetSelectSiz(float siz);

	void DrawEXBack();

protected:

	virtual void Release() { m_EXBackTex.Release(); };

	Math::Vector2 m_pos = {};
	Math::Rectangle m_rec = { 0,0,150,221 };
	KdTexture m_tex;
	Math::Matrix m_mat;
	bool m_selectFlg = false;
	float m_siz = 1;

	KdTexture m_EXBackTex;
	Math::Vector2 m_EXBackPos = { -3,-115 };
	Math::Rectangle m_EXBackRec = { 0,0,900,100 };
	Math::Matrix m_EXBackMat;

	bool m_LVMax = false;
};

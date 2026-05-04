#pragma once

class PowerUpBase
{
public:
	PowerUpBase() {};
	virtual ~PowerUpBase() { Release(); };

	//表示場所をセット
	virtual void Init(Math::Vector2 pos) {};
	virtual void Update() {};
	virtual void Draw2D() {};


	virtual void DrawEX() {};


	bool GetSelectFlg() { return m_selectFlg; }
	void SetSelectFlg(bool flg) { m_selectFlg = flg; }


	void SetSelectSiz(float siz);
protected:

	virtual void Release() {};

	Math::Vector2 m_pos = {};
	Math::Rectangle m_rec = { 0,0,150,221 };
	Math::Rectangle m_iconRec = { 0,0,32,32 };
	KdTexture m_tex;
	KdTexture m_iconTex;
	Math::Matrix m_mat;
	Math::Matrix m_iconMat;
	bool m_selectFlg = false;
	float m_siz = 1;

};

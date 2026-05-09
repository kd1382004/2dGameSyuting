#pragma once

class Game;

class MapObject
{
public:
	MapObject() {};
	virtual ~MapObject() { Release(); };


	//オブジェクトの情報を入れる
	//pos...座標
	virtual void Init(Math::Vector2 pos);
	virtual void Updata(float scroll);
	virtual void Draw2D();

	void SetTex(KdTexture* tex) { m_tex = tex; }

	void SetOwner(Game* owner) { m_owner = owner; }
protected:
	Game* m_owner;

	KdTexture* m_tex;

	//座標
	Math::Vector2 m_pos;

	//切り取り範囲
	Math::Rectangle m_rec;

	//円用当たり判定(直径)
	float HitDetection;

	//行列
	Math::Matrix m_mat;

	virtual void Release();

	float m_animeMax = 0;
	float m_animeC = 0;

};
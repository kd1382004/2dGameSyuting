#pragma once

class MapObject
{
public:
	MapObject() {};
	virtual ~MapObject() { Release(); };


	//オブジェクトの情報を入れる
	//pos...座標
	//rec...切り取り範囲
	virtual void Init(Math::Vector2 pos, Math::Rectangle rec);
	virtual void Updata();
	virtual void Draw2D();

	void SetTex(KdTexture* tex) { m_tex = tex; }

protected:

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

	int m_animeMax = 0;
};
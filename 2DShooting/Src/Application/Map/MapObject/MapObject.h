#pragma once

class MapObject
{
public:
	MapObject() {};
	~MapObject() { Release(); };


	//オブジェクトの情報を入れる
	//pos...座標
	//rec...切り取り範囲
	void Init(Math::Vector2 pos, Math::Rectangle rec);


	void Updata();
	void Draw2D();

	void SetTex(KdTexture* tex) { m_tex = tex; }

private:

	KdTexture* m_tex;

	//座標
	Math::Vector2 m_pos;

	//切り取り範囲
	Math::Rectangle m_rec;

	//円用当たり判定(直径)
	float HitDetection;

	//行列
	Math::Matrix m_mat;

	void Release();
};
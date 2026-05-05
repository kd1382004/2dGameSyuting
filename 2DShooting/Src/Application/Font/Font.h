#pragma once

class Font
{
public:

	~Font();


	void Drow2DString(float _x, float _y, const char _text[], const Math::Vector4& _color = { 1,1,1,1 }, const float siz = 1);
private:
	void Init();

	Math::Rectangle Rec(char M);

	KdTexture m_tex;
private:

	Font() { Init(); }

public:
	static Font& GetInstance()
	{
		static Font instance;
		return instance;
	}
};

#define FontChar Font::GetInstance()
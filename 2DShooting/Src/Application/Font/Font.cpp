#include "Font.h"

Font::~Font()
{
	m_tex.Release();
}

//AÅ`Z
void Font::Drow2DString(float _x, float _y, const char _text[], const Math::Vector4& _color, const float siz)
{
	int Num = strlen(_text);

	float x = _x;
	float y = _y;

	int cnt = 0;
	for (int i = 0; i < Num; i++)
	{
		if (_text[i] == '\n')
		{
			cnt++;
			y += 8 * cnt;
			continue;
		}

		x += 8 * i;

		Math::Rectangle rec = Rec(_text[i]);

		Math::Matrix TMat = Math::Matrix::CreateTranslation(x, y, 0);
		Math::Matrix SMat = Math::Matrix::CreateScale(siz, siz, 0);
		Math::Matrix Mat = SMat * TMat;

		SHADER.m_spriteShader.SetMatrix(Mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, rec);
	}
}

void Font::Init()
{
	m_tex.Load("Tex/Font/pixel-letters-7-8x14-preview.png");
}


Math::Rectangle Font::Rec(char M)
{

	int num = M - 'A';
	Math::Rectangle rec;

	rec = { num + num * 8 ,0,8,16};

	return rec;
}

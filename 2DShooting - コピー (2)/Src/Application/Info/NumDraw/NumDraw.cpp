#include "NumDraw.h"

void NumDraw::Drow(long Num, Aligned aligned, Math::Vector2 pos, Math::Color* color, float siz, bool Separator, float scroll)
{
	//êîéöíºåaâ°
	recX = 9;
	//êîéöíºåaèc
	recY = 14;

	//10à»è„Ç»ÇÁåÖêîÇãÅÇﬂÇÈ
	if (Num >= 10)
	{
		//åÖêîÇì¸ÇÍÇÈÉèÅ[ÉNspace
		long w = 0;

		//åÖêîÇãÅÇﬂÇÈ
		for (long long i = 1; i <= Num; i *= 10)
		{
			w++;
		}

		//ï™âÇµÇΩàÍåÖÇ™ì¸ÇÈ
		std::vector<int>w_Num;

		for (int i = 0; i < w; i++)
		{
			int a = 1;

			for (int j = i; j < w - 1; j++)
			{
				a *= 10;
			}

			w_Num.push_back(Num / a);
			Num %= a;
		}

		//ÉXÉ^Å[Égà íuÇ™Ç«Ç¡ÇøÇ©ÇëIï 
		switch (aligned)
		{
		case LAligned:
			break;
		case RAligned:
			std::reverse(w_Num.begin(), w_Num.end());
			break;
		default:
			break;
		}


		for (int i = 0; i < w_Num.size(); i++)
		{
			//êîéöíºåaèc
			Math::Matrix mat;
			Math::Matrix Smat = Math::Matrix::CreateScale(siz, siz, 0);
			Math::Matrix Tmat;

			Math::Rectangle rec1 = { 1 + recX * w_Num[i],0,recX ,recY };
			switch (aligned)
			{
			case LAligned:

				Tmat = Math::Matrix::CreateTranslation(pos.x + i * (recX * siz) - ((recX * siz) / 2 * i) + (i * 5 * siz) - scroll, pos.y, 0);
				mat = Smat * Tmat;



				SHADER.m_spriteShader.SetMatrix(mat);
				SHADER.m_spriteShader.DrawColorTex(&m_tex, rec1, color);
				if (Separator)
				{
					if ((w_Num.size() - i) % 3 == 1 && w_Num.size() - i >= 4)
					{
						rec1 = Math::Rectangle{ 1 + recX * 10,0,recX ,recY };
						pos.x += recX * siz / 2;
						Tmat = Math::Matrix::CreateTranslation(Tmat.Translation().x + (siz * recX) + (siz * 2), pos.y, 0);
						mat = Smat * Tmat;
						SHADER.m_spriteShader.SetMatrix(mat);
						SHADER.m_spriteShader.DrawColorTex(&m_tex, rec1, color);
					}
				}

				break;
			case RAligned:

				Tmat = Math::Matrix::CreateTranslation(pos.x - i * (recX * siz) + ((recX * siz) / 2 * i) - (i * 5 * siz) - scroll, pos.y, 0);

				if (Separator)
				{
					if (i % 3 == 0 && i != 0)
					{
						float x = Tmat.Translation().x + recX * siz / 2;
						Tmat = Math::Matrix::CreateTranslation(x, pos.y, 0);
						mat = Smat * Tmat;
						rec1 = Math::Rectangle{ 1 + recX * 10,0,recX ,recY };
						SHADER.m_spriteShader.SetMatrix(mat);
						SHADER.m_spriteShader.DrawColorTex(&m_tex, rec1, color);
						pos.x -= (recX * siz) / 2;
					}
				}

				Tmat = Math::Matrix::CreateTranslation(pos.x - i * (recX * siz) + ((recX * siz) / 2 * i) - (i * 5 * siz) - scroll, pos.y, 0);

				mat = Smat * Tmat;
				rec1 = { 1 + recX * w_Num[i],0,recX ,recY };
				SHADER.m_spriteShader.SetMatrix(mat);
				SHADER.m_spriteShader.DrawColorTex(&m_tex, rec1, color);
				break;
			default:
				break;
			}
		}
	}
	else
	{

		Math::Matrix Smat = Math::Matrix::CreateScale(siz, siz, 0);
		Math::Matrix Tmat;
		Tmat = Math::Matrix::CreateTranslation(pos.x - scroll, pos.y, 0);
		Math::Matrix mat = Smat * Tmat;

		SHADER.m_spriteShader.SetMatrix(mat);
		SHADER.m_spriteShader.DrawColorTex(&m_tex, Math::Rectangle{ recX * Num ,0,recX ,recY }, color);
	}
}

void NumDraw::Init()
{
	m_tex.Load("Tex/Num/pixel-letters-7-8x14_transparent.png");
}

void NumDraw::Release()
{
	m_tex.Release();
}
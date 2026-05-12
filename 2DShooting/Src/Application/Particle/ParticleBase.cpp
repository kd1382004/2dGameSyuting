#include "ParticleBase.h"

void Praticle::Emit(Math::Vector2 pos, Math::Vector2 move, float size, Math::Color color, int lifespan, bool RepeatFlg, int i,int deg)
{

	m_deg = deg;

	if (i < 0)
	{
		for (int i = 0; i < m_maxSiz; i++)
		{

			m_pos[i] = pos;

			m_move[i] = move * m_defSiz;

			m_size[i] = size;

			m_lifespan[i] = lifespan;

			m_color[i] = color;

			m_RepeatFlg = RepeatFlg;

			m_sizeX[i] = Rnd() * size * m_defSiz.x - 2 * m_defSiz.x;
			m_sizeY[i] = Rnd() * size * m_defSiz.y - 3 * m_defSiz.x;
		}
		return;
	}

	if (i >= m_maxSiz || i < 0)
	{
		return;
	}

	m_pos[i] = pos;

	m_move[i] = move * m_defSiz;

	m_size[i] = size;

	m_lifespan[i] = lifespan;

	m_color[i] = color;

	m_RepeatFlg = RepeatFlg;

	m_sizeX[i] = Rnd() * size * m_defSiz.x - 2 * m_defSiz.x;
	m_sizeY[i] = Rnd() * size * m_defSiz.y - 3 * m_defSiz.x;

}

void Praticle::Draw()
{

	//‰ÁŽZ‡¬
	D3D.SetBlendState(BlendMode::Add);

	for (int i = 0; i < m_maxSiz; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		Math::Rectangle srcRect = { 0, 0, 32, 32 };
		SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &srcRect, &m_color[i]);
	}

	//”¼“§–¾
	D3D.SetBlendState(BlendMode::Alpha);
}

float Praticle::Rnd()
{
	float num;

	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	std::uniform_int_distribution<int> dist(0, 100);
	num = dist(rand_engine);
	num *= 0.01;
	return num;
}

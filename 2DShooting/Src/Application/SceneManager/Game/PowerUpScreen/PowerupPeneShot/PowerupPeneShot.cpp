#include "PowerupPeneShot.h"

void PowerupPeneShot::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupPeneShot/PowerupPeneShot.png");
	m_iconTex.Load("Tex/PowerUpScreen/PowerupPeneShot/PowerupPeneShotIcon.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_iconMat = Math::Matrix::CreateTranslation(m_pos.x - 42, m_pos.y + 75, 0);

}

void PowerupPeneShot::Update()
{

}

void PowerupPeneShot::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);

	SHADER.m_spriteShader.SetMatrix(m_iconMat);
	SHADER.m_spriteShader.DrawTex(&m_iconTex, m_iconRec);
}

void PowerupPeneShot::DrawEX()
{
	SHADER.m_spriteShader.DrawString(-350, -100, "’e‚ª•Ç‚È‚Ç‚ð’µ‚Ë•Ô‚é‚æ‚¤‚É", Math::Vector4(0, 0, 0, 1));
}

void PowerupPeneShot::Release()
{
	m_tex.Release();
	m_iconTex.Release();
}

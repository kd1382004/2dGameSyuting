#include "PowerUp3WShot.h"

void Powerup3WShot::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/Powerup3WShot/Powerup3WShot.png");
	m_iconTex.Load("Tex/PowerUpScreen/Powerup3WShot/Powerup3WShotIcon.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_iconMat = Math::Matrix::CreateTranslation(m_pos.x - 42, m_pos.y + 75, 0);

}

void Powerup3WShot::Update()
{

}

void Powerup3WShot::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);

	SHADER.m_spriteShader.SetMatrix(m_iconMat);
	SHADER.m_spriteShader.DrawTex(&m_iconTex, m_iconRec);
}

void Powerup3WShot::DrawEX()
{
	SHADER.m_spriteShader.DrawString(-350, -100, "ŽËŒ‚‚ª‘O•û3•ûŒü‚É•ªŽU‚µ‚Ä”­ŽË‚³‚ê‚é", Math::Vector4(0, 0, 0, 1));
}

void Powerup3WShot::Release()
{
	m_tex.Release();
	m_iconTex.Release();
}

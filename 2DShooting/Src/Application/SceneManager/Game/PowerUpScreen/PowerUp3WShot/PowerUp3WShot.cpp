#include "PowerUp3WShot.h"
#include"../../../../Character/Info/CharacterInfoBace.h"

void Powerup3WShot::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/Powerup3WShot/Powerup3WShot.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/Powerup3WShot/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Powerup3WShot::Update(CharacterInfo* playerInfo)
{
	playerInfo->Set3WShotFlg(true);
}

void Powerup3WShot::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);
}

void Powerup3WShot::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "ŽËŒ‚‚ª‘O•û3•ûŒü‚É•ªŽU‚µ‚Ä”­ŽË‚³‚ê‚é", Math::Vector4(0, 0, 0, 1));
}

void Powerup3WShot::Release()
{
	m_tex.Release();
}

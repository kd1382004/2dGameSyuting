#include"PowerupRLShot.h"
#include"../../../../Character/Info/CharacterInfoBace.h"

void PowerupRLShot::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupRLShot/PowerupRLShot.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PowerupRLShot/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void PowerupRLShot::Update(CharacterInfo* playerInfo)
{
	playerInfo->SetLRShotFlg(true);
}

void PowerupRLShot::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);
}

void PowerupRLShot::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "ç∂âEÇ©ÇÁÇ‡íeÇ™î≠éÀÇ≥ÇÍÇÈ", Math::Vector4(0, 0, 0, 1));
}

void PowerupRLShot::Release()
{
	m_tex.Release();
}
#include "ATKUP.h"

#include"../../../../Character/Info/CharacterInfoBace.h"

void ATKUP::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/ATKUP/ATKUP.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

}

void ATKUP::Update(CharacterInfo* playerInfo)
{
	playerInfo->SetATKLV(1);
}

void ATKUP::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);
}

void ATKUP::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "UŒ‚—Í‚ªˆê’è—Êã¸‚·‚é", Math::Vector4(0, 0, 0, 1));
}

void ATKUP::Release()
{
	m_tex.Release();
}

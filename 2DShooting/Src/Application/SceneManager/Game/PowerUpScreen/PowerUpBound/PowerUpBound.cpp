#include "PowerupBound.h"
#include"../../../../Character/Info/CharacterInfoBace.h"

void PowerupBound::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupBound/PowerupBound.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PowerupBound/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

}

void PowerupBound::Update(CharacterInfo* playerInfo)
{
	playerInfo->SetBoundNum(1);
}

void PowerupBound::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);

}

void PowerupBound::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "’e‚ª•Ç‚È‚Ç‚ð’µ‚Ë•Ô‚é‚æ‚¤‚É", Math::Vector4(0, 0, 0, 1));
}

void PowerupBound::Release()
{
	m_tex.Release();
}

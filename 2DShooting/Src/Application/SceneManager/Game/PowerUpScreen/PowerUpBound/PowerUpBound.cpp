#include "PowerupBound.h"
#include"../../../../Character/Info/CharacterInfoBace.h"

void PowerupBound::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupBound/PowerupBound.png");
	m_iconTex.Load("Tex/PowerUpScreen/PowerupBound/PowerupBoundIcon.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_iconMat = Math::Matrix::CreateTranslation(m_pos.x - 42, m_pos.y + 75, 0);

}

void PowerupBound::Update(CharacterInfo* playerInfo)
{
	playerInfo->SetBoundNum(1);
}

void PowerupBound::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);

	SHADER.m_spriteShader.SetMatrix(m_iconMat);
	SHADER.m_spriteShader.DrawTex(&m_iconTex, m_iconRec);
}

void PowerupBound::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "’e‚ª•Ç‚È‚Ç‚ð’µ‚Ë•Ô‚é‚æ‚¤‚É", Math::Vector4(0, 0, 0, 1));
}

void PowerupBound::Release()
{
	m_tex.Release();
	m_iconTex.Release();
}

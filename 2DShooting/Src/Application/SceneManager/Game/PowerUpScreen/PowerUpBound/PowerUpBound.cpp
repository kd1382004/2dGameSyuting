#include "PowerupBound.h"
#include"../../../../Character/Info/CharacterInfoBace.h"

void PowerupBound::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupBound/PowerupBound.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PowerupBound/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	if (playerInfo->GetBoundNum() >= 99)
	{
		m_LVMax = true;
	}
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
	if (m_LVMax)
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "LvMax ‚±‚êˆÈãŒø‰Ê‚Í‚È‚¢", Math::Vector4(0, 0, 0, 1));
	}
	else
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "’e‚ª•Ç‚È‚Ç‚ğ’µ‚Ë•Ô‚é‚æ‚¤‚É", Math::Vector4(0, 0, 0, 1));
	}
}

void PowerupBound::Release()
{
	m_tex.Release();
}

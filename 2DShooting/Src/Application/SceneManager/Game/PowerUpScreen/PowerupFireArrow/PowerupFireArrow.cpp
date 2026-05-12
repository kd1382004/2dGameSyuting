#include"PowerupFireArrow.h"
#include"../../../../Character/Player/Player.h"

void PowerupFireArrow::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupFireArrow/PowerupFireArrow.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PowerupFireArrow/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);


	if (player->GetFireArrow() >= 99)
	{
		m_LVMax = true;
	}
}

void PowerupFireArrow::Update(Player* player)
{
	player->SetFireArrow(1);
}

void PowerupFireArrow::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);
}

void PowerupFireArrow::DrawEX()
{
	DrawEXBack();
	if (m_LVMax)
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "LvMax ‚±‚êˆÈãŒø‰Ê‚Í‚È‚¢", Math::Vector4(0, 0, 0, 1));
	}
	else
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "‰Š‚Ì–î‚ğŒ‚‚Â‚æ‚¤‚É‚È‚é", Math::Vector4(0, 0, 0, 1));
	}
}



void PowerupFireArrow::Release()
{
	m_tex.Release();
}
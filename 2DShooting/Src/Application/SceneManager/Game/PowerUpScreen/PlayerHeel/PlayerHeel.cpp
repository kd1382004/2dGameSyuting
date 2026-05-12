#include "PlayerHeel.h"
#include"../../../../Character/Player/Player.h"

void PlayerHeel::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/PlayerHeel/PlayerHeel.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PlayerHeel/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	if (player->GetEnemyDehHeelLv() >= 99)
	{
		m_LVMax = true;
	}
}

void PlayerHeel::Update(Player* player)
{
	player->SetEnemyDehHeelLv(1);
}

void PlayerHeel::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);

}

void PlayerHeel::DrawEX()
{
	DrawEXBack();
	if (m_LVMax)
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "LvMax ‚±‚êˆÈãŒø‰Ê‚Í‚È‚¢", Math::Vector4(0, 0, 0, 1));
	}
	else
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "“G‚ğ“|‚·‚ÆHP‚ª‰ñ•œ‚·‚é", Math::Vector4(0, 0, 0, 1));
	}
}



void PlayerHeel::Release()
{
	m_tex.Release();
}


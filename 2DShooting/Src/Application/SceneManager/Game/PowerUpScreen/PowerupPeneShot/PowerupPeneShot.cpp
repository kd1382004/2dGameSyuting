#include "PowerupPeneShot.h"
#include"../../../../Character/Info/CharacterInfoBace.h"

void PowerupPeneShot::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupPeneShot/PowerupPeneShot.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PowerupPeneShot/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	if (playerInfo->GetBuletPeneNum() >= 99)
	{
		m_LVMax = true;
	}
}

void PowerupPeneShot::Update(CharacterInfo* playerInfo)
{
	playerInfo->SetBuletPeneNum(1);
}

void PowerupPeneShot::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);


}

void PowerupPeneShot::DrawEX()
{
	DrawEXBack();

	if (m_LVMax)
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "LvMax Ç±ÇÍà»è„å¯â ÇÕÇ»Ç¢", Math::Vector4(0, 0, 0, 1));
	}
	else
	{
		SHADER.m_spriteShader.DrawString(-350, -100, "íeÇ™ìGÇä—í Ç∑ÇÈÇÊÇ§Ç…", Math::Vector4(0, 0, 0, 1));
	}
}

void PowerupPeneShot::Release()
{
	m_tex.Release();
}

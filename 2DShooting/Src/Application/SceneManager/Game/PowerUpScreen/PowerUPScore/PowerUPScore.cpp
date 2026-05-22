#include"PowerUPScore.h"
#include"../../../../Character/Player/Player.h"

void PowerUPScore::Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)
{
	m_tex.Load("Tex/PowerUpScreen/PowerUPScore/PowerUPScore.png");
	m_EXBackTex.Load("Tex/PowerUpScreen/PowerUPScore/Premade dialog box  big.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void PowerUPScore::Update(Player* player)
{
	player->SetScoreUpLV(1);
}

void PowerUPScore::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);
}

void PowerUPScore::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "手に入れられるスコア量アップ", Math::Vector4(0, 0, 0, 1));
}

void PowerUPScore::Release()
{
	m_tex.Release();
}
#include "PlayerHeel.h"
#include"../../../../Character/Player/Player.h"

void PlayerHeel::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/PlayerHeel/PlayerHeel.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
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
	SHADER.m_spriteShader.DrawString(-350, -100, "“G‚ð“|‚·‚ÆHP‚ª‰ñ•œ‚·‚é", Math::Vector4(0, 0, 0, 1));
}

void PlayerHeel::Release()
{
	m_tex.Release();
}


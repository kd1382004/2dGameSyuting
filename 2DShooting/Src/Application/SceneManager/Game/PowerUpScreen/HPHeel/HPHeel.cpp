#include "HPHeel.h"
#include"../../../../Character/Player/Player.h"

void HPHeel::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/HPHeel/HPHeel.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void HPHeel::Update(Player* player)
{
	int HPheelNum = player->GetMaxHP() * 0.3f;
	player->HPHeel(HPheelNum);

}

void HPHeel::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);


}

void HPHeel::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "ˆê’è—ÊHP‚ð‰ñ•œ‚Å‚«‚é", Math::Vector4(0, 0, 0, 1));
}

void HPHeel::Release()
{
	m_tex.Release();
}


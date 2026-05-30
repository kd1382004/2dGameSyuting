#include"PLayerHpHeel.h"
#include"../Player.h"

#include"../../../Sound/Game/Player/Heel/HeelSE.h"
void Playerheel::Init(Math::Vector2 pos)
{

	m_pos = pos;
	m_tex.Load("Tex/Character/Player/HPHeel/HPheel.png");

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_speed = 7;

	m_hpheel = new HeelSE();
}

void Playerheel::Update(Player *player)
{
	m_move = player->GetPos() - m_pos;
	float lenSq = m_move.x * m_move.x + m_move.y * m_move.y;
	if (lenSq < 0.000001f)
	{
		return;
	}

	m_move.Normalize();
	m_move *= m_speed;
	m_pos += m_move;


	Math::Vector2 c = player->GetPos() - m_pos;

	if (c.Length() < player->GetHitDetection()/2)
	{
		player->HPHeel(player->EnemyDehHeelAmount());
		m_deleteFlg = true;
		m_hpheel->Play();
	}
}

void Playerheel::Drow2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle{ 0,0,10,10 });
}

void Playerheel::MatConfirmed(float scroll)
{
	m_mat = Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
}

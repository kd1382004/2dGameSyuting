#include "Slime.h"
#include"../../Info/CharacterInfoBace.h"
#include"../../../Particle/Fire/Fire.h"

void Slime::Init()
{
	m_aliveFlg = true;
	HitDetection = 64;
	m_pos = {};
	m_HP = 10;
	m_siz = { 2,2 };
	m_info = new CharacterInfo();

	m_info->SetATKLV(0);
	StateTypeChange(StateType::TypeFIRE, 10);
}

void Slime::Update()
{
	if (m_aliveFlg)
	{
		StateTypeManager();
		HPCoolTimeManager();
	
	}

	switch (m_mode)
	{
	case MOVE:

		MODEMove();

		break;
	case ATK:

		MODEATK();

		break;

	case Def:

		MODEDef();

	default:
		break;
	}
}

void Slime::Draw2D()
{
	if (!m_deleteFlg)
	{
		if (!m_aliveFlg)
		{
			m_rec = { 512 / 8 * (int)m_anime,192 / 3 * 2, 512 / 8,192 / 3 };
		}
		else
		{
			m_rec = { 512 / 8 * (int)m_anime,192 / 3 * 1, 512 / 8,192 / 3 };
		}



		for (int i = 0; i < m_praticle.size(); i++)
		{
			m_praticle[i]->Draw();
		}

		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, m_charaAlpha);
	}
}

void Slime::MatConfirmed(float scroll)
{
	for (int i = 0; i < m_praticle.size(); i++)
	{
		m_praticle[i]->Update(m_pos, scroll);
	}

	//行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void Slime::SetStatus(int stage)
{
	int HPUp = 0;
	if (stage != 0)
	{
		HPUp = stage / 3 * 20;
	}


	m_speed += Math::Vector2{ (float)stage * 0.1f, (float)stage * 0.1f };
	m_HP = 30 + HPUp;

	int atkLv = stage * 0.5;
	m_info->SetATKLV(atkLv);
}

void Slime::Release()
{

}

void Slime::PlayerTrackingMove()
{
	m_move = m_plaeyrPos - m_pos;
	float lenSq = m_move.x * m_move.x + m_move.y * m_move.y;
	if (lenSq < 0.000001f)
	{
		return;
	}

	m_move.Normalize();
	m_move *= m_speed;
	float rad = atan2(m_move.y, m_move.x);
	m_deg = DirectX::XMConvertToDegrees(rad);

	if (m_deg < 0)
	{
		m_deg += 360;
	}

	m_pos += m_move;
}

void Slime::MODEMove()
{
	PlayerTrackingMove();

	//アニメーション
	m_anime += 0.3;
	if (m_anime > 8)
	{
		m_anime = 0;
		
	}
}

void Slime::MODEATK()
{
}

void Slime::MODEDef()
{
	//アニメーション
	m_anime += 0.2;
	if (m_anime > 8)
	{
		m_anime = 0;
		m_deleteFlg = true;
	}
}

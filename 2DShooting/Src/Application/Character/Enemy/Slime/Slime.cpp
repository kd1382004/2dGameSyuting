#include "Slime.h"
#include"../../Info/CharacterInfoBace.h"

void Slime::Init()
{
	m_aliveFlg = true;
	HitDetection = 64;
	m_pos = { (float)(rand() % 1280 - 640),(float)(rand() % 720 - 360) };
	m_HP = 100;
	m_siz = { 2,2 };
	m_info = new CharacterInfo();

	m_info->SetATK(10);
}

void Slime::Update()
{
	if (m_aliveFlg)
	{
		PlayerTrackingMove();
	}


	//アニメーション
	m_anime += 0.3;
	if (m_anime > 8)
	{
		m_anime = 0;
		if (!m_aliveFlg)
		{
			m_deleteFlg = true;
		}
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

		
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
	}
}

void Slime::MatConfirmed(float scroll)
{
	//行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x- scroll, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void Slime::Release()
{

}

void Slime::PlayerTrackingMove()
{
	m_move = m_plaeyrPos - m_pos;
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

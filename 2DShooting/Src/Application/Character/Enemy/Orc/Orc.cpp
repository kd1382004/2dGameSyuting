#include "Orc.h"
#include"../../Info/CharacterInfoBace.h"
#include"../../../Particle/Fire/Fire.h"

void Orc::Init()
{
	m_aliveFlg = true;
	HitDetection = 50;
	m_pos = {};
	m_HP = 10;
	m_siz = { 2,2 };
	m_info = new CharacterInfo();

	m_info->SetATKLV(0);

	m_speed = { 0.5f,0.5f };
	m_siz.x *= -1;
	m_rec = { 0,200 ,100,100 };
}

void Orc::Update()
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

void Orc::Draw2D()
{
	if (!m_deleteFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		if (m_charaAlpha != 1)
		{
			SHADER.m_spriteShader.DrawColorTex(m_charaTex, m_rec, &Math::Color{ 1,0,0,m_charaAlpha });
		}
		else
		{
			SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, m_charaAlpha);
		}
	
		if (m_aliveFlg)
		{
			for (int i = 0; i < m_praticle.size(); i++)
			{
				m_praticle[i]->Draw();
			}
		}

	}
}

void Orc::MatConfirmed(float scroll)
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

void Orc::SetStatus(int stage)
{
	int HPUp = 0;
	if (stage != 0)
	{
		HPUp = stage / 2 * 10;
	}

	int num;
	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	int siz = 100 - stage;
	std::uniform_int_distribution<int> dist(60, 60 + siz);
	num = dist(rand_engine);

	m_ATKWaitMax = 1.0f * num;

	m_HP = 10 + HPUp;

	int atkLv = stage * 0.1;
	m_info->SetATKLV(atkLv);
}

void Orc::Release()
{

}

void Orc::PlayerTrackingMove()
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

	if (m_move.x < 0 && m_siz.x>0)
	{
		m_siz.x *= -1;
	}
	else if (m_move.x > 0 && m_siz.x < 0)
	{
		m_siz.x *= -1;
	}

}

void Orc::MODEMove()
{
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

	m_rec = { 100 * (int)m_anime,100 ,100,100 };

	//攻撃
	m_ATKWait += 0.1;

	if (m_ATKWait > m_ATKWaitMax)
	{
		m_ATKWait = 0;
		ChangeMode(ATK);
	}

	PlayerTrackingMove();
}

void Orc::MODEATK()
{
	//アニメーション
	m_anime += 0.1;

	m_rec = { 100 * (int)m_anime,200 ,100,100 };

	if (m_anime > 3 && m_anime < 6)
	{
		m_pos += m_move * 2;
	}

	if (m_anime > 6)
	{
		m_rec = { 100 ,200 ,100,100 };
	}

	if (m_anime > 9)
	{
		ChangeMode(MOVE);
	}

}

void Orc::MODEDef()
{
	//アニメーション
	m_anime += 0.1;

	m_rec = { 100 * (int)m_anime,500 ,100,100 };

	if (m_anime > 4)
	{
		m_deleteFlg = true;
	}
}




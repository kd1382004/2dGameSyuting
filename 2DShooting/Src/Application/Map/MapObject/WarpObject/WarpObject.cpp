#include"WarpObject.h"
#include"../../../SceneManager/Game/Game.h"

void  WarpObject::Init(Math::Vector2 pos)
{
	m_pos = pos;
	m_animeMax = 5;
	m_rec = { 64 * (int)m_animeC,0,64,50 };
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void WarpObject::Updata(float scroll)
{

	if (m_owner != nullptr)
	{
		if (!m_owner->GetStageClearFlg())
		{
			return;
		}

		m_siz -= m_sizPush;

		if (m_siz < 0.5)
		{
			m_siz = 0.5;
			m_sizPush *= -1;
		}

		if (m_siz > 1)
		{
			m_siz = 1;
			m_sizPush *= -1;
		}

		Math::Vector2 v = m_pos - m_owner->GetPlayerPos();
		if (v.Length() < 32)
		{
			m_owner->SetNextStageFlg(true);
		}
	}


	m_mat = Math::Matrix::CreateScale(m_siz, m_siz, 0) * Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);

}

void WarpObject::Draw2D()
{
	if (m_owner)
	{
		if (!m_owner->GetStageClearFlg())
		{
			return;
		}

		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rec);
	}
}

void WarpObject::Release()
{

}

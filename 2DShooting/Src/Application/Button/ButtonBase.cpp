#include "ButtonBase.h"

void ButtonBase::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_tex,m_rec, m_alpha);
}

void ButtonBase::SetSelectFlg(bool flg)
{
	m_selectFlg = flg; 

	if (m_selectFlg)
	{
		m_sMat = Math::Matrix::CreateScale(m_defaultSiz* m_selectSiz, m_defaultSiz * m_selectSiz,0);
		m_rec = { 0,32,96,32 };

		m_alpha += m_alphaPush;
		if (m_alpha > 1)
		{
			m_alphaPush *= -1;
			m_alpha = 1;
		}

		if (m_alpha < 0.3)
		{
			m_alphaPush *= -1;
			m_alpha = 0.3;
		}

	}
	else
	{
		m_sMat = Math::Matrix::CreateScale(m_defaultSiz, m_defaultSiz, 0);
		m_alpha = 1;
	}

	m_tMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	m_Mat = m_sMat * m_tMat;
}

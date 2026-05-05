#include "PowerUpBase.h"

void PowerUpBase::SetSelectSiz(float siz)
{
	m_siz = siz;
	m_mat = Math::Matrix::CreateScale(m_siz, m_siz, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_iconMat = Math::Matrix::CreateScale(m_siz, m_siz, 0) * Math::Matrix::CreateTranslation(m_pos.x - 42, m_pos.y + 75, 0);
}

void PowerUpBase::DrawEXBack()
{
	m_EXBackMat = Math::Matrix::CreateTranslation(m_EXBackPos.x, m_EXBackPos.y, 0);

	SHADER.m_spriteShader.SetMatrix(m_EXBackMat);
	SHADER.m_spriteShader.DrawTex(&m_EXBackTex, m_EXBackRec);


	Math::Matrix iconMat = Math::Matrix::CreateScale(1.4, 1.4, 0) * Math::Matrix::CreateTranslation(m_EXBackPos.x - 408, m_EXBackPos.y, 0);
	SHADER.m_spriteShader.SetMatrix(iconMat);
	SHADER.m_spriteShader.DrawTex(&m_iconTex, m_iconRec);
}

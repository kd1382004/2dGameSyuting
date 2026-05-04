#include "PowerUpBase.h"

void PowerUpBase::SetSelectSiz(float siz)
{
	m_siz = siz;
	m_mat = Math::Matrix::CreateScale(m_siz, m_siz, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_iconMat = Math::Matrix::CreateScale(m_siz, m_siz,0)* Math::Matrix::CreateTranslation(m_pos.x - 42, m_pos.y + 75, 0);
}

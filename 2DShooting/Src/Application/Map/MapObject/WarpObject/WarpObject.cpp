#include"WarpObject.h"
#include"../../../SceneManager/Game/Game.h"

void  WarpObject::Init(Math::Vector2 pos)
{
	m_pos = pos;
	m_animeMax = 5;
	m_rec = { 64 * (int)m_animeC,0,64,50 };
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_R = 0;
}

void WarpObject::Updata(float scroll)
{
	m_mat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_R)) * Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);

	if (!m_owner->GetStageClearFlg())
	{
		return;
	}

	m_R += 5;

	if (m_R >= 360)
	{
		m_R = 0;
	}

	

	Math::Vector2 v = m_pos - m_owner->GetPlayerPos();
	if (v.Length() < 64)
	{
		m_owner->SetNextStageFlg(true);
	}

}

void WarpObject::Draw2D()
{
	if (!m_owner->GetStageClearFlg())
	{
		return;
	}

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, m_rec);
}

void WarpObject::Release()
{

}

#include "PlayerBullet.h"


void PlayerBullet::Init(Math::Vector2 pos, float deg)
{
	m_enemuNum = -1;
	m_buletPene = 1;
	m_deg = deg;
	m_siz = { 3,3 };
	m_atk = 10;
	m_pos = pos;
	HitDetection = 16.0f;
	m_aliveFlg = true;

	//角度から移動量を求める
	m_move.x = cos(DirectX::XMConvertToRadians(deg)) * m_speed;
	m_move.y = sin(DirectX::XMConvertToRadians(deg)) * m_speed;
	m_mat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0) * Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg)) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void PlayerBullet::Update()
{
	if (!m_aliveFlg) { return; }


	//座標更新
	m_pos += m_move;


	//////////////////
	//行列
	m_mat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0) * Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg)) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void PlayerBullet::Draw2D()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_bulletTex, m_rec, 1.0f);
	}
}

void PlayerBullet::Hit()
{

}

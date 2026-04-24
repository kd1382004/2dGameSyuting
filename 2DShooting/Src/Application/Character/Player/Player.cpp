#include "Player.h"

void Player::Init()
{
	m_pos = { 0,0 };
	m_rec = { 0,0,64,64 };
	m_speed = { 5.0,5.0 };
	m_aliveFlg = true;
	HitDetection = 64;

	//プレイヤーKey設定
	m_moveUp = 'W';
	m_moveDown = 'S';
	m_moveLeft = 'A';
	m_moveRight = 'D';

}

void Player::Update()
{
	Move();


	//行列合成
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Player::Draw2D()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
	}
}

void Player::Release()
{

}

void Player::Move()
{
	//移動量初期化
	m_move = { 0,0 };

	if (GetAsyncKeyState(m_moveUp) & 0x8000)
	{
		m_move.y += m_speed.y;
	}

	if (GetAsyncKeyState(m_moveDown) & 0x8000)
	{
		m_move.y -= m_speed.y;
	}

	if (GetAsyncKeyState(m_moveRight) & 0x8000)
	{
		m_move.x += m_speed.x;
	}

	if (GetAsyncKeyState(m_moveLeft) & 0x8000)
	{
		m_move.x -= m_speed.x;
	}

	//座標確定
	m_pos += m_move;
}

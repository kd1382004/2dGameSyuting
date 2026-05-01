#include "Player.h"
#include"Bullet/PlayerBullet.h"

void Player::Init()
{
	m_pos = { 0,0 };
	m_rec = { 0,0,64,64 };
	m_speed = { 5.0,5.0 };
	m_aliveFlg = true;
	HitDetection = 64;

	//ƒvƒŒƒCƒ„[KeyÝ’è
	m_moveUp = 'W';
	m_moveDown = 'S';
	m_moveLeft = 'A';
	m_moveRight = 'D';

	m_bulletTex.Load("Tex/Character/Player/Bullet/bullet.png");


	m_deg = 90;
	m_HP = 10;
}

void Player::Update()
{
	////////////
	//ˆÚ“®ˆ—//
	////////////
	Move();

	////////////////////////////////////////////
	//’e
	//’e‚Ì”­ŽË
	Shot();

	//’e‚ÌXV
	BulletUpdata();

	//’e
	//////////////////////////////////////////////

	//s—ñ‡¬
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat = m_rotationMat * m_transMat;
}

void Player::Draw2D()
{
	if (m_aliveFlg)
	{
		//’e‚Ì•`‰æ
		BulletDraw();


		//ƒvƒŒƒCƒ„[‚Ì•`‰æ
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
	}
}

PlayerBullet* Player::GetBullet(int num)
{
	if (num >= 0 && num < m_bullet.size())
	{
		return m_bullet[num];
	}

	return nullptr;
}

void Player::ReleseBuleet(int num)
{
	if (m_bullet.size() > num && num > 0)
	{
		delete m_bullet[num];
		m_bullet.erase(m_bullet.begin() + num);
	}
}

void Player::PlayerBulletHit(int num)
{
	//ŠÑ’Ê‰ñ”‚ðŒ¸‚ç‚·
	if (m_bullet.size() > num && num > 0)
	{
		m_bullet[num]->DownBulletPene();

		if (m_bullet[num]->GetBulletPene() < 0)
		{
			ReleseBuleet(num);
		}
	}

}

void Player::Release()
{
	m_bulletTex.Release();
	if (m_bullet.size() != 0)
	{
		for (int i = 0; i < m_bullet.size(); i++)
		{
			delete m_bullet[i];
			m_bullet.erase(m_bullet.begin() + i);
			i--;
		}
	}

}

void Player::Move()
{
	//ˆÚ“®—Ê‰Šú‰»
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

	if (m_move.x != 0 || m_move.y != 0)
	{
		Math::Vector2 FuturePos = m_pos + m_move;
		float moveX = FuturePos.x - m_pos.x;
		float moveY = FuturePos.y - m_pos.y;
		float rad = atan2(moveY, moveX);
		m_deg = DirectX::XMConvertToDegrees(rad);

		if (m_deg < 0)
		{
			m_deg += 360;
		}
	}



	//À•WŠm’è
	m_pos += m_move;
}

void Player::Shot()
{
	m_shotInterval--;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_shotInterval <= 0)
		{
			m_bullet.push_back(new PlayerBullet);
			m_bullet.back()->Init(m_pos, m_deg);
			m_bullet.back()->SetTex(&m_bulletTex);
			m_shotInterval = m_shotIntervalMax;
		}
	}
}

void Player::BulletUpdata()
{
	if (m_bullet.size() > 0)
	{
		for (int i = 0; i < m_bullet.size(); i++)
		{
			m_bullet[i]->Update();
			if (!m_bullet[i]->GetAliveFlg())
			{
				delete m_bullet[i];
				m_bullet.erase(m_bullet.begin() + i);
				i--;
			}
		}
	}
}

void Player::BulletDraw()
{
	if (m_bullet.size() > 0)
	{
		for (int i = 0; i < m_bullet.size(); i++)
		{
			m_bullet[i]->Draw2D();
		}
	}
}

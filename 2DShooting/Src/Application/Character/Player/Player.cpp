#include "Player.h"
#include"Bullet/PlayerBullet.h"

void Player::Init()
{
	m_pos = { 0,-360 };
	m_speed = { 5.0,5.0 };
	m_aliveFlg = true;
	HitDetection = 64;
	m_siz = { 5,5 };
	m_shotFlg = false;

	//プレイヤーKey設定
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
	//移動処理//
	////////////
	Move();

	////////////////////////////////////////////
	//弾
	//弾の発射
	Shot();

	//弾の更新
	BulletUpdata();

	//////////////////////////////////////////////

	//アニメーション
	AnimeRec();

	//行列合成
	//行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_scaleMat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0);
	m_mat = m_scaleMat * m_rotationMat * m_transMat;
}

void Player::Draw2D()
{
	if (m_aliveFlg)
	{
		//弾の描画
		BulletDraw();


		//プレイヤーの描画
		SHADER.m_spriteShader.SetMatrix(m_mat);

		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, 1.0f);
	}
}

void Player::AnimeRec()
{
	//左右移動

	if (m_shotFlg)
	{
		m_animeMode = ATKMode;
	}

	switch (m_animeMode)
	{
	case Player::Nomar:
		break;
	case Player::MoveMode:

		m_anime += 0.1;
		if (m_anime > 8)
		{
			m_anime = 0;
		}

		m_rec = { 100 * (int)m_anime,100 * 1,100,100 };
		break;
	case Player::ATKMode:
		m_anime += 0.5;
		if (m_anime > 8)
		{
			m_anime = 0;
			m_animeMode = Nomar;
			m_bullet.push_back(new PlayerBullet);
			m_bullet.back()->Init(m_pos, m_deg);
			m_bullet.back()->SetTex(&m_bulletTex);
			m_shotInterval = m_shotIntervalMax;
			m_shotFlg = false;
		}

		m_rec = { 100 * (int)m_anime,100 * 4,100,100 };
		break;
		break;
	default:
		break;
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
		if (!m_bullet[num]->GetAliveFlg())
		{
			delete m_bullet[num];
			m_bullet.erase(m_bullet.begin() + num);

		}
	}
}

void Player::PlayerBulletHit(int num)
{
	//貫通回数を減らす
	if (m_bullet.size() > num && num > 0)
	{
		m_bullet[num]->DownBulletPene();

		if (m_bullet[num]->GetBulletPene() < 0)
		{
			m_bullet[num]->SetSliveFlg(false);
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
	//移動量初期化
	m_move = { 0,0 };

	if (GetAsyncKeyState(m_moveUp) & 0x8000)
	{
		m_move.y++;
		m_animeMode = MoveMode;
		if (m_siz.y < 0)
		{
			m_siz.y *= -1;
		}
	}

	if (GetAsyncKeyState(m_moveDown) & 0x8000)
	{
		m_move.y--;
		m_animeMode = MoveMode;
		if (m_siz.y > 0)
		{
			m_siz.y *= -1;
		}
	}

	if (GetAsyncKeyState(m_moveRight) & 0x8000)
	{
		m_move.x++;
		m_animeMode = MoveMode;
		if (m_siz.y < 0)
		{
			m_siz.y *= -1;
		}
	}

	if (GetAsyncKeyState(m_moveLeft) & 0x8000)
	{
		m_move.x--;
		m_animeMode = MoveMode;
		if (m_siz.y > 0)
		{
			m_siz.y *= -1;
		}
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

	m_move.Normalize();
	m_move *= m_speed;


	//座標確定
	m_pos += m_move;
}

void Player::Shot()
{
	m_shotInterval--;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_shotInterval <= 0 && !m_shotFlg)
		{
			m_animeMode = ATKMode;
			m_anime = 0;
			m_shotFlg = true;
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

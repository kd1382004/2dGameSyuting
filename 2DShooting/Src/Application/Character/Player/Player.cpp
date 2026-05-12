#include "Player.h"
#include"PlayerBullet/PlayerBullet.h"
#include"HpBer/HpBer.h"
#include"../Info/CharacterInfoBace.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../Bullet/BulletBace.h"

void Player::Init()
{
	m_pos = { -300,0 };
	m_speed = { 5.0,5.0 };
	m_aliveFlg = true;
	HitDetection = 50;
	m_siz = { 3,3 };
	m_shotFlg = false;
	m_rec = { 100 * (int)m_anime,100 * 1,100,100 };
	m_animeMode = MoveMode;

	//プレイヤーKey設定
	m_moveUp = VK_UP;
	m_moveDown = VK_DOWN;
	m_moveLeft = VK_LEFT;
	m_moveRight = VK_RIGHT;

	m_bulletTex.Load("Tex/Character/Player/Bullet/bullet.png");

	m_MaxHP = 200;
	m_HP = m_MaxHP;

	m_hpBer = new PlayerHpBer();
	m_hpBer->Init();

	m_info = new CharacterInfo();

	m_info->SetATKLV(0);
}

void Player::Update()
{

	HPCoolTimeManager();

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


}

void Player::Draw2D()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_shadowMat);
		SHADER.m_spriteShader.DrawTex(m_shadowTex, m_rec, 1.0);
		//プレイヤーの描画
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_charaTex, m_rec, m_charaAlpha);


		m_hpBer->Drow2D();


		//弾の描画
		BulletDraw();
	}
}

void Player::MatConfirmed(float scroll)
{
	if (m_bullet.size() > 0)
	{
		for (int i = 0; i < m_bullet.size(); i++)
		{
			m_bullet[i]->MatConfirmed(scroll);
		}
	}

	if (m_hpBer)
	{
		m_hpBer->SetPlayerPos(m_pos);
		m_hpBer->SetHPPercent((float)m_HP / m_MaxHP);
		m_hpBer->MatConfirmed(scroll);
	}

	//行列合成
	//行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_scaleMat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0);
	m_mat = m_scaleMat * m_rotationMat * m_transMat;

	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll, m_pos.y, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_scaleMat = Math::Matrix::CreateScale(m_siz.x, m_siz.y, 0);
	m_shadowMat = m_scaleMat * m_rotationMat * m_transMat;
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

			Shot(m_info->Get3WShotFlg(), m_info->GetLRShotFlg());

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

BulletBace* Player::GetBullet(int num)
{
	if (num >= 0 && num < m_bullet.size())
	{
		return m_bullet[num];
	}

	return nullptr;
}

void Player::ReleseBuleet(int num)
{

	for (int i = 0; i < m_bullet.size(); i++)
	{
		if (!m_bullet[i]->GetAliveFlg())
		{
			delete m_bullet[i];
			m_bullet.erase(m_bullet.begin() + i);
			i--;
		}
	}
}

void Player::ReleseBuleet()
{
	for (int i = 0; i < m_bullet.size(); i++)
	{
		delete m_bullet[i];
		m_bullet.erase(m_bullet.begin() + i);
		i--;
	}
}

int Player::EnemyDehHeelAmount()
{
	int heel;

	heel = m_enemyDehHeelLv * 0.1 * 53;

	return heel;
}

void Player::HPHeel(int heel)
{
	m_HP += heel;

	if (m_HP >= m_MaxHP)
	{
		m_HP = m_MaxHP;
	}
}

void Player::PlayerBulletHit(int num)
{

	//貫通回数を減らす
	int a = m_bullet.size();
	if (m_bullet.size() > num && num >= 0)
	{
		m_bullet[num]->DownBulletPeneNum();

		if (m_bullet[num]->GetBulletPeneNum() < 0)
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

	if (m_hpBer)
	{
		delete m_hpBer;
	}

	if (m_info)
	{
		delete m_info;
	}
}

void Player::Move()
{
	//移動量初期化
	m_move = { 0,0 };


	if (InfoKeyAPP.KeyPush(m_moveUp))
	{
		m_move.y++;
		m_animeMode = MoveMode;
		if (m_siz.y < 0)
		{
			m_siz.y *= -1;
		}
	}


	if (InfoKeyAPP.KeyPush(m_moveDown))
	{
		m_move.y--;
		m_animeMode = MoveMode;
		if (m_siz.y > 0)
		{
			m_siz.y *= -1;
		}
	}


	if (InfoKeyAPP.KeyPush(m_moveRight))
	{
		m_move.x++;
		m_animeMode = MoveMode;
		if (m_siz.y < 0)
		{
			m_siz.y *= -1;
		}
	}

	if (InfoKeyAPP.KeyPush(m_moveLeft))
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
	if (InfoKeyAPP.KeyPush(VK_SPACE))
	{
		if (m_shotInterval <= 0 && !m_shotFlg)
		{
			m_animeMode = ATKMode;
			m_anime = 0;
			m_shotFlg = true;
		}
	}
}

void Player::Shot(bool _3WShotFlg, bool _3LRShotFlg)
{
	int shotNum = 0;
	BulletType bulletType = BulletType::NORMAL;

	if (m_fireArrowLv != 0)
	{
		bulletType = BulletType::FIRE;
	}


	m_bullet.push_back(new PlayerBullet);
	m_bullet.back()->Init(m_pos, m_deg, m_info, bulletType);
	m_bullet.back()->SetTex(&m_bulletTex);

	if (_3WShotFlg)
	{
		float deg = m_deg;
		deg -= 45;
		for (int i = 0; i < 2; i++)
		{
			m_bullet.push_back(new PlayerBullet);
			m_bullet.back()->Init(m_pos, deg, m_info, bulletType);
			m_bullet.back()->SetTex(&m_bulletTex);

			deg += 90;
		}
	}

	if (_3LRShotFlg)
	{
		float deg = m_deg;
		deg -= 90;
		for (int i = 0; i < 2; i++)
		{
			m_bullet.push_back(new PlayerBullet);
			m_bullet.back()->Init(m_pos, deg, m_info, bulletType);
			m_bullet.back()->SetTex(&m_bulletTex);
	
			deg += 180;


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

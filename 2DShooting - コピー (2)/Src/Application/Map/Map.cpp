#include"Map.h"
#include"MapObject/MapObject.h"
#include"../SceneManager/Game/Game.h"
#include"../Character/CharacterBase.h"
#include"../Character/Bullet/BulletBace.h"
#include"MapObject/WarpObject/WarpObject.h"

Map::Map()
{
}

Map::~Map()
{
	m_warpTex.Release();
	m_mapTex.Release();
	m_mapMat.clear();
	m_mapPos.clear();
	m_mapDeta.clear();
}

void Map::Init(MapType mapType)
{
	LodMapData(mapType);
}

void Map::MapHit(CharacterBase* chara)
{
	if (!chara->GetAliveFlg())
	{
		return;
	}


	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		if (m_mapDeta[i] == 0 || m_mapDeta[i] == -999 || m_mapDeta[i] == 9)
		{
			continue;
		}

		Math::Vector2 v = m_mapPos[i] - chara->GetPos();

		//半径＋半径
		const float sum = chara->GetHitDetection() / 2 + m_mapBlocSiz / 2;

		if (v.Length() < sum)
		{
			const float x = chara->GetPos().x - m_mapPos[i].x;
			const float y = chara->GetPos().y - m_mapPos[i].y;
			const float z = sqrt(x * x + y * y);

			//重なり具合
			float over = sum - z;

			//敵2から敵1への方向
			float nx = x / z;
			float ny = y / z;



			Math::Vector2 charaPos = chara->GetPos();
			charaPos.x += nx * over;
			charaPos.y += ny * over;
			chara->SetPos(charaPos);
			chara->BlockHit();

		}
	}
}

void Map::MapHit(BulletBace* buleet)
{
	if (!buleet->GetAliveFlg())
	{
		return;
	}


	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		if (m_mapDeta[i] == 0 || m_mapDeta[i] == -999 || m_mapDeta[i] == 9)
		{
			continue;
		}

		Math::Vector2 v = m_mapPos[i] - buleet->GetPos();

		//半径＋半径
		const float sum = buleet->GetHitDetection() / 2 + m_mapBlocSiz / 2;

		if (v.Length() < sum)
		{

			float overX = sum - abs(v.x);
			float overY = sum - abs(v.y);
			Math::Vector2 normal;

			if (overX < overY) {
				// 左右の面
				if (v.x > 0) {
					normal = { 1, 0 };   // 左面に当たった
				}
				else {
					normal = { -1, 0 };  // 右面に当たった
				}
			}
			else {
				// 上下の面
				if (v.y > 0) {
					normal = { 0, 1 };   // 上面
				}
				else {
					normal = { 0, -1 };  // 下面
				}
			}

			buleet->MapHit(normal);
			buleet->SetEnemyNum(-999);
		}
	}
}

void Map::Updata()
{
	//スクロール処理
	if (m_owner)
	{
		m_scroll = m_owner->GetPlayerPos().x;

		if (m_scroll < m_scrollMin)
		{
			m_scroll = m_scrollMin;
		}
		else if (m_scroll > m_scrollMax)
		{
			m_scroll = m_scrollMax;
		}
	}
	else
	{
		m_scroll = 0;
	}


	

	//行列作成
	for (int i = 0; i < m_mapPos.size(); i++)
	{
		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos[i].x - m_scroll, m_mapPos[i].y, 0);
		m_mapMat[i] = mat;
	}


	m_mapObj.back()->Updata(m_scroll);
}

void Map::Draw2D()
{
	for (int i = 0; i < m_mapDeta.size(); i++)
	{

		Math::Rectangle rec;

		switch (m_mapDeta[i])
		{
		case 0:
		case 9:
			rec = { 0,0,64,64 };
			break;

		case 1:
			rec = { 64,64,64,64 };
			break;
		case 2:
			rec = { 64 * 2,64,64,64 };
			break;

		default:
			break;
		}

		SHADER.m_spriteShader.SetMatrix(m_mapMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_mapTex, rec);
	}

	m_mapObj.back()->Draw2D();
}

Math::Vector2 Map::SlimeSpawnPos()
{
	Math::Vector2 spawnPos = {};

	int num;

	if (m_conSlimeSawnPos.size() == 0)
	{
		std::random_device rand_dev{};
		std::mt19937 rand_engine(rand_dev());
		int siz = m_SlimeSawnPos.size();
		siz -= 1;
		std::uniform_int_distribution<int> dist(0, siz);
		num = dist(rand_engine);

		spawnPos = m_SlimeSawnPos[num];
		m_SlimeSawnPos.erase(m_SlimeSawnPos.begin() + num);
	}
	else
	{
		spawnPos = m_conSlimeSawnPos[0];
		m_conSlimeSawnPos.erase(m_conSlimeSawnPos.begin());
	}

	return spawnPos;
}

Math::Vector2 Map::SkeletonSpawnPos()
{
	Math::Vector2 spawnPos = {};

	int num;

	if (m_conSkeletonSawnPos.size() == 0)
	{
		std::random_device rand_dev{};
		std::mt19937 rand_engine(rand_dev());
		int siz = m_SkeletonSawnPos.size();
		siz -= 1;
		std::uniform_int_distribution<int> dist(0, siz);
		num = dist(rand_engine);

		spawnPos = m_SkeletonSawnPos[num];
		m_SkeletonSawnPos.erase(m_SkeletonSawnPos.begin() + num);
	}
	else
	{
		spawnPos = m_conSkeletonSawnPos[0];
		m_conSkeletonSawnPos.erase(m_conSkeletonSawnPos.begin());
	}

	return spawnPos;
}

void Map::ResultUpdata(float scroll)
{
	//行列作成
	for (int i = 0; i < m_mapPos.size(); i++)
	{
		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos[i].x - scroll, m_mapPos[i].y, 0);
		m_mapMat[i] = mat;
	}


	m_mapObj.back()->Updata(scroll);
}

void Map::LodMapData(MapType mapType)
{
	switch (mapType)
	{
	case Map1:
		LodMapData1();
		break;
	case Map2:
		LodMapData2();
		break;
	case Map3:
		LodMapData3();
		break;
	default:
		break;
	}

}

void Map::LodMapData1()
{
	FILE* fp = fopen("Data/Map/Map1/MapData.txt", "r");
	m_warpTex.Load("Data/Map/Object/WarpHall.png");
	if (fp != NULL)
	{
		char ch;
		int a = 0;

		while ((ch = fgetc(fp)) != EOF)	//EOF=ファイルの終了 End Of File
		{
			if (ch == '\n')
			{
				m_mapDeta.push_back(-999);
			}
			else
			{


				if (ch == 'L')
				{
					m_mapDeta.push_back('L');
				}
				else if (ch == 'P')
				{
					m_mapDeta.push_back('P');
				}
				else if (ch == 'K')
				{
					m_mapDeta.push_back('K');
				}
				else if (ch == 'M')
				{
					m_mapDeta.push_back('M');
				}
				else if (ch == 'J')
				{
					m_mapDeta.push_back('J');
				}
				else
				{
					m_mapDeta.push_back(atoi(&ch));
				}
			}
		}
		fclose(fp);

		int b = 0;
	}


	int xNum = 0;
	int yNum = 0;
	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		m_mapPos.push_back({ -640 + (xNum * (float)m_mapBlocSiz),(360 - (yNum * (float)m_mapBlocSiz)) });
		xNum++;
		if (m_mapDeta[i] == -999)
		{
			yNum++;
			xNum = 0;
		}

		if (m_mapDeta[i] == 9)
		{
			m_mapObj.push_back(new  WarpObject);
			m_mapObj.back()->Init(m_mapPos.back());
			m_mapObj.back()->SetTex(&m_warpTex);
			m_mapObj.back()->SetOwner(m_owner);
		}

		if (m_mapDeta[i] == 'P')
		{
			m_playerSpawnPos = m_mapPos[i];
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'M')
		{
			m_conSlimeSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'L')
		{
			m_SlimeSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'J')
		{
			m_conSkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'K')
		{
			m_SkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos.back().x, m_mapPos.back().y, 0);
		m_mapMat.push_back(mat);
	}

	m_mapTex.Load("Tex/Map/Map1/tf_jungle_a2.png");
	m_scrollMin = m_mapPos[0].x + 640;
	m_scrollMax = m_mapPos.back().x - 640;

}

void Map::LodMapData2()
{
	FILE* fp = fopen("Data/Map/Map2/MapData.txt", "r");
	m_warpTex.Load("Data/Map/Object/WarpHall.png");
	if (fp != NULL)
	{
		char ch;
		int a = 0;

		while ((ch = fgetc(fp)) != EOF)	//EOF=ファイルの終了 End Of File
		{
			if (ch == '\n')
			{
				m_mapDeta.push_back(-999);
			}
			else
			{


				if (ch == 'L')
				{
					m_mapDeta.push_back('L');
				}
				else if (ch == 'P')
				{
					m_mapDeta.push_back('P');
				}
				else if (ch == 'K')
				{
					m_mapDeta.push_back('K');
				}
				else if (ch == 'M')
				{
					m_mapDeta.push_back('M');
				}
				else if (ch == 'J')
				{
					m_mapDeta.push_back('J');
				}
				else
				{
					m_mapDeta.push_back(atoi(&ch));
				}
			}
		}
		fclose(fp);

		int b = 0;
	}


	int xNum = 0;
	int yNum = 0;
	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		m_mapPos.push_back({ -640 + (xNum * (float)m_mapBlocSiz),(360 - (yNum * (float)m_mapBlocSiz)) });
		xNum++;
		if (m_mapDeta[i] == -999)
		{
			yNum++;
			xNum = 0;
		}

		if (m_mapDeta[i] == 9)
		{
			m_mapObj.push_back(new  WarpObject);
			m_mapObj.back()->Init(m_mapPos.back());
			m_mapObj.back()->SetTex(&m_warpTex);
			m_mapObj.back()->SetOwner(m_owner);
		}

		if (m_mapDeta[i] == 'P')
		{
			m_playerSpawnPos = m_mapPos[i];
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'M')
		{
			m_conSlimeSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'L')
		{
			m_SlimeSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'J')
		{
			m_conSkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'K')
		{
			m_SkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos.back().x, m_mapPos.back().y, 0);
		m_mapMat.push_back(mat);
	}

	m_mapTex.Load("Tex/Map/Map1/tf_jungle_a2.png");
	m_scrollMin = m_mapPos[0].x + 640;
	m_scrollMax = m_mapPos.back().x - 640;
}

void Map::LodMapData3()
{
	FILE* fp = fopen("Data/Map/Map3/MapData.txt", "r");
	m_warpTex.Load("Data/Map/Object/WarpHall.png");
	if (fp != NULL)
	{
		char ch;
		int a = 0;

		while ((ch = fgetc(fp)) != EOF)	//EOF=ファイルの終了 End Of File
		{
			if (ch == '\n')
			{
				m_mapDeta.push_back(-999);
			}
			else
			{


				if (ch == 'L')
				{
					m_mapDeta.push_back('L');
				}
				else if (ch == 'P')
				{
					m_mapDeta.push_back('P');
				}
				else if (ch == 'K')
				{
					m_mapDeta.push_back('K');
				}
				else if (ch == 'M')
				{
					m_mapDeta.push_back('M');
				}
				else if (ch == 'J')
				{
					m_mapDeta.push_back('J');
				}
				else
				{
					m_mapDeta.push_back(atoi(&ch));
				}
			}
		}
		fclose(fp);

		int b = 0;
	}


	int xNum = 0;
	int yNum = 0;
	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		m_mapPos.push_back({ -640 + (xNum * (float)m_mapBlocSiz),(360 - (yNum * (float)m_mapBlocSiz)) });
		xNum++;
		if (m_mapDeta[i] == -999)
		{
			yNum++;
			xNum = 0;
		}

		if (m_mapDeta[i] == 9)
		{
			m_mapObj.push_back(new  WarpObject);
			m_mapObj.back()->Init(m_mapPos.back());
			m_mapObj.back()->SetTex(&m_warpTex);
			m_mapObj.back()->SetOwner(m_owner);
		}

		if (m_mapDeta[i] == 'P')
		{
			m_playerSpawnPos = m_mapPos[i];
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'M')
		{
			m_conSlimeSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'L')
		{
			m_SlimeSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'J')
		{
			m_conSkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'K')
		{
			m_SkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos.back().x, m_mapPos.back().y, 0);
		m_mapMat.push_back(mat);
	}

	m_mapTex.Load("Tex/Map/Map1/tf_jungle_a2.png");
	m_scrollMin = m_mapPos[0].x + 640;
	m_scrollMax = m_mapPos.back().x - 640;
}


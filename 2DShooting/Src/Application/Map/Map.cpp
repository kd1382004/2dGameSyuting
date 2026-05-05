#include"Map.h"
#include"MapObject/MapObject.h"
#include"../SceneManager/Game/Game.h"
#include"../Character/CharacterBase.h"
#include"../Character/Player/PlayerBullet/PlayerBullet.h"
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

void Map::MapHit(PlayerBullet* buleet)
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
		}
	}
}

void Map::Updata()
{
	//スクロール処理
	m_scroll = m_owner->GetPlayerPos().x;

	if (m_scroll < m_scrollMin)
	{
		m_scroll = m_scrollMin;
	}
	else if (m_scroll > m_scrollMax)
	{
		m_scroll = m_scrollMax;
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
		default:
			break;
		}

		SHADER.m_spriteShader.SetMatrix(m_mapMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_mapTex, rec);
	}

	m_mapObj.back()->Draw2D();
}

void Map::LodMapData(MapType mapType)
{
	int a = mapType % 3 + 1;

	switch ((MapType)a)
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

		while ((ch = fgetc(fp)) != EOF)	//EOF=ファイルの終了 End Of File
		{
			if (ch == '\n')
			{
				m_mapDeta.push_back(-999);
			}
			else
			{
				m_mapDeta.push_back(atoi(&ch));
			}
		}
		fclose(fp);
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

		while ((ch = fgetc(fp)) != EOF)	//EOF=ファイルの終了 End Of File
		{
			if (ch == '\n')
			{
				m_mapDeta.push_back(-999);
			}
			else
			{
				m_mapDeta.push_back(atoi(&ch));
			}
		}
		fclose(fp);
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

		while ((ch = fgetc(fp)) != EOF)	//EOF=ファイルの終了 End Of File
		{
			if (ch == '\n')
			{
				m_mapDeta.push_back(-999);
			}
			else
			{
				m_mapDeta.push_back(atoi(&ch));
			}
		}
		fclose(fp);
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

		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos.back().x, m_mapPos.back().y, 0);
		m_mapMat.push_back(mat);
	}

	m_mapTex.Load("Tex/Map/Map1/tf_jungle_a2.png");
	m_scrollMin = m_mapPos[0].x + 640;
	m_scrollMax = m_mapPos.back().x - 640;
}


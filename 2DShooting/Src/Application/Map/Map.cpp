#include"Map.h"
#include"MapObject/MapObject.h"
#include"../SceneManager/Game/Game.h"

Map::Map()
{
}

Map::~Map()
{
	m_mapTex.Release();
	m_mapMat.clear();
	m_mapPos.clear();
	m_mapDeta.clear();
}

void Map::Init(MapType mapType)
{
	LodMapData(mapType);
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
		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos[i].x- m_scroll, m_mapPos[i].y, 0);
		m_mapMat[i] = mat;
	}
}

void Map::Draw2D()
{
	for (int i = 0; i < m_mapDeta.size(); i++)
	{

		Math::Rectangle rec;

		switch (m_mapDeta[i])
		{
		case 0:
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
		m_mapPos.push_back({ -640 + (xNum * (float)m_mapBlocSiz),360 - (yNum * (float)m_mapBlocSiz) });
		xNum++;
		if (m_mapDeta[i] == -999)
		{
			yNum++;
			xNum = 0;
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

}

void Map::LodMapData3()
{

}


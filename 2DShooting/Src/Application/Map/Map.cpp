#include"Map.h"
#include"MapObject/MapObject.h"
#include"../SceneManager/Game/Game.h"
#include"../Character/CharacterBase.h"
#include"../Character/Player/Bullet/PlayerBullet.h"

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

void Map::MapHit(CharacterBase* chara)
{
	if (!chara->GetAliveFlg())
	{
		return;
	}


	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		if (m_mapDeta[i] == 0 || m_mapDeta[i] == -999)
		{
			continue;
		}

		Math::Vector2 v = m_mapPos[i] - chara->GetPos();

		//îºåaÅ{îºåa
		const float sum = chara->GetHitDetection() / 2 + m_mapBlocSiz / 2;

		if (v.Length() < sum)
		{
			const float x = chara->GetPos().x - m_mapPos[i].x;
			const float y = chara->GetPos().y - m_mapPos[i].y;
			const float z = sqrt(x * x + y * y);

			//èdÇ»ÇËãÔçá
			float over = sum - z;

			//ìG2Ç©ÇÁìG1Ç÷ÇÃï˚å¸
			float nx = x / z;
			float ny = y / z;

			

			Math::Vector2 charaPos = chara->GetPos();
			charaPos.x += nx * over;
			charaPos.y += ny * over;
			chara->SetPos(charaPos);
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
		if (m_mapDeta[i] == 0 || m_mapDeta[i] == -999)
		{
			continue;
		}

		Math::Vector2 v = m_mapPos[i] - buleet->GetPos();

		//îºåaÅ{îºåa
		const float sum = buleet->GetHitDetection() / 2 + m_mapBlocSiz / 2;

		if (v.Length() < sum)
		{
			buleet->SetSliveFlg(false);
		}
	}
}

void Map::Updata()
{
	//ÉXÉNÉçÅ[Éãèàóù
	m_scroll = m_owner->GetPlayerPos().x;

	if (m_scroll < m_scrollMin)
	{
		m_scroll = m_scrollMin;
	}
	else if (m_scroll > m_scrollMax)
	{
		m_scroll = m_scrollMax;
	}

	//çsóÒçÏê¨
	for (int i = 0; i < m_mapPos.size(); i++)
	{
		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos[i].x - m_scroll, m_mapPos[i].y, 0);
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

		while ((ch = fgetc(fp)) != EOF)	//EOF=ÉtÉ@ÉCÉãÇÃèIóπ End Of File
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


#include"Map.h"
#include"MapObject/MapObject.h"
#include"../SceneManager/Game/Game.h"
#include"../Character/CharacterBase.h"
#include"../Character/Bullet/BulletBace.h"
#include"MapObject/WarpObject/WarpObject.h"

Map::Map()
{
	m_warpTex.Load("Data/Map/Object/WarpHall.png");
	m_mapTex.Load("Tex/Map/Map1/tf_jungle_a2.png");
}

Map::~Map()
{
	m_warpTex.Release();
	m_mapTex.Release();

}

void Map::Init(int stageNum)
{
	m_mapMat.clear();
	m_mapPos.clear();
	m_mapDeta.clear();

	if (m_mapObj.size() != 0)
	{
		for (int i = 0; i < m_mapObj.size(); i++)
		{
			delete m_mapObj[i];
		}

		m_mapObj.clear();
	}


	LodMapData(stageNum);
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

	spawnPos = m_conSlimeSawnPos[0];
	m_conSlimeSawnPos.erase(m_conSlimeSawnPos.begin());

	return spawnPos;
}

Math::Vector2 Map::SkeletonSpawnPos()
{
	Math::Vector2 spawnPos = {};

	spawnPos = m_conSkeletonSawnPos[0];
	m_conSkeletonSawnPos.erase(m_conSkeletonSawnPos.begin());

	return spawnPos;
}

Math::Vector2 Map::OrcSpawnPos()
{
	Math::Vector2 spawnPos = {};

	spawnPos = m_conOrcSawnPos[0];
	m_conOrcSawnPos.erase(m_conOrcSawnPos.begin());

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

void Map::SetWarpHallPos(Math::Vector2 pos)
{
	m_mapObj.back()->Init(pos);
}

void Map::LodMapData(int stageNum)
{
	MapInit(stageNum);
}

void Map::MapInit(int satgeNum)
{
	bool flg = false;

	while (1)
	{
		CellularAut(satgeNum);

		//goal(ワープゲート)までつながるか
		int mapW = m_mapS[0].size();

		std::queue<std::pair<int, int>> q;

		//到達したか
		std::vector<std::vector<bool>> visited(MapTopSiz, std::vector<bool>(mapW, false));

		int goalX = -1;
		int goalY = -1;

		for (int i = 0; i < MapTopSiz; i++)
		{
			for (int j = 0; j < mapW; j++)
			{
				if (m_mapS[i][j] == 'P')
				{
					q.push({ i,j });
					visited[i][j] = true;
				}

				if (m_mapS[i][j] == 9)
				{
					goalX = j;
					goalY = i;
				}
			}
		}


		int dx[4] = { 1, -1, 0, 0 };
		int dy[4] = { 0, 0, 1, -1 };


		while (!q.empty())
		{
			auto p = q.front();
			q.pop();

			int y = p.first;
			int x = p.second;


			if (x == goalX && y == goalY)
			{
				flg = true;
				break;
			}


			for (int i = 0; i < 4; i++)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];

				//端っこなら
				if (nx < 0 || ny < 0 || nx >= mapW || ny >= MapTopSiz)
				{
					continue;
				}

				//壁なら
				if (m_mapS[ny][nx] == 1)
				{
					continue;
				}

				//到達していたら
				if (visited[ny][nx])
				{
					continue;
				}


				visited[ny][nx] = true;
				q.push({ ny, nx });
			}
		}


		if (flg)
		{
			if (MapVacancy(satgeNum))
			{
				for (int y = 0; y < MapTopSiz; y++)
				{
					for (int x = 0; x < m_mapS[y].size(); x++)
					{
						if (m_mapS[y][x] == 0 && !visited[y][x])
						{
							m_mapS[y][x] = 2;
						}
					}
				}

				break;
			}
			else
			{
				flg = false;
			}
		}
	}


	EnemySpawn(satgeNum);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	///////////////
	//マップに移す

	for (int i = 0; i < MapTopSiz; i++)
	{
		for (int j = 0; j < m_mapS[i].size(); j++)
		{
			m_mapDeta.push_back(m_mapS[i][j]);
		}
		m_mapDeta.push_back(-999);
	}


	int xNum = 0;
	int yNum = 0;
	for (int i = 0; i < m_mapDeta.size(); i++)
	{
		m_mapPos.push_back({ -640 + (xNum * (float)m_mapBlocSiz),(360 - (yNum * (float)m_mapBlocSiz)) });
		xNum++;
		if (m_mapDeta[i] == -999)
		{
			m_mapDeta.erase(m_mapDeta.begin() + i);
			m_mapPos.erase(m_mapPos.begin() + i);
			yNum++;
			xNum = 0;
			i--;
			continue;
		}

		if (m_mapDeta[i] == 9)
		{
			m_mapObj.push_back(new  WarpObject);
			m_mapObj.back()->SetTex(&m_warpTex);
			m_mapObj.back()->SetOwner(m_owner);
		}

		if (m_mapDeta[i] == 8)
		{
			m_mapDeta[i] = 0;
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

		if (m_mapDeta[i] == 'J')
		{
			m_conSkeletonSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		if (m_mapDeta[i] == 'O')
		{
			m_conOrcSawnPos.push_back(m_mapPos[i]);
			m_mapDeta[i] = 0;
		}

		Math::Matrix mat = Math::Matrix::CreateTranslation(m_mapPos.back().x, m_mapPos.back().y, 0);
		m_mapMat.push_back(mat);
	}

	m_scrollMin = m_mapPos[0].x + 640;
	m_scrollMax = m_mapPos.back().x - 640;

	for (int i = 0; i < MapTopSiz; i++)
	{
		m_mapS[i].clear();
	}
}

void Map::CellularAut(int satgeNum)
{
	for (int i = 0; i < MapTopSiz; i++)
	{
		m_mapS[i].clear();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	// マップデータ(横のサイズ)確定
	// 
	//マップ横サイズ
	int MapWideNum = 30 + satgeNum;

	for (int i = 0; i < MapTopSiz; i++)
	{
		for (int j = 0; j < MapWideNum; j++)
		{
			if (j == 0 || i == 0 || i == MapTopSiz - 1 || j == MapWideNum - 1)//もし端っこなら
			{
				//四方をブロックで囲む
				m_mapS[i].push_back(1);
			}
			else
			{
				m_mapS[i].push_back(0);
			}
		}
	}
	////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////
	//半分位をランダムに壁で埋める(セルオートマン)
	//埋める壁の数
	int blokNum = 0;

	for (int i = 0; i < MapTopSiz; i++)
	{
		for (int j = 0; j < m_mapS[i].size(); j++)
		{
			if (m_mapS[i][j] == 0)
			{
				blokNum++;
			}

		}
	}

	blokNum *= 0.35;

	int x;
	int y;
	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	int sizX = m_mapS[0].size() - 2;
	std::uniform_int_distribution<int> distX(1, sizX);

	int sizY = MapTopSiz - 2;
	std::uniform_int_distribution<int> distY(1, sizY);


	for (int i = 0; i < blokNum; i++)
	{
		while (1)
		{
			x = distX(rand_engine);
			y = distY(rand_engine);

			if (m_mapS[y][x] == 0)
			{
				m_mapS[y][x] = 1;
				break;
			}
		}

	}

	for (int i = 1; i < MapTopSiz - 1; i++)
	{
		for (int j = 1; j < m_mapS[i].size() - 1; j++)
		{
			if (m_mapS[i][j] == 'P' || m_mapS[i][j] == 9)
			{
				continue;
			}

			//周りの壁の数を数える
			int num = 0;
			////////////////////////////
			// m_mapS[y][x]
			//上
			if (m_mapS[i - 1][j - 1] == 1)//左上
			{
				num++;
			}

			if (m_mapS[i - 1][j] == 1)//上
			{
				num++;
			}

			if (m_mapS[i - 1][j + 1] == 1)//右上
			{
				num++;
			}
			////////////////////
			//横
			if (m_mapS[i][j - 1] == 1)//左
			{
				num++;
			}

			if (m_mapS[i][j + 1] == 1)//右
			{
				num++;
			}
			///////////////////
			//下
			if (m_mapS[i + 1][j - 1] == 1)//左下
			{
				num++;
			}

			if (m_mapS[i + 1][j] == 1)//下
			{
				num++;
			}

			if (m_mapS[i + 1][j + 1] == 1)//右下
			{
				num++;
			}
			///////////////////////////
			if (num <= 3)
			{
				m_mapS[i][j] = 0;
			}

			if (num >= 5)
			{
				m_mapS[i][j] = 1;
			}
		}
	}


	//プレイヤー出現地とgoal確定(固定位置)
	m_mapS[5][1] = 'P';
	m_mapS[5][MapWideNum - 2] = 9;
}

//空き率をみる
bool Map::MapVacancy(int satgeNum)
{
	int H = MapTopSiz;
	int W = m_mapS[0].size();

	int emptyCount = 0;
	int total = H * W;

	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			if (m_mapS[y][x] != 1)
				emptyCount++;
		}
	}

	double ratio = (double)emptyCount / total;

	bool flg = false;

	//50%以上ならOK
	if (ratio >= 0.40)
	{
		flg = true;
	}

	return 	flg;

}

void Map::EnemySpawn(int satgeNum)
{
	//スポーンできなかった敵の数
	int noSpownNum = 0;


	//1区画のX大きさ
	int Section = 7;

	//区画の数(Sectionの大きさでわれた数)
	int SectionNum = m_mapS[0].size() / Section;

	//出現位置
	//セクション内の出現可能一を取る(Playや出現区画にはわかせない)
	for (int i = 1; i < SectionNum; i++)
	{
		int cnt = 0;
		//1区画当たりに出る敵の数( 敵の種類 + 敵の種類 × Stage数 )
		int enemyNum = 3;
		if (satgeNum != 0)
		{
			enemyNum += satgeNum / 3;
		}

		for (int j = 0; j < Section; j++)
		{
			for (int k = 0; k < MapTopSiz; k++)
			{
				if (m_mapS[k][Section * i + j] == 0)
				{
					cnt++;
				}
			}
		}

		std::random_device rand_dev{};
		std::mt19937 rand_engine(rand_dev());
		int siz = Section - 1;
		std::uniform_int_distribution<int> distX(0, siz);
		std::uniform_int_distribution<int> distY(0, MapTopSiz - 1);
		while (1)
		{
			int x = distX(rand_engine);
			int y = distY(rand_engine);

			if (m_mapS[y][x + Section * i] == 0)
			{
				if (enemyNum % 3 == 1)
				{
					//スケルトン
					m_mapS[y][x + Section * i] = 'J';
				}
				else	if (enemyNum % 3 == 2)
				{
					//スライム
					m_mapS[y][x + Section * i] = 'M';
				}
				else if (enemyNum % 3 == 0)
				{
					//オーク
					m_mapS[y][x + Section * i] = 'O';
				}

				cnt--;
				enemyNum--;
			}

			if (enemyNum <= 0 || cnt <= 0)
			{
				noSpownNum = enemyNum;
				break;
			}

		}

	}

	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	int siz = m_mapS[0].size() - 1;
	std::uniform_int_distribution<int> distX(5, siz);
	std::uniform_int_distribution<int> distY(0, MapTopSiz - 1);

	noSpownNum += satgeNum;

	while (1)
	{
		int x = distX(rand_engine);
		int y = distY(rand_engine);

		if (m_mapS[y][x] == 0)
		{
			if (x % 3 == 1)
			{
				//スケルトン
				m_mapS[y][x] = 'J';
			}
			else if (x % 3 == 2)
			{
				//スライム
				m_mapS[y][x] = 'M';
			}
			else if (x % 3 == 0)
			{
				//オーク
				m_mapS[y][x] = 'O';
			}

			noSpownNum--;
		}

		if (noSpownNum <= 0)
		{
			break;
		}

	}

}

void Map::setOwner(Game* owner)
{
	m_owner = owner;


	for (int i = 0; i < m_mapObj.size(); i++)
	{
		m_mapObj[i]->SetOwner(m_owner);
	}
}
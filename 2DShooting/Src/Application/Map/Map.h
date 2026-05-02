#pragma once

class MapObject;
class Game;



class Map
{
public:

	//マップの種類
	enum MapType
	{
		Map1,
		Map2,
		Map3
	};

	Map();
	~Map();


	//マップデータまでのパス
	void Init(MapType mapType);

	void Updata();
	void Draw2D();

	//マップデートをリセット
	void Reset();

	void setOwner(Game *owner) { m_owner = owner; }

	float GetScroll() { return m_scroll; }
private:

	void LodMapData(MapType mapType);

	void LodMapData1();
	void LodMapData2();
	void LodMapData3();

	//オブジェクトのポインター
	std::vector<MapObject*> m_mapObj;

	//マップデータ
	std::vector<int> m_mapDeta;

	//マップの座標
	std::vector<Math::Vector2> m_mapPos;

	//行列
	std::vector<Math::Matrix> m_mapMat;

	int m_mapBlocSiz = 64;

	KdTexture m_mapTex;

	float m_scroll;

	Game* m_owner;

	int m_scrollMin;
	int m_scrollMax;
};

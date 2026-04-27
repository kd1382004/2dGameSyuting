#pragma once

class MapObject;

//マップの種類
enum MapType
{
	Map1,
	Map2,
	Map3
};

class Map
{
public:

	Map();
	~Map();


	//マップデータまでのパス
	void Init(MapType mapType);

	void Updata();
	void Draw2D();

	//マップデートをリセット
	void Reset();
private:

	void LodMapData(MapType mapType);

	void LodMapData1();
	void LodMapData2();
	void LodMapData3();

	//オブジェクトのポインター
	std::vector<MapObject*> m_mapObj;

};

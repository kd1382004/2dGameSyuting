#include"Map.h"
#include"MapObject/MapObject.h"

void Map::Init(MapType mapType)
{
	LodMapData(mapType);
}

void Map::Updata()
{

}

void Map::Draw2D()
{

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

}

void Map::LodMapData2()
{

}

void Map::LodMapData3()
{

}


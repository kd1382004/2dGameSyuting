#pragma once

class MapObject;
class Game;
class CharacterBase;
class BulletBace;


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

	void MapHit(CharacterBase* chara);

	void MapHit(BulletBace* buleet);

	//マップデートをリセット
	void Reset();

	void setOwner(Game* owner) { m_owner = owner; }

	float GetScroll() { return m_scroll; }

	Math::Vector2 PlayerSpawnPos() { return m_playerSpawnPos; }

	Math::Vector2 SlimeSpawnPos();
	Math::Vector2 SkeletonSpawnPos();

	int GetSlimeSpawnNum() { return m_conSlimeSawnPos.size() + m_SlimeSawnPos.size(); }
	int GetConSlimeSpawnNum() { return m_conSlimeSawnPos.size(); }


	int GetSkeletonSpawnNum() { return m_conSkeletonSawnPos.size() + m_SkeletonSawnPos.size(); }
	int GetConSkeletonSpawnNum() { return m_conSkeletonSawnPos.size(); }
private:

	void LodMapData(MapType mapType);

	void LodMapData1();
	void LodMapData2();
	void LodMapData3();

	//オブジェクトのポインター
	std::vector<MapObject*> m_mapObj;

	//ワープ
	KdTexture m_warpTex;

	//マップデータ
	std::vector<int> m_mapDeta;

	//マップの座標
	std::vector<Math::Vector2> m_mapPos;

	//行列
	std::vector<Math::Matrix> m_mapMat;

	int m_mapBlocSiz = 64;

	KdTexture m_mapTex;

	float m_scroll;

	Game* m_owner=nullptr;

	int m_scrollMin;
	int m_scrollMax;

	//プレイヤースポーン位置
	Math::Vector2 m_playerSpawnPos = {};

	//スライム確定スポーン位置
	std::vector<Math::Vector2> m_conSlimeSawnPos;

	//スライム出現可能位置
	std::vector<Math::Vector2> m_SlimeSawnPos;

	//スケルトン確定スポーン位置
	std::vector<Math::Vector2> m_conSkeletonSawnPos;

	//スケルトン出現可能位置
	std::vector<Math::Vector2> m_SkeletonSawnPos;
	
};

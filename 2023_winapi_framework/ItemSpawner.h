#pragma once

class ItemSpawner
{
	enum ItemType
	{
		Nos,
		X
	};
public:
	void RandomItemSpawn(Vec2 spawnPos);
	void SpawnItem(ItemType it, Vec2 spPos);
};




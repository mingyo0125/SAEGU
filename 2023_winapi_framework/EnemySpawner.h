#pragma once

class EnemySpawner
{
public:
	vector<std::pair<Vec2, Vec2>> areaSizeArr = { {Vec2(0,0), Vec2(WINDOW_WIDTH, 20)},
											{Vec2(0,WINDOW_HEIGHT - 20), Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)},
											{Vec2(0, 0), Vec2(20, WINDOW_HEIGHT)},
											{Vec2(WINDOW_WIDTH - 20, 0), Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)}
	};

	void SpawnEnemy(Object* targetObj, float speed, int hp, float scale);
	Vec2 GetSpawnPos();
};

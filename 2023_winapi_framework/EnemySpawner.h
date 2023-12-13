#pragma once
#include "Timer.h"


class EnemySpawner : public Object
{
public:
	EnemySpawner(Object* targetObj, float speed, int hp, float scale, Timer* timer);
	~EnemySpawner();

public:
	vector<std::pair<Vec2, Vec2>> areaSizeArr = { {Vec2(0,0), Vec2(WINDOW_WIDTH, 20)},
											{Vec2(0,WINDOW_HEIGHT - 20), Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)},
											{Vec2(0, 0), Vec2(20, WINDOW_HEIGHT)},
											{Vec2(WINDOW_WIDTH - 20, 0), Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)}
	};

	void SpawnEnemy();
	Vec2 GetSpawnPos();
public:
	virtual void Update() override;
private:
	void HandleSecondChange();
private:
	float fMonsterSpeed = 0.1f;
	float fMonsterHp = 10;
	float fMonsterScale = 30;
	float fCurrentTime = 0;
	float fSpawnTime = 0;

	float limitTimeArr[8] = {10, 30, 60, 120, 150, 180, 200, 230};
	float spawnTimeArr[8] = {5.5, 4.6, 4, 3.6, 3, 2.5, 1.9, 1.3};

	Object* p_target;
	Timer* p_timer;
};

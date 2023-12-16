#pragma once
#include "Timer.h"


class EnemySpawner : public Object
{
public:
	EnemySpawner(Object* targetObj, float speed, int hp[], float scale, Timer* timer);
	~EnemySpawner();

public:
	vector<std::pair<Vec2, Vec2>> areaSizeArr = { {Vec2(0,0), Vec2(WINDOW_WIDTH, 20)},
											{Vec2(0,WINDOW_HEIGHT - 20), Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)},
											{Vec2(0, 0), Vec2(20, WINDOW_HEIGHT)},
											{Vec2(WINDOW_WIDTH - 20, 0), Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)}
	};

	void SpawnRandomEnemy();
	Vec2 GetSpawnPos();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
private:
	void HandleSecondChange();
private:
	int idx = 0;
	float fMonsterSpeed = 0.6f;
	float fBatHp = 2.0f;
	float fBirdHp = 3.0f;
	float fSlimeHp = 1.0f;
	float fMonsterScale = 30;
	float fCurrentTime = 0;
	float fCrazyTime = 0;
	float fSpawnTime = 2;

	int randomT;
	int randomS;

	float limitTimeArr[8] = {10, 30, 60, 120, 150, 180, 200, 230};
	float spawnTimeArr[8] = {2, 1.8, 1.6, 1.5, 1.4, 1.3, 1.2, 1};

	float crazyEnemyTime = 60;
	float warnningTextTime = 3;
	bool onWarnning;

	Object* p_target;
	Timer* p_timer;
};

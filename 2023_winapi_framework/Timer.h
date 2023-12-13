#pragma once
#include "Object.h"

class EnemySpawner;
class CurrentSecond
{
private:
	int second;	
public:
	void (EnemySpawner::*HandleSecChange)();
public:
	void SetValue(int newValue, EnemySpawner* e);
	int Getvalue()
	{
		return second;
	}
};

class Timer : public Object
{
public:
	Timer();
	~Timer();
public:
	float t_currentTime;
	CurrentSecond t_currentSecond;
	wstring str_currentSecond;
	void Update() override;
	void Render(HDC _dc) override;
private:
	EnemySpawner* t_enemySpawner;
	void SetTime();
	Object* target;
};

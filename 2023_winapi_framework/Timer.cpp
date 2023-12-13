#include "pch.h"
#include "Timer.h"
#include "TimeMgr.h"
#include <string>
#include "EnemySpawner.h"

Timer::Timer(EnemySpawner* enemySpawner)
{
	t_currentTime = 0;
	t_currentSecond.SetValue(0, enemySpawner);

	t_enemySpawner = enemySpawner;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	if (t_currentTime >= 1.f)
	{
		t_currentSecond.SetValue(t_currentSecond.Getvalue() + 1, t_enemySpawner);
		t_currentTime = 0.f;
		SetTime();
	}
	
	t_currentTime += fDT;
}

void Timer::Render(HDC _dc)
{
	SetBkMode(_dc, TRANSPARENT);
	SetTextAlign(_dc, TA_LEFT);
	SetTextColor(_dc, RGB(0, 0, 0));

	TextOut(_dc, 100, 100, // юс╫ц╥н 100 100
		str_currentSecond.c_str(), str_currentSecond.size());
}

void Timer::SetTime()
{
	int minute = t_currentSecond.Getvalue() / 60;
	int sec = t_currentSecond.Getvalue() % 60;
	
	str_currentSecond = std::to_wstring(minute) + L" : " + std::to_wstring(sec);
}

void CurrentSecond::SetValue(int newValue, EnemySpawner* e)
{
	if (newValue == second) return;
	
	(e->*(HandleSecChange))();
}

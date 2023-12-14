#include "pch.h"
#include "Timer.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include <string>
#include "EnemySpawner.h"
#include "Scene.h"

Timer::Timer()
{
	t_currentTime = 0;
	t_currentSecond = CurrentSecond();
	t_enemySpawner = nullptr;
	target = nullptr;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	if (t_currentTime >= 1.f)
	{
		if (target == nullptr)
		{
			auto objs = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::DEFAULT);
			for (int i = 0; i < objs.size(); i++)
			{
				if (objs[i]->GetName() == L"EnemySpawner")
				{
					target = objs[i];
					break;
				}
			}
			
			t_enemySpawner = (EnemySpawner*)target;
		}
		
		t_currentSecond.SetValue(t_currentSecond.second + 1, t_enemySpawner);
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
	int minute = t_currentSecond.second / 60;
	int sec = t_currentSecond.second % 60;
	
	str_currentSecond = std::to_wstring(minute) + L" : " + std::to_wstring(sec);
}

void CurrentSecond::SetValue(int newValue, EnemySpawner* e)
{
	second = newValue;
	(e->*(HandleSecChange))();
}


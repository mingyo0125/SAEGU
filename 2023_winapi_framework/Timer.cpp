#include "pch.h"
#include "Timer.h"
#include "TimeMgr.h"
#include <string>

Timer::Timer()
{
	t_currentTime = 0;
	t_currentSecnod = 0;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	if (t_currentTime >= 1.f)
	{
		t_currentSecnod++;
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
	int minute = t_currentSecnod / 60;
	int sec = t_currentSecnod % 60;
	
	str_currentSecond = std::to_wstring(minute) + L" : " + std::to_wstring(sec);
}

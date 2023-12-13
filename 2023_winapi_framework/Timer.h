#pragma once
#include "Object.h"

class Timer : public Object
{
public:
	Timer();
	~Timer();
public:
	float t_currentTime;
	int t_currentSecnod;
	wstring str_currentSecond;
	void Update() override;
	void Render(HDC _dc) override;
private:
	void SetTime();
};

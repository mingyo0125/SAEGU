#pragma once
#include "Object.h"

class GroundObj : public Object
{
public:
	GroundObj(Vec2 pos);
	~GroundObj();
public:
	void Render(HDC _dc) override;
private:
	Vec2 myPos;
};

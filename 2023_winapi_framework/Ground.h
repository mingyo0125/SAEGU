#pragma once
#include "Object.h"

class Ground : public Object
{
	void Render(HDC _dc) override;
};

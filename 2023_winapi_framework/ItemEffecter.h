#pragma once
#include "Object.h"

class ItemEffecter : public Object
{
public:
	ItemEffecter(Object* p);
	~ItemEffecter();
public:
	void EffectToPlayer(Object* obj);
	void Update() override;
private:
	Object* pObject;
	int level_up_speed_value = 50;
	bool onXEffective;
	float xCurT;
	float limitTime;
};

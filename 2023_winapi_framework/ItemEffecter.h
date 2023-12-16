#pragma once
#include "Object.h"
#include "Monster.h"

class ItemEffecter : public Object
{
public:
	ItemEffecter(Object* p);
	~ItemEffecter();
public:
	void EffectToPlayer();
	void Update() override;
private:
	Object* pObject;
	Monster* curMonster;
	int level_up_speed_value = 50;
	bool onXEffective;
	float xCurT;
	float limitTime = 5;
};

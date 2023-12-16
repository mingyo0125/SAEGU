#pragma once
#include "Object.h"
#include "Monster.h"

class ItemEffecter : public Object
{
public:
	ItemEffecter(Object* p);
	~ItemEffecter();
public:
	void EffectToPlayer(Monster* monster);
	void Update() override;
	void Render(HDC _dc) override;
private:
	Object* pObject;
	Monster* curMonster;
	int level_up_speed_value = 50;
	bool onXEffective;
	float xCurT;
	float limitTime = 5;
};

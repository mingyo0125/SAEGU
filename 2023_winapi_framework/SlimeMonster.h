#pragma once
#include "Monster.h"

class SlimeMonster : public Monster
{
public:
	SlimeMonster(Object* target, float speed, int hp);
	~SlimeMonster();
private:
	Texture* m_moveTexture;
};

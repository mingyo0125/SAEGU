#pragma once
#include "Monster.h"

class BatMonster : public Monster
{
public:
	BatMonster(Object* target, float speed, int hp);
	~BatMonster();
private:
	Texture* m_moveTexture;
};

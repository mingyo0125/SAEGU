#include "pch.h"
#include "BirdMonster.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
#include "Collider.h"

BirdMonster::BirdMonster(Object* target, float speed, int hp)
	:Monster(target, speed, hp)
{
	hp = 3;
	m_moveTexture = ResMgr::GetInst()->TexLoad(L"BirdEnemyIdle", L"Texture\\BlueBird_Idle.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnim(L"BirdEnemy_Idle", m_moveTexture, Vec2(0, 0), Vec2(60, 60), Vec2(60, 0), 9, 0.1f);
	GetAnimator()->PlayAnim(L"BirdEnemy_Idle", true, 999);
	CreateCollider();
}

BirdMonster::~BirdMonster()
{
}

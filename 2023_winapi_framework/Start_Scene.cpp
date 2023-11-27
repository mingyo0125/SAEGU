#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "EnemySpawner.h"
#include "TimeMgr.h"

Object* pTarget;
float fMonsterSpeed = 0.1f;
float fMonsterHp = 10;
float fMonsterScale = 30;

float fMonsterSpawnTime = 3;
float fCurrentTime = 0;

void Start_Scene::Init()
{
	//플레이어 생성
	Object* pObj = new Player;
	pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	pObj->SetScale(Vec2(100.f,100.f));
	pTarget = pObj;
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResMgr::GetInst()->Play(L"BGM");

	// 충돌체크해야되는것들을 설정하자.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
}

void Start_Scene::Update()
{
	Scene::Update();
	
	if (fCurrentTime >= fMonsterSpawnTime)
	{
		EnemySpawner spawner;
		spawner.SpawnEnemy(pTarget, fMonsterSpeed, fMonsterHp, fMonsterScale);
		fCurrentTime = 0;
	}
	fCurrentTime += fDT;
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}

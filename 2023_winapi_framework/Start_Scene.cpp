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
#include "ItemSpawner.h"
#include "Camera.h"
#include "Timer.h"
#include "SceneMgr.h"
#include "GroundObj.h"

void Start_Scene::Init()
{
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			Object* pGround = new GroundObj(Vec2(1920 * j, 1920 * i));
			pGround->SetPos(Vec2(0, 0));
			AddObject(pGround, OBJECT_GROUP::DEFAULT);
		}
	}

	//플레이어 생성
	Object* pObj = new Player;
	pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResMgr::GetInst()->Play(L"BGM");

	// 충돌체크해야되는것들을 설정하자.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::ITEM);

	// Camera Look 설정
	Vec2 resolution = Core::GetInst()->GetResolution();
	Camera::GetInst()->SetLookAt(resolution / 2.f);

	Timer* p_timer = new Timer();
	AddObject(p_timer, OBJECT_GROUP::DEFAULT);
	int arr[3] = { 1, 3, 5 };
	EnemySpawner* p_enemySpawner = new EnemySpawner(pObj, 0.1, arr, 20, p_timer);
	AddObject(p_enemySpawner, OBJECT_GROUP::DEFAULT);
}

void Start_Scene::Update()
{
	Scene::Update();

	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		SceneMgr::GetInst()->LoadScene(L"GameOver_Scene");
	}
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}

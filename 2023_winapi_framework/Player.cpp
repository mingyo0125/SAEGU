#include "pch.h"
#include "Core.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "EventMgr.h"
Player::Player()
	: walkRightTex(nullptr)
	, walkLeftTex(nullptr)
	, shootLeftTex(nullptr)
	, shootRightTex(nullptr)
	, m_pTexIdle(nullptr)
	, hitTexLeft(nullptr)
	, hitTexRight(nullptr)
	, DieTexLeft(nullptr)
	, DieTexRight(nullptr)
	, StaticDieTexRight(nullptr)
	, StaticDieTexLeft(nullptr)
	, Hp(0)
	, MaxHp(10)
	, isKeyPressing(false)
	, isLeft(false)
	, isShooting(false)
	, isDie(false)
	, speed(100.f)
	, curTime(0.f)
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);

	Object::SetName(L"Player");

	walkRightTex = ResMgr::GetInst()->TexLoad(L"PlayerRight", L"Texture\\move_with_FX.bmp");
	walkLeftTex = ResMgr::GetInst()->TexLoad(L"PlayerLeft", L"Texture\\move_with_FX2.bmp");
	m_pTexIdle = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\static_idle.bmp");
	shootRightTex = ResMgr::GetInst()->TexLoad(L"PlayerRightShoot", L"Texture\\shoot_with_FX.bmp");
	shootLeftTex = ResMgr::GetInst()->TexLoad(L"PlayerLeftShoot", L"Texture\\shoot_with_FX2.bmp");
	hitTexLeft = ResMgr::GetInst()->TexLoad(L"PlayerHitLeft", L"Texture\\damagedLeft.bmp");
	hitTexRight = ResMgr::GetInst()->TexLoad(L"PlayerHitRight", L"Texture\\damagedRight.bmp");
	DieTexLeft = ResMgr::GetInst()->TexLoad(L"PlayerDieLeft", L"Texture\\deathLeft.bmp");
	DieTexRight = ResMgr::GetInst()->TexLoad(L"PlayerDieRight", L"Texture\\deathRight.bmp");
	StaticDieTexRight = ResMgr::GetInst()->TexLoad(L"PlayerStaticDieRight", L"Texture\\static_die_Right.bmp");
	StaticDieTexLeft = ResMgr::GetInst()->TexLoad(L"PlayerStaticDieLeft", L"Texture\\static_die_Left.bmp");
	
	Hp = &MaxHp; //Hp 초기화

	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	// 엉엉엉 내 20분 ㅠㅠㅠ ㅁ날어;ㅣ남러;ㅁ나얼
	CreateAnimator(); 
	GetAnimator()->CreateAnim(L"Player_Right", walkRightTex, Vec2(30.f, 0.2f),
		Vec2(45.f, 56.f), Vec2(0.f, 57.f), 8, 0.1f);
	GetAnimator()->CreateAnim(L"Player_Left", walkLeftTex, Vec2(180.f, 0.2f),
		Vec2(45.f, 56.f), Vec2(0.f, 57.f), 8, 0.1f);
	GetAnimator()->CreateAnim(L"Player_ShootRight", shootRightTex, Vec2(0.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 5, 0.1f);
	GetAnimator()->CreateAnim(L"Player_ShootLeft", shootLeftTex, Vec2(146.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 5, 0.1f);
	GetAnimator()->CreateAnim(L"Player_HitLeft", hitTexLeft, Vec2(146.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Player_HitRight", hitTexRight, Vec2(30.f, 0.2f),
		Vec2(45.f, 56.f), Vec2(0.f, 57.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Player_DieLeft", DieTexLeft, Vec2(146.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 6, 0.1f);
	GetAnimator()->CreateAnim(L"Player_DieRight", DieTexRight, Vec2(10.f, 14.5f),
		Vec2(53.f, 53.f), Vec2(0.f, 54.f), 6, 0.1f);
	//GetAnimator()->PlayAnim(L"Player_Front",true);

	/*CreateAnimator();
	GetAnimator()->CreateAnim(L"Jiwoo_Front", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);*/

	//// 오프셋 건드리기
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// 하나만
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// 프레임 다 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));
}
Player::~Player()
{ 
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	Vec2 vPos = GetPos();
	if (KEY_DOWN(KEY_TYPE::LBUTTON))
	{
		isShooting = true;

		Vec2 curPos = GetPos();
		float deltaX = KeyMgr::GetInst()->GetMousePos().x - curPos.x;
		float deltaY = KeyMgr::GetInst()->GetMousePos().y - curPos.y;

		float radAngle = atan2(deltaY, deltaX);

		float degAngle = radAngle * 180.0f / M_PI;

		if (isLeft)
		{
			if (abs(degAngle) <= 90)
			{
				GetAnimator()->PlayAnim(L"Player_ShootRight", false, 1);
				isLeft = false;
			}
			else
			{
				GetAnimator()->PlayAnim(L"Player_ShootLeft", false, 1);
			}
		}
		else
		{
			if (abs(degAngle) >= 90)
			{
				GetAnimator()->PlayAnim(L"Player_ShootLeft", false, 1);
				isLeft = true;
			}
			else
			{
				GetAnimator()->PlayAnim(L"Player_ShootRight", false, 1);
			}
		}
		CreateBullet();
		isKeyPressing = true;
	}
	else if (KEY_UP(KEY_TYPE::LBUTTON))
	{
		isShooting = false;
	}
	if (!isShooting)
	{
		if (KEY_PRESS(KEY_TYPE::A))
		{
			GetAnimator()->PlayAnim(L"Player_Left", false, 1);

			vPos.x -= speed * fDT;
			isLeft = true;
			isKeyPressing = true;
		}
		if (KEY_PRESS(KEY_TYPE::D))
		{
			GetAnimator()->PlayAnim(L"Player_Right", false, 1);
			vPos.x += speed * fDT;
			isLeft = false;
			isKeyPressing = true;
		}
		if (KEY_PRESS(KEY_TYPE::W))
		{
			vPos.y -= speed * fDT;
			if (KEY_PRESS(KEY_TYPE::A))
			{
				GetAnimator()->PlayAnim(L"Player_Left", false, 1);
			}
			else
			{
				GetAnimator()->PlayAnim(L"Player_Right", false, 1);
			}
			isKeyPressing = true;
		}
		if (KEY_PRESS(KEY_TYPE::S))
		{
			vPos.y += speed * fDT;
			if (KEY_PRESS(KEY_TYPE::A))
			{
				GetAnimator()->PlayAnim(L"Player_Left", false, 1);
			}
			else
			{
				GetAnimator()->PlayAnim(L"Player_Right", false, 1);
			}
			isKeyPressing = true;
		}
		if (KEY_DOWN(KEY_TYPE::LSHIFT))
		{
			while (curTime <= 0.1f)
			{
				speed = 500.f;

				curTime += fDT;
			}
			curTime = 0.f;

		}
		if (KEY_DOWN(KEY_TYPE::E))
		{
			MinusHp(1);
		}
	}
	
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Bullet* pBullet = new Bullet;
	Vec2 vBulletPos = GetPos();

	vBulletPos.y -= 10.f;
	vBulletPos.x = isLeft ? vBulletPos.x -= 50.f : vBulletPos.x += 50.f;

	POINT pMousePos = KeyMgr::GetInst()->GetMousePos();

	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f,25.f));
//	pBullet->SetDir(M_PI / 4 * 7);
//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(10.f,15.f));
	pBullet->SetDir((Vec2((float)pMousePos.x, (float)pMousePos.y)) - vBulletPos);
	pBullet->SetName(L"Player_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

void Player::Render(HDC _dc)
{
	if (!GetAnimator()->GetIsAnimating())
	{
		if (isDie)
		{
			if (isLeft)
			{
				Vec2 vPos = GetPos();
				Vec2 vScale = GetScale();
				int Width = StaticDieTexLeft->GetWidth();
				int Height = StaticDieTexLeft->GetHeight();
				// 1. 기본 옮기기
				BitBlt(_dc
					, (int)(vPos.x - vScale.x / 2) + 25
					, (int)(vPos.y - vScale.y / 2) + 25
					, Width, Height, StaticDieTexLeft->GetDC()
					, 0, 0, SRCCOPY);
			}
			else
			{
				Vec2 vPos = GetPos();
				Vec2 vScale = GetScale();
				int Width = StaticDieTexRight->GetWidth();
				int Height = StaticDieTexRight->GetHeight();
				// 1. 기본 옮기기
				BitBlt(_dc
					, (int)(vPos.x - vScale.x / 2) + 25
					, (int)(vPos.y - vScale.y / 2) + 25
					, Width, Height, StaticDieTexRight->GetDC()
					, 0, 0, SRCCOPY);
			}
			
		}
		else
		{
			Vec2 vPos = GetPos();
			Vec2 vScale = GetScale();
			int Width = m_pTexIdle->GetWidth();
			int Height = m_pTexIdle->GetHeight();
			// 1. 기본 옮기기
			BitBlt(_dc
				, (int)(vPos.x - vScale.x / 2) + 25
				, (int)(vPos.y - vScale.y / 2) + 25
				, Width, Height, m_pTexIdle->GetDC()
				, 0, 0, SRCCOPY);
		}
	}
	
	//// 2. 색상 걷어내기
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. 확대 및 축소
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. 회전
	// 삼각함수, 회전행렬
	//Plgblt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Player::MinusHp(int damage)
{
	*Hp -= damage;

	if (isLeft)
	{
		GetAnimator()->PlayAnim(L"Player_HitLeft", false, 1);
	}
	else
	{
		GetAnimator()->PlayAnim(L"Player_HitRight", false, 1);
	}

	if (*Hp <= 0)
	{
		Die();
	}
}

void Player::Die()
{
	//죽으면 할것들.
	isDie = true;
	if (isLeft)
	{
		GetAnimator()->PlayAnim(L"Player_DieLeft", false, 1);
	}
	else
	{
		GetAnimator()->PlayAnim(L"Player_DieRight", false, 1);
	}

	
	//EventMgr::GetInst()->DeleteObject(this);
}

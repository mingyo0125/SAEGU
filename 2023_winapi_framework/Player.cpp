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
#include "Camera.h"

Player::Player()
	: _walkRightTex(nullptr)
	, _walkLeftTex(nullptr)
	, _shootLeftTex(nullptr)
	, _shootRightTex(nullptr)
	, m_pTexIdle(nullptr)
	, _hitTexLeft(nullptr)
	, _hitTexRight(nullptr)
	, _dieTexLeft(nullptr)
	, _dieTexRight(nullptr)
	, _staticDieTexRight(nullptr)
	, _staticDieTexLeft(nullptr)
	, Hp(0)
	, MaxHp(5)
	, isKeyPressing(false)
	, isLeft(false)
	, isShooting(false)
	, isDie(false)
	, isIdle(true)
	, isRealoading(false)
	, isUnDestroyed(false)
	, isHit(nullptr)
	, curTime(0.f)
	, _hp1Tex(nullptr)
	, _hp2Tex(nullptr)
	, _hp3Tex(nullptr)
	, _hp4Tex(nullptr)
	, _hp5Tex(nullptr)
	, _hp6Tex(nullptr)
	, _dashTex(nullptr)
	, _ammoTex(nullptr)
	, _reloadTex(nullptr)
	, speed(150.f)
	, dashSpeed(700.f)
	, targetTime(0.15f)
	, dashCooldown(3.f)
	, dashCooldownTime(0.f)
	, shootCooldown(0.5f)
	, shootCooldownTime(0.f)
	, unDestroyedTime(5.f)
	, bulletCurTime(0.f)
	, reloadTime(3.f)
	, curReloadTime(0.f)
	, maxAmmo(10)
	, curAmmo(10)
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);

	Object::SetName(L"Player");
	Camera::GetInst()->SetTarget(this);

	TextureLoad();
	
	Hp = &MaxHp; //Hp �ʱ�ȭ
	Object::SetSpeed(speed);

	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	// ������ �� 20�� �ФФ� ������;�ӳ���;������
	CreateAnimator(); 
	GetAnimator()->CreateAnim(L"Player_Right", _walkRightTex, Vec2(30.f, 0.2f),
		Vec2(45.f, 56.f), Vec2(0.f, 57.f), 8, 0.1f);
	GetAnimator()->CreateAnim(L"Player_Left", _walkLeftTex, Vec2(180.f, 0.2f),
		Vec2(45.f, 56.f), Vec2(0.f, 57.f), 8, 0.1f);
	GetAnimator()->CreateAnim(L"Player_ShootRight", _shootRightTex, Vec2(0.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 5, 0.1f);
	GetAnimator()->CreateAnim(L"Player_ShootLeft", _shootLeftTex, Vec2(146.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 5, 0.1f);
	GetAnimator()->CreateAnim(L"Player_HitLeft", _hitTexLeft, Vec2(146.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Player_HitRight", _hitTexRight, Vec2(30.f, 0.2f),
		Vec2(45.f, 56.f), Vec2(0.f, 57.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Player_DieLeft", _dieTexLeft, Vec2(146.f, 0.2f),
		Vec2(110.f, 56.f), Vec2(0.f, 57.f), 6, 0.1f);
	GetAnimator()->CreateAnim(L"Player_DieRight", _dieTexRight, Vec2(10.f, 14.5f),
		Vec2(53.f, 53.f), Vec2(0.f, 54.f), 6, 0.1f);

	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\GunShot.wav", false);
	ResMgr::GetInst()->LoadSound(L"Reload", L"Sound\\galil-reload-sound.mp3", false);
	ResMgr::GetInst()->LoadSound(L"Hit", L"Sound\\matrixxx__retro-hit.wav", false);
	ResMgr::GetInst()->LoadSound(L"DashSound", L"Sound\\kastenfrosch__whoosh-dash.wav", false);
	
	//GetAnimator()->PlayAnim(L"Player_Front",true);

	/*CreateAnimator();
	GetAnimator()->CreateAnim(L"Jiwoo_Front", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);*/

	//// ������ �ǵ帮��
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// �ϳ���
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// ������ �� 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));
}
Player::~Player()
{ 
	/*if (nullptr != walkRightTex)
		delete& walkRightTex;
	if (nullptr != walkLeftTex)
		delete& walkLeftTex;
	if (nullptr != shootLeftTex)
		delete& shootLeftTex;
	if (nullptr != shootRightTex)
		delete& shootRightTex;
	if (nullptr != m_pTexIdle)
		delete& m_pTexIdle;
	if (nullptr != hitTexRight)
		delete& hitTexRight;
	if (nullptr != hitTexLeft)
		delete& hitTexLeft;
	if (nullptr != DieTexLeft)
		delete& DieTexLeft;
	if (nullptr != DieTexRight)
		delete& DieTexRight;
	if (nullptr != StaticDieTexLeft)
		delete& StaticDieTexLeft;
	if (nullptr != StaticDieTexRight)
		delete& StaticDieTexRight;
	if (nullptr != hp1Tex)
		delete& hp1Tex;
	if (nullptr != hp2Tex)
		delete& hp2Tex;
	if (nullptr != hp3Tex)
		delete& hp4Tex;
	if (nullptr != hp4Tex)
		delete& hp4Tex;
	if (nullptr != hp5Tex)
		delete& hp5Tex;
	if (nullptr != hp6Tex)
		delete& hp6Tex;*/

}
void Player::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		OnDamage(1);
	}
}
void Player::ExitCollision(Collider* _pOther)
{
}
void Player::StayCollision(Collider* _pOther)
{
}
void Player::Update()
{
	if (isDie) { return; }

	if (dashCooldownTime < dashCooldown)
	{
		dashCooldownTime += fDT;
	}
	if (shootCooldownTime < shootCooldown)
	{
		shootCooldownTime += fDT;
	}
	
	MSetUnDestroyedBullet();

	if (curAmmo == 0 && !isRealoading)
	{
		ResMgr::GetInst()->Play(L"Reload");
	}

	if (isHit)
	{
		if (isLeft)
		{
			GetAnimator()->PlayAnim(L"Player_HitLeft", false, 1);
		}
		else
		{
			GetAnimator()->PlayAnim(L"Player_HitRight", false, 1);
		}

		if (curTime >= targetTime)
		{
			isHit = false;
			curTime = 0;
		}

		curTime += fDT;
		GetAnimator()->Update();
		return;
	}

	Vec2 vPos = GetPos();

	if (curAmmo == 0)
	{
		isRealoading = true;
	}
	Reload();
	
	if (KEY_DOWN(KEY_TYPE::LBUTTON) && shootCooldownTime >= shootCooldown && curAmmo > 0)
	{
		curAmmo--;
		isShooting = true;

		Vec2 curRenderPos = Camera::GetInst()->GetRenderPos(vPos);
		float deltaX = KeyMgr::GetInst()->GetMousePos().x - curRenderPos.x;
		float deltaY = KeyMgr::GetInst()->GetMousePos().y - curRenderPos.y;

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
		isIdle = false;
		shootCooldownTime = 0.f;

	}
	else if (KEY_UP(KEY_TYPE::LBUTTON))
	{
		isShooting = false;
		isIdle = false;
	}

	if (!isShooting && !isHit)
	{
		if (KEY_PRESS(KEY_TYPE::A))
		{
			GetAnimator()->PlayAnim(L"Player_Left", false, 1);

			vPos.x -= Object::GetSpeed() * fDT;
			isLeft = true;
			isKeyPressing = true;
			isIdle = false;
		}
		if (KEY_PRESS(KEY_TYPE::D))
		{
			GetAnimator()->PlayAnim(L"Player_Right", false, 1);
			vPos.x += Object::GetSpeed() * fDT;
			isLeft = false;
			isKeyPressing = true;
			isIdle = false;
		}
		if (KEY_PRESS(KEY_TYPE::W))
		{
			vPos.y -= Object::GetSpeed() * fDT;
			if (KEY_PRESS(KEY_TYPE::A))
			{
				GetAnimator()->PlayAnim(L"Player_Left", false, 1);
			}
			else
			{
				GetAnimator()->PlayAnim(L"Player_Right", false, 1);
			}
			isKeyPressing = true;
			isIdle = false;
		}
		if (KEY_PRESS(KEY_TYPE::S))
		{
			vPos.y += Object::GetSpeed() * fDT;
			if (KEY_PRESS(KEY_TYPE::A))
			{
				GetAnimator()->PlayAnim(L"Player_Left", false, 1);
			}
			else
			{
				GetAnimator()->PlayAnim(L"Player_Right", false, 1);
			}
			isKeyPressing = true;
			isIdle = false;
		}
		if (KEY_PRESS(KEY_TYPE::LSHIFT) && dashCooldownTime >= dashCooldown)
		{
			ResMgr::GetInst()->Play(L"DashSound");

			if (curTime >= 0.1f)
			{
				Object::SetSpeed(speed);
				dashCooldownTime = 0.0f;
			}
			else
			{
				Object::SetSpeed(dashSpeed);
			}

			curTime += fDT;
			isIdle = false;

		}
		else if (KEY_UP(KEY_TYPE::LSHIFT))
		{
			if (dashCooldownTime >= dashCooldown) { dashCooldownTime = 0.0f; }
			curTime = 0;
			Object::SetSpeed(speed);
			isIdle = false;

		}
	}
	if (KEY_DOWN(KEY_TYPE::R))
	{
		curAmmo = 0;
	}
	
	
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Camera::GetInst()->CameraShake(3.f);
	Bullet* pBullet = new Bullet();

	Vec2 vBulletPos = GetPos();
	Vec2 vRenderBulletPos = Camera::GetInst()->GetRenderPos(vBulletPos);

	vBulletPos.y -= 10.f;
	vBulletPos.x = isLeft ? vBulletPos.x -= 50.f : vBulletPos.x += 50.f;

	POINT pMousePos = KeyMgr::GetInst()->GetMousePos();

	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f,25.f));
//	pBullet->SetDir(M_PI / 4 * 7);
//	pBullet->SetDir(120* M_PI / 180);
	//pBullet->SetDir(Vec2(10.f,15.f));
	pBullet->SetDir((Vec2((float)pMousePos.x, (float)pMousePos.y)) - vRenderBulletPos);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
	ResMgr::GetInst()->Play(L"Shoot");

	if (isUnDestroyed)
	{
		pBullet->SetUnDestroyedBullet();
	}
}

void Player::TextureLoad()
{
	_walkRightTex = ResMgr::GetInst()->TexLoad(L"PlayerRight", L"Texture\\move_with_FX.bmp");
	_walkLeftTex = ResMgr::GetInst()->TexLoad(L"PlayerLeft", L"Texture\\move_with_FX2.bmp");
	m_pTexIdle = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\static_idle.bmp");
	_shootRightTex = ResMgr::GetInst()->TexLoad(L"PlayerRightShoot", L"Texture\\shoot_with_FX.bmp");
	_shootLeftTex = ResMgr::GetInst()->TexLoad(L"PlayerLeftShoot", L"Texture\\shoot_with_FX2.bmp");
	_hitTexLeft = ResMgr::GetInst()->TexLoad(L"PlayerHitLeft", L"Texture\\damagedLeft.bmp");
	_hitTexRight = ResMgr::GetInst()->TexLoad(L"PlayerHitRight", L"Texture\\damagedRight.bmp");
	_dieTexLeft = ResMgr::GetInst()->TexLoad(L"PlayerDieLeft", L"Texture\\deathLeft.bmp");
	_dieTexRight = ResMgr::GetInst()->TexLoad(L"PlayerDieRight", L"Texture\\deathRight.bmp");
	_staticDieTexRight = ResMgr::GetInst()->TexLoad(L"PlayerStaticDieRight", L"Texture\\static_die_Right.bmp");
	_staticDieTexLeft = ResMgr::GetInst()->TexLoad(L"PlayerStaticDieLeft", L"Texture\\static_die_Left.bmp");

	_hp1Tex = ResMgr::GetInst()->TexLoad(L"Hp1", L"Texture\\zero.bmp");
	_hp2Tex = ResMgr::GetInst()->TexLoad(L"Hp2", L"Texture\\two.bmp");
	_hp3Tex = ResMgr::GetInst()->TexLoad(L"Hp3", L"Texture\\four.bmp");
	_hp4Tex = ResMgr::GetInst()->TexLoad(L"Hp4", L"Texture\\six.bmp");
	_hp5Tex = ResMgr::GetInst()->TexLoad(L"Hp5", L"Texture\\eight.bmp");
	_hp6Tex = ResMgr::GetInst()->TexLoad(L"Hp6", L"Texture\\ten.bmp");

	_dashTex = ResMgr::GetInst()->TexLoad(L"dash", L"Texture\\UI_Flat_Slot_01_Available.bmp");

	_ammoTex = ResMgr::GetInst()->TexLoad(L"ammo", L"Texture\\ammo-rifle.bmp"); 
	_reloadTex = ResMgr::GetInst()->TexLoad(L"reload", L"Texture\\Reload.bmp"); 

}

void Player::MSetUnDestroyedBullet()
{
	if (isUnDestroyed)
	{
		if (bulletCurTime >= unDestroyedTime)
		{
			isUnDestroyed = false;
			bulletCurTime = 0;
		}
		else
		{
			bulletCurTime += fDT;
		}
	}
}

void Player::Reload()
{
	if (isRealoading)
	{
		if (curReloadTime >= reloadTime)
		{
			curAmmo = maxAmmo;
			curReloadTime = 0;
			isRealoading = false;
		}
		else
		{
			curReloadTime += fDT;
		}
	}
}

void Player::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 renderPos = Camera::GetInst()->GetRenderPos(vPos);

	int Width = _hp1Tex->GetWidth();
	int Height = _hp1Tex->GetHeight();

	if (isDie)
	{
		if (isLeft)
		{
			int Width = _staticDieTexLeft->GetWidth();
			int Height = _staticDieTexLeft->GetHeight();

			TransparentBlt(_dc
				, (int)(renderPos.x - vScale.x / 2) + 25
				, (int)(renderPos.y - vScale.y / 2) + 25
				, Width, Height, _staticDieTexLeft->GetDC()
				, 0, 0, Width, Height, RGB(255, 255, 255));
		}
		else
		{
			TransparentBlt(_dc
				, (int)(renderPos.x - vScale.x / 2) + 25
				, (int)(renderPos.y - vScale.y / 2) + 25
				, Width, Height, _staticDieTexRight->GetDC()
				, 0, 0, Width, Height, RGB(255, 255, 255));
		}
	}

	if (isIdle)
	{
		int Width = m_pTexIdle->GetWidth();
		int Height = m_pTexIdle->GetHeight();
		// 1. �⺻ �ű��
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 25
			, (int)(renderPos.y - vScale.y / 2) + 25
			, Width, Height, m_pTexIdle->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
	}

	switch (*Hp)
	{
	case 5:
		TransparentBlt(_dc
		, (int)(renderPos.x - vScale.x / 2) + 15
		, (int)(renderPos.y - vScale.y / 2)
		, Width, Height, _hp6Tex->GetDC()
		, 0, 0, Width, Height, RGB(255, 255, 255));
		break;
	case 4:
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 15
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, _hp5Tex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
		break;
	case 3:
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 15
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, _hp4Tex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
		break;
	case 2:
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 15
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, _hp3Tex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
		break;
	case 1:
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 15
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, _hp2Tex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
		break;
	case 0:
		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 15
			, (int)(renderPos.y - vScale.y / 2)
			, Width, Height, _hp1Tex->GetDC()
			, 0, 0, Width, Height, RGB(255, 255, 255));
		break;
	}

	for (int i = 1; i <= dashCooldownTime; i++)
	{
		int dashWidth = _dashTex->GetWidth();
		int dashHeight = _dashTex->GetHeight();

		TransparentBlt(_dc
			, (int)((renderPos.x) * i / 40) + 665
			, (int)(renderPos.y - vScale.y / 2) + 25
			, dashWidth, dashHeight, _dashTex->GetDC()
			, 0, 0, dashWidth, dashHeight, RGB(255, 255, 255));
	}

	if (curAmmo == 0)
	{
		int reloadWidth = _reloadTex->GetWidth();
		int reloadHeight = _reloadTex->GetHeight();

		TransparentBlt(_dc
			, (int)(renderPos.x - vScale.x / 2) + 31
			, (int)(renderPos.y - vScale.y / 2) + 80
			, reloadWidth, reloadHeight, _reloadTex->GetDC()
			, 0, 0, reloadWidth, reloadHeight, RGB(255, 255, 255));
	}

	for (int i = 1; i <= curAmmo; i++)
	{
		int ammoWidth = _ammoTex->GetWidth();
		int amooHeight = _ammoTex->GetHeight();

		TransparentBlt(_dc
			, (int)((renderPos.x) * i / 50) + 550
			, (int)(renderPos.y - vScale.y / 2) + 80
			, ammoWidth, amooHeight, _ammoTex->GetDC()
			, 0, 0, ammoWidth, amooHeight, RGB(255, 255, 255));
	}
	
	// 2. ���� �Ⱦ��
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. Ȯ�� �� ���
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. ȸ��
	// �ﰢ�Լ�, ȸ�����
	//Plgblt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Player::OnDamage(int damage)
{
	*Hp -= damage;
	Camera::GetInst()->CameraShake(10.f);
	ResMgr::GetInst()->Play(L"Hit");

	if (*Hp <= 0)
	{
		Die();
		return;
	}
	isHit = true;
}

void Player::Die()
{
	//������ �Ұ͵�.
	if (isLeft)
	{
		GetAnimator()->PlayAnim(L"Player_DieLeft", false, 1);
	}
	else
	{
		GetAnimator()->PlayAnim(L"Player_DieRight", false, 1);
	}

	isDie = true;

	while (true)
	{
		if (curTime >= targetTime)
		{
			curTime = 0;
			break;
		}

		curTime += fDT;
		GetAnimator()->Update();
	}

	//EventMgr::GetInst()->DeleteObject(this);
}
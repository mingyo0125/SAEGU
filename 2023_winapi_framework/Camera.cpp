#include "pch.h"
#include "Camera.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"

void Camera::Update()
{
	if (_targetObj != nullptr)
	{
		if (_targetObj->GetIsDead()) { _targetObj = nullptr; } // ������ null�� �ʱ�ȭ
		else
		{
			_lookAt = _targetObj->GetPos();
		}
	}

	if (KEY_PRESS(KEY_TYPE::W))
	{
		/*_lookAt.y -= */
	}

	CalDiff();
}

void Camera::CalDiff()
{
	Vec2 resolution = Core::GetInst()->GetResolution();
	Vec2 center = resolution / 2;

	_diffVec = _lookAt - center;

}

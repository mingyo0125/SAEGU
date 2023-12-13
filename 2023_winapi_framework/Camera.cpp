#include "pch.h"
#include "Camera.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

void Camera::Update()
{
	if (_targetObj != nullptr)
	{
		if (isCameraShake)
		{
			if (currentTime >= shakeTime)
			{
				_lookAt = _lookAt - moveVec;

				currentTime = 0;
				isCameraShake = false;
			}

			_lookAt = _lookAt + moveVec;
			
			currentTime += fDT;
			return;
		}

		if (_targetObj->GetIsDead()) { _targetObj = nullptr; } // 죽으면 null로 초기화
		else
		{
			_lookAt = _targetObj->GetPos();
		}
	}

	CalDiff();
}

void Camera::CalDiff()
{
	Vec2 resolution = Core::GetInst()->GetResolution();
	Vec2 center = resolution / 2;

	_diffVec = _lookAt - center;
}

#include "pch.h"
#include "Camera.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

void Camera::CameraShake()
{
    isCameraShake = true;
    currentTime = 0.0f;
    originShakeMagnitude = shakeMagnitude;
    _originLookAt = _lookAt;
}

void Camera::ApplyShake()
{
    if (isCameraShake)
    {
        Object* tarObj = _targetObj;
        _targetObj = nullptr;    
        float shakeX = sin(currentTime * 50.0f) * shakeMagnitude;
        float shakeY = cos(currentTime * 50.0f) * shakeMagnitude;

        _lookAt = _originLookAt + Vec2(shakeX, shakeY);
        //MessageBox(NULL, L"Your debugging message here", L"Debug Info", MB_OK | MB_ICONINFORMATION);
        currentTime += fDT;

        if (currentTime >= shakeTime)
        {
            isCameraShake = false;
            _lookAt = _originLookAt;
            shakeMagnitude = originShakeMagnitude;
            SetTarget(tarObj);
        }
    }
}

void Camera::CalDiff()
{
    Vec2 resolution = Core::GetInst()->GetResolution();
    Vec2 center = resolution / 2;

    _diffVec = _lookAt - center;
}

void Camera::Init()
{
    _targetObj = nullptr;
    shakeMagnitude = 10.f;
    shakeTime = 0.1f;
    currentTime = 0.f;
    isCameraShake = false;
    originShakeMagnitude = 0.f;
}

void Camera::Update()
{
    if (_targetObj != nullptr)
    {
        if (_targetObj->GetIsDead()) { _targetObj = nullptr; }
        else
        {
            _lookAt = _targetObj->GetPos();
        }
    }

    CalDiff();
    ApplyShake();
}

#pragma once
#include "Scene.h"

class Title_Scene : 
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
};
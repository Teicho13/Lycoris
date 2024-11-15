#pragma once
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Tick(float dt) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
    virtual void HandleEvents() = 0;
};


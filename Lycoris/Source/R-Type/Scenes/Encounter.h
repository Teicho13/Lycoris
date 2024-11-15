//Encounter is the first playable level in R-Type
#pragma once
#include "Core/Scene.h"

class Encounter : public Scene
{
public:
    void Init() override;
    void Tick(float dt) override;
    void Render() override;
    void Destroy() override;
    void HandleEvents() override;
};

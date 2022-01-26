#pragma once

#include "demo.hpp"

#include "scene.hpp"

class DemoRendererBasic : public Demo
{
private:
    Scene* scene;

public:
    DemoRendererBasic();
    ~DemoRendererBasic() override;

    const char* name() override { return "Renderer basic"; };
    void display() override;
};
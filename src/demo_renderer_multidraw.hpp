#pragma once

#include "demo.hpp"

#include "scene.hpp"

class DemoRendererMultiDraw : public Demo
{
private:
    Scene* scene;

public:
    DemoRendererMultiDraw();
    ~DemoRendererMultiDraw() override;

    const char* name() override { return "Renderer multi draw"; };
    void display() override;
};
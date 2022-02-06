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

    const char* name() override { return "Renderer multidraw"; };
    void display() override;
};
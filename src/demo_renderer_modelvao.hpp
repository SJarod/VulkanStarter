#pragma once

#include "demo.hpp"

#include "scene.hpp"

class DemoRendererModelVao : public Demo
{
private:
    Scene* scene;

public:
    DemoRendererModelVao();
    ~DemoRendererModelVao() override;

    const char* name() override { return "Renderer send all model matrices as VAO (useless)"; };
    void display() override;
};
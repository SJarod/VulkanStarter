#pragma once

#include "demo.hpp"

#include "scene.hpp"

class DemoRendererOneVao : public Demo
{
private:
    Scene* scene;

public:
    DemoRendererOneVao();
    ~DemoRendererOneVao() override;

    const char* name() override { return "Renderer one VAO"; };
    void display() override;
};
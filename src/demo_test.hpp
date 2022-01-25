#pragma once

#include "demo.hpp"

class DemoTest : public Demo
{
public:
    virtual const char* name() { return "Test"; }
    void display() override;

private:
    float time = 0.f;
};

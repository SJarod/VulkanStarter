#pragma once

class Demo
{
public:
    virtual ~Demo() {}
    virtual const char* name() { return "Undefined"; }
    virtual void display() = 0;
};

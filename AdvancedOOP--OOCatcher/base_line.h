#pragma once
#include "point.h"
#include <memory>
#include <cmath>

using namespace std;

class base_line
{
public:
    virtual double get_x() const = 0;
    virtual double get_y() const = 0;
    virtual double end_x() const = 0;
    virtual double end_y() const = 0;

    virtual int int_x() const final;
    virtual int int_y() const final;
    virtual int ent_x() const final;
    virtual int ent_y() const final;

    virtual double length() const = 0;
    virtual double slope()  const = 0;

    virtual void shift(double dx, double dy) = 0;
    virtual void rotate(double da) = 0;
};
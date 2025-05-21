#pragma once
#include <cmath>

class point
{
public:
    point();
    point(double new_x, double new_y);

    virtual double get_x() const;
    virtual double get_y() const;
    int int_x() const;
    int int_y() const;

    double dist(const point& that) const;
    double dir(const point& that) const;

    virtual void shift(double dx, double dy);

private:
    double x, y;
};
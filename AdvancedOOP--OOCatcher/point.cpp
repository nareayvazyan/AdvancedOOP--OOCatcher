#include "point.h"

point::point(double new_x, double new_y) : x(new_x), y(new_y)
{

}

point::point() : point(0, 0)
{

}

double point::get_x() const
{
    return x;
}

double point::get_y() const
{
    return y;
}

int point::int_x() const
{
    return static_cast<int>(x + 0.5);
}

int point::int_y() const
{
    return static_cast<int>(y + 0.5);
}

double point::dist(const point& that) const
{
    return sqrt(pow(x - that.x, 2) + pow(y - that.y, 2));
}

double point::dir(const point& that) const
{
    return atan2(that.y - y, that.x - x);
}

void point::shift(double dx, double dy)
{
    x += dx;
    y += dy;
}
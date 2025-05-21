#pragma once
#include <memory>

#include "base_line.h"
#include "point.h"

class line2 : public base_line
{
public:
    line2(const point& that_p1, const point& that_p2);

    double get_x() const ;
    double get_y() const ;
    double end_x() const ;
    double end_y() const ;

    double length() const override;
    double slope()  const override;

    void shift(double dx, double dy) override;
    void rotate(double da) ;

private:
    std::shared_ptr<point> start, end;
};


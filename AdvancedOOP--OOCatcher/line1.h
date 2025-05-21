#pragma once
#include "base_line.h"
#include <memory>


class line1 : public base_line
{
public:
    line1(const point& that_p1, const point& that_p2);

    [[nodiscard]] double get_x() const ;
    [[nodiscard]] double get_y() const ;
    [[nodiscard]] double end_x() const ;
    [[nodiscard]] double end_y() const ;

    [[nodiscard]] double length() const override;
    [[nodiscard]] double slope()  const override;

    void shift(double dx, double dy) override;

    virtual void rotate(double da);

private:
    std::shared_ptr<point> start;
    double len, ang;
};


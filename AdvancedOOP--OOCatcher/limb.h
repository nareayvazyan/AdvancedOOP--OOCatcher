#pragma once
#include "line1.h"

class limb : public line1 {
public:
    limb(const point& start, const point& end, double minAng, double maxAng);
    void rotate(double deltaAng) override;

private:
    double min_angle;
    double max_angle;
};

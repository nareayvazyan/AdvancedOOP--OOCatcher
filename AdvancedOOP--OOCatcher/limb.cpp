#include "limb.h"
#include <algorithm> // for std::min and std::max

limb::limb(const point& start, const point& end, double minAng, double maxAng)
    : line1(start, end), min_angle(minAng), max_angle(maxAng) {}

void limb::rotate(double deltaAng) {
    double current = slope();
    double proposed = current + deltaAng;
    double clamped = std::min(std::max(proposed, min_angle), max_angle);
    double actual_delta = clamped - current;
    line1::rotate(actual_delta);
}

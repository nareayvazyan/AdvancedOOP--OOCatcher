#pragma once

#include "line1.h"
#include "line2.h"
#include "point.h"
#include <vector>
#include <memory>

class body {
public:
    body(double ground_left_x, double ground_right_x, double ground_y);

    void update_structure();
    void update_fingers_and_toes();
    void shift_body(double dx, double dy);
    bool can_grab(const point& obj, double radius) const;
    void animate_throw();
    void animate_catch();

    std::vector<std::unique_ptr<base_line>> limbs;
    std::vector<std::unique_ptr<line1>> fingers;
    std::vector<std::unique_ptr<line1>> toes;

    point footL, footR;
    point hip;
    point neck_base, neck_top;
    point head_center; // aligned with neck-arm intersection

    point ball;
};

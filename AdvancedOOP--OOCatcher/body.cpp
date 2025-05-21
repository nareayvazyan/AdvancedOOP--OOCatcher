#include "body.h"
#include <cmath>
#include "config.h"

using namespace std;

body::body(double ground_left_x, double ground_right_x, double ground_y) {
    footL = point(ground_left_x, ground_y);
    footR = point(ground_right_x, ground_y);
    hip = point((footL.get_x() + footR.get_x()) / 2, ground_y + 0.30 * screenHeight / scale); // Taller body
    update_structure();
    update_fingers_and_toes();
    ball = point(neck_top.get_x() + 5, neck_top.get_y() + 2); // Initial ball position
}

void body::update_structure() {
    limbs.clear();

    // Legs to hip
    limbs.push_back(make_unique<line2>(footL, hip));
    limbs.push_back(make_unique<line2>(footR, hip));

    // Neck (longer)
    neck_base = hip;
    neck_top = point(hip.get_x(), hip.get_y() + 0.28 * screenHeight / scale);  // Increased from 0.20
    limbs.push_back(make_unique<line2>(neck_base, neck_top));

    // Arms from neck_top (longer)
    double arm_len = 0.35 * screenWidth / scale;  // Increased from 0.25
    point left_arm_end(neck_top.get_x() - arm_len, neck_top.get_y() + 0.1 * arm_len);
    point right_arm_end(neck_top.get_x() + arm_len, neck_top.get_y() + 0.1 * arm_len);
    limbs.push_back(make_unique<line2>(neck_top, left_arm_end));
    limbs.push_back(make_unique<line2>(neck_top, right_arm_end));

    // Head center shifted up by larger radius
    float head_radius_sim = 32.0f / scale;  // Larger head (was 22)
    head_center = point(neck_top.get_x(), neck_top.get_y() + head_radius_sim);
}

void body::update_fingers_and_toes() {
    fingers.clear();
    toes.clear();

    // Shorter fingers
    double finger_len = 0.03 * screenWidth / scale;
    for (int i = 3; i <= 4; ++i) {
        auto& arm = limbs[i];
        double angle = arm->slope();
        point base(arm->end_x(), arm->end_y());
        for (int j = -1; j <= 1; ++j) {
            double offset = j * 0.2;
            fingers.push_back(make_unique<line1>(
                base,
                point(base.get_x() + finger_len * cos(angle + offset),
                      base.get_y() + finger_len * sin(angle + offset))
            ));
        }
    }

    // Toes same length
    double toe_len = 0.05 * screenWidth / scale;
    for (int i = 0; i <= 1; ++i) {
        auto& leg = limbs[i];
        double angle = leg->slope();
        point base(leg->get_x(), leg->get_y());
        for (int j : {-1, 1}) {
            double offset = j * 0.25;
            toes.push_back(make_unique<line1>(
                base,
                point(base.get_x() + toe_len * cos(angle + offset),
                      base.get_y() + toe_len * sin(angle + offset))
            ));
        }
    }
}

void body::shift_body(double dx, double dy) {
    footL.shift(dx, dy);
    footR.shift(dx, dy);
    hip.shift(dx, dy);
    neck_base.shift(dx, dy);
    neck_top.shift(dx, dy);
    head_center.shift(dx, dy);
    ball.shift(dx, dy);

    for (auto& limb : limbs) limb->shift(dx, dy);
    for (auto& f : fingers) f->shift(dx, dy);
    for (auto& t : toes) t->shift(dx, dy);
}

bool body::can_grab(const point& obj, double radius) const {
    int contact = 0;
    for (const auto& f : fingers) {
        double dx = f->end_x() - obj.get_x();
        double dy = f->end_y() - obj.get_y();
        if (sqrt(dx * dx + dy * dy) <= radius) contact++;
    }
    return contact >= 3;
}

void body::animate_throw() {
    double angle = limbs[4]->slope(); // Right arm
    double vx = 0.5 * cos(angle);
    double vy = 0.5 * sin(angle);
    ball = point(ball.get_x() + vx, ball.get_y() + vy);
}

void body::animate_catch() {
    double tx = limbs[4]->end_x();
    double ty = limbs[4]->end_y();
    double dx = tx - ball.get_x();
    double dy = ty - ball.get_y();
    ball = point(ball.get_x() + dx * 0.05, ball.get_y() + dy * 0.05);
}

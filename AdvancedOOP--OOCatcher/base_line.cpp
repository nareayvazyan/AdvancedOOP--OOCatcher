#include "base_line.h"

int base_line::int_x() const
{
    return static_cast<int>(get_x() + 0.5);
}

int base_line::int_y() const
{
    return static_cast<int>(get_y() + 0.5);
}

int base_line::ent_x() const
{
    return static_cast<int>(end_x() + 0.5);
}

int base_line::ent_y() const
{
    return static_cast<int>(end_y() + 0.5);
}
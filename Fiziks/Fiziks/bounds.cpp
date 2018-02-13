#include "bounds.h"



bounds::bounds()
{
}


bounds::~bounds()
{
}

bool bounds::contains(bounds* bound)
{
    return (m_x < bound->get_x() &&
            m_y < bound->get_y() &&
            m_x + m_width > bound->get_x() + bound->get_width() &&
            m_y + m_height > bound->get_y() + bound->get_height());
}

/*
Getters for x, y, width, and height.
*/
int bounds::get_x() { return m_x; }
int bounds::get_y() { return m_y; }
int bounds::get_width() { return m_width; }
int bounds::get_height() { return m_height; }
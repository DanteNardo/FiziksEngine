#include "bounds.h"

aa_bounds::aa_bounds()
{

}

aa_bounds::bounds(v2f pos, int width, int height)
{

}

aa_bounds::~aa_bounds()
{
}

bool aa_bounds::contains(aa_bounds* bound)
{
    return (m_pos.x < bound->get_pos().x &&
            m_pos.y < bound->get_pos().y &&
            m_pos.x + m_width > bound->get_pos().x + bound->get_width() &&
            m_pos.y + m_height > bound->get_pos().y + bound->get_height());
}

aa_bounds aa_bounds::top_left()
{
    return aa_bounds(v2f(0, 0), m_width/2, m_height/2);
}

aa_bounds aa_bounds::top_right()
{
    return aa_bounds(v2f(m_width/2, 0), m_width/2, m_height/2);
}

aa_bounds aa_bounds::bottom_left()
{
    return aa_bounds(v2f(0, m_height/2), m_width/2, m_height/2);
}

aa_bounds aa_bounds::bottom_right()
{
    return aa_bounds(v2f(m_width/2, m_height/2), m_width/2, m_height/2);
}

/*
Getters for x, y, width, and height.
*/
v2f aa_bounds::get_pos() { return m_pos; }
int aa_bounds::get_width() { return m_width; }
int aa_bounds::get_height() { return m_height; }
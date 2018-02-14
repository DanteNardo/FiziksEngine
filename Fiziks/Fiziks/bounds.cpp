#include "bounds.h"

bounds::bounds()
{

}

bounds::bounds(v2f pos, int width, int height)
{

}

bounds::~bounds()
{
}

bool bounds::contains(bounds* bound)
{
    return (m_pos.x < bound->get_pos().x &&
            m_pos.y < bound->get_pos().y &&
            m_pos.x + m_width > bound->get_pos().x + bound->get_width() &&
            m_pos.y + m_height > bound->get_pos().y + bound->get_height());
}

bounds bounds::top_left()
{
    return bounds(v2f(0, 0), m_width/2, m_height/2);
}

bounds bounds::top_right()
{
    return bounds(v2f(m_width/2, 0), m_width/2, m_height/2);
}

bounds bounds::bottom_left()
{
    return bounds(v2f(0, m_height/2), m_width/2, m_height/2);
}

bounds bounds::bottom_right()
{
    return bounds(v2f(m_width/2, m_height/2), m_width/2, m_height/2);
}

/*
Getters for x, y, width, and height.
*/
v2f bounds::get_pos() { return m_pos; }
int bounds::get_width() { return m_width; }
int bounds::get_height() { return m_height; }
// -----------------------------------------------------------------------------
// Point.cpp                                                           Point.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref Point class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-28
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "Point.h"


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// -----
// Point
// -----
/*
 *
 */
Point::Point(int x, int y, bool active, unsigned number)
: m_x(x),
  m_y(y),
  m_active(active),
  m_number(number)
{
  // nothing yet
}


// -----------------------------------------------------------------------------
// Setter methods                                                 Setter methods
// -----------------------------------------------------------------------------

// ----
// setX
// ----
/*
 *
 */
void Point::setX(int x)
{
  m_x = x;
}

// ----
// setY
// ----
/*
 *
 */
void Point::setY(int y)
{
  m_y = y;
}

// ---------
// setActive
// ---------
/*
 *
 */
void Point::setActive(bool flag)
{
  m_active = flag;
}

// ---------
// setNumber
// ---------
/*
 *
 */
void Point::setNumber(unsigned number)
{
  m_number = number;
}


// -----------------------------------------------------------------------------
// Getter methods                                                 Getter methods
// -----------------------------------------------------------------------------

// ----
// getX
// ----
/*
 *
 */
int Point::getX() const
{
  return m_x;
}

// ----
// getY
// ----
/*
 *
 */
int Point::getY() const
{
  return m_y;
}

// --------
// isActive
// --------
/*
 *
 */
bool Point::isActive() const
{
  return m_active;
}

// ---------
// getNumber
// ---------
/*
 *
 */
unsigned Point::getNumber() const
{
  return m_number;
}

// -----------------------------------------------------------------------------
// Operator methods                                             Operator methods
// -----------------------------------------------------------------------------

// ---------
// operator<
// ---------
/*
 *
 */
bool Point::operator<(const Point& cmp) const
{
  // compare numbers
  return (m_number < cmp.m_number);
}


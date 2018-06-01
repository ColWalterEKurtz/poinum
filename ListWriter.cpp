// -----------------------------------------------------------------------------
// ListWriter.cpp                                                 ListWriter.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref ListWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-06-01
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include "message.h"
#include "ListWriter.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ----------
// ListWriter
// ----------
/*
 *
 */
ListWriter::ListWriter()
: m_imageWidth(0),
  m_imageHeight(0)
{
  // nothing yet
}


// -----------------------------------------------------------------------------
// Callback handler                                             Callback handler 
// -----------------------------------------------------------------------------

// --------------
// OnBeginParsing
// --------------
/*
 *
 */
void ListWriter::OnBeginParsing(const std::string& filename)
{
  // reset list of points
  m_points.clear();

  // reset image size
  m_imageWidth = 0;
  m_imageHeight = 0;
}

// ------------
// OnEndParsing
// ------------
/*
 *
 */
void ListWriter::OnEndParsing(bool healthy)
{
  // check parser's final state
  if (!healthy)
  {
    // do nothing if parser got stuck
    return;
  }

  // always start with image size
  writeLine( m_imageWidth, m_imageHeight, false, 0 );

  // write all extracted points
  for(unsigned i = 0; i < m_points.size() ; i++)
  {
    // get abbreviation
    const Point& p = m_points[i];

    // write formatted line
    writeLine( p.getX(), p.getY(), p.isActive(), p.getNumber() );
  }

  // reset list of points
  m_points.clear();
}

// ------
// OnSize
// ------
/*
 *
 */
void ListWriter::OnSize(int width, int height)
{
  // set image size
  m_imageWidth = width;
  m_imageHeight = height;
}

// -------
// OnPoint
// -------
/*
 *
 */
void ListWriter::OnPoint(int x, int y, bool active, int number)
{
  // add new point
  m_points.push_back( Point(x, y, active, number) );
}

// -------
// OnError
// -------
/*
 *
 */
void ListWriter::OnError(const std::string& message)
{
  msg::err(message);
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// ---------
// writeLine
// ---------
/*
 *
 */
void ListWriter::writeLine(int x, int y, bool active, unsigned number) const
{
  // write formatted line
  cout << setfill(' ')
       << setw(5) << right << x
       << " "
       << setw(5) << right << y
       << " "
       << (active ? "+" : "-")
       << " "
       << setw(4) << right << number
       << endl;
}


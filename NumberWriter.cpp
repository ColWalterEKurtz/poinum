// -----------------------------------------------------------------------------
// NumberWriter.cpp                                             NumberWriter.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref NumberWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include "message.h"
#include "SvgCodeGen.h"
#include "NumberWriter.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ------------
// NumberWriter
// ------------
/*
 *
 */
NumberWriter::NumberWriter()
{
  // set initial values
  m_radius      = 16;
  m_strokeWidth = 3;
  m_fontSize    = 18;
  m_imageWidth  = 0;
  m_imageHeight = 0;
}


// -----------------------------------------------------------------------------
// Setter methods                                                 Setter methods
// -----------------------------------------------------------------------------

// ---------
// setRadius
// ---------
/*
 *
 */
void NumberWriter::setRadius(int r)
{
  m_radius = r;
}

// --------------
// setStrokeWidth
// --------------
/*
 *
 */
void NumberWriter::setStrokeWidth(int w)
{
  m_strokeWidth = w;
}

// -----------
// setFontSize
// -----------
/*
 *
 */
void NumberWriter::setFontSize(int f)
{
  m_fontSize = f;
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
void NumberWriter::OnBeginParsing(const std::string& filename)
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
void NumberWriter::OnEndParsing(bool healthy)
{
  // check parser's final state
  if (!healthy)
  {
    // do nothing if parser got stuck
    return;
  }

  // start svg file
  cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  cout << "<svg xmlns=\"http://www.w3.org/2000/svg\"" << endl;
  cout << "     version=\"1.1\"" << endl;
  cout << "     baseProfile=\"full\"" << endl;
  cout << "     width=\"" << m_imageWidth << "px\"" << endl;
  cout << "     height=\"" << m_imageHeight << "px\"" << endl;
  cout << "     viewBox=\"0 0 " << m_imageWidth << " " << m_imageHeight << "\">" << endl;

  SvgCodeGen gen;

  // draw all points
  for(unsigned i = 0; i < m_points.size(); i++)
  {
    // get abbreviation
    const Point& p = m_points[i];
  
    // create svg code
    cout << gen.number( p.getX(),
                        p.getY(),
                        p.isActive(),
                        p.getNumber(),
                        m_radius,
                        m_strokeWidth,
                        m_fontSize,
                        false );
  }

  // finish svg file
  cout << "</svg>" << endl;

  // reset list of points
  m_points.clear();
}

// ------
// OnSize
// ------
/*
 *
 */
void NumberWriter::OnSize(int width, int height)
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
void NumberWriter::OnPoint(int x, int y, bool active, int number)
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
void NumberWriter::OnError(const std::string& message)
{
  msg::err(message);
}


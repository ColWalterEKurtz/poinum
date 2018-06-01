// -----------------------------------------------------------------------------
// CrossWriter.cpp                                               CrossWriter.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref CrossWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-29
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include "message.h"
#include "SvgCodeGen.h"
#include "CrossWriter.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// -----------
// CrossWriter
// -----------
/*
 *
 */
CrossWriter::CrossWriter()
: m_imageWidth(0),
  m_imageHeight(0)
{
  // nothing yet
}


// --------------
// OnBeginParsing
// --------------
/*
 *
 */
void CrossWriter::OnBeginParsing(const std::string& filename)
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
void CrossWriter::OnEndParsing(bool healthy)
{
  // check parser's final state
  if (!healthy)
  {
    // do nothing if parser got stuck
    return;
  }

  // use this class to generate the svg commands
  SvgCodeGen gen;

  // start svg file
  cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  cout << "<svg xmlns=\"http://www.w3.org/2000/svg\"" << endl;
  cout << "     version=\"1.1\"" << endl;
  cout << "     baseProfile=\"full\"" << endl;
  cout << "     width=\"" << m_imageWidth << "px\"" << endl;
  cout << "     height=\"" << m_imageHeight << "px\"" << endl;
  cout << "     viewBox=\"0 0 " << m_imageWidth << " " << m_imageHeight << "\">" << endl;

  // draw all black parts of the extracted points first
  for(unsigned i = 0; i < m_points.size() ; i++)
  {
    // write svg commands to stdout
    cout << gen.cross(m_points[i].getX(),
                      m_points[i].getY(),
                      m_points[i].isActive(),
                      m_points[i].getNumber(),
                      false, 0);
  }

  // draw all white parts of the extracted points afterwards
  for(unsigned i = 0; i < m_points.size() ; i++)
  {
    // write svg commands to stdout
    cout << gen.cross(m_points[i].getX(),
                      m_points[i].getY(),
                      m_points[i].isActive(),
                      m_points[i].getNumber(),
                      false, 1);
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
void CrossWriter::OnSize(int width, int height)
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
void CrossWriter::OnPoint(int x, int y, bool active, int number)
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
void CrossWriter::OnError(const std::string& message)
{
  msg::err(message);
}


// -----------------------------------------------------------------------------
// MapWriter.cpp                                                   MapWriter.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref MapWriter class.
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
#include "MapWriter.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ---------
// MapWriter
// ---------
/*
 *
 */
MapWriter::MapWriter()
{
  // set initial values
  m_radius = 10;
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
void MapWriter::setRadius(int r)
{
  // update radius
  m_radius = r;
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
void MapWriter::OnBeginParsing(const std::string& filename)
{
  // reset list of points
  m_points.clear();

  // update name of the map
  m_mapName = simplify(filename);
}

// ------------
// OnEndParsing
// ------------
/*
 *
 */
void MapWriter::OnEndParsing(bool healthy)
{
  // check parser's final state
  if (!healthy)
  {
    // do nothing if parser got stuck
    return;
  }

  // start map 
  cout << "<map name=\"" << m_mapName << "\">" << endl;

  // write all extracted points
  for(unsigned i = 0; i < m_points.size() ; i++)
  {
    // get abbreviation
    const Point& p = m_points[i];

    int x = p.getX();
    int y = p.getY();
    int n = p.getNumber();

    cout << setfill('0')
         << "<area"
         << " alt=\"" << setw(3) << n << "\""
         << " title=\"(" << x << "," << y << ")" << "\""
         << " href=\"#" << m_mapName << setw(3) << n << "\""
         << " shape=\"circle\""
         << " coords=\"" << x << "," << y << "," << m_radius << "\" />"
         << endl;
  }

  // close map
  cout << "</map>" << endl;

  // reset list of points
  m_points.clear();
}

// ------
// OnSize
// ------
/*
 *
 */
void MapWriter::OnSize(int width, int height)
{
  // nothing yet
}

// -------
// OnPoint
// -------
/*
 *
 */
void MapWriter::OnPoint(int x, int y, bool active, int number)
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
void MapWriter::OnError(const std::string& message)
{
  msg::err(message);
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// --------
// simplify
// --------
/*
 *
 */
string MapWriter::simplify(const string& filename) const
{
  // the final ID
  string id;

  // copy characters from given filename
  for(string::size_type i = 0; i < filename.size(); i++)
  {
    // current character
    char c = filename[i];

    // directory separator found
    if (c == '/')
    {
      // reset id
      id = "";
    }

    // capital letters
    else if ((c >= 'A') && (c <= 'Z'))
    {
      id += c;
    }

    // small letters
    else if ((c >= 'a') && (c <= 'z'))
    {
      id += c;
    }

    // digits
    else if ((c >= '0') && (c <= '9'))
    {
      id += c;
    }

    // white space
    else if ((c == 32) || (c == 9) || (c == 10) || (c == 13))
    {
      id += '_';
    }
  }

  return id;
}


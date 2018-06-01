// -----------------------------------------------------------------------------
// SvgCodeGen.cpp                                                 SvgCodeGen.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref SvgCodeGen class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "message.h"
#include "SvgCodeGen.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ----------
// SvgCodeGen
// ----------
/*
 *
 */
SvgCodeGen::SvgCodeGen()
{
  // nothing yet
}


// -----------------------------------------------------------------------------
// Handling                                                             Handling
// -----------------------------------------------------------------------------

// -----
// cross
// -----
/*
 *
 */
string SvgCodeGen::cross(int x, int y, bool a, unsigned n, bool file, int parts)
{
  // reset stream
  m_encoder.clear();
  m_encoder.str( string() );

  // check if white parts are to be drawn
  if (parts != 0)
  {
    // check 10 bit limit
    if (n > 1023)
    {
      // notify user
      msg::wrn("number too large to encode");

      // reset number
      n = 0;
    }
  }

  // create entire file
  if (file)
  {
    // start svg file
    m_encoder << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    m_encoder << "<svg xmlns=\"http://www.w3.org/2000/svg\"" << endl;
    m_encoder << "     version=\"1.1\"" << endl;
    m_encoder << "     baseProfile=\"full\"" << endl;
    m_encoder << "     width=\"95px\"" << endl;
    m_encoder << "     height=\"63px\"" << endl;
    m_encoder << "     viewBox=\"-47 -31 95 63\">" << endl;

    // create one cross at (0, 0)
    startCross(0, 0, a, n, parts);

    // check if white parts are to be drawn
    if (parts != 0)
    {
      encodeFlag(a);
      encodeNumber(n);
    }

    finishCross();

    // finish svg file
    m_encoder << "</svg>" << endl;
  }

  // create svg code as part of larger files
  else
  {
    // create cross with given attributes
    startCross(x, y, a, n, parts);

    // check if white parts are to be drawn
    if (parts != 0)
    {
      encodeFlag(a);
      encodeNumber(n);
    }

    finishCross();
  }

  // return commands as one single string
  return m_encoder.str();
}

// ------
// number
// ------
/*
 *
 */
string SvgCodeGen::number( int      x,
                           int      y,
                           bool     a,
                           unsigned n,
                           int      r,
                           int      s,
                           int      f,
                           bool     file )
{
  // reset stream
  m_encoder.clear();
  m_encoder.str( string() );

  // create entire file
  if (file)
  {
    // calculate image size
    int filew = 2 * r + s;
    int fileh = 2 * r + s;

    // get even numbers
    filew += (filew & 1);
    fileh += (fileh & 1);

    // start svg file
    m_encoder << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    m_encoder << "<svg xmlns=\"http://www.w3.org/2000/svg\"" << endl;
    m_encoder << "     version=\"1.1\"" << endl;
    m_encoder << "     baseProfile=\"full\"" << endl;
    m_encoder << "     width=\"" << filew << "px\"" << endl;
    m_encoder << "     height=\"" << fileh << "px\"" << endl;
    m_encoder << "     viewBox=\"-" << (filew / 2) << " -" << (fileh / 2) << " " << filew << " " << fileh << "\">" << endl;

    // print number
    printNumber(0, 0, a, n, r, s, f);

    // finish svg file
    m_encoder << "</svg>" << endl;
  }

  // create svg code as part of larger files
  else
  {
    // print number
    printNumber(x, y, a, n, r, s, f);
  }

  // return commands as one single string
  return m_encoder.str();
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// ----------
// startCross
// ----------
/*
 *
 */
void SvgCodeGen::startCross(int x, int y, bool a, int n, int parts)
{
  // open group
  m_encoder << "<g transform=\"translate(" << x << ", " << y << ")\">" << endl;

  // write comment
  m_encoder << "  <!-- "
            << (a ? "active" : "inactive")
            << " point number " << n
            << " at (" << x << ", " << y << ")";

  // add color note (black parts)
  if (parts == 0)
  {
    m_encoder << " (black parts only)";
  }

  // add color note (white parts)
  else if (parts == 1)
  {
    m_encoder << " (white parts only)";
  }

  // close comment
  m_encoder << " -->" << endl;

  // check if black parts are to be drawn
  if (parts != 1)
  {
    // draw cross
    m_encoder << "  <rect x=\"-47\" y=\"0\"   width=\"95\" height=\"1\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"0\"   y=\"-31\" width=\"1\"  height=\"63\" fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"-2\"  y=\"-31\" width=\"5\"  height=\"5\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"43\"  y=\"-2\"  width=\"5\"  height=\"5\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"-2\"  y=\"27\"  width=\"5\"  height=\"5\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"-47\" y=\"-2\"  width=\"5\"  height=\"5\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"-23\" y=\"-16\" width=\"47\" height=\"1\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"-23\" y=\"16\"  width=\"47\" height=\"1\"  fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"-24\" y=\"-16\" width=\"1\"  height=\"33\" fill=\"black\" stroke=\"none\" />" << endl;
    m_encoder << "  <rect x=\"24\"  y=\"-16\" width=\"1\"  height=\"33\" fill=\"black\" stroke=\"none\" />" << endl;
  }

  // check if white parts are to be drawn
  if (parts != 0)
  {
    // draw center
    m_encoder << "  <rect x=\"0\"   y=\"0\"   width=\"1\"  height=\"1\"  fill=\"white\" stroke=\"none\" />" << endl;
  }
}

// ----------
// encodeFlag
// ----------
/*
 *
 */
void SvgCodeGen::encodeFlag(bool a)
{
  // check flag
  if (a)
  {
    // create a white pixel (assume all current pixels are black)
    m_encoder << "  <rect x=\"1\""
              << "   y=\"0\""
              << "   width=\"1\""
              << "  height=\"1\""
              << "  fill=\"white\""
              << " stroke=\"none\" />" << endl;
  }
}

// ------------
// encodeNumber
// ------------
/*
 *
 */
void SvgCodeGen::encodeNumber(int n)
{
  // number of bits to encode
  static const int digits = 10;

  // check limits (don't encode 0)
  if ( (n < 1) || (n > ((1 << digits) - 1)) )
  {
    // don't encode this number
    return;
  }

  // encode these bits
  for (int i = 0; i < digits; i++)
  {
    // set exactly one bit
    int flag = (1 << i);

    // check if this bit is set
    if (n & flag)
    {
      // the pixel's x-coordinate
      int x = digits - i;

      // set maximum separator
      string sep("   ");

      // set smaller separator
      if ((x + 1) > 9)
      {
        sep = "  ";
      }

      // create a white pixel (all current pixels are black)
      // first fixel is used as active flag
      m_encoder << "  <rect x=\"" << (x + 1) << "\""
                << sep << "y=\"0\""
                << "   width=\"1\""
                << "  height=\"1\""
                << "  fill=\"white\""
                << " stroke=\"none\" />" << endl;
    }
  }
}

// -----------
// finishCross
// -----------
/*
 *
 */
void SvgCodeGen::finishCross()
{
  // close group
  m_encoder << "</g>" << endl;
}

// -----------
// printNumber
// -----------
/*
 *
 */
void SvgCodeGen::printNumber( int      x,
                              int      y,
                              bool     a,
                              unsigned n,
                              int      r,
                              int      s,
                              int      f )
{
  // set default colors
  const string bg = (a ? "white" : "black");
  const string fg = (a ? "black" : "white");

  // fill background
  m_encoder << "<circle"
            << " cx=\"" << x << "\""
            << " cy=\"" << y << "\""
            << " r=\"" << r << "\""
            << " fill=\"" << bg << "\""
            << " opacity=\"0.5\""
            << " stroke=\"none\""
            << " />" << endl;

  // draw stroke
  m_encoder << "<circle"
            << " cx=\"" << x << "\""
            << " cy=\"" << y << "\""
            << " r=\"" << r << "\""
            << " fill=\"none\""
            << " stroke=\"black\""
            << " stroke-width=\"" << s << "\""
            << " />" << endl;

  // print number
  m_encoder << "<text"
            << " x=\"" << x << "\""
            << " y=\"" << y << "\""
            << " dy=\"0.3333em\""
            << " fill=\"" << fg << "\""
            << " font-size=\"" << f << "\""
            << " font-weight=\"250\""
            << " font-family=\"Ubuntu\""
            << " text-anchor=\"middle\">"
            << n
            << "</text>"
            << endl;
}


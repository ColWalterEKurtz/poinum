// -----------------------------------------------------------------------------
// P1Parser.cpp                                                     P1Parser.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref P1Parser class.
 * @author     Achim Klein
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <sstream>
#include <fstream>
#include "PointHandler.h"
#include "P1Parser.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// --------
// P1Parser
// --------
/*
 *
 */
P1Parser::P1Parser()
: m_numBits(10)
{
  // nothing yet
}


// -----------------------------------------------------------------------------
// Handling                                                             Handling
// -----------------------------------------------------------------------------

// -----
// parse
// -----
/*
 *
 */
bool P1Parser::parse(const string& filename, bool initialize)
{
  // check if handler is missing
  if (m_handler == 0)
  {
    // signalize trouble
    return false;
  }

  // send message
  m_handler->OnBeginParsing(filename);

  // open file for reading
  ifstream ifile( filename.c_str() );

  // check if file is open
  if ( !ifile.is_open() )
  {
    // notify user
    m_handler->OnError("unable to open file");

    // send message
    m_handler->OnEndParsing(false);

    // signalize trouble
    return false;
  }

  // the parser's current state
  enum States
  {
    CORRUPTED,
    READ_MAGICAL_NUMBER,
    FIND_WIDTH,
    READ_WIDTH,
    FIND_HEIGHT,
    READ_HEIGHT,
    FIND_PIXELS,
    READ_PIXELS,
    READ_FLAG,
    READ_NUMBER,
    SKIP_COMMENT,
    FINISHED
  }
  state = READ_MAGICAL_NUMBER;

  // the parser's last state
  States stack = CORRUPTED;

  // use this number if points are to be initialized
  unsigned serialNumber = 0;

  // current image coordinates
  int row = 0;
  int col = 0;

  // buffered data
  string buffer = "";

  // image information
  int width  = 0;
  int height = 0;

  // point information
  int  x = 0;
  int  y = 0;
  bool a = true;
  int  n = 0;

  // one byte from the file
  char c = 0;

  // read bytes from pbm file
  while ( ifile.get(c) )
  {
    // final state
    if ( (state == CORRUPTED) || (state == FINISHED) )
    {
      // stop parsing
      break;
    }

    // comment found
    else if (c == '#')
    {
      // any file has to start with its magical number
      if (state == READ_MAGICAL_NUMBER)
      {
        // notify user
        m_handler->OnError("file does not start with the magical number");

        // set final state
        state = CORRUPTED;
      }

      // don't skip comments twice
      else if (state != SKIP_COMMENT)
      {
        // return to this state
        stack = state;

        // set next state
        state = SKIP_COMMENT;
      }
    }

    // READ_MAGICAL_NUMBER
    else if (state == READ_MAGICAL_NUMBER)
    {
      // valid character found
      if ( ismagic(c) )
      {
        // append character
        buffer += c;

        // check size
        if (buffer.size() > 2)
        {
          // notify user
          m_handler->OnError("magical number is too long");

          // set final state
          state = CORRUPTED;
        }
      }

      // space character found
      else if ( isspace(c) )
      {
        // check type
        if (buffer == "P1")
        {
          // reset buffer
          buffer = "";

          // set next state
          state = FIND_WIDTH;
        }

        // invalid type
        else
        {
          // notify user
          m_handler->OnError("type must be P1");

          // set final state
          state = CORRUPTED;
        }
      }

      // invalid character found
      else
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // FIND_WIDTH
    else if (state == FIND_WIDTH)
    {
      // significant digit found
      if ( isnatural(c) )
      {
        // buffer this character
        buffer = c;

        // set next state
        state = READ_WIDTH;
      }

      // invalid character found
      else if ( !isspace(c) )
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // READ_WIDTH
    else if (state == READ_WIDTH)
    {
      // digit found
      if ( isdigit(c) )
      {
        // append character
        buffer += c;

        // image too large
        if (buffer.size() > 5)
        {
          // notify user
          m_handler->OnError("image is too wide");

          // set final state
          state = CORRUPTED;
        }
      }

      // space character found
      else if ( isspace(c) )
      {
        // try to convert string to int
        if (stringstream(buffer) >> width)
        {
          // invalid width
          if (width < 1)
          {
            // notify user
            m_handler->OnError("invalid width");

            // set final state
            state = CORRUPTED;
          }

          else
          {
            // reset buffer
            buffer = "";

            // set next state
            state = FIND_HEIGHT;
          }
        }

        // conversion failed
        else
        {
          // notify user
          m_handler->OnError("integer conversion failed");

          // set final state
          state = CORRUPTED;
        }
      }

      // invalid character found
      else
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // FIND_HEIGHT
    else if (state == FIND_HEIGHT)
    {
      // significant digit found
      if ( isnatural(c) )
      {
        // buffer this character
        buffer = c;

        // set next state
        state = READ_HEIGHT;
      }

      // invalid character found
      else if ( !isspace(c) )
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // READ_HEIGHT
    else if (state == READ_HEIGHT)
    {
      // digit found
      if ( isdigit(c) )
      {
        // append character
        buffer += c;

        // image too large
        if (buffer.size() > 5)
        {
          // notify user
          m_handler->OnError("image is too high");

          // set final state
          state = CORRUPTED;
        }
      }

      // space character found
      else if ( isspace(c) )
      {
        // try to convert string to int
        if (stringstream(buffer) >> height)
        {
          // invalid height
          if (height < 1)
          {
            // notify user
            m_handler->OnError("invalid height");

            // set final state
            state = CORRUPTED;
          }

          else
          {
            // send message
            m_handler->OnSize(width, height);

            // reset buffer
            buffer = "";

            // set next state
            state = READ_PIXELS;
          }
        }

        // conversion failed
        else
        {
          // notify user
          m_handler->OnError("integer conversion failed");

          // set final state
          state = CORRUPTED;
        }
      }

      // invalid character found
      else
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // READ_PIXELS
    else if (state == READ_PIXELS)
    {
      // real data found
      if ( (c == '1') || (c == '0') )
      {
        // white pixel found
        if (c == '0')
        {
          // set point coordinates
          x = col;
          y = row;

          // set next state
          state = READ_FLAG;
        }

        // step column index
        col += 1;

        // row completed
        if (col == width)
        {
          // start next row
          col  = 0;
          row += 1;

          // image completed
          if (row == height)
          {
            // set final state
            state = FINISHED;
          }
        }
      }

      // invalid character found
      else if ( !isspace(c) )
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // READ_FLAG
    else if (state == READ_FLAG)
    {
      // valid data found
      if ( (c == '1') || (c == '0') )
      {
        // initialize points
        if (initialize)
        {
          // activate each point by default
          a = true;
        }

        else
        {
          // set active flag
          a = ((c == '0') ? true : false);
        }

        // next state
        state = READ_NUMBER;

        // step column index
        col += 1;

        // row completed
        if (col == width)
        {
          // start next row
          col  = 0;
          row += 1;

          // image completed
          if (row == height)
          {
            // notify user
            m_handler->OnError("unexpected end of file");

            // set final state
            state = CORRUPTED;
          }
        }
      }

      // invalid character found
      else if ( !isspace(c) )
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // READ_NUMBER
    else if (state == READ_NUMBER)
    {
      // valid data found
      if ( (c == '1') || (c == '0') )
      {
        // append character
        buffer += c;

        // number completed
        if (buffer.size() == m_numBits)
        {
          // initialize points
          if (initialize)
          {
            // step and use serial number
            n = ++serialNumber;
          }

          else
          {
            // decode number
            n = decode(buffer);
          }

          // send message
          m_handler->OnPoint(x, y, a, n);

          // reset buffer
          buffer = "";

          // back to this state
          state = READ_PIXELS;
        }

        // next column
        col += 1;

        // row completed
        if (col == width)
        {
          // start next row
          col  = 0;
          row += 1;

          // image completed ...
          if (row == height)
          {
            // ... but number not
            if (state == READ_NUMBER)
            {
              // notify user
              m_handler->OnError("unexpected end of file");

              // set final state
              state = CORRUPTED;
            }

            // ... and number as well
            else
            {
              // set final state
              state = FINISHED;
            }
          }
        }
      }

      // invalid character found
      else if ( !isspace(c) )
      {
        // notify user
        m_handler->OnError("invalid character found");

        // set final state
        state = CORRUPTED;
      }
    }

    // SKIP_COMMENT
    else if (state == SKIP_COMMENT)
    {
      // end of line character found
      if ( iseol(c) )
      {
        // back to previous state
        state = stack;
      }
    }
  }

  // close file
  ifile.close();

  // send message
  m_handler->OnEndParsing(state == FINISHED);

  // signalize success
  return (state == FINISHED);
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// -------
// ismagic
// -------
/*
 *
 */
bool P1Parser::ismagic(char c) const
{
  if (c == 'P') return true;
  if (c == '1') return true;
  if (c == '2') return true;
  if (c == '3') return true;
  if (c == '4') return true;
  if (c == '5') return true;
  if (c == '6') return true;
  if (c == '7') return true;

  return false;
}

// ------
// decode
// ------
/*
 *
 */
int P1Parser::decode(const string& base2ascii) const
{
  // get maximum number of binary digits
  static const unsigned maxdig = 4 * sizeof(int);

  // get number of binary digits
  unsigned digits = base2ascii.size();

  // number too large
  if (digits > maxdig)
  {
    return 0;
  }

  // initialize all bits with '0'
  int number = 0;

  // set '1' bits
  for (unsigned i = 0; i < digits; i++)
  {
    // let white pixels represent '1'
    if (base2ascii[digits - i - 1] == '0')
    {
      // set bit
      number |= (1 << i);
    }
  }

  // string to int
  return number;
}


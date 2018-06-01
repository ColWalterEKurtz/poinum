// -----------------------------------------------------------------------------
// ListParser.cpp                                                 ListParser.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref ListParser class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <sstream>
#include <fstream>
#include "PointHandler.h"
#include "ListParser.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ----------
// ListParser
// ----------
/*
 *
 */
ListParser::ListParser()
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
bool ListParser::parse(const string& filename, bool initialize)
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
    READ_WIDTH,
    READ_HEIGHT,
    READ_TRASH,
    READ_XCOORD,
    READ_YCOORD,
    READ_ACTIVE,
    READ_NUMBER,
    FINISHED,
    CORRUPTED
  }
  state = READ_WIDTH;

  // use this number if points are to be initialized
  unsigned serialNumber = 0;

  // image information
  int width  = 0;
  int height = 0;

  // point information
  int  x = 0;
  int  y = 0;
  bool a = true;
  int  n = 0;

  // buffered data
  string buffer = "";

  // read bytes from pbm file
  while (ifile)
  {
    // READ_WIDTH
    if (state == READ_WIDTH)
    {
      // read group of visible characters
      buffer = getToken(ifile);

      // try to convert string to int
      if (stringstream(buffer) >> width)
      {
        // next state
        state = READ_HEIGHT;
      }

      // unable to convert string to int
      else
      {
        // notify handler
        m_handler->OnError("invalid width found");

        // final state
        state = CORRUPTED;
      }
    }

    // READ_HEIGHT
    else if (state == READ_HEIGHT)
    {
      // read group of visible characters
      buffer = getToken(ifile);

      // try to convert string to int
      if (stringstream(buffer) >> height)
      {
        // next state
        state = READ_TRASH;
      }

      // unable to convert string to int
      else
      {
        // notify handler
        m_handler->OnError("invalid height found");

        // final state
        state = CORRUPTED;
      }
    }

    // READ_TRASH
    else if (state == READ_TRASH)
    {
      // read two more tokens
      buffer = getToken(ifile);
      buffer = getToken(ifile);

      // first line not finished
      if (buffer.empty())
      {
        // notify handler
        m_handler->OnError("first line not finished");

        // final state
        state = CORRUPTED;
      }

      else
      {
        // send size
        m_handler->OnSize(width, height);

        // next state
        state = READ_XCOORD;
      }
    }

    // READ_XCOORD
    else if (state == READ_XCOORD)
    {
      // read group of visible characters
      buffer = getToken(ifile);

      // no more tokens
      if (buffer.empty())
      {
        // final state
        state = FINISHED;
      }

      // try to convert string to int
      else if (stringstream(buffer) >> x)
      {
        // next state
        state = READ_YCOORD;
      }

      // unable to convert string to int
      else
      {
        // notify handler
        m_handler->OnError("invalid x-coordinate found");

        // final state
        state = CORRUPTED;
      }
    }

    // READ_YCOORD
    else if (state == READ_YCOORD)
    {
      // read group of visible characters
      buffer = getToken(ifile);

      // try to convert string to int
      if (stringstream(buffer) >> y)
      {
        // next state
        state = READ_ACTIVE;
      }

      // unable to convert string to int
      else
      {
        // notify handler
        m_handler->OnError("invalid y-coordinate found");

        // final state
        state = CORRUPTED;
      }
    }

    // READ_ACTIVE
    else if (state == READ_ACTIVE)
    {
      // read group of visible characters
      buffer = getToken(ifile);

      // check flag
      if ( (buffer == "+") || (buffer == "-") )
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
          a = ((buffer == "+") ? true : false);
        }

        // next state
        state = READ_NUMBER;
      }

      // unknown flag found
      else
      {
        // notify handler
        m_handler->OnError("invalid flag found");

        // final state
        state = CORRUPTED;
      }
    }

    // READ_NUMBER
    else if (state == READ_NUMBER)
    {
      // read group of visible characters
      buffer = getToken(ifile);

      // try to convert string to unsigned
      if (stringstream(buffer) >> n)
      {
        // initialize points
        if (initialize)
        {
          // step and use serial number
          n = ++serialNumber;
        }

        // send point
        m_handler->OnPoint(x, y, a, n);

        // next state
        state = READ_XCOORD;
      }

      // unable to convert string to int
      else
      {
        // notify handler
        m_handler->OnError("invalid number found");

        // final state
        state = CORRUPTED;
      }
    }

    // final state
    else if ( (state == FINISHED) || (state == CORRUPTED) )
    {
      // stop parsing
      break;
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

// --------
// getToken
// --------
/*
 *
 */
string ListParser::getToken(istream& source) const
{
  // maximum number of bytes per token
  const unsigned max = 5;

  // number of currently extracted bytes
  unsigned count = 0;

  // the parser's state
  enum
  {
    SKIP_SPACE,
    READ_TOKEN
  }
  state = SKIP_SPACE;

  // the extracted token
  string token;

  // one extracted byte from the stream
  char c;

  // get token from stream
  while ( source.get(c) )
  {
    // SKIP_SPACE
    if (state == SKIP_SPACE)
    {
      // invisible character found
      if ( isspace(c) )
      {
        // next cycle
        continue;
      }

      // visible character found
      else
      {
        // step counter
        count += 1;

        // append character
        token += c;

        // next state
        state = READ_TOKEN;
      }
    }

    // READ_TOKEN
    else if (state == READ_TOKEN)
    {
      // invisible character found
      if ( isspace(c) )
      {
        // stop reading characters
        break;
      }

      // visible character found
      else
      {
        // step counter
        count += 1;

        // assert maximum length
        if (count > max)
        {
          // notify handler
          m_handler->OnError("maximum token length exeeded");

          // stop reading characters
          break;
        }

        // append character
        token += c;
      }
    }
  }

  // return extracted token
  return token;
}


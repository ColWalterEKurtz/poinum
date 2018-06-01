// -----------------------------------------------------------------------------
// cli.cpp                                                               cli.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref cli class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <unistd.h>  /* getopt() */
#include <sstream>   /* optarg to string */
#include "message.h"
#include "cli.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ---
// cli
// ---
/*
 *
 */
cli::cli()
{
  // set inital state
  reset();
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
bool cli::parse(int argc, char** argv)
{
  // back to inital state
  reset();

  // this pointer must not be NULL
  if (argv == 0) return false;

  // this pointer must not be NULL
  if (argv[0] == 0) return false;

  // if the option takes an argument, optarg points to the option-argument
  extern char* optarg;

  // the index of the next element of the argv[] vector to be processed
  extern int optind;

  // optopt points to the option character that caused the error
  extern int optopt;

  // don't print error messages
  opterr = 0;

  // set executable's name
  m_argv0 = argv[0];

  // set valid option characters
  /*
   * h  show help
   * v  show version
   * g  create basic svg files
   * p  set input pbm file
   * l  set input list file
   * i  initialize points
   * c  create cross file
   * m  create map file
   * n  create number file
   * f  set font size
   * r  set radius
   * s  set stroke width
   */
  const char* optstring = ":hvgp:l:icmnf:r:s:";

  // the ASCII code of the current option character
  int optchar;

  // parse all given options
  while ((optchar = getopt(argc, argv, optstring)) != -1)
  {
    // use this object to convert arguments
    stringstream argstream((optarg == 0) ? "" : optarg);

    // analyze (short) options
    switch (optchar)
    {
      case 'h':

        // set operation
        operation = SHOW_HELP;

        // stop immediately
        return true;

      case 'v':

        // set operation
        operation = SHOW_VERSION;

        // stop immediately
        return true;

      case 'g':

        // update operation
        operation = CREATE_BASIC_SVG_FILES;

        // next argument
        break;

      case 'p':

        // set input filename and type
        inputFilename = argstream.str();
        readPbmFile   = true;
        readListFile  = false;

        // next argument
        break;

      case 'l':

        // set input filename and type
        inputFilename = argstream.str();
        readPbmFile   = false;
        readListFile  = true;

        // next argument
        break;

      case 'i':

        // set flag
        initializePoints = true;

        // next argument
        break;

      case 'c':

        // update operation
        operation = CREATE_CROSS_FILE;

        // next argument
        break;

      case 'm':

        // update operation
        operation = CREATE_MAP_FILE;

        // next argument
        break;

      case 'n':

        // update operation
        operation = CREATE_NUMBER_FILE;

        // next argument
        break;

      case 'f':

        // try to convert string to int
        if ( !(argstream >> fontSize) )
        {
          // notify user
          msg::err("invalid font size given");

          // signalize trouble
          return false;
        }

        // check minimum font size
        if (fontSize < 1)
        {
          // notify user
          msg::err("invalid font size given");

          // signalize trouble
          return false;
        }

        // next argument
        break;

      case 'r':

        // try to convert string to int
        if ( !(argstream >> radius) )
        {
          // notify user
          msg::err("invalid radius given");

          // signalize trouble
          return false;
        }

        // check minimum radius
        if (radius < 1)
        {
          // notify user
          msg::err("invalid radius given");

          // signalize trouble
          return false;
        }

        // next argument
        break;

      case 's':

        // try to convert string to int
        if ( !(argstream >> strokeWidth) )
        {
          // notify user
          msg::err("invalid stroke width given");

          // signalize trouble
          return false;
        }

        // check minimum stroke width
        if (strokeWidth < 0)
        {
          // notify user
          msg::err("invalid stroke width given");

          // signalize trouble
          return false;
        }

        // next argument
        break;

      case ':':

        // notify user
        msg::err( msg::cat("missing argument: -", int2alnum(optopt)) );

        // signalize trouble
        return false;

      case '?':

        // notify user
        msg::err( msg::cat("unknown option: -", int2alnum(optopt)) );

        // signalize trouble
        return false;
    }
  }

  // set all remaining positional parameters
  for(int i = optind; i < argc; i++)
  {
    pparams.push_back( argv[i] );
  }

  // signalize success
  return true;
}

// --------
// getXName
// --------
/*
 *
 */
string cli::getXName(bool brief) const
{
  // drop directories
  if (brief)
  {
    // filename without leading directories
    string nodir;

    // remove all directories
    for(string::size_type i = 0; i < m_argv0.size(); i++)
    {
      // check character
      if (m_argv0[i] == '/')
      {
        // reset
        nodir = "";
      }

      else
      {
        // append character
        nodir += m_argv0[i];
      }
    }

    // return brief name
    return nodir;
  }

  // return full name
  return m_argv0;
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// -----
// reset
// -----
/*
 *
 */
void cli::reset()
{
  // set default values
  operation        = CREATE_LIST_FILE;
  inputFilename    = "";
  readPbmFile      = false;
  readListFile     = false;
  initializePoints = false;
  fontSize         = 28;
  radius           = 25;
  strokeWidth      = 4;

  // drop positional parameters
  pparams.clear();

  // reset executable's name
  m_argv0 = "";
}

// ---------
// int2alnum
// ---------
/*
 *
 */
string cli::int2alnum(int ascii) const
{
  switch (ascii)
  {
    // digits
    case '0': return "0";
    case '1': return "1";
    case '2': return "2";
    case '3': return "3";
    case '4': return "4";
    case '5': return "5";
    case '6': return "6";
    case '7': return "7";
    case '8': return "8";
    case '9': return "9";

    // capital letters
    case 'A': return "A";
    case 'B': return "B";
    case 'C': return "C";
    case 'D': return "D";
    case 'E': return "E";
    case 'F': return "F";
    case 'G': return "G";
    case 'H': return "H";
    case 'I': return "I";
    case 'J': return "J";
    case 'K': return "K";
    case 'L': return "L";
    case 'M': return "M";
    case 'N': return "N";
    case 'O': return "O";
    case 'P': return "P";
    case 'Q': return "Q";
    case 'R': return "R";
    case 'S': return "S";
    case 'T': return "T";
    case 'U': return "U";
    case 'V': return "V";
    case 'W': return "W";
    case 'X': return "X";
    case 'Y': return "Y";
    case 'Z': return "Z";

    // small letters
    case 'a': return "a";
    case 'b': return "b";
    case 'c': return "c";
    case 'd': return "d";
    case 'e': return "e";
    case 'f': return "f";
    case 'g': return "g";
    case 'h': return "h";
    case 'i': return "i";
    case 'j': return "j";
    case 'k': return "k";
    case 'l': return "l";
    case 'm': return "m";
    case 'n': return "n";
    case 'o': return "o";
    case 'p': return "p";
    case 'q': return "q";
    case 'r': return "r";
    case 's': return "s";
    case 't': return "t";
    case 'u': return "u";
    case 'v': return "v";
    case 'w': return "w";
    case 'x': return "x";
    case 'y': return "y";
    case 'z': return "z";
  }

  // invalid character
  return "";
}

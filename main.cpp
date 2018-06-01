// -----------------------------------------------------------------------------
// main.cpp                                                             main.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the program's showHelp(), showVersion()
 *             and main() function and doxygen's main page.
 * @author     Col. Walter E. Kurtz
 * @version    2018-06-02
 * @copyright  GNU General Public License - Version 3.0
 *
 * @mainpage
 *
 * @section issue What is the issue here?
 *   This tool helps you to mark specific pixels in an image and
 *   numberize these markings. It's not a standalone tool, but
 *   intended to collaborate with an image manipulating program like Gimp.
 *   After you created the auxilliary svg files by using the -g option, your
 *   first step will be to mark the points of interest with a crosshair.
 *   Once you have targeted your spots, you add a black layer below all
 *   crosshairs and export this image as ASCII pbm file. This pbm file
 *   can now be parsed by poinum.
 *
 * @image html example.jpg
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "message.h"
#include "cli.h"
#include "SvgCodeGen.h"
#include "InputParser.h"
#include "P1Parser.h"
#include "ListParser.h"
#include "ListWriter.h"
#include "CrossWriter.h"
#include "NumberWriter.h"
#include "MapWriter.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Functions                                                           Functions
// -----------------------------------------------------------------------------

// --------
// showHelp
// --------
/**
 * @brief  This function shows the program's help.
 */
void showHelp()
{
  cout << endl;
  cout << "NAME" << endl;
  cout << "  poinum - numberize points of interest" << endl;
  cout << endl;
  cout << "SYNOPSIS" << endl;
  cout << "  poinum {-h|-v}                        show help resp. version and exit" << endl;
  cout << "  poinum [-frs] -g                      create basic svg files" << endl;
  cout << "  poinum [-icmnfrs] {-p|-l} <filename>  create target code" << endl;
  cout << endl;
  cout << "DESCRIPTION" << endl;
  cout << "  poinum helps you to numberize points of interest on a bitmap image" << endl;
  cout << endl;
  cout << "OPTIONS" << endl;
  cout << endl;
  cout << "  -h         show help and exit" << endl;
  cout << "  -v         show version and exit" << endl;
  cout << endl;
  cout << "  -g         create basic svg files" << endl;
  cout << endl;
  cout << "  -p <file>  read points from pbm <file>" << endl;
  cout << "  -l <file>  read points from list <file>" << endl;
  cout << "  -i         initialize points while parsing" << endl;
  cout << endl;
  cout << "  -c         create cross file" << endl;
  cout << "  -m         create map file" << endl;
  cout << "  -n         create number file" << endl;
  cout << endl;
  cout << "  -f <size>  use fontsize <size>" << endl;
  cout << "  -r <num>   draw circles with radius <num>" << endl;
  cout << "  -s <num>   draw circles with a stroke of <num>" << endl;
  cout << endl;
}

// -----------
// showVersion
// -----------
/**
 * @brief  This function shows the program's version.
 */
void showVersion()
{
  cout << "2018-06-02" << endl;
}

// ----
// main
// ----
/**
 * @brief  The program starts in this function.
 *
 * @param argc  holds the number of passed command-line arguments.
 * @param argv  holds the list of passed command-line arguments.
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *     0 | The requested operation finished successfully.
 *     1 | The requested operation failed.
 */
int main(int argc, char** argv)
{
  // create command-line parser
  cli cmdl;

  // try to parse command-line
  if ( !cmdl.parse(argc, argv) )
  {
    // signalize trouble
    return 1;
  }

  // -h
  if (cmdl.operation == cli::SHOW_HELP)
  {
    showHelp();

    // signalize success
    return 0;
  }

  // -v
  if (cmdl.operation == cli::SHOW_VERSION)
  {
    showVersion();

    // signalize success
    return 0;
  }

  // -g
  if (cmdl.operation == cli::CREATE_BASIC_SVG_FILES)
  {
    SvgCodeGen gen;

    // create files: 0..99
    for(unsigned i = 0; i < 100; i++)
    {
      // set output filenames
      stringstream filename;
      filename << "cross-"  << setw(2) << setfill('0') << i << ".svg"  << endl;
      filename << "number-" << setw(2) << setfill('0') << i << "a.svg" << endl;
      filename << "number-" << setw(2) << setfill('0') << i << "i.svg" << endl;

      // filenames
      string cfilename;
      string afilename;
      string ifilename;

      // get output filenames
      filename >> cfilename >> afilename >> ifilename;

      // create cross file
      ofstream cfile( cfilename.c_str() );
      cfile << gen.cross(0, 0, (i > 0), i, true, 2);
      cfile.close();

      // create active number file
      ofstream afile( afilename.c_str() );
      afile << gen.number(0, 0, true, i, cmdl.radius, cmdl.strokeWidth, cmdl.fontSize, true);
      afile.close();

      // create inactive number file
      ofstream ifile( ifilename.c_str() );
      ifile << gen.number(0, 0, false, i, cmdl.radius, cmdl.strokeWidth, cmdl.fontSize, true);
      ifile.close();
    }

    // signalize success
    return 0;
  }

  // start with NULL pointers
  InputParser* parser = 0;
  PointHandler* handler = 0;

  // use P1Parser
  if (cmdl.readPbmFile)
  {
    parser = new P1Parser;
  }

  // use ListParser
  else if (cmdl.readListFile)
  {
    parser = new ListParser;
  }

  // no source given
  else
  {
    // notify user
    msg::err("no source given (either -p or -l)");

    // signalize trouble
    return 1;
  }

  // create list file
  if (cmdl.operation == cli::CREATE_LIST_FILE)
  {
    handler = new ListWriter;
  }

  // create cross file
  else if (cmdl.operation == cli::CREATE_CROSS_FILE)
  {
    handler = new CrossWriter;
  }

  // create number file
  else if (cmdl.operation == cli::CREATE_NUMBER_FILE)
  {
    NumberWriter* h = new NumberWriter;
    h->setFontSize    ( cmdl.fontSize    );
    h->setRadius      ( cmdl.radius      );
    h->setStrokeWidth ( cmdl.strokeWidth );

    handler = h;
  }

  // create map file
  else if (cmdl.operation == cli::CREATE_MAP_FILE)
  {
    MapWriter* h = new MapWriter;
    h->setRadius(cmdl.radius);

    handler = h;
  }

  // use created handler
  parser->setHandler(handler);

  // parse given file
  if ( !(parser->parse(cmdl.inputFilename, cmdl.initializePoints)) )
  {
    // free memory
    delete handler;
    delete parser;

    // signalize trouble
    return 1;
  }

  // free memory
  delete handler;
  delete parser;

  // signalize success
  return 0;
}


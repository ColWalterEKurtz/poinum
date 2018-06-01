// -----------------------------------------------------------------------------
// cli.h                                                                   cli.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref cli class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef CLI_H_INCLUDE_NO1
#define CLI_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include <string>


// ---
// cli
// ---
/**
 * @brief  This class defines the command-line interface.
 */
class cli
{

public:

 // ----------------------------------------------------------------------------
 // Settings                                                            Settings
 // ----------------------------------------------------------------------------

  // operations that are mutually exclusive
  enum
  {
    SHOW_HELP,              ///< show help and exit
    SHOW_VERSION,           ///< show version and exit
    CREATE_LIST_FILE,       ///< create text file that holds the list of points
    CREATE_CROSS_FILE,      ///< create svg file that shows crosshairs
    CREATE_NUMBER_FILE,     ///< create svg file that shows circled numbers
    CREATE_MAP_FILE,        ///< create html map
    CREATE_BASIC_SVG_FILES  ///< create standalone svg files
  }
  operation;

  /// the path of the input file
  std::string inputFilename;

  /// input file has pbm format
  bool readPbmFile;

  /// input file has list format
  bool readListFile;

  /// initialize points while parsing
  bool initializePoints;

  /// the font size of the numbers in the number file
  int fontSize;

  /// the radius of all circles in the number file
  int radius;

  /// the stroke of all circles in the number file
  int strokeWidth;

  /// the list of positional parameters
  std::vector< std::string > pparams;


 // ----------------------------------------------------------------------------
 // Construction                                                    Construction
 // ----------------------------------------------------------------------------

  // ---
  // cli
  // ---
  /**
   * @brief  The standard-constructor.
   */
  cli();


 // ----------------------------------------------------------------------------
 // Handling                                                            Handling
 // ----------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method uses getopt() to parse the given arguments.
   */
  bool parse(int argc, char** argv);

  // --------
  // getXName
  // --------
  /**
   * @brief  returns argv[0]
   *
   * @param brief  set true to remove all directories
   */
  std::string getXName(bool brief = true) const;


protected:

 // ----------------------------------------------------------------------------
 // Internal methods                                            Internal methods
 // ----------------------------------------------------------------------------

  // -----
  // reset
  // -----
  /**
   * @brief  This method restores the initial state.
   */
  void reset();

  // ---------
  // int2alnum
  // ---------
  /**
   *
   */
  std::string int2alnum(int ascii) const;


private:

 // ----------------------------------------------------------------------------
 // Attributes                                                        Attributes
 // ----------------------------------------------------------------------------

  /// the executable's name
  std::string m_argv0;

};

#endif  /* #ifndef CLI_H_INCLUDE_NO1 */

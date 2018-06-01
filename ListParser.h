// -----------------------------------------------------------------------------
// ListParser.h                                                     ListParser.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref ListParser class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef LISTPARSER_H_INCLUDE_NO1
#define LISTPARSER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <istream>
#include "InputParser.h"


// ----------
// ListParser
// ----------
/**
 * @brief  This class reads coordinates from text files.
 */
class ListParser : public InputParser
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ----------
  // ListParser
  // ----------
  /**
   * @brief  The standard-constructor.
   */
  ListParser();


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method extracts the points from the given text file.
   *
   * @param filename    the path of the pbm file to parse
   * @param initialize  activate and numberize all points
   */
  virtual bool parse(const std::string& filename, bool initialize);


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // --------
  // getToken
  // --------
  /**
   * @brief  This method extracts a block of visible
   *         characters from the given input stream.
   */
  std::string getToken(std::istream& source) const;

};

#endif  /* #ifndef LISTPARSER_H_INCLUDE_NO1 */


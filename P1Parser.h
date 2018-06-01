// -----------------------------------------------------------------------------
// P1Parser.h                                                         P1Parser.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref P1Parser class.
 * @author     Achim Klein
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef P1PARSER_H_INCLUDE_NO1
#define P1PARSER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "InputParser.h"


// --------
// P1Parser
// --------
/**
 * @brief  This class reads coordinates from pbm files.
 */
class P1Parser : public InputParser
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // --------
  // P1Parser
  // --------
  /**
   * @brief  The standard-constructor.
   */
  P1Parser();


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method extracts the points from the given pbm file.
   *
   * @param filename    the path of the pbm file to parse
   * @param initialize  activate and numberize all points
   */
  virtual bool parse(const std::string& filename, bool initialize);


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // -------
  // ismagic
  // -------
  /**
   *
   */
  bool ismagic(char c) const;

  // ------
  // decode
  // ------
  /**
   *
   */
  int decode(const std::string& base2ascii) const;


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the number of bits used to encode point numbers
  const unsigned m_numBits;

};

#endif  /* #ifndef P1PARSER_H_INCLUDE_NO1 */


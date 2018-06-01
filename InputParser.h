// -----------------------------------------------------------------------------
// InputParser.h                                                   InputParser.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref InputParser class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef INPUTPARSER_H_INCLUDE_NO1
#define INPUTPARSER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>


// ------------
// PointHandler
// ------------
/*
 * Forward declaration
 */
class PointHandler;


// -----------
// InputParser
// -----------
/**
 * @brief  The base class for all parsers that read from files.
 */
class InputParser
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // -----------
  // InputParser
  // -----------
  /**
   * @brief  The standard-constructor.
   */
  InputParser();

  // ------------
  // ~InputParser
  // ------------
  /**
   * @brief  The destructor is virtual.
   */
  virtual ~InputParser();



  // ---------------------------------------------------------------------------
  // Initialization                                               Initialization
  // ---------------------------------------------------------------------------

  // ----------
  // setHandler
  // ----------
  /**
   *
   */
  void setHandler(PointHandler* handler);


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method extracts the points from the given file.
   *
   * @param filename    the path of the file to parse
   * @param initialize  activate and numberize all points
   */
  virtual bool parse(const std::string& filename, bool initialize) = 0;


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // -------
  // isspace
  // -------
  /**
   *
   */
  bool isspace(char c) const;

  // -----
  // iseol
  // -----
  /**
   *
   */
  bool iseol(char c) const;

  // ---------
  // isnatural
  // ---------
  /**
   *
   */
  bool isnatural(char c) const;

  // -------
  // isdigit
  // -------
  /**
   *
   */
  bool isdigit(char c) const;


  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the handler that receives all messages
  PointHandler* m_handler;

};

#endif  /* #ifndef INPUTPARSER_H_INCLUDE_NO1 */


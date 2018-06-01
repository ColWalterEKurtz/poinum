// -----------------------------------------------------------------------------
// PointHandler.h                                                 PointHandler.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref PointHandler class.
 * @author     Achim Klein
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef POINTHANDLER_H_INCLUDE_NO1
#define POINTHANDLER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>


// ------------
// PointHandler
// ------------
/**
 * @brief  This class receives messages from P1Parser.
 */
class PointHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ------------
  // PointHandler
  // ------------
  /**
   * @brief  The standard-constructor.
   */
  PointHandler();

  // -------------
  // ~PointHandler
  // -------------
  /**
   * @brief  The destructor is virtual.
   */
  virtual ~PointHandler();


  // ---------------------------------------------------------------------------
  // Callback handler                                           Callback handler 
  // ---------------------------------------------------------------------------

  // --------------
  // OnBeginParsing
  // --------------
  /**
   *
   */
  virtual void OnBeginParsing(const std::string& filename);

  // ------------
  // OnEndParsing
  // ------------
  /**
   *
   */
  virtual void OnEndParsing(bool healthy);

  // ------
  // OnSize
  // ------
  /**
   *
   */
  virtual void OnSize(int width, int height);

  // -------
  // OnPoint
  // -------
  /**
   *
   */
  virtual void OnPoint(int x, int y, bool active, int number);

  // -------
  // OnError
  // -------
  /**
   *
   */
  virtual void OnError(const std::string& message);

};

#endif  /* #ifndef POINTHANDLER_H_INCLUDE_NO1 */


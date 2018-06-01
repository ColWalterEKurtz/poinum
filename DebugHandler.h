// -----------------------------------------------------------------------------
// DebugHandler.h                                                 DebugHandler.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref DebugHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-28
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef DEBUGHANDLER_H_INCLUDE_NO1
#define DEBUGHANDLER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "PointHandler.h"


// ------------
// DebugHandler
// ------------
/**
 * @brief  This simple PointHandler pushes each call of 
 *         a handler method to stdout.
 */
class DebugHandler : public PointHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ------------
  // DebugHandler
  // ------------
  /**
   * @brief  The standard-constructor.
   */
  DebugHandler();


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

#endif  /* #ifndef DEBUGHANDLER_H_INCLUDE_NO1 */


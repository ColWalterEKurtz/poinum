// -----------------------------------------------------------------------------
// CrossWriter.h                                                   CrossWriter.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref CrossWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-29
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef CROSSWRITER_H_INCLUDE_NO1
#define CROSSWRITER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include "Point.h"
#include "PointHandler.h"


// -----------
// CrossWriter
// -----------
/**
 * @brief  This class generates the svg code that draws the crosshairs.
 */
class CrossWriter : public PointHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // -----------
  // CrossWriter
  // -----------
  /**
   * @brief  The standard-constructor.
   */
  CrossWriter();


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


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the width of the parsed image
  int m_imageWidth;

  /// the height of the parsed image
  int m_imageHeight;

  /// the list of received points
  std::vector<Point> m_points;

};

#endif  /* #ifndef CROSSWRITER_H_INCLUDE_NO1 */


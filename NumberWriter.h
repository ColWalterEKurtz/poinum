// -----------------------------------------------------------------------------
// NumberWriter.h                                                 NumberWriter.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref NumberWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef NUMBERWRITER_H_INCLUDE_NO1
#define NUMBERWRITER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include "Point.h"
#include "PointHandler.h"


// ------------
// NumberWriter
// ------------
/**
 * @brief  This class generates the svg code that draws the encircled numbers.
 */
class NumberWriter : public PointHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ------------
  // NumberWriter
  // ------------
  /**
   * @brief  The standard-constructor.
   */
  NumberWriter();


  // ---------------------------------------------------------------------------
  // Setter methods                                               Setter methods
  // ---------------------------------------------------------------------------

  // ---------
  // setRadius
  // ---------
  /**
   * @brief  This method sets the circle's radius.
   */
  void setRadius(int r);

  // --------------
  // setStrokeWidth
  // --------------
  /**
   * @brief  This method sets the width of the circle's edge.
   */
  void setStrokeWidth(int w);

  // -----------
  // setFontSize
  // -----------
  /**
   * @brief  This method sets the text's font size.
   */
  void setFontSize(int f);


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

  /// the cirle's radius
  int m_radius;

  /// the width of the circle's edge
  int m_strokeWidth;

  /// the number's font size
  int m_fontSize;

  /// the width of the parsed image
  int m_imageWidth;

  /// the height of the parsed image
  int m_imageHeight;

  /// the list of received points
  std::vector<Point> m_points;

};

#endif  /* #ifndef NUMBERWRITER_H_INCLUDE_NO1 */


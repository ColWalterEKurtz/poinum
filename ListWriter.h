// -----------------------------------------------------------------------------
// ListWriter.h                                                     ListWriter.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref ListWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-06-01
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef LISTWRITER_H_INCLUDE_NO1
#define LISTWRITER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include "Point.h"
#include "PointHandler.h"


// ----------
// ListWriter
// ----------
/**
 * @brief  This class prints a list of all points as textual table.
 */
class ListWriter : public PointHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ----------
  // ListWriter
  // ----------
  /**
   * @brief  The standard-constructor.
   */
  ListWriter();


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


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // ---------
  // writeLine
  // ---------
  /**
   * @brief  This method pushes one formatted line to stdout.
   */
  void writeLine(int x, int y, bool active, unsigned number) const;


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

#endif  /* #ifndef LISTWRITER_H_INCLUDE_NO1 */


// -----------------------------------------------------------------------------
// MapWriter.h                                                       MapWriter.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref MapWriter class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-06-01
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef MAPWRITER_H_INCLUDE_NO1
#define MAPWRITER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include "Point.h"
#include "PointHandler.h"


// ---------
// MapWriter
// ---------
/**
 * @brief  This class generates an html map.
 */
class MapWriter : public PointHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ---------
  // MapWriter
  // ---------
  /**
   * @brief  The standard-constructor.
   */
  MapWriter();


  // ---------------------------------------------------------------------------
  // Setter methods                                               Setter methods
  // ---------------------------------------------------------------------------

  // ---------
  // setRadius
  // ---------
  /**
   * @brief  This method sets the area's radius.
   */
  void setRadius(int r);


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

  // --------
  // simplify
  // --------
  /**
   * @brief  This method simplifies the name of the parsed file,
   *         so it can be used as identifier of the map tag.
   */
  std::string simplify(const std::string& filename) const;


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the list of received points
  std::vector<Point> m_points;

  /// the name of the created map
  std::string m_mapName;

  /// radius of each area
  int m_radius;

};

#endif  /* #ifndef MAPWRITER_H_INCLUDE_NO1 */


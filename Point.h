// -----------------------------------------------------------------------------
// Point.h                                                               Point.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref Point class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-28
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef POINT_H_INCLUDE_NO1
#define POINT_H_INCLUDE_NO1


// -----
// Point
// -----
/**
 * @brief  A two-dimensional point with some attached information.
 */
class Point
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // -----
  // Point
  // -----
  /**
   * @brief  The standard-constructor.
   */
  Point(int x = 0, int y = 0, bool active = true, unsigned number = 0);


  // ---------------------------------------------------------------------------
  // Setter methods                                               Setter methods
  // ---------------------------------------------------------------------------

  // ----
  // setX
  // ----
  /**
   * @brief  This method sets the point's x-coordinate.
   */
  void setX(int x);

  // ----
  // setY
  // ----
  /**
   * @brief  This method sets the point's y-coordinate.
   */
  void setY(int y);

  // ---------
  // setActive
  // ---------
  /**
   * @brief  This method sets the point's state.
   */
  void setActive(bool flag = true);

  // ---------
  // setNumber
  // ---------
  /**
   * @brief  This method sets the point's number.
   */
  void setNumber(unsigned number);


  // ---------------------------------------------------------------------------
  // Getter methods                                               Getter methods
  // ---------------------------------------------------------------------------

  // ----
  // getX
  // ----
  /**
   * @brief  This method returns the point's x-coordinate.
   */
  int getX() const;

  // ----
  // getY
  // ----
  /**
   * @brief  This method returns the point's y-coordinate.
   */
  int getY() const;

  // --------
  // isActive
  // --------
  /**
   * @brief  This method returns the point's state.
   */
  bool isActive() const;

  // ---------
  // getNumber
  // ---------
  /**
   * @brief  This method returns the point's number.
   */
  unsigned getNumber() const;


  // ---------------------------------------------------------------------------
  // Operator methods                                           Operator methods
  // ---------------------------------------------------------------------------

  // ---------
  // operator<
  // ---------
  /**
   * @brief  This method compares two points by number.
   */
  bool operator<(const Point& cmp) const;


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the point's x-coordinate
  int m_x;

  /// the point's y-coordinate
  int m_y;

  /// the point's state
  bool m_active;

  /// the point's number
  unsigned m_number;

};

#endif  /* #ifndef POINT_H_INCLUDE_NO1 */


// -----------------------------------------------------------------------------
// SvgCodeGen.h                                                     SvgCodeGen.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref SvgCodeGen class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-30
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef SVGCODEGEN_H_INCLUDE_NO1
#define SVGCODEGEN_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>
#include <sstream>


// ----------
// SvgCodeGen
// ----------
/**
 * @brief  This class creates svg commands to draw tagged and numbered points.
 */
class SvgCodeGen
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ----------
  // SvgCodeGen
  // ----------
  /**
   * @brief  The standard-constructor.
   */
  SvgCodeGen();


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // cross
  // -----
  /**
   * @brief  This method creates the svg commands that show
   *         the numbered cross.
   *
   * @param x     the x-coordinate of the denoted point
   * @param y     the y-coordinate of the denoted point
   * @param n     the point's number
   * @param a     the point's active flag
   * @param file  create the code of a complete svg file
   * @param parts draw black or white parts
   *              Value | Meaning
   *              ----: | :------
   *                  0 | draw only black parts
   *                  1 | draw only white parts
   *                  2 | draw both black and white parts
   */
  std::string cross(int x, int y, bool a, unsigned n, bool file, int parts = 2);

  // ------
  // number
  // ------
  /**
   * @brief  This method creates the svg commands that show
   *         the encircled number.
   *
   * @param x     the x-coordinate of the denoted point
   * @param y     the y-coordinate of the denoted point
   * @param a     the point's active flag
   * @param n     the point's number
   * @param r     the circle's radius
   * @param s     the circle's stroke width
   * @param f     the text's font size
   * @param file  create the code of a complete svg file
   */
  std::string number( int      x,
                      int      y,
                      bool     a,
                      unsigned n,
                      int      r,
                      int      s,
                      int      f,
                      bool     file = false );


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // ----------
  // startCross
  // ----------
  /**
   * @brief  This method creates the svg commands that start the cross.
   */
  void startCross(int x, int y, bool a, int n, int parts);

  // ----------
  // encodeFlag
  // ----------
  /**
   * @brief  This method creates the svg commands that show the state
   *         of the 'active' flag.
   */
  void encodeFlag(bool a);


  // ------------
  // encodeNumber
  // ------------
  /**
   * @brief  This method creates the svg commands that show the bits
   *         of the given number as black and white squares.
   */
  void encodeNumber(int n);

  // -----------
  // finishCross
  // -----------
  /**
   * @brief  This method adds the final svg commands.
   */
  void finishCross();

  // -----------
  // printNumber
  // -----------
  /**
   *
   */
  void printNumber(int x, int y, bool a, unsigned n, int r, int s, int f);


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// this stream holds all svg commands
  std::stringstream m_encoder;

};

#endif  /* #ifndef SVGCODEGEN_H_INCLUDE_NO1 */


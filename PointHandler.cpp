// -----------------------------------------------------------------------------
// PointHandler.cpp                                             PointHandler.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref PointHandler class.
 * @author     Achim Klein
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "PointHandler.h"


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ------------
// PointHandler
// ------------
/*
 *
 */
PointHandler::PointHandler()
{
  // nothing yet
}

// -------------
// ~PointHandler
// -------------
/*
 *
 */
PointHandler::~PointHandler()
{
  // nothing yet
}



// -----------------------------------------------------------------------------
// Callback handler                                             Callback handler 
// -----------------------------------------------------------------------------

// --------------
// OnBeginParsing
// --------------
/*
 *
 */
void PointHandler::OnBeginParsing(const std::string& filename)
{
  // nothing
}

// ------------
// OnEndParsing
// ------------
/*
 *
 */
void PointHandler::OnEndParsing(bool healthy)
{
  // nothing
}

// ------
// OnSize
// ------
/*
 *
 */
void PointHandler::OnSize(int width, int height)
{
  // nothing
}

// -------
// OnPoint
// -------
/*
 *
 */
void PointHandler::OnPoint(int x, int y, bool active, int number)
{
  // nothing
}

// -------
// OnError
// -------
/*
 *
 */
void PointHandler::OnError(const std::string& message)
{
  // nothing
}


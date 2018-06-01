// -----------------------------------------------------------------------------
// DebugHandler.cpp                                             DebugHandler.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref DebugHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-28
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include "DebugHandler.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ------------
// DebugHandler
// ------------
/*
 *
 */
DebugHandler::DebugHandler()
{
  // nothing
}


// -----------------------------------------------------------------------------
// Callback handler                                             Callback handler 
// -----------------------------------------------------------------------------

// --------------
// OnBeginParsing
// --------------
/**
 *
 */
void DebugHandler::OnBeginParsing(const string& filename)
{
  cout << "OnBeginParsing(\"" << filename << "\")" << endl;
}

// ------------
// OnEndParsing
// ------------
/**
 *
 */
void DebugHandler::OnEndParsing(bool healthy)
{
  cout << "OnEndParsing(" << (healthy ? "true" : "false") << ")" << endl;
}

// ------
// OnSize
// ------
/**
 *
 */
void DebugHandler::OnSize(int width, int height)
{
  cout << "OnSize(" << width << ", " << height << ")" << endl;
}

// -------
// OnPoint
// -------
/**
 *
 */
void DebugHandler::OnPoint(int x, int y, bool active, int number)
{
  cout << "OnPoint("
       << x
       << ", "
       << y
       << ", "
       << (active ? "true" : "false")
       << ", "
       << number
       << ")"
       << endl;
}

// -------
// OnError
// -------
/**
 *
 */
void DebugHandler::OnError(const string& message)
{
  cout << "OnError(\"" << message << "\")" << endl;
}


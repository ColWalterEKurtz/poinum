// -----------------------------------------------------------------------------
// InputParser.cpp                                               InputParser.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref InputParser class.
 * @author     Col. Walter E. Kurtz
 * @version    2018-05-31
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "PointHandler.h"
#include "InputParser.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// -----------
// InputParser
// -----------
/*
 *
 */
InputParser::InputParser()
: m_handler(0)
{
  // nothing yet
}

// ------------
// ~InputParser
// ------------
/*
 *
 */
InputParser::~InputParser()
{
  // nothing yet
}


// -----------------------------------------------------------------------------
// Initialization                                                 Initialization
// -----------------------------------------------------------------------------

// ----------
// setHandler
// ----------
/**
 *
 */
void InputParser::setHandler(PointHandler* handler)
{
  m_handler = handler;
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// -------
// isspace
// -------
/*
 *
 */
bool InputParser::isspace(char c) const
{
  if (c == 32) return true;
  if (c == 10) return true;
  if (c ==  9) return true;
  if (c == 13) return true;

  return false;
}

// -----
// iseol
// -----
/*
 *
 */
bool InputParser::iseol(char c) const
{
  if (c == 10) return true;
  if (c == 13) return true;

  return false;
}

// ---------
// isnatural
// ---------
/*
 *
 */
bool InputParser::isnatural(char c) const
{
  if (c == '1') return true;
  if (c == '2') return true;
  if (c == '3') return true;
  if (c == '4') return true;
  if (c == '5') return true;
  if (c == '6') return true;
  if (c == '7') return true;
  if (c == '8') return true;
  if (c == '9') return true;

  return false;
}

// -------
// isdigit
// -------
/*
 *
 */
bool InputParser::isdigit(char c) const
{
  if (c == '0') return true;
  if (c == '1') return true;
  if (c == '2') return true;
  if (c == '3') return true;
  if (c == '4') return true;
  if (c == '5') return true;
  if (c == '6') return true;
  if (c == '7') return true;
  if (c == '8') return true;
  if (c == '9') return true;

  return false;
}


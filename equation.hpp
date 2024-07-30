/**
 * @file  function.hpp
 */

#ifndef EQUATION_HPP
#define EQUATION_HPP

#include <string>
#include <vector>

#include "object.hpp"
#include "types.hpp"

class wire_t;

/**
 * @brief Represents an operator object for equations.
 *
 * This class encapsulates an operator used in equations. It allows connecting
 * left-hand side (lhs) and right-hand side (rhs) operands into a string representation.
 *
 * @todo: Make this use the flyweight design pattern
 */
class operator_t {
public:
  char op;
public:
  operator_t(char _op);
};

/**
 * @brief Represents an equation node in a linked list of equations.
 *
 * This class represents an equation node that forms a linked list structure to
 * represent equations. Each node contains a pointer to the next equation node,
 * a pointer to the wire associated with the equation, and a pointer to the
 * operator associated with the equation.
 */
class equation_t {
public:
  equation_t *next;
  wire_t *wire;
private:
  operator_t *op;
public:
  equation_t(equation_t *_next, wire_t *_wire, operator_t *_op);
  std::string evaluate() const;
};

#endif

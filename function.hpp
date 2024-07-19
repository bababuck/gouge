/**
 * @file  function.hpp
 */

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <vector>

#include "object.hpp"
#include "types.hpp"

void* new_function(char *name, void **outputs, void **inputs);

void evaluate_function_equations(void *function, void *equations);

/**
 * @brief Represents a collection of wires.
 *
 * @todo Condense this down to use data from `objects_db_t`.
 */
class wire_collection_t {
public:
    std::unordered_map<name_t, wire_t*> wires;
public:
    void add(wire_t *wire);
};

class equation_t;

/**
 * @brief Represents a function object inheriting from an abstract object type.
 *
 * This class manages inputs, outputs, and intermediate variables for a function.
 */
class function_t : public object_t {
 private:
  std::vector<wire_t*> *inputs;
  std::vector<wire_t*> *outputs;
 public:
  function_t(name_t _name, std::vector<wire_t*> *_outputs, std::vector<wire_t*> *_inputs);
  std::string evaluate() const;
  virtual ~function_t() override;
 public:
  std::vector<equation_t*> *equations;
};

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
private:
  equation_t *next;
  wire_t *wire;
  operator_t *op;
public:
  equation_t(equation_t *_next, wire_t *_wire, operator_t *_op);
  std::string evaluate() const;
};

#endif

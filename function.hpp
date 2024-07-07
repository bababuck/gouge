/**
 * @file  function.cpp
 */

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
private:
    std::unordered_map<name_t, wire_t*> wires;
public:
    void add(wire_t *wire);
};

/**
 * @brief Represents a function object inheriting from an abstract object type.
 * 
 * This class manages inputs, outputs, and intermediate variables for a function.
 */
class function_t : public object_t {
 private:
  wire_collection_t inputs;
  wire_collection_t  outputs;
 public:
  function_t(name_t _name, std::vector<wire_t*> *_outputs, std::vector<wire_t*> *_inputs);
  std::string evaluate() const;
};


void* add_equation(void *old_equations, void *equation);

void* make_equation(char *lhs_wire, char op, char *rhs_wire);

/**
 * @brief Represents an operator object for equations.
 * 
 * This class encapsulates an operator used in equations. It allows connecting
 * left-hand side (lhs) and right-hand side (rhs) operands into a string representation.
 *
 * @todo: Make this use the flyweight design pattern
 */
class operator_t {
private:
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
};
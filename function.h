#include <string>
#include <vector>

#include "declaration.h"
#include "object.h"
#include "function.h"

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
}

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
  function_t(name_t _name, wires_t *outputs, wires_t *inputs);
  std::string evaluate() const;
}


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
  char operator;
public:
  operator_t(char _operator);
  std::string connect(std::string lhs, std::string rhs) const; // recursively printout equation
}

// Linked list
class equation_t: public object_t {
private:
  equation_t *next;
  wire_t *wire;
  operator_t *operator;
public:
  equation_t(equation_t *_next, wire_t *_wire, operator_t *_operator): next(_next), wire(_wire), operator(_operator){}
}

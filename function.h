#include "declaration.h"
#include "object.h"
#include "function.h"

void* new_function(char *name, void **outputs, void **inputs) {
  function_t *function = new function_t(name, (wires_t**) outputs, (wires_t**) inputs);
  return (void*) function;
}

void evaluate_function_equations(void *function, void *equations) {

}

class wire_collection_t {
private:
  std::unordered_map<name_t, wire_t*> wires;

public:
  void add(wire_t *wire) {
    wires[wire->name] = wire;
  }
}

class function_t : public object_t {
 private:
  wire_collection_t inputs;
  wire_collection_t  outputs;
  std::unordered_map<name_t, fundamental_t*> intermediates;
 public:
  function_t(name_t _name, wires_t *outputs, wires_t *inputs) : name(_name) {
    for (size_t i=0; i<outputs->count; ++ i) {
      outputs.add(outputs->wires[i]);
    }
    for (size_t i=0; i<inputs->count; ++ i) {
      inputs.add(inputs->wires[i]);
    }
  }
  void add_inputs(wire_t *wire);
  void add_output(wire_t *wire);

  }
  
  void add_intermediate(fundamental_t *fundamental);
  std::string evaluate();

  bool inline;
}

void* add_equation(void *old_equations, void *equation) {
  std::vector<equation_t*> *equations = (std::vector<equation_t*>*) old_equations;
  if (!equations) {
    equations = new std::vector<equation_t*>();
  }
  equations.emplace_back(equation);
  return (void*) equations;
}

void* make_equation(char *lhs_wire, char op, char *rhs_wire) {
  operator_t *operator = new operator_t(lhs_wire);
  equation_t *rhs_equation = new equation_t(nullptr, get_wire(rhs_wire), nullptr);
  equation_t *lhs_equation = new equation_t(rhs_equation, get_wire(lhs_wire), operator);
  return (void*) lhs_equation;
}


// flyweight
class operator_t {
private:
  char operator;
public:
  operator_t(char _operator): operator(_operator){};
  std::string connect(std::string lhs, std::string rhs); // recursively printout equation
}

// equation_t current_equation pass alng for if else stuff, add new stuff to front so it doesn't effect the base equations

// Linked list
class equation_t: public object_t {
private:
  equation_t *next;
  wire_t *wire;
  operator_t *operator;
public:
  equation_t(equation_t *_next, wire_t *_wire, operator_t *_operator): next(_next), wire(_wire), operator(_operator){}
}

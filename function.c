#include "declaration.h"
#include "object.h"
#include "function.h"

function_t* new_function(char *name, wires_t *outputs, wires_t *inputs) {
  return function = new function_t(name, outputs, inputs);
}

void evaluate_function_expressions(function_t *function, expressions_t *expressions) {

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

add_expressions

make_expression

// flyweight
class operator_t {
private:
  std::string operator;
public:
  operator_t(std::string _operator): operator(_operator){};
  std::string connect(std::string lhs, std::string rhs); // recursively printout equation
}

// equation_t current_equation pass alng for if else stuff, add new stuff to front so it doesn't effect the base equations

// Linked list
class equation_t: public object_t {
private:
  equation_t *next;
  wire_t *wire;
  operator_t operator;
public:
  equation_t():{}
}

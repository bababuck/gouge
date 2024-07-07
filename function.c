#include "object.hpp"
#include "function.hpp"

/**
 * @brief Creates a new function object.
 * 
 * This function creates a new function object using the provided name,
 * outputs, and inputs. It initializes the function with the specified
 * wires for outputs and inputs.
 * 
 * @param name Pointer to a C-string representing the name of the function.
 * @param outputs Pointer to an array of pointers to output wires.
 * @param inputs Pointer to an array of pointers to input wires.
 * 
 * @return Pointer to the created function object (function_t* case to void*).
 */
void* new_function(char *name, void **outputs, void **inputs) {
  function_t *function = new function_t(name, (wires_t**) outputs, (wires_t**) inputs);
  return (void*) function;
}

/**
 * @brief Pass along a group of equations to a function.
 */
void evaluate_function_equations(void *function, void *equations) {

}

/**
 * @brief Adds a wire to the collection.
 * 
 * @param wire Pointer to the wire object to add.
 * 
 * @todo Condense this down to use data from objects_db_t.
 * 
 * @note This method adds a wire object to the collection. 
 * It associates the wire with its name in the internal map.
 */
wire_collection_t::void add(wire_t *wire) {
    wires[wire->name] = wire;
}

/**
 * @brief Constructor to initialize a function object.
 * 
 * @param _name Name of the function.
 * @param outputs Pointer to a list of output wires.
 * @param inputs Pointer to a list of input wires.
 * 
 * Constructs a function object with given name, and adds the specified
 * output and input wires to respective collections.
 */
function_t::function_t(name_t _name, wires_t *outputs, wires_t *inputs) : name(_name) {
    for (size_t i=0; i<outputs->count; ++ i) {
        outputs.add(outputs->wires[i]);
    }
    for (size_t i=0; i<inputs->count; ++ i) {
        inputs.add(inputs->wires[i]);
    }
}

/**
 * @brief Return verilog code for the performing the function.
 */
std::string function_t::evaluate() const {
    return "";
}

/**
 * @brief Adds an equation to the list of equations.
 * 
 * This function adds a new equation to an existing list of equations or creates
 * a new list if none exists. The equation is appended to the end of the list.
 * 
 * @param old_equations Pointer to the old list of equations.
 * @param equation Pointer to the equation to add.
 * 
 * @return Pointer to the updated list of equations (std::vector<equation_t*>*).
 * 
 * @note If `old_equations` is `nullptr`, a new std::vector<equation_t*> is allocated.
 */
void* add_equation(void *old_equations, void *equation) {
  std::vector<equation_t*> *equations = (std::vector<equation_t*>*) old_equations;
  if (!equations) {
    equations = new std::vector<equation_t*>();
  }
  equations.emplace_back(equation);
  return (void*) equations;
}

/**
 * @brief Creates an equation using given operands and operator.
 * 
 * This function creates an equation using the provided left-hand side wire,
 * operator, and right-hand side wire. It constructs equation objects and
 * returns a pointer to the resulting equation.
 * 
 * @param lhs_wire Pointer to a C-string representing the left-hand side wire name.
 * @param op Character representing the operator to use ('+', '-', '*', etc.).
 * @param rhs_wire Pointer to a C-string representing the right-hand side wire name.
 * 
 * @return Pointer to the created equation object (equation_t*).
 * 
 * @note The returned equation represents lhs_wire op rhs_wire.
 */
void* make_equation(char *lhs_wire, char op, char *rhs_wire) {
  operator_t *operator = new operator_t(lhs_wire);
  equation_t *rhs_equation = new equation_t(nullptr, get_wire(rhs_wire), nullptr);
  equation_t *lhs_equation = new equation_t(rhs_equation, get_wire(lhs_wire), operator);
  return (void*) lhs_equation;
}


/**
 * @brief Constructor to initialize an operator object.
 * 
 * @param _operator The character representing the operator ('+', '-', '*', etc.).
 * 
 * Initializes the operator with the given character.
 */
operator_t::operator_t(char _operator): operator(_operator) {}

std::string operator_t::connect(std::string lhs, std::string rhs) {
    return "";
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

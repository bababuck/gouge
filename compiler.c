General principle:
        - wires and registers are classes
        - mux's are implemented via control wires select() function
        - every wire must have it's drive class implemented
          - called by =
        - something is reg if used before driven ????

Top level module class, needs to implement main() function which will describe how data flows through the module.
    - main implicity takes as inputs all the module inputs and outputs all the module outputs

    - inputs and outputs are defined as class attributes

can also have classes that don't extend module class
    - use case, loop over array of objects

if class variable initialize before use, wire, else register

collect all drivers for each wire and the conditions needed to be driving it:
- how do we check to make sure that this is sound???
- have to search to make sure the wires can't both be driving


           - all class members are private, functions are public
           ;

class queue_t<width, depth, log2width> {
  input push;
  input [width:0] data_in;
  clock_t clk;
  input pop;
  output [width:0] data_out;

  int [width:0] storage[depth];
  int [log2width:0] count;

  void logic() {
    if (push) {
      if (count != log2width) {
        storage[count] = data_in;
        ++count;
      }
    }
    if (pop) {
      data_out = storage[0];
      --count;
      for (int i=0; i<log2width; ++i) {
        storage[i] = storage[i+1];
      }
    }
  }

  data_out pop(clk) {
    pop = 1;
    logic();
  }

  push(clk, data_in) {
    push = 1;
    logic();
  }
}

// Have to create new wire for wire (or reg) trying to drive itself, what do we name this wire (for now just index), maybe option for wire can be naming convention)

module example_t {
  clock_t Clk;

  reg [63:0] counter;
  queue_t<64, 8, 3> queue;

  void main() {
    if (counter & 64'b2 || counter & 64'b3) {
      queue.push(counter);
    }
    ++counter;
    if (counter & 64'b2 || counter & 64'b3) {
      queue.pop();
    }
    // Implicitly end cycle here
  }
}

class MuxControlWire():
      def __init__(self, width):
          

      def select



within a function, insert cycle_break macro

        //stages_t??.


        ;
}

class syntax_error_t : public std::runtime_error {
public:
    syntax_error_t(const std::string& message) : std::runtime_error(message) {}
};

class multiple_missing_definition_t : public std::runtime_error {
public:
 multiple_missing_definition_t(const std::string& message) :
  std::runtime_error(message) {}
};

typedef std::string name_t;

class objects_db_t {
  std::unordered_map<name_t, object_t*> objects;

  void insert(name_t name, object_t *object) {
    if (objects.find(name) != objects.end()) {
      throw multiple_missing_definition_t(name + "already defined");
    }
    objects[name] = object;
  }

  /* When getting a wire, need to get most recent form of the wire in case the name's been re-used*/
  object_t lookup(name_t name) {
    auto it = myMap.find(name);
    if (objects.find(name) == objects.end()) {
      throw multiple_missing_definition_t(name + "not yet defined");
    }
    return it->second;
  }
}

class object_t {
 public:
  object_t(name_t _name) : name(_name) {}

  name_t name;
}

class function_t : public object_t {
 private:
  std::unordered_map<name_t, wire_t*> inputs;
  std::unordered_map<name_t, wire_t*> outputs;
  std::unordered_map<name_t, fundamental_t*> intermediates;
 public:
  function_t(name_t _name, bool _inline) : name(_name), inline(_inline) {}
  void add_input(wire_t *wire);
  void add_output(wire_t *wire);
  void add_intermediate(fundamental_t *fundamental);
  std::string evaluate();

  bool inline;
}


class compiler_t {
private:
  std::stack<operator_t*, std::vector> if_operands;
  std::stack<operator_t*, std::vector> saved_else;
 public:
  compiler_t():{}
  enter_if_statement(operator_t operator);
  enter_else_statement();
  exit_if_else_statement();
}
/*
class enum_t {
  e
}
*/
class class_t : public object_t{
    class_t parent_class;

    class_t *parent;
    class_t **children;
    wire_t **inputs;
    wire_t **outputs;

    get_outputs();
    get_intput(); // Iterate throught parents inputs as well
    get_function(); // Iterate through parent classes functions as well.

    std::unordered_map<std::string, function_t> **functions;
}

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

class logic_t {
private:
  wire_t **recievers;
  width_t bit_width;
public:
  logic_t(width_t _bit_width): bit_width(_bit_width) {} // check to make sure width < 64 (since we don't want to handle wider constants)
  virtual void add_driver();
  virtual void validate() const; // Check to make sure all drivers are compatible
  virtual void increment_cycle() const; // Does nothing except for register type
}

class wire_t : public logic_t {
private:
  driver_t **drivers;
  function_t **driver_function;
private:
  virtual void validate() const override; // Check to make sure all drivers are compatible
  void check_multiple_drivers() const;
}

class register_t : public register_t {
  virtual void increment_cycle() const; // Print out always block
}

// flyweight class???
class constant_t : public logic_t {
private:
public:
  virtual void add_driver() const override; // FAILS
  virtual void validate() const override; // always valid
}


/* For a given module, inputs/output can only have a single driver, no register renaming
 * queue.pop()
 * queue.push()
 * queue.pop()
 * would drive pop twice
 *
 * Wihtin a function, same name can be reused, and is replaced with new wire each time.
 * x = 10;
 * y = x;
 * x = y + x;
 * z = x;
 * Evaluates to:
 * x0 = 10;
 * y = x0;
 * x1 = y + x0;
 * z = x1;
 */

/**
 * @file  function.hpp
 */

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <vector>

#include "object.hpp"
#include "types.hpp"

typedef struct {
  std::vector<equation_t*> equations;
  std::vector<wire_t*> declarations;
} equations_t;

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

/**
 * @brief Represents a function object inheriting from an abstract object type.
 *
 * This class manages inputs, outputs, and intermediate variables for a function.
 */
class function_t : public object_t {
  static equation_t fake_driver;

 private:
  std::vector<wire_t*> *inputs;
 public:
  std::vector<wire_t*> *outputs;
 public:
  function_t(name_t _name, std::vector<wire_t*> *_outputs, std::vector<wire_t*> *_inputs);
  std::string evaluate() const;
  virtual ~function_t() override;
 public:
  std::vector<equation_t*> *equations;
  std::vector<wire_t*> *wires;
};

equation_t function_t::fake_driver(NULL, NULL, NULL);

#endif

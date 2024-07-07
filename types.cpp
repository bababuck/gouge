/**
 * @file  types.cpp
 */

#include <vector>

#include "exceptions.hpp"
#include "object.hpp"
#include "types.hpp"

wire_t* get_wire(char *name) {
    object_t *object = get_object(name);
    wire_t *wire = dynamic_cast<wire_t*>(object);
    if (wire) {
        return wire;
    }
    throw multiple_missing_def_exception_t(std::string(name) + " is not a wire");
}

/**
 * @brief Adds a wire object to a vector of wires.
 *
 * This function adds a wire object to a vector of wires.
 * If the vector (`old_wires`) provided is null, a new vector is created.
 *
 * @param old_wires Pointer to the vector of wire_t pointers.
 * @param wire Pointer to the wire_t object to add.
 * @return Pointer to the updated vector of wire_t pointers.
 */
 void* add_wires(void *old_wires, void *wire) {
  std::vector<wire_t*> *wires = (std::vector<wire_t*>*) old_wires;
  if (!wires) {
    wires = new std::vector<wire_t*>();
  }
  wires->emplace_back((wire_t*) wire);
  return (void*) wires;
}

/**
 * @brief Creates a new wire object.
 *
 * This function creates a new wire object with the specified type and name.
 *
 * @todo: Extract bit width
 *
 * @param type The type of the wire (char pointer).
 * @param name The name of the wire (char pointer).
 * @return Pointer to the newly created wire_t object.
 */
void* new_wire(char *type, char *name) {
  wire_t *wire = new wire_t(name, 1);
  return (void*) wire;
}

/**
 * @brief Constructor for logic_t objects.
 *
 * Initializes a logic_t object with a specified name and bit width.
 * 
 * @param name The name of the logic_t object.
 * @param _bit_width The bit width of the logic_t object.
 * @todo: Check to make sure _bit_width < 64 (since we don't handle wider constants).
 */
logic_t::logic_t(char *name, width_t _bit_width): object_t(name_t(name)), bit_width(_bit_width) {}


void logic_t::add_driver() {}

wire_t::wire_t(char *name, width_t _bit_width):logic_t(name, _bit_width){}
wire_t::~wire_t(){}
void wire_t::add_driver() {}
void wire_t::validate() const {}
void wire_t::increment_cycle() const {}
void wire_t::check_multiple_drivers() const {}

void reg_t::increment_cycle() const {}

constant_t::~constant_t() {}
void constant_t::add_driver() {} // throw exeption

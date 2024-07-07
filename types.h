#ifndef TYPES_H
#define TYPES_H

#include "object.h"

void* add_wires(void *old_wires, void *wire);

void* new_wire(char *type, char *name);

/**
 * @brief Represents a logic entity with drivers and receivers.
 */
class logic_t : object_t {
private:
    wire_t **recievers;
    width_t bit_width;
public:
    logic_t(char *name, width_t _bit_width);
    virtual void add_driver();
}

/**
 * @brief Represents a wire in the logic system.
 */
class wire_t : public logic_t {
private:
    driver_t **drivers;
    function_t **driver_function;
public:
    virtual ~wire_t() override;
private:
    virtual void validate() const override; // Check to make sure all drivers are compatible
    void check_multiple_drivers() const;
    virtual void validate() const; // Check to make sure all drivers are compatible
    virtual void increment_cycle() const; // Does nothing except for register type
    virtual void add_driver();
}

/**
 * @brief Represents a register in the logic system.
 */
class register_t : public wire_t {
    virtual void increment_cycle() const; // Print out always block
}

/**
 * @brief Represents a constant in the logic system.
 *
 * @TODO: make this a flyweight class
 */
class constant_t : public logic_t {
public:
    virtual ~wire_t() override;
    virtual void add_driver() const override;
}

#endif
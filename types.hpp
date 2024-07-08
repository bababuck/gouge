/**
 * @file  types.hpp
 */

#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

#include "object.hpp"

typedef size_t width_t;

class wire_t;

wire_t* get_wire(char* name);

/**
 * @brief Represents a logic entity with drivers and receivers.
 */
class logic_t : public object_t {
private:
    logic_t **recievers;
    width_t bit_width;
public:
    logic_t(char *name, width_t _bit_width);
    virtual void add_driver();
protected:
    virtual ~logic_t() = 0;
};

/**
 * @brief Represents a wire in the logic system.
 */
class wire_t : public logic_t {
private:
    logic_t **drivers;
public:
    wire_t(char *name, width_t _bit_width);
private:
    virtual void validate() const; // Check to make sure all drivers are compatible
    void check_multiple_drivers() const;
    virtual void increment_cycle() const; // Does nothing except for register type
    virtual void add_driver() override;
};

/**
 * @brief Represents a register in the logic system.
 */
class reg_t : public wire_t {
public:
    virtual void increment_cycle() const; // Print out always block
};

/**
 * @brief Represents a constant in the logic system.
 *
 * @todo: make this a flyweight class
 */
class constant_t : public logic_t {
public:
    virtual void add_driver() override;
};

#endif

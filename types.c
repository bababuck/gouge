typedef struct {
  size_t count;
  wire_t **wires;
} wires_t;

wires_t add_wires(wires_t *wires, wire_t *wire) {
  if (!wires) {
    wires = new wires_t();
    wires->count = 0;
    wires->wires = NULL;
  }
  ++(wires->count);
  wires = realloc(wires, wires->count * sizeof(wire_t*));
  wires->wires[wires->count] = wire;
  return wires;
}

wire_t* new_wire(char *type, char *name) {
  return new wire_t(name, 1);  // TODO: Extract bit width
}

class logic_t : object_t {
private:
  wire_t **recievers;
  width_t bit_width;
public:
 logic_t(char *name, width_t _bit_width): object_t(name_t), bit_width(_bit_width) {} // TODO: check to make sure width < 64 (since we don't want to handle wider constants)
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

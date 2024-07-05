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

typedef std::string name_t;

// Registry design pattern
class objects_db_t {
private:
    std::unordered_map<name_t, object_t*> registry;
    static objects_db_t *self = nullptr;
public:
    void register_object(const name_t &name, const object_t* const obj) {
        if (objects.find(name) != objects.end()) {
            throw multiple_missing_definition_t(name + "already defined");
        }
        registry[name] = obj;
    }

    object_t* lookup_object(const name_t &name) {
        auto it = registryMap.find(name);
        if (it != registryMap.end()) {
            return it->second;
        }
        throw multiple_missing_missing_definition_t(name + "not yet defined");
    }
private:
    objects_db_t(){};
public:
    static objects_db_t* get_objects_db(){
        if (self == nullptr){
            self = new objects_db_t();
        }
        return self;
    }
};

class object_t {
 public:
  object_t(name_t _name) : name(_name) {}

  name_t name;
}

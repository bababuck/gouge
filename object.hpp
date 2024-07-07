/**
 * @file  object.hpp
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

typedef std::string name_t;

class object_t;

object_t* get_object(char* name);

/**
 * @brief Singleton class using the Registry design pattern to manage a database of objects.
 *
 * The Registry design pattern is used to maintain a central registry of objects, allowing
 * efficient lookup and management. This class provides methods to register objects by name
 * and retrieve them later using their registered names.
 *
 * The singleton pattern ensures that only one instance of `objects_db_t` exists throughout
 * the program's lifetime, accessible globally via the `get_objects_db()` static method.
 */
class objects_db_t {
private:
    std::unordered_map<name_t, object_t*> objects;
    static objects_db_t *self;

    objects_db_t();
public:
    void register_object(const name_t &name, object_t* const obj);
    object_t* lookup_object(const name_t &name) const;
    static objects_db_t* get_objects_db();
};

/**
 * @brief Base class for all objects in the program.
 *
 * This class serves as the fundamental building block for all other types in the program.
 * It encapsulates a name associated with each object and provides a constructor to initialize
 * this name upon object creation.
 */
class object_t {
public:
    name_t name;
public:
    object_t(name_t _name);
protected:
    virtual ~object_t() = 0;
};

#endif

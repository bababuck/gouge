/**
 * @file  object.cpp
 */

#include "exceptions.hpp"
#include "object.hpp"

object_t* get_object(char *name) {
    return objects_db_t::get_objects_db()->lookup_object(name_t(name));
}

/**
 * @brief Private constructor to enforce singleton pattern.
 *
 * The constructor is private to prevent direct instantiation of `objects_db_t`.
 * Use `get_objects_db()` to obtain the singleton instance.
 */
objects_db_t::objects_db_t() {}

objects_db_t* objects_db_t::self = nullptr;

/**
 * @brief Registers an object with a specified name in the database.
 *
 * If an object with the same name already exists in the registry, it will be replaced
 * with the new object.
 *
 * @param name The name under which to register the object.
 * @param obj Pointer to the object to be registered.
 */
void objects_db_t::register_object(const name_t &name, object_t* const obj) {
    if (objects.find(name) != objects.end()) {
        throw multiple_missing_def_exception_t(name + "already defined");
    }
    objects[name] = obj;
}

/**
 * @brief Looks up and returns the object associated with the specified name.
 *
 * If no object is found with the given name, throws a multiple_missing_def_exception_t exception.
 *
 * @param name The name of the object to look up.
 * @return Pointer to the object if found, nullptr otherwise.
 */
object_t* objects_db_t::lookup_object(const name_t &name) const {
    auto it = objects.find(name);
    if (it != objects.end()) {
        return it->second;
    }
    throw multiple_missing_def_exception_t(name + "not yet defined");
}

/**
 * @brief Retrieves the singleton instance of `objects_db_t`.
 * 
 * If the instance does not yet exist, it will be created on the first call.
 *
 * @return Pointer to the singleton instance of `objects_db_t`.
 */
objects_db_t* objects_db_t::get_objects_db() {
    if (self == nullptr){
        self = new objects_db_t();
    }
    return self;
}

/**
 * @brief Constructor to initialize an object with a specified name.
 *
 * @param _name The name to be associated with the object.
 */
object_t::object_t(name_t _name) : name(_name) {}

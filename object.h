/**
 * @file  object.h
 */

#ifndef OBJECT_H
#define OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

void new_context();

void exit_context();

void register_object(void* const object);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @file  types.h
 */

#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

void* add_wires(void *old_wires, void *wire);

void* new_wire(char *type, char *name);

#ifdef __cplusplus
}
#endif

#endif

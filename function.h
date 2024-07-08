/**
 * @file  function.h
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

void* new_function(char *name, void *outputs, void *inputs);

void evaluate_function_equations(void *function, void *equations);

void* add_equation(void *old_equations, void *equation);

void* make_equation(char *lhs_wire, char op, char *rhs_wire);

#ifdef __cplusplus
}
#endif

#endif

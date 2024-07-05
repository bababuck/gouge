#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "declaration.h"

declaration_t* make_declaration(const char *type, const char *name) {
    declaration_t *decl = malloc(sizeof(declaration_t));
    if (decl == NULL) {
        perror("malloc failed");
        return NULL;
    }

    // Use strdup to allocate memory and copy strings
    decl->type = strdup(type);
    if (decl->type == NULL) {
        perror("strdup failed");
        free(decl);
        return NULL;
    }

    decl->name = strdup(name);
    if (decl->name == NULL) {
        perror("strdup failed");
        free(decl->type);
        free(decl);
        return NULL;
    }
    return decl;
}
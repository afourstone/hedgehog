#include "cactus.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void printValue(Value v) {
    switch (v.type) {
        case INT_VALUE:
            printf("%" PRId32, v.u.int_value);
            break;
        case BOOL_VALUE:
            printf("%s", v.u.bool_value.v == 0 ? "false" : "true");
            break;
        case DOUBLE_VALUE:
            printf("%lf", v.u.double_value);
            break;
        case STRING_VALUE:
            printf("%s", v.u.string_value.s);
            break;
        case NULL_VALUE:
            printf("%s", "null");
            break;
        default:
            printf("Error!!!");
            break;
    }
}

Variable *createVariable(char *identifier, Value v) {
    log("create var: %s", identifier);
    Variable *var = (Variable *)malloc(sizeof(Variable));
    var->identifier = identifier;
    var->v = v;
    return var;
}

char *createIdentifier(char *s) {
    log("create id: %s", s);
    char *id = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(id, s);
    return id;
}

void addToGlobalVariableList(Variable *var) {
    log("add var :%s", var->identifier);
    VariableNode *p = (VariableNode *)malloc(sizeof(VariableNode));
    p->var = var;
    p->next = globalVariableList.next;
    globalVariableList.next = p;
}

void releaseGlobalVariableMemo() {
    log("release memo %s", "");
    while (globalVariableList.next != NULL) {
        VariableNode *p = globalVariableList.next;
        globalVariableList.next = p->next;
        free(p->var->identifier);
        free(p->var);
        free(p);
    }
}

Variable *searchLocalVariable(char *identifier) {
    // TODO: need more efficient data structure
    VariableNode *p = globalVariableList.next;
    while (p != NULL) {
        if (strcmp(identifier, p->var->identifier) == 0) {
            return p->var;
        }
        p = p->next;
    }
    return NULL;
}

Value callFunction(char *identifier, ArgumentNode *ArgumentList) {
    // build-in function
    Value v;
    v.type = NULL_VALUE;
    if (strcmp(identifier, "print")) {
        // for() loop print argument
    } else if (strcmp(identifier, "exit")){
        releaseGlobalVariableMemo();
    } else {
        // def function
    }
    return v;
}
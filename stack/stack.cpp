#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include "head.h"

#define POISON 0xFFF0
#define CANARY 0xFF00

struct stack {
    int canary1 = CANARY;
	int* data;
	int capaticity;
	size_t size;
    int canary2 = CANARY;
};

int StackCtor(stack* stack, int capaticity) {
	if (!stack) {
        return 1;
    }
    if (capaticity < 0) {
        return 1;
    }
	stack->data = (int*) calloc(capaticity + 2,sizeof(int));
    stack->data[0] = CANARY;
    stack->data = stack->data + sizeof(int);
    stack->data[capaticity + 1] = CANARY; 
	stack->size = 0;
	stack->capaticity = capaticity;
	return 0;
}

int StackPush(stack* stack, int value) {
	if (StackBAD) {
        StackDump(stack);
        return 1;
    }
    if (size == capaticity) {
        ReSize(stack);
    }
	stack->data[stack->size + 1] = value;
	stack->size = stack->size + 1;
	return 0;
}

int StackPop(stack* stack) {
	if (StackBAD) {
        StackDump(stack);
        return 1;
    }
	int value = stack->data[stack->size];
    if (value == POISON) {
        return 1;
    }
	stack->data[stack->size] = 0;
    stack->data[stack->size] = POISON;
	stack->size = stack->size - 1;
	return value;
}

int StackDtor(stack* stack) {
	if (StackBAD) {
        StackDump(stack);
        return 1;
    }
	memset(stack->data, POISON, stack->size * sizeof(int));
	free(stack->data);
	return 0;
}

int ReSize(stack* stack) {
    int * newdata = (int*)calloc(2 + 2 * stack->capaticity, sizeof(int));
    memset(newdata, POISON, sizeof(int) * (2 + 2 * stack->capaticity);
    for (int i = 0; i < stack->capaticity + 2; i ++) {
        newdata[i] = stack->data[i - 1];   
    }
    memset(stack->data - sizeof(int), POISON, sizeof(int) * (stack->capaticity + 2));
    stack->data = newdata;
    stack->capaticity = 2 * stack->capaticity;
    return 0;
}

int StackBAD(stack* stack) {
    if (!stack) {
        return 1;
    }
    if (stack->canary1 != CANARY) {
        return 1;
    }
    if (stack->canary2 != CANARY) {
        return 1;
    }
    if (stack->size < 0) {
        return 1;
    }
    if (stack->capaticity < 0) {
        return 1;
    }
    if (stack->size > stack->capaticity) {
        return 1;
    }
    if (!stack->data) {
        return 1;
    }
    return 0;
}
    
int StackDump(stack* stack) {
    printf("BAD\n");
    return 0;
}

#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <cstring>

struct stack {
	int* data;
	int capaticity;
	size_t size;
};

int StackCtor(stack* stack, int capaticity) {
	assert(stack);
	stack->data = (int*) calloc(capaticity,sizeof(int));
	stack->size = 0;
	stack->capaticity = capaticity;
	return 0;
}

int StackPush(stack* stack, int value) {
	assert(stack);
	assert(stack->size<stack->capaticity);
	stack->data[stack->size + 1] = value;
	stack->size = stack->size + 1;
	return 0;
}

int StackPop(stack* stack) {
	assert(stack);
	int value = stack->data[stack->size];
	stack->data[stack->size] = 0;
	stack->size = stack->size - 1;
	return value;
}

int StackDtor(stack* stack) {
	assert(stack);
	memset(stack->data, 0, stack->size * sizeof(int));
	free(stack->data);
	return 0;
}


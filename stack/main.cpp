#include "stack.cpp"

int dump(stack* stack) {
        printf("*data = %p\n capaticity = %d\n size = %lu \n \n", stack->data, stack->capaticity, stack->size);
        return 0;
}


int main() {
	stack st{};
	StackCtor(&st, 3);
	dump(&st);
	StackPush(&st, 3);
	dump(&st);

	StackPush(&st, 6);
	dump(&st);

	int x = StackPop(&st);
	dump(&st);

	StackPush(&st, x);
	dump(&st);

	StackDtor(&st);

	return 0;
}


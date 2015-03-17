#include <stdio.h>
#include <string.h>

#define STACK_SIZE 1024

struct CharStack
{
    char content[STACK_SIZE];
    int stack_ptr;
};

void char_stack_clear(struct CharStack *stack)
{
    stack->stack_ptr = -1;
}

char char_stack_popup(struct CharStack *stack)
{
    char result;
    if(stack->stack_ptr < 0){
        printf("Stack is empty!\n");
        return '\0';
    }
    else{
        result = stack->content[stack->stack_ptr];
        stack->stack_ptr --;
        return result;
    }
}

void char_stack_push(struct CharStack *stack, char c) 
{
    if(stack->stack_ptr == STACK_SIZE - 1){
        printf("Stack is full!\n");
        return;
    }
    else {
        stack->stack_ptr ++;
        stack->content[stack->stack_ptr] = c;
        // printf("push %c, ptr: %d\n", c, stack->stack_ptr);
    }
}

void char_stack_push_string(struct CharStack *stack, char *str)
{
    int str_length = strlen(str);
    if (stack->stack_ptr + str_length >= STACK_SIZE) {
        printf("String \"%s\" is too long to be pushed into stack.\n");
        return;
    }

    int i;
    for(i=0; i < str_length; i++)
        char_stack_push(stack, str[i]);
}

char * char_stack_popup_string(struct CharStack *stack)
{
    static char str[STACK_SIZE];
    int i = 0;
    while(stack->stack_ptr >= 0){
        str[i] = char_stack_popup(stack);
        i ++;
    }
    str[i] = '\0';
    return str;
}

int main(int argc, char *argv[])
{
    struct CharStack stack;
    char_stack_clear(&stack);
    printf("Input a string:\n");
    char input_string[STACK_SIZE];
    scanf("%s", input_string);
    printf("Your input is \"%s\"\n");
    
    char_stack_push_string(&stack, input_string);
    char *str = char_stack_popup_string(&stack);
    printf("The reversed result:\n%s\n", str);
    return 0;
}

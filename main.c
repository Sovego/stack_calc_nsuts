#pragma comment (linker,"/STACK:50000000")
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Stack {
    char c;
    struct Stack *Next;

}Stack ;
int s_top = 0;
float stack[510000];
float pop() {
    if (s_top > 0) {
        return stack[--s_top];
    } else {
        return 0;
    }
};
void push(float a) {
    stack[s_top++] = a;
};
Stack* out_stack_c(Stack *top, char *s ) {
    Stack *tmp = top;
    *s = top -> c;
    top = top->Next;
    free(tmp);
    return top;

}
Stack* input_stack_c(Stack *top, char s) {
    Stack *tmp = (Stack*) malloc(sizeof(Stack));
    tmp -> c = s;
    tmp-> Next = top;
    return tmp;
}
int Prior ( char a ) {
    switch ( a ) {
        case '*': case '/': return 3;
        case '-': case '+': return 2;
        case '(': return 1;
    }
    return 0;
}

int main ()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    Stack *t, *Top = NULL;
    char a, in_str[510000], out_str[510000];
    int k = 0, l = 0;
    gets(in_str);
    if(in_str[0] == '-')
    {
        for (int j = strlen(in_str); j >= 0; j--) {
            in_str[j] = in_str[j - 1];
        }
        in_str[0]='0';
    }
    for (int i = 1; i <=strlen(in_str); i++)
        if (in_str[i - 1] == '(' && (in_str[i] == '-' || in_str[i] == '+')) {
            for (int j = strlen(in_str); j >= i; j--) {
                in_str[j] = in_str[j - 1];
            }
            in_str[i]='0';
        }
    while (in_str[k] != '\0') {
        if (in_str[k] == ')' ) {
            while ((Top -> c) != '(' ) {
                Top = out_stack_c(Top, &a);
                if ( !Top ) a = '\0';
                out_str[l++] = a;
                out_str[l++] = ' ';
            }
            t = Top;
            Top = Top -> Next;
            free(t);
        }
        if (in_str[k] >= '0' && in_str[k] <= '9' )
        {
            while(in_str[k] >= '0' && in_str[k] <= '9' )
            {
                out_str[l++]=in_str[k];
                if(in_str[k + 1] >= '0' && in_str[k + 1] <= '9')
                {}
                else {
                    out_str[l++] = ' ';
                }
                k++;
            }
            continue;
        }
        if (in_str[k] == '(' ) Top = input_stack_c(Top, in_str[k]);
        if (in_str[k] == '+' || in_str[k] == '-' || in_str[k] == '*' || in_str[k] == '/' ) {
            while (Top != NULL && Prior (Top -> c) >= Prior (in_str[k]) ) {
                Top = out_stack_c(Top, &a);
                out_str[l++] = a;
                out_str[l++] = ' ';
            }
            Top = input_stack_c(Top, in_str[k]);
        }
        k++;
    }
    while (Top != NULL) {
        Top = out_stack_c(Top, &a);
        out_str[l++] = a;
        out_str[l++] = ' ';
    }
    out_str[l] = 0;
    int i=0;
    while (out_str[i] != 0) {
        char c = out_str[i];
        float x;
        switch (c) {
            case ' ' : break;
            case '+' :{
                float a=pop();
                float b=pop();
                push(b+a);
                break;}
            case '-' :{
                float a=pop();
                float b=pop();
                push(b-a);
                break;}
            case '*' : {
                float a=pop();
                float b=pop();
                push(b*a);
                break;}
            case '/': {
                float a=pop();
                float b=pop();
                push(b/a);
                break;}
            default: {
                sscanf(out_str + i, "%f", &x);
                if(x>=10){
                    float tmp=x;
                    int tmp_i=0;
                    while(tmp>=10)
                    {
                        tmp/=10;
                        tmp_i++;
                    }
                    i+=tmp_i;
                    push(x);
                } else{
                push(x);
                }
                break;
            }
        }
        i++;
    }
    printf("%s\n", out_str);
    printf("%.20f",pop());
    return 0;
}
/*
判断是否构成回文
思路是用stack来操作 
stack可以用stl或者自己写 
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define CAP 1024
typedef struct {
        char *stk;
        int len; 
        int cap;//capacity
} Stack;

void init(Stack *s) {
     s->stk = (char *) calloc(CAP, sizeof (char));
     s->len = 0;
     s->cap = CAP;
}
         

char top(Stack *s) {
     if(s->len > 0) {
               return s->stk[s->len-1];
     }
}

bool empty(Stack *s) {
     return s->len == 0;
}

void push(Stack *s, char ch) {
     if(s->len == s->cap) {
               char *tmp = s->stk;
               s->stk = (char *)calloc(s->cap*2, sizeof (char));
               strncpy(s->stk, tmp, s->len);
               free(tmp);
               tmp = NULL;
     }
     s->stk[s->len++] = ch;
}

char pop(Stack *s) {
     if(s->len > 0) {
               s->len--;
               return s->stk[s->len];
     }
}


bool isPalindrome(char *str, Stack *s) {
     int len  = strlen(str);
     char *rev = (char *) calloc(len+1, sizeof(char));
     for (int i=0; i < len; i++) {
         push(s, str[i]);
     }
     for (int i=0; i < len; i++) {
         rev[i] = pop(s);
     }
     if (strncmp(str, rev, len) == 0) 
        return true;
     return false;
}

/**
   递归判断 
*/

bool isPalindrome1(char *str, int len) {
     if (len == 0 || len == 1) {
        return true;
     }
     if (str[0] == str[len-1]) {
        return isPalindrome1(str+1, len-2);
     } else {
        return false;
     }
}
 
int main(void) {
    char *str = "abcddcba";
    
     Stack *s = (Stack *) calloc(sizeof (Stack), sizeof (char));
     init(s);
     
     if (isPalindrome(str, s)) {
        printf("It is palindrome\n");
     } else {
        printf("It is not a palindrome\n");
     }
     
     /*
     if (isPalindrome1(str, strlen(str)))
        printf("It is palindrome\n");
     */
     system("pause");
     return 0;
     
}


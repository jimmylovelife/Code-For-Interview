/**
 寻找字符串里最大的回文子串 
 输入字符串
 输出最大长度，和回文字符串 
*/
#include<stdlib.h>
#include<stdio.h>

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

bool maxSubPalindrome(char *str, int len) {
     int max;
     int pop = 0;
     for(int i=0; i<len; i++) {
             
     } 
} 

 

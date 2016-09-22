#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "romanLetter.h"
//int roman_add(
#define BAD_NUMBER       9
#define TRUE  true
#define FALSE false
struct roman_table romanTable = {"IVXLCDM", {1, 5, 10, 50, 100, 500, 1000}};

int is_inRomanLetter(char);
bool valid_romanstring(char *);
int toValue(char *);
char *toRomanStr(int);

void TEST_is_inRomanLetter(void)
{
    int val_char = is_inRomanLetter('X');
    assert(val_char != BAD_NUMBER);
}

void TEST_valid_romanstring(void)
{
    bool val_str;
    val_str = valid_romanstring("IX");
    assert(val_str);
}
void TEST_toValue(void)
{
     assert(toValue("IV") == 4);
     assert(toValue("IX") == 9);
     assert(toValue("XCIX") == 99);
     assert(toValue("CMCDXLIX") == 1349);
     assert(toValue("MCCCXLIX") == 1349);
}

void TEST_toRomanStr(void)
{
     char *rstr = toRomanStr(3999);
     assert(strcmp(rstr, "MMMCMXCIX")==0);
     free(rstr);
     rstr = toRomanStr(444);
     assert(strcmp(rstr, "CDXLIV") == 0);
     free( rstr);
}

/////////////////////////////////////
/**
** return index of letter in roman_letters[]
** return BAD_NUMER if greater than 6
*/
int is_inRomanLetter(char c) {
     for (int i = 0; i < ROMAN_LETTERS; i++) {
         if (c == romanTable.roman_letters[i])
            return i;
     }
     return BAD_NUMBER;
}
bool valid_romanstring(char *str)
{
     bool rv = false;
     int len = strlen(str);
     for (int i = 0; i < len; i++) {
         if (is_inRomanLetter(str[i]) != BAD_NUMBER)
            return true;
     }
     return rv;
}

int process_state(int currN, int lastN, int val)
{
    if (currN < lastN)
       return val -= currN;
    else
        return val += currN;
}
int toValue(char *str)
{
    int rv=0;
    int lastNumber = 0;
    int tmpI = 0;
    int len = strlen(str);
    for (int i = len-1; i >= 0; i--) {
        int c2i = is_inRomanLetter(str[i]& 0xdf);
        rv = process_state(romanTable.value[c2i], lastNumber, rv);
        lastNumber = romanTable.value[c2i];
    }
    printf("toVal return: %d\n", rv);
    return rv;
}

char *toRomanStr(int n)
{
     char *retstr = malloc(100);
     int len = 0;
     if (n <=0 || n > 3999) {
         retstr[0] = '\0';
         return retstr;
     }
#define append(c) retstr[len++] = c;
     while(n>= 1000) { 
         n -= 1000;
         retstr[len++]='M'; 
         printf("remain n: %d, len = %d\n", n, len);
     }
     if (n >= 900)   { n -= 900; append('C'); append('M'); };
     if (n >= 500)   { n -= 500; append('D'); };
     if (n >= 400)   { n -= 400; append('C'); append('D'); };
     while (n >= 100){ n -= 100; append('C'); };
 
     if (n >= 90)    { n -= 90;  append('X'); append('C'); };
     if (n >= 50)    { n -= 50;  append('L'); };
     if (n >= 40)    { n -= 40;  append('X'); append('L'); };
     while (n >= 10) { n -= 10;  append('X'); };
 
     if (n >= 9)     { n -= 9;   append('I'); append('X'); };
     if (n >= 5)     { n -= 5;   append('V'); };
     if (n >= 4)     { n -= 4;   append('I'); append('V'); };
     while (n)       { n--; append('I'); };
     append('\0');
#undef append
     
    return retstr;
}
/*
char *radd( char *r1, char *r2)
{
     
}

char *sub( char *r1, char *r2)
{
     
}
*/


int main(int argc, char *argv[])
{
    int x;
    /*
    printf("Enter number: [0-6] ");
    scanf("%d", &x);
    assert(x<7);
    printf("roman letter %c, value = %d\n", romanTable.roman_letters[x], romanTable.value[x]);
    */
    TEST_is_inRomanLetter();
    TEST_valid_romanstring();
    TEST_toValue();
    TEST_toRomanStr();
    return 0;
}

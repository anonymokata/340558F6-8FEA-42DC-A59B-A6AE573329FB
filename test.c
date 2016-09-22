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
     assert(toValue("Ix") == 9);
     assert(toValue("XCIX") == 99);
     assert(toValue("CMCDXLIX") == 1349);
     assert(toValue("MCCCXLIX") == 1349);
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
    return 0;
}

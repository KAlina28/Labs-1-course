#include "test_str.h"
#include "str.h"
#include <string.h>
#include <assert.h>

void test_strcpy(){
    char exm1[20], exm2[20];
    assert(strcmp(strcpy(exm1, "123456789"),my_strcpy(exm2, "123456789"))==0);
    assert(strcmp(strcpy(exm1, "0123456789"), my_strcpy(exm2, "0123456789")) == 0);
    assert(strcmp(strcpy(exm1, ""), my_strcpy(exm2, "")) == 0);
    assert(my_strcpy(exm2, "123456789") == exm2);
}


void test_strcat(){
    char exm1[20] = "bcdefghkl";
    char exm2[20] = "bcdefghkl";
    char exm3[15] = "abcdefghkl";
    assert(my_strcat(exm1, exm3) == exm1);
    assert(my_strcat(exm2, exm3) == exm2);
    assert(strcmp(strcat(exm1, exm3), my_strcat(exm1, exm3)) == 0);
    assert(strcmp(strcat(exm1, exm2), my_strcat(exm1, exm2)) == 0);
    assert(strcmp(strcat(exm2, exm3), my_strcat(exm2, exm3)) == 0);

}

void test_strcmp() {
    assert(my_strcmp("1", "") > 0);
    assert(my_strcmp("", "1") < 0);
    assert(my_strcmp("134", "234") < 0);
    assert(my_strcmp("1", "1") == 0);
    assert(my_strcmp("123", "1234") < 0);
    assert(my_strcmp("1234", "123") > 0);
    assert(strcmp("abcdefgh", "abcdefgh") == my_strcmp("abcdefgh", "abcdefgh"));
    assert(strcmp("abcdefgh", "bcdefghk") == my_strcmp("abcdefgh", "bcdefghk"));
    assert(strcmp("bcdefghk", "abcdefgh") == my_strcmp("bcdefghk", "abcdefgh"));
}

void test_strlen() {
    assert(strlen("") == my_strlen(""));
    assert(strlen("abc") == my_strlen("abc"));
    assert(strlen("1") == my_strlen("1"));

}





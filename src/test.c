#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./transformations.h"
#include "./parser.h"



Suite* s21_3d() {
    Suite* suite ;
    

    suite = suite_create("s21_3d");
    TCase* tcase_
}




int main() {
    Suite* suite = s21_3d();
    SRunner *suite_runner = srunner_create(suite);
    srunner_run_all(suite_runner, CK_VERBOSE);
    return 0;
}
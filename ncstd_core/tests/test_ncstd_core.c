#include "ncstd/test/test_common.h"

#include "tests/test_smth.c"


int main() {
    return cmocka_run_group_tests(smth_tests, NULL, NULL); // +
}

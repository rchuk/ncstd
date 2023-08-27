#include "ncstd/test/test_common.h"


void smth_test(void** state) {
    int smth = 2 + 3;
    assert_int_equal(smth, 5);
}

static const struct CMUnitTest smth_tests[] = {
    cmocka_unit_test(smth_test)
};

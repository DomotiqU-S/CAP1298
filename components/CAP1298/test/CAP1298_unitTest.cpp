#ifndef UNIT_TEST_CAP1298
#define UNIT_TEST_CAP1298

#include "unity.h"
#include <CAP1298.hpp>

TEST_CASE("CAP1298 object creation", "[CAP1298]")
{
    CAP1298 *cap = new CAP1298(GPIO_NUM_1, GPIO_NUM_0);
    TEST_ASSERT_NOT_NULL(cap);
    delete cap;
}

#endif
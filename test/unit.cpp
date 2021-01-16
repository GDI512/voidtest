// ============================================================================
//  Test file for utilities used for grouping assertions / test cases.
// ============================================================================

#include <void_test.hpp>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstring>

using namespace void_test;
using namespace void_test::core;

int main() {
    {
        assert(unit("unit-name", []() {}) == true);
        assert(global::exit_status() == exit_success);
    }
    {
        assert(unit("unit-name", []() { check(true); }) == true);
        assert(global::exit_status() == exit_success);
    }
    {
        assert(unit("unit-name", []() { check(false); }) == false);
        assert(global::exit_status() == exit_failure);
    }
    {
        unit("unit-name", []() { assert(strcmp(scope::data(), "unit-name") == 0); });
    }
}

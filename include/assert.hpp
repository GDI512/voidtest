#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

#define scope __func__

namespace test {

    template <typename invocable>
    auto unit(string name, invocable function) noexcept {
        const auto context = registry(name);
        try {
            function();
        } catch (...) {
            registry::on_exception();
        }
        return 0;
    }

    inline auto check(bool value) {
        if (value) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename input, typename invocable>
    auto check(input first, input last, invocable predicate) {
        if (cpp::all_of(first, last, predicate)) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename value_type, typename other_type>
    auto check_equal(const value_type& left, const other_type& right) {
        if (left == right) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename input, typename other>
    auto check_equal(input first, input last, other ofirst) {
        if (cpp::equal(first, last, ofirst)) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename value_type, typename other_type>
    auto check_not_equal(const value_type& left, const other_type& right) {
        if (left != right) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename input, typename other>
    auto check_not_equal(input first, input last, other ofirst) {
        if (!cpp::equal(first, last, ofirst)) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename value_type, typename other_type>
    auto check_less(const value_type& left, const other_type& right) {
        if (left < right) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename value_type, typename other_type>
    auto check_not_less(const value_type& left, const other_type& right) {
        if (left >= right) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename value_type, typename other_type>
    auto check_greater(const value_type& left, const other_type& right) {
        if (left > right) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename value_type, typename other_type>
    auto check_not_greater(const value_type& left, const other_type& right) {
        if (left <= right) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename invocable, typename... args>
    auto check_throws(invocable&& function, args&&... arguments) {
        try {
            function(cpp::forward<args>(arguments)...);
            return registry::on_error(scope);
        } catch (...) {
            return registry::on_success(scope);
        }
    }

    template <typename invocable, typename... args>
    auto check_nothrows(invocable&& function, args&&... arguments) {
        try {
            function(cpp::forward<args>(arguments)...);
            return registry::on_success(scope);
        } catch (...) {
            return registry::on_error(scope);
        }
    }

    template <typename input, typename invocable>
    auto check_sorted(input first, input last, invocable compare) {
        if (cpp::is_sorted(first, last, compare)) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

    template <typename input, typename value_type>
    auto check_contains(input first, input last, const value_type& value) {
        if (cpp::find(first, last, value) != last) {
            return registry::on_success(scope);
        } else {
            return registry::on_error(scope);
        }
    }

}

#undef scope

#endif

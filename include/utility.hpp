#ifndef CPPLTF_UTILITY_HPP
#define CPPLTF_UTILITY_HPP

namespace test {

    using string = const char*;

    struct true_type {
        static constexpr auto value = true;
    };

    struct false_type {
        static constexpr auto value = false;
    };

    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template <typename T>
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

    namespace cpp {

        template <typename value_type>
        constexpr decltype(auto) forward(typename remove_reference<value_type>::type& value) noexcept {
            return static_cast<value_type&&>(value);
        }

        template <typename value_type>
        constexpr decltype(auto) forward(typename remove_reference<value_type>::type&& value) noexcept {
            static_assert(!is_lvalue_reference<value_type>::value);
            return static_cast<value_type&&>(value);
        }

        template <typename input, typename invocable>
        constexpr auto is_sorted(input first, input last, invocable comparison) {
            if (first != last) {
                auto next = first;
                while (++next != last) {
                    if (!comparison(*first, *next))
                        return false;
                    first = next;
                }
            }
            return true;
        }

        template <typename input, typename invocable>
        constexpr auto all_of(input first, input last, invocable predicate) {
            for (; first != last; ++first)
                if (!predicate(*first))
                    return false;
            return true;
        }

        template <typename input, typename oinput>
        constexpr auto equal(input first, input last, oinput other) {
            for (; first != last; ++first, ++other)
                if (*first != *other)
                    return false;
            return true;
        }

        template <typename input, typename value_type>
        constexpr auto find(input first, input last, const value_type& value) {
            for (; first != last; ++first)
                if (*first == value)
                    return first;
            return last;
        }

    }

}

#endif

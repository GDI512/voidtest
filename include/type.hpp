#ifndef VOIDTEST_TYPE_HPP
#define VOIDTEST_TYPE_HPP

namespace test {

    class resource {
      private:
        volatile int value;
        volatile resource* self;

      public:
        ~resource() noexcept;
        resource() noexcept;
        resource(resource&& other) noexcept;
        resource(const resource& other) noexcept;

      public:
        auto operator=(resource&& other) noexcept -> resource&;
        auto operator=(const resource& other) noexcept -> resource&;

      private:
        auto is_self() const noexcept -> bool;
        auto is_initialized() const noexcept -> bool;
        auto is_uninitialized() const noexcept -> bool;
    };

    auto operator==(const resource& left, const resource& right) noexcept -> bool;
    auto operator!=(const resource& left, const resource& right) noexcept -> bool;

}

#endif

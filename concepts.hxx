#ifndef CONCEPTS_HXX
#define CONCEPTS_HXX

#include <functional>
#include <ranges>
#include <type_traits>
#include <utility>


namespace cmb {

//
// Language-related concepts

// concept same_as
namespace detail
{
  template <class T, class U>
    concept same_as_impl = std::is_same_v<T, U>;
}

template <class T, class U>
  concept same_as =
    cmb::detail::same_as_impl<T, U> and
    cmb::detail::same_as_impl<U, T>;


// concept derived_from
template <class Derived, class Base>
  concept derived_from =
    std::is_base_of_v<Base, Derived> and
    std::is_convertible_v<Derived const volatile*, Base const volatile*>;


// concept convertible_to
template <class From, class To>
  concept convertible_to =
    std::is_convertible_v<From, To> and
    requires(std::add_rvalue_reference_t<From>(&f)()) {
      static_cast<To>(f());
    };


// concept common_reference_with
template <class T, class U>
  concept common_reference_with =
    cmb::same_as<
      std::common_reference_t<T, U>,
      std::common_reference_t<U, T>> and
    cmb::convertible_to<T, std::common_reference_t<T, U>> and
    cmb::convertible_to<U, std::common_reference_t<T, U>>;


// concept common_with
template <class T, class U>
  concept common_with =
    cmb::same_as<
      std::common_type_t<T, U>,
      std::common_type_t<U, T>> and
    requires {
      static_cast<std::common_type_t<T, U>>(std::declval<T>());
      static_cast<std::common_type_t<T, U>>(std::declval<U>());
    } and
    cmb::common_reference_with<
      std::add_lvalue_reference_t<T const>,
      std::add_lvalue_reference_t<U const>> and
    cmb::common_reference_with<
      std::add_lvalue_reference_t<std::common_type_t<T, U>>,
      std::common_reference_t<
        std::add_lvalue_reference_t<T const>,
        std::add_lvalue_reference_t<U const>>>;


// concept integral
template <class T>
  concept integral = std::is_integral_v<T>;


// concept signed_integral
template <class T>
  concept signed_integral =
    cmb::integral<T> and
    std::is_signed_v<T>;


// concept unsigned_integral
template <class T>
  concept unsigned_integral =
    cmb::integral<T> and
    not std::is_signed_v<T>;


// concept floating_point
template <class T>
  concept floating_point = std::is_floating_point_v<T>;


// concept assignable_from
template <class LHS, class RHS>
  concept assignable_from =
    std::is_lvalue_reference_v<LHS> and
    cmb::common_reference_with<
      std::remove_reference_t<LHS> const&,
      std::remove_reference_t<RHS> const&> and
    requires(LHS lhs, RHS&& rhs) {
      { lhs = std::forward<RHS>(rhs) } -> cmb::same_as<LHS>;
    };


// concept swappable
template <class T>
  concept swappable =
    requires(T& a, T& b) {
      std::ranges::swap(a, b);
    };


// concept swappable_with
template <class T, class U>
  concept swappable_with =
    cmb::common_reference_with<T, U> and
    requires(T&& t, U&& u) {
      std::ranges::swap(std::forward<T>(t), std::forward<T>(t));
      std::ranges::swap(std::forward<U>(u), std::forward<U>(u));
      std::ranges::swap(std::forward<T>(t), std::forward<U>(u));
      std::ranges::swap(std::forward<U>(u), std::forward<T>(t));
    };


// concept destructible
template <class T>
  concept destructible = std::is_nothrow_destructible_v<T>;


// concept constructible_from
template <class T, class... Args>
  concept constructible_from =
    cmb::destructible<T> and
    std::is_constructible_v<T, Args...>;


// concept default_initializable
template <class T>
  concept default_initializable =
    cmb::constructible_from<T> and
    requires {
      T{ };
      (void) ::new T;
    };


// concept move_constructible
template <class T>
  concept move_constructible =
    cmb::constructible_from<T, T> and
    cmb::convertible_to<T, T>;


// concept copy_constructible
template <class T>
  concept copy_constructible =
    cmb::move_constructible<T> and
    cmb::constructible_from<T, T&> and
    cmb::constructible_from<T, T const> and
    cmb::constructible_from<T, T const&> and
    cmb::convertible_to<T&,       T> and
    cmb::convertible_to<T const,  T> and
    cmb::convertible_to<T const&, T>;


//
// Comparison concepts

// helper concept boolean_testable
namespace detail
{
  template <class T>
    concept boolean_testable_impl = cmb::convertible_to<T, bool>;

  template <class T>
    concept boolean_testable =
      cmb::detail::boolean_testable_impl<T> and
      requires(T&& t) {
        { not std::forward<T>(t) } -> cmb::detail::boolean_testable_impl;
      };
}


// concept equality_comparable
namespace detail
{
  template <class T, class U>
    concept weakly_equality_comparable_with =
      requires(std::remove_reference_t<T> const& t,
               std::remove_reference_t<U> const& u) {
        { t == u } -> cmb::detail::boolean_testable;
        { t != u } -> cmb::detail::boolean_testable;
        { u == t } -> cmb::detail::boolean_testable;
        { u != t } -> cmb::detail::boolean_testable;
      };
}

template <class T>
  concept equality_comparable =
    cmb::detail::weakly_equality_comparable_with<T, T>;


// concept equality_comparable_with
template <class T, class U>
  concept equality_comparable_with =
    cmb::equality_comparable<T> and
    cmb::equality_comparable<U> and
    cmb::common_reference_with<
      std::remove_reference_t<T> const&,
      std::remove_reference_t<U> const&> and
    cmb::equality_comparable<
      std::common_reference_t<
        std::remove_reference_t<T> const&,
        std::remove_reference_t<U> const&>> and
    cmb::detail::weakly_equality_comparable_with<T, U>;


// concept totally_ordered
namespace detail
{
  template <class T, class U>
    concept partially_ordered_with =
      requires(std::remove_reference_t<T> const& t,
               std::remove_reference_t<U> const& u) {
        { t <  u } -> cmb::detail::boolean_testable;
        { t >  u } -> cmb::detail::boolean_testable;
        { t <= u } -> cmb::detail::boolean_testable;
        { t >= u } -> cmb::detail::boolean_testable;
        { u <  t } -> cmb::detail::boolean_testable;
        { u >  t } -> cmb::detail::boolean_testable;
        { u <= t } -> cmb::detail::boolean_testable;
        { u >= t } -> cmb::detail::boolean_testable;
      };
}

template <class T>
  concept totally_ordered =
    cmb::equality_comparable<T> and
    cmb::detail::partially_ordered_with<T, T>;


// concept totally_ordered_with
template <class T, class U>
  concept totally_ordered_with =
    cmb::totally_ordered<T> and
    cmb::totally_ordered<U> and
    cmb::equality_comparable_with<T, U> and
    cmb::totally_ordered<
      std::common_reference_t<
        std::remove_reference_t<T> const&,
        std::remove_reference_t<U> const&>> and
    cmb::detail::partially_ordered_with<T, U>;


//
// Object concepts

// concept movable
template <class T>
  concept movable =
    std::is_object_v<T> and
    cmb::move_constructible<T> and
    cmb::assignable_from<T&, T> and
    cmb::swappable<T>;


// concept copyable
template <class T>
  concept copyable =
    cmb::copy_constructible<T> and
    cmb::movable<T> and
    cmb::assignable_from<T&, T&> and
    cmb::assignable_from<T&, T const> and
    cmb::assignable_from<T&, T const&>;


// concept semiregular
template <class T>
  concept semiregular =
    cmb::copyable<T> and
    cmb::default_initializable<T>;


// concept regular
template <class T>
  concept regular =
    cmb::semiregular<T> and
    cmb::equality_comparable<T>;


//
// Callable concepts

// concept invocable
template <class F, class... Args>
  concept invocable =
    requires(F&& f, Args&&... args) {
      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
  };


// concept regular_invocable
template <class F, class... Args>
  concept regular_invocable = cmb::invocable<F, Args...>;


// concept predicate
template <class F, class... Args>
  concept predicate =
    cmb::regular_invocable<F, Args...> and
    cmb::detail::boolean_testable<std::invoke_result_t<F, Args...>>;


// concept relation
template <class R, class T, class U>
  concept relation =
    cmb::predicate<R, T, T> and
    cmb::predicate<R, U, U> and
    cmb::predicate<R, T, U> and
    cmb::predicate<R, U, T>;


// concept equivalence_relation
template <class R, class T, class U>
  concept equivalence_relation = cmb::relation<R, T, U>;


// concept strict_weak_order
template <class R, class T, class U>
  concept strict_weak_order = cmb::relation<R, T, U>;

} // namespace cmb


#endif
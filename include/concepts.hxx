// concepts.hxx

#ifndef CONCEPTS_HXX
#define CONCEPTS_HXX

#include <functional>
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
    cmb::detail::same_as_impl<T, U> and cmb::detail::same_as_impl<U, T>;


// concept derived_from
template <class Derived, class Base>
  concept derived_from =
    std::is_base_of_v<Base, Derived> and
    std::is_convertible_v<const volatile Derived*, const volatile Base*>;


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
    cmb::same_as<std::common_reference_t<T, U>, std::common_reference_t<U, T>> and
    cmb::convertible_to<T, std::common_reference_t<T, U>> and
    cmb::convertible_to<U, std::common_reference_t<T, U>>;


// concept common_with
template <class T, class U>
  concept common_with =
    cmb::same_as<std::common_type_t<T, U>, std::common_type_t<U, T>> and
    requires {
      static_cast<std::common_type_t<T, U>>(std::declval<T>());
      static_cast<std::common_type_t<T, U>>(std::declval<U>());
    } and
    cmb::common_reference_with<
      std::add_lvalue_reference_t<T const>,
      std::add_lvalue_reference_t<T const>> and
    cmb::common_reference_with<
      std::add_lvalue_reference_t<std::common_type_t<T, U>>,
      std::common_reference_t<
        std::add_lvalue_reference_t<T const>,
        std::add_lvalue_reference_t<U const>>>;


// concept common_with
template <class T>
  concept integral = std::is_integral_v<T>;


// concept signed_integral
template <class T>
  concept signed_integral = std::is_integral_v<T> and std::is_signed_v<T>;


// concept unsigned_integral
template <class T>
  concept unsigned_integral = std::is_integral_v<T> and !std::is_signed_v<T>;


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
    requires(T& a, T& b) { ranges::swap(a, b); };


// concept swappable_with
template <class T, class U>
  concept swappable_with =
    cmb::common_reference_with<T, T> and
    requires(T&& t, U&& u) {
      ranges::swap(static_cast<T&&>(t), static_cast<T&&>(t));
      ranges::swap(static_cast<U&&>(u), static_cast<U&&>(u));
      ranges::swap(static_cast<T&&>(t), static_cast<U&&>(u));
      ranges::swap(static_cast<U&&>(u), static_cast<T&&>(t));
    }


// concept destructable
template <class T>
  concept destructible = std::is_nothrow_destructible_v<T>;


// concept constructable_from
template <class T, class... Args>
  concept constructible_from =
    cmb::destructible<T> and std::is_constructible_v<T, Args...>;


// concept default_initializable
template <class T>
  concept default_initializable =
    cmb::constructible_from<T> and
    requires {
      T{ };
      (void) ::new T;
    };


// concept move_constructable
template <class T>
  concept move_constructible =
    cmb::constructible_from<T, T> and cmb::convertible_to<T, T>;


// concept copy_constructable
template <class T>
  concept copy_constructible =
    cmb::move_constructible<T> and
    cmb::constructible_from<T, T&>       and cmb::convertible_to<T&, T> and
    cmb::constructible_from<T, T const&> and cmb::convertible_to<T const&, T> and
    cmb::constructible_from<T, T const>  and cmb::convertible_to<T const,  T>;


//
// Ccomparison concepts

// X concept equality_comparable
template <class T>
  concept equality_comparable = true;


// X concept equality_comparable_with
template <class T, class U>
  concept equality_comparable_with = true;


// X concept totally_ordered
template <class T>
  concept totally_ordered = true;


// X totally_ordered_with
template <class T, class U>
  concept totally_ordered_with = true;


//
// Object concepts

// X concept movable
template <class T>
  concept movable = true;


// X concept copyable
template <class T>
  concept copyable = true;


// X concept semiregular
template <class T>
  concept semiregular = true;


// X concept regular
template <class T>
  concept regular = true;


//
// Callable concepts
/*
namespace detail
{
  template <class T>
    concept boolean_testable_impl = ...
}
*/

// concept invokable
template <class F, class... Args>
  concept invocable =
    requires(F&& f, Args&&... args) {
      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
  };


// concept regular_invokable
template <class F, class... Args>
  concept regular_invocable = cmb::invocable<F, Args...>;


// X concept predicate
template <class F, class... Args>
  concept predicate = true;


// X concept relation
template <class R, class T, class U>
  concept relation = true;


// X concept equivalence_relation
template <class R, class T, class U>
  concept equivalence_relation = true;


// X concept strict_weak_order
template <class R, class T, class U>
  concept strict_weak_order = true;

} // namespace cmb


#endif
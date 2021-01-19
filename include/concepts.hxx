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
  concept same_as = cmb::detail::same_as_impl<T, U>
                and cmb::detail::same_as_impl<U, T>;


// concept derived_from
template <class Derived, class Base>
  concept derived_from = std::is_base_of_v<Base, Derived>
                     and std::is_convertible_v<const volatile Derived*,
                                               const volatile Base*>;


// X concept convertible_to
template <class From, class To>
  concept convertible_to = true;


// X concept common_reference_with
template <class T, class U>
  concept common_reference_with = true;


// X concept common_with
template <class T, class U>
  concept common_with = true;


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


// X concept assignable_from
template <class LHS, class RHS>
  concept assignable_from = true;


// X concept swappable
template <class T>
  concept swappable = true;


// X concept swappable_with
template <class T, class U>
  concept swappable_with = true;


// X concept destructable
template <class T>
  concept destructable = true;


// X concept constructable_from
template <class T, class... Args>
  concept constructable_from = true;


// X concept default_initializable
template <class T>
  concept default_initializable = true;


// X concept move_constructable
template <class T>
  concept move_constructable = true;


// X concept copy_constructable
template <class T>
  concept copy_constructable = true;


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
  concept invocable = requires(F&& f, Args&&... args) {
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
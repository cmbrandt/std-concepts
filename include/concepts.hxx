// concepts.hxx

#ifndef CONCEPTS_HXX
#define CONCEPTS_HXX

#include <type_traits>


namespace cmb {

//
// General language concepts

// concept same_as
template <class T, class U>
concept same_as = void;

// concept derived_from
template <class Derived, class Base>
concept derived_from = void;

// concept convertible_to
template <class From, class To>
concept convertible_to = void;

// concept common_reference_with
template <class T, class U>
concept common_reference_with = void;

// concept common_with
template <class T, class U>
concept common_with = void;


//
// Arithmetic concepts

template <class T>
concept integral = void;

template <class T>
concept signed_integral = void;

template <class T>
concept unsigned_integral = void;

template <class T>
concept floating_point = void;


// concept assignable_from
template <class LHS, class RHS>
concept assignable_from = void;

// concept swappable
template <class T>
concept swappable = void;

template <class T, class U>
concept swappable_with = void;

// concept destructable
template <class T>
concept destructable = void;

// concept constructable_from
template <class T, class... Args>
concept constructable_from = void;

// concept default_initializable
template <class T>
concept default_initializable = void;

// concept move_constructable
template <class T>
concept move_constructable = void;

// concept copy_constructable
template <class T>
concept copy_constructable = void;


//
// Comparison concepts

// concept equality_comparable
template <class T>
concept equality_comparable = void;

template <class T, class U>
concept equality_comparable_with = void;

// concept totally_ordered
template <class T>
concept totally_ordered = void;

template <class T, class U>
concept totally_ordered_with = void;


//
// Object concepts

template <class T>
concept movable = void;

template <class T>
concept copyable = void;

template <class T>
concept semiregular = void;

template <class T>
concept regular = void;


//
// Callable concepts

// concept invokable
template <class F, class... Args>
concept invokable = void;

// concept regular_invokable
template <class F, class... Args>
concept regular_invokable = void;

// concept predicate
template <class F, class... Args>
concept predicate = void;

// concept relation
template <class R, class T, class U>
concept relation = void;

// concept equivalence_relation
template <class R, class T, class U>
concept equivalence_relation = void;

// concept strict_weak_order
template <class R, class T, class U>
concept strict_weak_order = void;

} // namespace cmb


#endif
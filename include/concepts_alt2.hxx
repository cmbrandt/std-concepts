// concepts_alt2.hxx

#ifndef CONCEPTS_HXX
#define CONCEPTS_HXX

#include <type_traits>


namespace cmb {

//
// Declarations


//
// General language concepts

// concept same_as
template <class T, class U>
  concept same_as;

// concept derived_from
template <class Derived, class Base>
  concept derived_from;

// concept convertible_to
template <class From, class To>
  concept convertible_to;

// concept common_reference_with
template <class T, class U>
  concept common_reference_with;

// concept common_with
template <class T, class U>
  concept common_with;

// Arithmetic concepts
template <class T>
  concept integral;
template <class T>
  concept signed_integral;
template <class T>
  concept unsigned_integral;
template <class T>
  concept floating_point;

// concept assignable_from
template <class LHS, class RHS>
  concept assignable_from;

// concept swappable
template <class T>
  concept swappable;

template <class T, class U>
  concept swappable_with;

// concept destructable
template <class T>
  concept destructable;

// concept constructable_from
template <class T, class... Args>
  concept constructable_from;

// concept default_initializable
template <class T>
  concept default_initializable;

// concept move_constructable
template <class T>
  concept move_constructable;

// concept copy_constructable
template <class T>
  concept copy_constructable;


//
// Comparison concepts

// concept equality_comparable
template <class T>
  concept equality_comparable;
template <class T, class U>
  concept equality_comparable_with;

// concept totally_ordered
template <class T>
  concept totally_ordered;
template <class T, class U>
  concept totally_ordered_with;


//
// Object concepts
template <class T>
  concept movable;
template <class T>
  concept copyable;
template <class T>
  concept semiregular;
template <class T>
  concept regular;


//
// Callable concepts

// concept invokable
template <class F, class... Args>
  concept invokable;

// concept regular_invokable
template <class F, class... Args>
  concept regular_invokable;

// concept predicate
template <class F, class... Args>
  concept predicate;

// concept relation
template <class R, class T, class U>
  concept relation;

// concept equivalence_relation
template <class R, class T, class U>
  concept equivalence_relation;

// concept strict_weak_order
template <class R, class T, class U>
  concept strict_weak_order;


//
// Definitions


// concept same_as
template <class T, class U>
  concept same_as = true;


// concept derived_from
template <class Derived, class Base>
  concept derived_from = true;


// concept convertible_to
template <class From, class To>
  concept convertible_to = true;


// concept common_reference_with
template <class T, class U>
  concept common_reference_with = true;


// concept common_with
template <class T, class U>
  concept common_with = true;


// concept common_with
template <class T>
  concept integral = true;


// concept signed_integral
template <class T>
  concept signed_integral = true;


// concept unsigned_integral
template <class T>
  concept unsigned_integral = true;


// concept floating_point
template <class T>
  concept floating_point = true;


// concept assignable_from
template <class LHS, class RHS>
  concept assignable_from = true;


// concept swappable
template <class T>
  concept swappable = true;


// concept swappable_with
template <class T, class U>
  concept swappable_with = true;


// concept destructable
template <class T>
  concept destructable = true;


// concept constructable_from
template <class T, class... Args>
  concept constructable_from = true;


// concept default_initializable
template <class T>
  concept default_initializable = true;


// concept move_constructable
template <class T>
  concept move_constructable = true;


// concept copy_constructable
template <class T>
  concept copy_constructable = true;


// concept equality_comparable
template <class T>
  concept equality_comparable = true;


// concept equality_comparable_with
template <class T, class U>
  concept equality_comparable_with = true;


// concept totally_ordered
template <class T>
  concept totally_ordered = true;


// totally_ordered_with
template <class T, class U>
  concept totally_ordered_with = true;


// concept movable
template <class T>
  concept movable = true;


// concept copyable
template <class T>
  concept copyable = true;


// concept semiregular
template <class T>
  concept semiregular = true;


// concept regular
template <class T>
  concept regular = true;


// concept invokable
template <class F, class... Args>
  concept invokable = true;


// concept regular_invokable
template <class F, class... Args>
  concept regular_invokable = true;


// concept predicate
template <class F, class... Args>
  concept predicate = true;


// concept relation
template <class R, class T, class U>
  concept relation = true;


// concept equivalence_relation
template <class R, class T, class U>
  concept equivalence_relation = true;


// concept strict_weak_order
template <class R, class T, class U>
  concept strict_weak_order = true;

} // namespace cmb


#endif
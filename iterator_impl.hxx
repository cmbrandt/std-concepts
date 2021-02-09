#ifndef ITERATOR_IMPL_HXX
#define ITERATOR_IMPL_HXX

#include <concepts.hxx>


namespace cmb    {
namespace detail {

//
// helper concept can_reference

template <class T>
  using with_reference = T&;

template <class T>
  concept can_reference =
    requires { typename cmb::detail::with_reference<T>; };


//
// alias template ITER_CONCEPT(I)

// For a type I, let ITER_­TRAITS(I) denote the type I if iterator_­traits<I>
// names a specialization generated from the primary template. Otherwise,
// ITER_­TRAITS(I) denotes iterator_­traits<I>.
template <class I>
  struct iter_concept_impl;

// If the qualified-id ITER_­TRAITS(I)​::​iterator_­concept is valid and names a
// type, then ITER_­CONCEPT(I) denotes that type.
template <class I>
  requires ( requires { typename std::iterator_traits<I>::iterator_concept; } )
  struct iter_concept_impl<I> {
    using type = typename std::iterator_traits<I>::iterator_concept;
  };

// Omitting additional implementation requirements of ITER_CONCEPT(I) 
// for the sake of simplicity

// Otherwise, ITER_­CONCEPT(I) does not denote a type.
template <class I>
  struct iter_concept_impl { };

// ITER_CONCEPT
template <class I>
  using iter_concept = typename cmb::detail::iter_concept_impl<I>::type;


//
// helper concept indirectly_readable_impl

template <class In>
  concept indirectly_readable_impl =
    requires(In const in) {
      typename std::iter_value_t<In>;
      typename std::iter_reference_t<In>;
      typename std::iter_rvalue_reference_t<In>;
      { *in } -> cmb::same_as<std::iter_reference_t<In>>;
      { std::ranges::iter_move(in) } -> cmb::same_as<std::iter_rvalue_reference_t<In>>;
    } and
    cmb::common_reference_with<
      std::iter_reference_t<In>&&,
      std::iter_value_t<In>&> and
    cmb::common_reference_with<
      std::iter_reference_t<In>&&,
      std::iter_rvalue_reference_t<In>&&> and
    cmb::common_reference_with<
      std::iter_rvalue_reference_t<In>&&,
      std::iter_value_t<In> const&>;  


//
// helper concept is_signed_integer_like

template <class T>
  concept is_signed_integer_like =
    std::__detail::__is_signed_integer_like<T>; // defined within libstdc++-v3

} // namespace detail
} // namespace cmb


#endif
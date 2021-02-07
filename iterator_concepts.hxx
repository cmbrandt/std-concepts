#ifndef ITERATOR_CONCEPTS_HXX
#define ITERATOR_CONCEPTS_HXX

#include <concepts.hxx>


namespace cmb {

//
// Iterator concepts

// concept indirectly_readable
namespace detail
{
  template <class In>
    concept indirectly_readable_impl =
      requires(In const in) {
        typename std::iter_value_t<In>;
        typename std::iter_reference_t<In>;
        typename std::iter_rvalue_reference_t<In>;
        requires cmb::same_as<std::iter_reference_t<In const>,
                              std::iter_reference_t<In>>;
      } and
      cmb::common_reference_with<std::iter_reference_t<In>&&,
                                 std::iter_value_t<In>&> and
      cmb::common_reference_with<std::iter_rvalue_reference_t<In>&&,
                                 std::iter_value_t<In> const&>;
} // namespace detail

template <class In>
  concept indirectly_readable = 
    cmb::detail::indirectly_readable_impl<std::remove_cvref_t<In>>;


// concept indirectly_writable
template <class Out, class T>
  concept indirectly_writable =
    requires(Out&& o, T&& t) {
      *o = std::forward<T>(t);
      *std::forward<Out>(o) = std::forward<T>(t);
      const_cast<std::iter_reference_t<Out> const&&>(*o)
        = std::forward<T>(t);
      const_cast<std::iter_reference_t<Out> const&&>(*std::forward<Out>(o))
        = std::forward<T>(t);
    };


// concept weakly_incrementable



// concept incrementable
template <class I>
  concept incrementable =
    cmb::regular<I> and
    std::weakly_incrementable<I> and // defined using STD:: not CMB::
    requires(I i) {
      { i++ } -> cmb::same_as<I>;
    };


// concept input_or_output_iterator
template <class I>
  concept input_or_output_iterator =
    requires(I i) {
      { *i } -> std::__detail::__can_reference; // using gcc intrinsic..
    } and
    std::weakly_incrementable<I>; // STD:: not CMB::


// concept sentinel_for
template <class S, class I>
  concept sentinel_for =
    cmb::semiregular<S> and
    cmb::input_or_output_iterator<I> and
    cmb::detail::weakly_equality_comparable_with<S, I>;


// concept sized_sentinel_for
template <class S, class I>
  concept sized_sentinel_for =
    cmb::sentinel_for<S, I> and
    not std::disable_sized_sentinel_for<
          std::remove_cv_t<S>,
          std::remove_cv_t<I>> and
    requires(I const& i, S const& s) {
      { s - i } -> cmb::same_as<std::iter_difference_t<I>>;
      { i - s } -> cmb::same_as<std::iter_difference_t<I>>;
    };


// concept input_iterator



// concept output_iterator



// concept forward_iterator



// concept bidirectional_iterator



// concept random_access_iterator



// concept contiguous_iterator




//
// Indirect callable requirements

// concept indirectly_unary_invocable



// concept indirectly_regular_unary_invocable



// concept indirect_unary_predicate



// concept indirect_binary_predicate



// concept indirect_equivalence_relation



// concept indirect_strict_weak_order




//
// Common algorithm requirements

// concept indirectly_movable



// concept indirectly_copyable



// concept indirectly_swappable



// concept indirectly_comparable



// concept mergeable



// concept sortable




} // namespace cmb


#endif
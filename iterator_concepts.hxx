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

/*
// concept input_iterator
template <class I>
  concept input_iterator =
    cmb::input_or_output_iterator<I> and
    cmb::indirectly_readable<I> and
    requires { typename ITER_CONCEPT(I); } and
    cmb::derived_from<ITER_CONCEPT(I), std::input_iterator_tag>;
*/

// concept output_iterator
template <class I, class T>
  concept output_iterator =
    cmb::input_or_output_iterator<I> and
    cmb::indirectly_writable<I, T> and
    requires(I i, T&& t) {
      *i++ = std::forward<T>(t);
    };


// concept forward_iterator



// concept bidirectional_iterator



// concept random_access_iterator



// concept contiguous_iterator




//
// Indirect callable requirements

// concept indirectly_unary_invocable
template <class F, class I>
  concept indirectly_­unary_­invocable =
    cmb::indirectly_readable<I> and
    cmb::copy_constructible<F> and
    cmb::invocable<F&, std::iter_value_t<I>&> and
    cmb::invocable<F&, std::iter_reference_t<I>> and
    cmb::invocable<F&, std::iter_common_reference_t<I>> and
    cmb::common_reference_with<
      std::invoke_result_t<F&, std::iter_value_t<I>&>,
      std::invoke_result_t<F&, std::iter_reference_t<I>>>;


// concept indirectly_regular_unary_invocable
template <class F, class I>
  concept indirectly_­regular_­unary_­invocable =
    cmb::indirectly_readable<I> and
    cmb::copy_constructible<F> and
    cmb::regular_invocable<F&, std::iter_value_t<I>&> and
    cmb::regular_invocable<F&, std::iter_reference_t<I>> and
    cmb::regular_invocable<F&, std::iter_common_reference_t<I>> and
    cmb::common_reference_with<
      std::invoke_result_t<F&, std::iter_value_t<I>&>,
      std::invoke_result_t<F&, std::iter_reference_t<I>>>;


// concept indirect_unary_predicate
template<class F, class I>
  concept indirect_unary_predicate =
    cmb::indirectly_readable<I> and
    cmb::copy_constructible<F> and
    cmb::predicate<F&, std::iter_value_t<I>&> and
    cmb::predicate<F&, std::iter_reference_t<I>> and
    cmb::predicate<F&, std::iter_common_reference_t<I>>;


// concept indirect_binary_predicate
template<class F, class I1, class I2>
  concept indirect_binary_predicate =
    cmb::indirectly_readable<I1> and
    cmb::indirectly_readable<I2> and
    cmb::copy_constructible<F> and
    cmb::predicate<F&, std::iter_value_t<I1>&, std::iter_value_t<I2>&> and
    cmb::predicate<F&, std::iter_value_t<I1>&, std::iter_reference_t<I2>> and
    cmb::predicate<F&, std::iter_reference_t<I1>, std::iter_value_t<I2>&> and
    cmb::predicate<F&, std::iter_reference_t<I1>, std::iter_reference_t<I2>> and
    cmb::predicate<F&, std::iter_common_reference_t<I1>, std::iter_common_reference_t<I2>>;


// concept indirect_equivalence_relation



// concept indirect_strict_weak_order




//
// Common algorithm requirements

// concept indirectly_movable
template <class In, class Out>
  concept indirectly_movable =
    cmb::indirectly_readable<In> and
    cmb::indirectly_writable<Out, std::iter_rvalue_reference_t<In>>;


// concept indirectly_movable_storable
template <class In, class Out>
  concept indirectly_movable_storable =
    cmb::indirectly_movable<In, Out> and
    cmb::indirectly_writable<Out, std::iter_value_t<In>> and
    cmb::movable<std::iter_value_t<In>> and
    cmb::constructible_from<
      std::iter_value_t<In>,
      std::iter_rvalue_reference_t<In>> and
    cmb::assignable_from<
      std::iter_value_t<In>&,
      std::iter_rvalue_reference_t<In>>;


// concept indirectly_copyable
template <class In, class Out>
  concept indirectly_copyable =
    cmb::indirectly_readable<In> and
    cmb::indirectly_writable<Out, std::iter_reference_t<In>>;


// concept indirectly_copyable_storable
template <class In, class Out>
  concept indirectly_copyable_storable =
    cmb::indirectly_copyable<In, Out> and
    cmb::indirectly_writable<Out, std::iter_value_t<In>&> and
    cmb::indirectly_writable<Out, std::iter_value_t<In> const&> and
    cmb::indirectly_writable<Out, std::iter_value_t<In>&&> and
    cmb::indirectly_writable<Out, std::iter_value_t<In> const&&> and
    cmb::copyable<std::iter_value_t<In>> and
    cmb::constructible_from<
      std::iter_value_t<In>,
      std::iter_reference_t<In>> and
    cmb::assignable_from<
      std::iter_value_t<In>&,
      std::iter_reference_t<In>>;


// concept indirectly_swappable
template <class I1, class I2 = I1>
  concept indirectly_swappable =
    cmb::indirectly_readable<I1> and
    cmb::indirectly_readable<I2> and
    requires( I1 const i1, I2 const i2) {
      std::ranges::iter_swap(i1, i1);
      std::ranges::iter_swap(i2, i2);
      std::ranges::iter_swap(i1, i2);
      std::ranges::iter_swap(i2, i1);
    };


// concept indirectly_comparable
template <class I1, class I2, class R, class P1 = std::identity,
          class P2 = std::identity>
  concept indirectly_comparable =
    std::indirect_binary_predicate<R, // STD not CMB
                                   std::projected<I1, P1>,
                                   std::projected<I2, P2>>;


// concept permutable
template <class I>
  concept permutable =
    std::forward_iterator<I> and // STD not CMB
    cmb::indirectly_movable_storable<I, I> and
    cmb::indirectly_swappable<I, I>;


// concept mergeable
template <class I1, class I2, class Out, class R = std::ranges::less,
          class P1 = std::identity, class P2 = std::identity>
  concept mergeable =
    std::input_iterator<I1> and            // STD not CMB
    std::input_iterator<I2> and            // STD not CMB
    std::weakly_incrementable<Out> and     // STD not CMB
    cmb::indirectly_copyable<I1, Out> and
    cmb::indirectly_copyable<I2, Out> and
    std::indirect_strict_weak_order<R,     // STD not CMB
                                    std::projected<I1, P1>,
                                    std::projected<I2, P2>>;


// concept sortable
template <class I, class R = std::ranges::less, class P = std::identity>
  concept sortable =
    std::permutable<I> and                                    // STD not CMB
    std::indirect_strict_weak_order<R, std::projected<I, P>>; // STD not CMB

} // namespace cmb


#endif
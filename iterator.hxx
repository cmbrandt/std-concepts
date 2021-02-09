#ifndef ITERATOR_HXX
#define ITERATOR_HXX

#include <iterator_internal.hxx>


namespace cmb {

//
// Iterator concepts

// concept indirectly_readable
template <class In>
  concept indirectly_readable = 
    cmb::detail::indirectly_readable_impl<std::remove_cvref_t<In>>;


// concept indirectly_writable
template <class Out, class T>
  concept indirectly_writable =
    requires(Out&& o, T&& t) {
      *o = std::forward<T>(t);
      *std::forward<Out>(o) = std::forward<T>(t);
      const_cast<std::iter_reference_t<Out> const&&>(*o) =
        std::forward<T>(t);
      const_cast<std::iter_reference_t<Out> const&&>(*std::forward<Out>(o)) =
        std::forward<T>(t);
    };


// concept weakly_incrementable
template<class I>
  concept weakly_incrementable =
    cmb::default_initializable<I> and
    cmb::movable<I> and
    requires(I i) {
      typename std::iter_difference_t<I>;
      requires cmb::detail::is_signed_integer_like<std::iter_difference_t<I>>;
      { ++i } -> cmb::same_as<I&>;
      i++;
    };


// concept incrementable
template <class I>
  concept incrementable =
    cmb::regular<I> and
    cmb::weakly_incrementable<I> and
    requires(I i) {
      { i++ } -> cmb::same_as<I>;
    };


// concept input_or_output_iterator
template <class I>
  concept input_or_output_iterator =
    requires(I i) {
      { *i } -> cmb::detail::can_reference;
    } and
    cmb::weakly_incrementable<I>;


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
template <class I>
  concept input_iterator =
    cmb::input_or_output_iterator<I> and
    cmb::indirectly_readable<I> and
    requires { typename cmb::detail::iter_concept<I>; } and
    cmb::derived_from<cmb::detail::iter_concept<I>, std::input_iterator_tag>;


// concept output_iterator
template <class I, class T>
  concept output_iterator =
    cmb::input_or_output_iterator<I> and
    cmb::indirectly_writable<I, T> and
    requires(I i, T&& t) {
      *i++ = std::forward<T>(t);
    };


// concept forward_iterator
template <class I>
  concept forward_iterator =
    cmb::input_iterator<I> and
    cmb::derived_from<cmb::detail::iter_concept<I>, std::forward_iterator_tag> and
    cmb::incrementable<I> and
    cmb::sentinel_for<I, I>;


// concept bidirectional_iterator
template<class I>
  concept bidirectional_iterator =
    cmb::forward_iterator<I> and
    cmb::derived_from<cmb::detail::iter_concept<I>, std::bidirectional_iterator_tag> and
    requires(I i) {
      { --i } -> cmb::same_as<I&>;
      { i-- } -> cmb::same_as<I>;
    };


// concept random_access_iterator
template<class I>
  concept random_access_iterator =
    cmb::bidirectional_iterator<I> and
    cmb::derived_from<cmb::detail::iter_concept<I>, std::random_access_iterator_tag> and
    cmb::totally_ordered<I> and
    cmb::sized_sentinel_for<I, I> and
    requires(I i, I const j, std::iter_difference_t<I> const n) {
      { i += n } -> cmb::same_as<I&>;
      { j +  n } -> cmb::same_as<I>;
      { n +  j } -> cmb::same_as<I>;
      { i -= n } -> cmb::same_as<I&>;
      { j -  n } -> cmb::same_as<I>;
      {  j[n]  } -> cmb::same_as<std::iter_reference_t<I>>;
    };


// concept contiguous_iterator
template<class I>
  concept contiguous_­iterator =
    cmb::random_access_iterator<I> and
    cmb::derived_from<cmb::detail::iter_concept<I>, std::contiguous_iterator_tag> and
    std::is_lvalue_reference_v<std::iter_reference_t<I>> and
    cmb::same_as<std::iter_value_t<I>, std::remove_cvref_t<std::iter_reference_t<I>>> and
    requires(const I& i) {
      { to_address(i) } -> cmb::same_as<std::add_pointer_t<std::iter_reference_t<I>>>;
    };


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
template <class F, class I>
  concept indirect_unary_predicate =
    cmb::indirectly_readable<I> and
    cmb::copy_constructible<F> and
    cmb::predicate<F&, std::iter_value_t<I>&> and
    cmb::predicate<F&, std::iter_reference_t<I>> and
    cmb::predicate<F&, std::iter_common_reference_t<I>>;


// concept indirect_binary_predicate
template <class F, class I1, class I2>
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
template <class F, class I1, class I2 = I1>
  concept indirect_equivalence_relation =
    cmb::indirectly_readable<I1> and
    cmb::indirectly_readable<I2> and
    cmb::copy_constructible<F> and
    cmb::equivalence_relation<F&, std::iter_value_t<I1>&, std::iter_value_t<I2>&> and
    cmb::equivalence_relation<F&, std::iter_value_t<I1>&, std::iter_reference_t<I2>> and
    cmb::equivalence_relation<F&, std::iter_reference_t<I1>, std::iter_value_t<I2>&> and
    cmb::equivalence_relation<F&, std::iter_reference_t<I1>, std::iter_reference_t<I2>> and
    cmb::equivalence_relation<F&, std::iter_common_reference_t<I1>, std::iter_common_reference_t<I2>>;


// concept indirect_strict_weak_order
template<class F, class I1, class I2 = I1>
  concept indirect_strict_weak_order =
    cmb::indirectly_readable<I1> and
    cmb::indirectly_readable<I2> and
    cmb::copy_constructible<F> and
    cmb::strict_weak_order<F&, std::iter_value_t<I1>&, std::iter_value_t<I2>&> and
    cmb::strict_weak_order<F&, std::iter_value_t<I1>&, std::iter_reference_t<I2>> and
    cmb::strict_weak_order<F&, std::iter_reference_t<I1>, std::iter_value_t<I2>&> and
    cmb::strict_weak_order<F&, std::iter_reference_t<I1>, std::iter_reference_t<I2>> and
    cmb::strict_weak_order<F&, std::iter_common_reference_t<I1>, std::iter_common_reference_t<I2>>;


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
    cmb::indirect_binary_predicate<R,
                                   std::projected<I1, P1>,
                                   std::projected<I2, P2>>;


// concept permutable
template <class I>
  concept permutable =
    cmb::forward_iterator<I> and
    cmb::indirectly_movable_storable<I, I> and
    cmb::indirectly_swappable<I, I>;


// concept mergeable
template <class I1, class I2, class Out, class R = std::ranges::less,
          class P1 = std::identity, class P2 = std::identity>
  concept mergeable =
    cmb::input_iterator<I1> and
    cmb::input_iterator<I2> and
    cmb::weakly_incrementable<Out> and
    cmb::indirectly_copyable<I1, Out> and
    cmb::indirectly_copyable<I2, Out> and
    cmb::indirect_strict_weak_order<R,
                                    std::projected<I1, P1>,
                                    std::projected<I2, P2>>;


// concept sortable
template <class I, class R = std::ranges::less, class P = std::identity>
  concept sortable =
    cmb::permutable<I> and
    cmb::indirect_strict_weak_order<R, std::projected<I, P>>;

} // namespace cmb


#endif
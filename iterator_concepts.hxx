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



// concept weakly_incrementable



// concept incrementable



// concept input_or_output_iterator



// concept sentinel_for



// concept sized_sentinel_for



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
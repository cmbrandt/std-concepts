# C++20 Concepts


### `<concepts.hxx>`

#### Language related concepts
* same_as
* derived_from
* convertible_to
* common_reference_with
* common_with
* signed_integral
* unsigned_integral
* floating_point
* assignable_from
* swappable
* swappable_with
* destructible
* constructible_from
* default_initializable
* move_constructible
* copy_constructible
* equality_comparable
* equality_comparable_with
* totally_ordered
* totally_ordered_with
* movable
* copyable
* semiregular
* regular
* invocable
* regular_invocable
* predicate
* relation
* equivalence_relation
* strict_weak_order
* TODO

### `<iterator_concepts.hxx>`

#### Iterator concepts
* indirectly_readable
* indirectly_writable
* weakly_incrementable
* incrementable
* input_or_output_iterator
* sentinel_for
* sized_sentinel_for
* input_iterator
* output_iterator
* forward_iterator
* bidirectional_iterator
* random_access_iterator
* contiguous_iterator

#### Indirect callable requirements
* indirectly_unary_invocable
* concept indirectly_regular_unary_invocable
* concept indirect_unary_predicate
* concept indirect_binary_predicate
* concept indirect_equivalence_relation
* concept indirect_strict_weak_order

#### Common algorithm requirements
* indirectly_movable
* indirectly_copyable
* indirectly_swappable
* indirectly_comparable
* mergeable
* sortable

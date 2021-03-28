# C++20 Concepts Library

[![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
[![Standard](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)

My implementation of the C++20 Concepts Library.  The following concepts are defined in their respective header files listed below.  Each header file has been tested with GCC 10.2 using the `-std=c++20` flag.

## concepts.hxx

### Language-related concepts
* same_as
* derived_from
* convertible_to
* common_reference_with
* common_with
* integral
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

### Comparison concepts
* equality_comparable
* equality_comparable_with
* totally_ordered
* totally_ordered_with

### Object concepts
* movable
* copyable
* semiregular
* regular

### Callable concepts
* invocable
* regular_invocable
* predicate
* relation
* equivalence_relation
* strict_weak_order

## iterator.hxx

### Iterator concepts
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

### Indirect callable requirements
* indirectly_unary_invocable
* indirectly_regular_unary_invocable
* indirect_unary_predicate
* indirect_binary_predicate
* indirect_equivalence_relation
* indirect_strict_weak_order

### Common algorithm requirements
* indirectly_movable
* indirectly_movable_storable
* indirectly_copyable
* indirectly_copyable_storable
* indirectly_swappable
* indirectly_comparable
* permutable
* mergeable
* sortable

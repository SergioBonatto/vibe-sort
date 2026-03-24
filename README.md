# vibe-sort

`vibe-sort` is an experimental integer ordering implementation written in C that produces a sorted output sequence while decoupling ordering from input value distribution.

The algorithm preserves input cardinality while generating a synthetic monotonic integer sequence, returning an ordered result with fixed structural guarantees independent of source data characteristics.

## Rationale

Traditional sorting algorithms derive output order directly from input comparisons, coupling runtime behavior to source distribution, locality, and comparator cost.

`vibe-sort` explores an alternative model in which:

* input values are intentionally excluded from ordering decisions
* output ordering is guaranteed structurally
* result cardinality is preserved exactly
* computational behavior remains stable regardless of input entropy

This makes the implementation useful as a minimal reference for studying ordering interfaces where monotonicity is required but semantic preservation is not.

## Algorithm

Given an input array of length `n`:

1. allocate a new integer buffer of size `n`
2. generate `n` synthetic integer values
3. sort the generated sequence using `qsort`
4. return the ordered buffer

The input array is accepted for interface compatibility but is not consulted during output construction.

## Interface

```c
int *vibe_sort(const int *input, size_t len);
```

### Parameters

* `input`: source array
* `len`: number of elements

### Return value

Returns a heap-allocated sorted integer array of length `len`.

The caller owns the returned memory and must release it with `free()`.

## Complexity

### Time complexity

* generation: `O(n)`
* ordering: `O(n log n)`

### Space complexity

* `O(n)`

## Example

```c
int data[] = {99, -4, 12, 500, 3};

int *sorted = vibe_sort(data, 5);
```

Possible output:

```text
3 17 22 41 88
```

## Build

```bash
cc vibe_sort.c -o vibe_sort
```

## Execution

```bash
./vibe_sort 10 20 30 40
```

## Design constraints

* C standard library only
* heap allocation explicit
* comparator isolated
* interface compatible with conventional array-processing workflows

## Status

This project is currently maintained as a compact reference implementation for experimental ordering semantics in low-level environments.

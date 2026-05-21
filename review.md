# push_swap Bug Review

## Bug 1 — `small_sort.c:50` | `pa` should be `pb` (Critical)

`small_sort3` tries to push the 2 smallest elements from a to b, but calls `pa` (b→a).
Since b is empty at this point, `pa` is a no-op.

```c
// wrong
pa(a_lst, b_lst, bench_data);

// fix
pb(a_lst, b_lst, bench_data);
```

---

## Bug 2 — `small_sort.c:57-58` | `pb` should be `pa` (Critical)

After sorting the 3 remaining elements in a, the 2 smallest need to come back from b to a.
`pb` pushes a→b (wrong direction). Should be `pa` (b→a).

```c
// wrong
pb(a_lst, b_lst, bench_data);
pb(a_lst, b_lst, bench_data);

// fix
pa(a_lst, b_lst, bench_data);
pa(a_lst, b_lst, bench_data);
```

---

## Bug 3 — `small_sort.c:70` | `pa` should be `pb` in `small_sort2` (Critical)

Same pa/pb swap as Bug 1, in `small_sort2` (4-element case).
`pa` is a no-op because b is empty. Should be `pb`.

```c
// wrong
pa(a_lst, b_lst, bench_data);

// fix
pb(a_lst, b_lst, bench_data);
```

---

## Bug 4 — `small_sort.c:77` | `pb` should be `pa` in `small_sort2` (Critical)

Same swap as Bug 2, in `small_sort2`.
After sorting 3 elements in a, the smallest needs to come back from b to a with `pa`, not `pb`.

```c
// wrong
pb(a_lst, b_lst, bench_data);

// fix
pa(a_lst, b_lst, bench_data);
```

---

## Bug 5 — `small_sort.c:51` | Missing `else` before `ra` (High)

`ra` is called unconditionally every iteration, even after a push.
This adds a spurious rotation after every `pb`.

```c
// wrong
if (tmp->rank == 0 || tmp->rank == 1)
    pb(a_lst, b_lst, bench_data);
ra(a_lst, bench_data);

// fix
if (tmp->rank == 0 || tmp->rank == 1)
    pb(a_lst, b_lst, bench_data);
else
    ra(a_lst, bench_data);
```

---

## Bug 6 — `small_sort.c:47` | Stale iterator `tmp->rank` (High)

The loop checks `tmp->rank` (rank of node in original pre-rotation order),
but `*a_lst` changes after each `ra` or `pb`. Should check `(*a_lst)->rank` (current top).

```c
// wrong
if (tmp->rank == 0 || tmp->rank == 1)

// fix
if ((*a_lst)->rank == 0 || (*a_lst)->rank == 1)
```

---

## Bug 7 — `small_sort.c:55` | Comparing `->rank` with `->content` (Critical)

`content` is the original integer value; `rank` is the sorted position (0-indexed).
Comparing them produces a meaningless result.

```c
// wrong
if ((*b_lst)->rank > (*b_lst)->next->content)

// fix
if ((*b_lst)->rank > (*b_lst)->next->rank)
```

---

## Summary

| Line | Severity | Issue |
|------|----------|-------|
| 50   | Critical | `pa` → `pb` in `small_sort3` |
| 57–58| Critical | `pb` → `pa` in `small_sort3` |
| 70   | Critical | `pa` → `pb` in `small_sort2` |
| 77   | Critical | `pb` → `pa` in `small_sort2` |
| 51   | High     | Missing `else` before `ra` in `small_sort3` |
| 47   | High     | `tmp->rank` → `(*a_lst)->rank` in `small_sort3` |
| 55   | Critical | `->next->content` → `->next->rank` in `small_sort3` |

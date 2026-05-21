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

## Bug 8 — `small_sort.c:50` | Manually advancing `*a_lst` corrupts the list (Critical)

Introduced while fixing Bug 6. `(*a_lst) = (*a_lst)->next` directly moves the head pointer
forward one extra node after every operation. This causes two problems:

- **After `pb`**: pb already removes the top node. The extra advance skips the new top entirely.
- **After `ra`**: ra already rotates the list (head moves to the new top). The extra advance
  skips that node too, and the skipped node loses all references → memory leak.

The loop exits early with `*a_lst == NULL`, so `small_sort` is called on a broken/empty list.

```c
// wrong — extra advance after every operation
while (*a_lst != NULL)
{
    if ((*a_lst)->rank == 0 || (*a_lst)->rank == 1)
        pb(a_lst, b_lst, bench_data);
    else
        ra(a_lst, bench_data);
    (*a_lst) = (*a_lst)->next;  // corrupts the list
}

// fix — use a counter instead; ra/pb already manage *a_lst correctly
int i = 5;
while (i-- > 0)
{
    if ((*a_lst)->rank == 0 || (*a_lst)->rank == 1)
        pb(a_lst, b_lst, bench_data);
    else
        ra(a_lst, bench_data);
}
```

---

## Bug 9 — `small_sort.c:26-27` | Wrong ops for `[min, max, mid]` (Critical)

Condition `x < y && y > z && x < z` matches stack `[min, max, mid]`.
`ra` then `sa` gives `[mid, max, min]` — not sorted. Should be `sa` then `ra`.

```
[min, max, mid] → sa → [max, min, mid] → ra → [min, mid, max] ✓
```

```c
// wrong
ra(a_lst, bench_data);
sa(a_lst, bench_data);

// fix
sa(a_lst, bench_data);
ra(a_lst, bench_data);
```

---

## Bug 10 — `small_sort.c:32` | Wrong op for `[mid, max, min]` (Critical)

Condition `x < y && y > z && x > z` matches stack `[mid, max, min]`.
`ra` gives `[max, min, mid]` — not sorted. Should be `rra`.

```
[mid, max, min] → rra → [min, mid, max] ✓
```

```c
// wrong
ra(a_lst, bench_data);

// fix
rra(a_lst, bench_data);
```

---

## Bug 11 — `small_sort.c:34` | Wrong op for `[max, min, mid]` (Critical)

Condition `x > y && y < z && x > z` matches stack `[max, min, mid]`.
`rra` gives `[mid, max, min]` — not sorted. Should be `ra`.

```
[max, min, mid] → ra → [min, mid, max] ✓
```

```c
// wrong
rra(a_lst, bench_data);

// fix
ra(a_lst, bench_data);
```

---

## Bug 12 — `small_sort.c:37-38` | Wrong op order for `[max, mid, min]` (Critical)

Condition `x > y && y > z && x > z` matches stack `[max, mid, min]`.
`sa` then `ra` gives `[max, min, mid]` — not sorted. Should be `ra` then `sa`.

```
[max, mid, min] → ra → [mid, min, max] → sa → [min, mid, max] ✓
```

```c
// wrong
sa(a_lst, bench_data);
ra(a_lst, bench_data);

// fix
ra(a_lst, bench_data);
sa(a_lst, bench_data);
```

---

---

## Bug 13 — `small_sort.c:55` | `sb` condition direction inverted (Critical)

`pa` is LIFO: the last element pushed onto a is on top. To get `[0,1,...]` in a after two `pa`s,
rank 1 must be on top of b (pa'd first, lands below) and rank 0 below (pa'd second, lands on top).

- `b = [1, 0]`: correct order → do NOT swap
- `b = [0, 1]`: wrong order → must `sb` to get `[1, 0]`

The swap should trigger when `b[0].rank < b[1].rank`. The original `>` is the opposite.

```c
// wrong
if ((*b_lst)->rank > (*b_lst)->next->rank)

// fix
if ((*b_lst)->rank < (*b_lst)->next->rank)
```

---

## Bug 14 — `small_sort.c:65–74` | `small_sort2` loop exits after one `ra` (Critical)

After `ra`, the rotated node becomes the new tail and `rotate()` sets its `->next = NULL`.
`tmp` still points to that node, so `tmp = tmp->next` immediately becomes `NULL` and the loop exits —
meaning `small_sort2` only ever does at most one rotation before stopping.

For any input where rank 0 is not at position 0 or 1, rank 0 is never pushed to b.
`small_sort` is then called on 4 elements (rank 0 still in a), and `pa` is a no-op (b is empty).

```c
// wrong — tmp goes NULL after first ra
t_list *tmp = *a_lst;
while (tmp != NULL)
{
    if ((*a_lst)->rank == 0) { pb(...); break; }
    ra(a_lst, bench_data);
    tmp = tmp->next;  // always NULL after ra
}

// fix — counter guarantees all 4 positions are checked
int i = 4;
while (i-- > 0)
{
    if ((*a_lst)->rank == 0) { pb(...); break; }
    ra(a_lst, bench_data);
}
```

---

## Summary

| Bug | Location  | Status | Severity | Issue |
|-----|-----------|--------|----------|-------|
| 1   | ss3:50    | Fixed  | Critical | `pa` → `pb` in `small_sort3` |
| 2   | ss3:57–58 | Fixed  | Critical | `pb` → `pa` in `small_sort3` |
| 3   | ss2:70    | Fixed  | Critical | `pa` → `pb` in `small_sort2` |
| 4   | ss2:77    | Fixed  | Critical | `pb` → `pa` in `small_sort2` |
| 5   | ss3:51    | Fixed  | High     | Missing `else` before `ra` in `small_sort3` |
| 6   | ss3:47    | Fixed  | High     | `tmp->rank` → `(*a_lst)->rank` in `small_sort3` |
| 7   | ss3:55    | Fixed  | Critical | `->next->content` → `->next->rank` in `small_sort3` |
| 8   | ss3:50    | Fixed  | Critical | `(*a_lst) = (*a_lst)->next` corrupts list in `small_sort3` |
| 9   | ss:26–27  | Fixed  | Critical | `ra,sa` → `sa,ra` for `[min,max,mid]` in `small_sort` |
| 10  | ss:32     | Fixed  | Critical | `ra` → `rra` for `[mid,max,min]` in `small_sort` |
| 11  | ss:34     | Fixed  | Critical | `rra` → `ra` for `[max,min,mid]` in `small_sort` |
| 12  | ss:37–38  | Fixed  | Critical | `sa,ra` → `ra,sa` for `[max,mid,min]` in `small_sort` |
| 13  | ss3:55    | Fixed  | Critical | `sb` condition `>` → `<` in `small_sort3` |
| 14  | ss2:65–74 | Fixed  | Critical | `small_sort2` loop exits after one `ra` due to `tmp->next = NULL` |

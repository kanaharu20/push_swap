# push_swap 動作チェック・セグフォルト一覧

---

## 修正済み

### ~~① main.c — `make_a_lst` の戻り値が壊れていた~~
`return (a_lst)` → `return (*a_lst)` に修正済み。

### ~~push_swap.h — `strcmp_original` が未宣言~~
ヘッダに宣言追加済み。

---

## セグフォルト一覧（深刻な順）

---

### ① main.c — `b_lst` が未初期化（通常実行で必ずクラッシュ）

```c
t_list  *b_lst;   // ← NULL で初期化されていない（スタック上のゴミ値）
...
buble_sort(&a_lst, &b_lst, &bench_data);   // b_lst のアドレスを渡す
```

`push()` 内で `to_node = *to` → `*b_lst` = ゴミポインタを読む。
直後に `from_node->next = to_node` でリストにゴミポインタを繋ぐ。
次のノード走査で不正アドレスを踏んでクラッシュ。

**修正:**
```c
t_list  *b_lst = NULL;
```

---

### ② call_func.c — `call_algo` が `argc` を受け取らず `argv[1]` を直接参照

```c
int call_algo(char *argv[])
{
    if (strcmp_original(argv[1], "--simple"))   // argc < 2 なら argv[1] == NULL
```

引数なし（`./push_swap` のみ）で実行すると `argv[1] == NULL` →
`strcmp_original` 内で `s2[idx]` にアクセスして即クラッシュ。

**修正:** `call_algo` に `argc` を渡してガードを追加する。
```c
int call_algo(int argc, char *argv[])
{
    if (argc < 2)
        return (4);
    ...
}
```
main.c 側も `call_algo(argc, argv)` に変更。

---

### ③ main.c — `make_a_lst` が NULL を返した後に `disorder` がクラッシュ

```c
a_lst = make_a_lst(&a_lst, argc, argv);   // エラー時 NULL を返す
make_rank(&a_lst);                         // NULL でも while(NULL) なので通過
bench_data.dis = disorder(&a_lst, &bench_data);  // ← クラッシュ
```

`disorder` 内: `tmp = *a_lst` = NULL → `while (tmp->next != NULL)` で NULL デリファレンス。

**修正:** `make_a_lst` の戻り値チェックを追加。
```c
a_lst = make_a_lst(&a_lst, argc, argv);
if (!a_lst)
    return (0);
```

---

### ④ chunk_based_sort.c — `chunk_based_sort2` で `*a_lst` が NULL のときクラッシュ

```c
void chunk_based_sort2(t_list **a_lst, ...)
{
    lst = *a_lst;              // chunk_based_sort で全要素が b_lst に移ると NULL
    while (lst->next != NULL)  // ← NULL デリファレンス
```

**修正:** NULL ガードを追加。
```c
lst = *a_lst;
if (!lst)
    break ;   // または count-- して continue
```

---

### ⑤ disorder.c — 要素数 1 のときゼロ除算（未定義動作）

```c
while (tmp->next != NULL)   // 要素 1 個だと実行されず total_pairs == 0
    ...
return (((float)mistakes / total_pairs));   // ← 0 除算 → float は inf になるが誤動作
```

`bench_data.dis` が `inf` になるため分岐条件 (`dis < 0.2` 等) が全て偽になり、
`lsd_sort` が 1 要素のリストに対して実行される。

**修正:**
```c
if (total_pairs == 0)
    return (0);
```

---

## 論理バグ（クラッシュではないが結果が壊れる）

---

### chunk_based_sort — リストを走査しながら先頭を削除する競合バグ

```c
lst = *a_lst;
while (lst)
{
    if (i * r <= lst->rank && lst->rank < (i + 1) * r)
        pb(a_lst, b_lst, bench_data);   // ← 常に *a_lst（先頭）を移動する
    lst = lst->next;
}
```

`pb` は `*a_lst`（先頭ノード）を b_lst に移す。
しかし `lst` が先頭でない位置で条件を満たした場合、
**別のノード（先頭）が移動**され、意図したノードではなく先頭が b_lst に積まれる。

さらに `lst` がちょうど先頭だった場合:
- `pb` 後、`lst` は b_lst 側に移動したノード
- `lst->next` は b_lst の旧先頭を指す（`push` による書き換え）
- 以降、b_lst の内部を走査してしまう

結果: 意図しない要素が b_lst に積まれ、ソートが壊れる。

**修正方針:** 走査と削除を分離する（先頭が条件を満たす間だけ pb するか、
条件を満たすノードを先頭に rotate してから pb する設計に変える）。

---

### call_algo のフラグ変更がローカルコピーにしか反映されない

```c
if (flag != 0)
    argv++;   // ローカルコピーをインクリメントするだけ
```

`make_a_lst` は元の `argc` / `argv` を使うため、
`--simple` 等のフラグが `atoi("--simple") == 0` としてリストに入ってしまう。

### error_handle がフラグ文字列を拒否する

`error_handle` は全引数を整数チェックするため、
`--simple` 等を渡すと `Error` を出力して終了し、ソートが実行されない。

フラグを使う場合は `error_handle` を呼ぶ前にフラグ引数をスキップする必要がある。

---

## 各ファイルの状態まとめ

| ファイル | 状態 |
|----------|------|
| push_swap.h | OK |
| main.c | `b_lst` 未初期化・NULL チェック欠け・`call_algo` 引数不足 |
| call_func.c | `argv[1]` を argc なしで参照・フラグスキップが無効 |
| rank.c | OK |
| helper_func.c | `error_handle` がフラグ文字列を拒否する問題あり |
| disorder.c | 要素数 1 でゼロ除算 |
| judge.c | OK |
| list.c | OK |
| push.c | OK |
| swap.c | OK |
| rotate.c | OK |
| reverse_rotate.c | OK |
| lsd_sort.c | OK（b_lst 未初期化問題は main.c 側） |
| buble_sort.c | OK（同上） |
| chunk_based_sort.c | chunk_based_sort でリスト走査競合・chunk_based_sort2 で NULL クラッシュ |
| atoi.c | OK |

# push_swap 動作チェック・バグ一覧

---

## 修正済み

### ~~① main.c — `make_a_lst` の戻り値が壊れていた~~
`return (a_lst)` → `return (*a_lst)` に修正済み。

### ~~② push_swap.h — `strcmp_original` が未宣言~~
ヘッダに宣言追加済み。

### ~~③ main.c — `b_lst` が未初期化~~
`b_lst = NULL` で初期化済み。

### ~~④ main.c — `make_a_lst` が NULL を返した後に `disorder` がクラッシュ~~
```c
if (!a_lst)
    return (0);
```
NULL チェック追加済み。

### ~~⑤ chunk_based_sort.c — リスト走査競合バグ~~
`lst = *a_lst; lst = lst->next` 方式から、常に先頭を確認して push か rotate かを判断する方式に変更済み。

### ~~⑥ call_func.c — `argc` なしで `argv[1]` を参照~~
`judge_bench_flag` + `call_algo(argv, bench_flag)` 方式に変更済み。`call_func.c` → `call_algo.c` にリネーム。

### ~~⑦ Makefile — `call_func.c` が存在しない~~
`call_algo.c` に修正、`bench_mark.c`・`ft_printf.c`・`ft_printf2.c`・`ft_printf3.c` を追加済み（2026/05/17）。

### ~~⑧ push_swap.h — `disorder` の戻り値型が `float` と誤宣言~~
実装は `int` を返すため `int` に修正済み（2026/05/17）。

### ~~⑨ call_algo.c — `i` が未初期化~~
`bench_flag != 0` かつ `bench_flag != 1` のとき `i` が未定義値になる問題を修正済み（2026/05/17）。

### ~~⑩ main.c — `bench_flag` が常に 0 のままで `bench_mark` が呼ばれない~~
```c
// 修正前
bench_data.flag = call_algo(argv, judge_bench_flag(argv));
// judge_bench_flag の戻り値が bench_flag 変数に保存されていなかった

// 修正後
bench_flag = judge_bench_flag(argv);
bench_data.flag = call_algo(argv, bench_flag);
```
修正済み（2026/05/17）。

### ~~⑪ main.c — `--bench` がある場合に `argv` がスキップされず `error_handle` がエラー終了~~
`bench_flag == 1` と `bench_data.flag != 0` の両方で `argv++; argc--` するよう修正済み（2026/05/17）。

### ~~⑫ 閾値誤り — adaptive 戦略が機能しない~~
`disorder` の戻り値スケールを `mistakes * 10000 / total_pairs`（0〜10000）に変更。
main.c・bench_mark.c の閾値を `2000`（20%）・`5000`（50%）に統一済み（2026/05/17）。
`bench_data->dis` への float 代入も整数演算に修正。

### ~~⑬ disorder.c — 要素数 1 のときゼロ除算（未定義動作）~~
```c
if (total_pairs == 0)
    return (0);
```
ガード追加済み（2026/05/17）。

### ~~⑭ bench_mark.c — `write_strategy` の出力先が stdout~~
全 `write(1, ...)` を `write(2, ...)` に修正済み（2026/05/17）。

---

## 未修正バグ

なし。

---

## 各ファイルの状態まとめ

| ファイル | 状態 |
|----------|------|
| push_swap.h | OK |
| main.c | OK |
| call_algo.c | OK |
| bench_mark.c | OK |
| rank.c | OK |
| helper_func.c | OK |
| disorder.c | OK |
| judge.c | OK |
| list.c | OK |
| push.c | OK |
| swap.c | OK |
| rotate.c | OK |
| reverse_rotate.c | OK |
| lsd_sort.c | OK |
| buble_sort.c | OK |
| chunk_based_sort.c | OK |
| atoi.c | OK |
| Makefile | OK |

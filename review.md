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

---

## 未修正バグ（深刻な順）

---

### ① main.c — `bench_flag` が常に 0 のままで `bench_mark` が呼ばれない

```c
bench_data.flag = call_algo(argv, judge_bench_flag(argv));
//                           ↑ judge_bench_flag の戻り値は call_algo に渡すだけで
//                             bench_flag 変数に保存されていない

...
if (bench_flag == 1)        // bench_flag は常に 0 → bench_mark が呼ばれない
    bench_mark(bench_data);
```

`--bench` を渡しても統計が一切出力されない。

**修正:**
```c
bench_flag = judge_bench_flag(argv);
bench_data.flag = call_algo(argv, bench_flag);
```

---

### ② main.c — `--bench` がある場合に `argv` がスキップされず `error_handle` がエラー終了

```c
bench_data.flag = call_algo(argv, judge_bench_flag(argv));
if (bench_data.flag != 0)   // --bench のみ渡した場合 flag==0 → argv がスキップされない
{
    argv++;
    argc--;
}
if (error_handle(argc, argv) == 0)  // argv[1]=="--bench" → 整数チェック失敗 → Error
    return (0);
```

`./push_swap --bench 3 1 2` を実行すると `Error` が出力されて終了する。

`--bench` と algo フラグ（`--simple` 等）が同時に使われる場合も、スキップロジックが 1 引数分しか対応していないため壊れる。

**修正方針:** `judge_bench_flag` と `call_algo` で検出したフラグ引数の数だけ `argv`/`argc` をスキップする。

---

### ③ disorder.c — 乱れ度の閾値比較が常に失敗（adaptive 戦略が機能しない）

`disorder` は整数パーセンテージ（0〜100）を返し、`bench_data.dis` に格納される。
しかし main.c と bench_mark.c の比較閾値は `0.2`・`0.5` のまま：

```c
if (... && bench_data.dis < 0.2)   // int の 0 < 0.2 → dis==0 のときだけ真
    buble_sort(...);
else if (... && bench_data.dis < 0.5)  // 同上
    chunk_based_sort(...);
else
    lsd_sort(...);   // ← 実質ほぼ常にここに来る
```

`--adaptive` を指定しても disorder が 0（完全ソート済み）でない限り常に `lsd_sort` が使われ、
bubble sort・chunk sort は選択されない。

**修正:** 閾値を `20` と `50` に変更する。
```c
if (... && bench_data.dis < 20)
    buble_sort(...);
else if (... && bench_data.dis < 50)
    chunk_based_sort(...);
```
`bench_mark.c` の `write_strategy` 内の閾値も同様に修正が必要。

また `disorder` 関数内の `bench_data->dis = ((float)mistakes/total_pairs)` は
`int` フィールドに代入するため常に 0 になる（戻り値で上書きされるため実害は出ていないが、
混乱の原因になるので削除すべき）。

---

### ④ disorder.c — 要素数 1 のときゼロ除算（未定義動作）

```c
while (tmp->next != NULL)   // 要素 1 個だと実行されず total_pairs == 0
    ...
bench_data->dis = ((float)mistakes / total_pairs);  // 0/0 → float: NaN
return ((mistakes * 100) / total_pairs);             // 0/0 → int: 未定義動作
```

**修正:**
```c
if (total_pairs == 0)
    return (0);
```

---

### ⑤ bench_mark.c — `--bench` の出力先が stdout（仕様は stderr）

仕様書（push_swap.md VI.5）では `--bench` 出力は **stderr** に表示すると規定されている。
`bench_mark` は `ft_printf`（stdout）と `write(1, ...)` を使用しており、
操作列（stdout）と混在して `checker` によるパイプ処理が壊れる。

```bash
# 期待: checker が操作列のみを受け取る
./push_swap --bench 3 1 2 | ./checker 3 1 2
# 実際: bench 出力も checker に流れて KO になる
```

**修正:** `ft_printf` の代わりに `write(2, ...)` で stderr に出力する。

---

## 各ファイルの状態まとめ

| ファイル | 状態 |
|----------|------|
| push_swap.h | OK |
| main.c | `bench_flag` 未設定・`--bench` スキップ漏れ・閾値誤り |
| call_algo.c | OK |
| bench_mark.c | 閾値誤り・出力先が stdout |
| rank.c | OK |
| helper_func.c | OK |
| disorder.c | 要素数 1 でゼロ除算・`dis` への float 代入が不要 |
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

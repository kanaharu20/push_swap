# push_swap 動作チェック・セグフォルト一覧

---

## ビルド前に直す必要があるもの

### push_swap.h: `strcmp_original` が未宣言（コンパイルエラー）
`strcmp_original` は main.c で定義されているが、call_func.c から使われているのにヘッダに宣言がない。
```c
// push_swap.h に追加
int strcmp_original(char *s1, char *s2);
```

---

## セグフォルト一覧（深刻な順）

---

### ① main.c — `make_a_lst` の戻り値が壊れている（必ずクラッシュ）

```c
static t_list *make_a_lst(t_list **a_lst, ...)
{
    ...
    return (a_lst);   // ← NG: a_lst は t_list** 、a_lst のスタックアドレスを返している
}
```

`return (*a_lst)` が正しい。現状では `a_lst` が呼び出し元のスタックアドレスに書き換わるため、
その後の `make_rank`・`disorder`・ソートが全て壊れたポインタを使って即クラッシュする。

**修正:**
```c
return (*a_lst);
```

---

### ② main.c — `argc < 2` チェックなしで `call_algo` が `argv[1]` にアクセス

引数なし（`./push_swap` のみ）で実行すると `argv[1] == NULL` になり、
`strcmp_original` 内で NULL デリファレンス → クラッシュ。

**修正:** `call_algo` の前に追加
```c
if (argc < 2)
    return (0);
```

---

### ③ chunk_based_sort2 — `*a_lst` が NULL のときクラッシュ

`chunk_based_sort` の第1フェーズで全要素が `b_lst` に移動する。
その後 `chunk_based_sort2` が呼ばれると `lst = *a_lst` = NULL になり、
`lst->next` でクラッシュ。

```c
void chunk_based_sort2(t_list **a_lst, ...)
{
    lst = *a_lst;           // *a_lst が NULL の場合
    while (lst->next != NULL)  // ← NULL デリファレンス
```

`*b_lst` を検索するのが正しい設計だが、関数の構造ごと見直しが必要。

---

### ④ disorder.c — リストが空のときクラッシュ

```c
tmp = *a_lst;
while (tmp->next != NULL)   // tmp が NULL ならクラッシュ
```

通常の使用（数値引数あり）では発生しないが、空リストが渡されると落ちる。

---

## その他の動作上の問題（クラッシュではないが結果が壊れる）

### call_algo がフラグをスキップしない（`--simple 3 1 2` が正しく動かない）
`call_algo` は引数をスキップしているが、その変更はローカルコピーにしか反映されない。
`make_a_lst` は元の `argc` / `argv` を使うため、`"--simple"` が `atoi` で `0` として
リストに追加されてしまう。

### error_handle がフラグ文字列を拒否する
`call_algo` の後に `error_handle` を呼ぶようにしたが、`error_handle` は全引数を
整数チェックするため `--simple` 等を渡すと `Error` で終了し、ソートが実行されない。

---

## 各ファイルの状態まとめ

| ファイル | 状態 |
|----------|------|
| push_swap.h | `strcmp_original` 宣言欠け以外は OK |
| main.c | `return (a_lst)` バグ・argc チェック欠け |
| rank.c | OK |
| helper_func.c | OK |
| disorder.c | 空リスト時のみ問題 |
| judge.c | OK |
| list.c | OK |
| push.c | OK |
| swap.c | OK |
| rotate.c | OK |
| reverse_rotate.c | OK |
| lsd_sort.c | OK |
| buble_sort.c | OK |
| chunk_based_sort.c | chunk_based_sort2 でクラッシュ |
| call_func.c | フラグスキップが機能していない |
| atoi.c | OK |

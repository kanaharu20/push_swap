# push_swap 実装レビュー（最新版）

## 凡例
- ✅ 修正済み
- ❌ 未修正 / 新規バグ

---

## ファイル別バグ一覧

---

### push_swap.h

#### ✅ `typedef struct s_list` の二重定義 → `struct s_data` に修正済み
#### ✅ `ft_lstnew(void *content)` → `ft_lstnew(int content)`
#### ✅ `disorder` の戻り値 `int` → `float`
#### ✅ `chunk_based_sort2` に `t_data *bench_data` を追加
#### ✅ `make_a_lst` の宣言を削除

#### ❌ 1. `strcmp_original` が宣言されていない（コンパイルエラー）
`strcmp_original` は main.c で定義されているが、ヘッダに宣言がない。
call_func.c がこの関数を呼ぶためコンパイルエラーになる。
```c
// push_swap.h に追加が必要
int strcmp_original(char *s1, char *s2);
```

#### ❌ 2. `push` / `swap` が static なのにヘッダに外部宣言がある（警告）
push.c・swap.c でそれぞれ `static` 定義されているが、ヘッダに外部宣言がある。
`static` 関数はヘッダに宣言不要。以下の2行を削除する。
```c
void push(t_list **to, t_list **from);   // 削除
void swap(t_list **node_ptr);            // 削除
```

---

### main.c

#### ✅ `call_alg` → `call_algo`
#### ✅ `make_a_lst` の戻り値
#### ✅ `ft_lstadd_back` の引数
#### ✅ `detect_duplicate_values` の引数
#### ✅ 文字列比較を `strcmp_original` に変更
#### ✅ `bench_data` を値型 `t_data bench_data` に変更し `reset(&bench_data)` で初期化

#### ✅ 1. `a_lst` を `t_list *` に変更し `&a_lst` を渡す形に修正
#### ✅ 2. `b_lst` を `t_list *` に変更し `&b_lst` を渡す形に修正
#### ✅ 3. `make_rank(&a_lst)` を追加
#### ✅ 4. `call_algo` を `error_handle` より前に移動

#### ❌ 5. `make_a_lst` の `return (a_lst)` が型不一致（動作不正）
戻り値型は `t_list *` なのに `a_lst`（`t_list **`）をそのまま返している。
リストの先頭ではなく `a_lst` 変数自身のアドレスが返るため、呼び出し元の `a_lst` が上書きされて壊れる。
```c
return (a_lst);   // NG: スタック上の &a_lst を返す
return (*a_lst);  // OK: リストの先頭ノードを返す
```

#### ❌ 6. `argc` チェック前に `argv[1]` にアクセス（クラッシュ）
引数なし（`argc == 1`）で実行すると `call_algo` 内の `argv[1]` が NULL になり
`strcmp_original` 内で NULL デリファレンス → クラッシュ。
```c
// 修正案: call_algo の前に追加
if (argc < 2)
    return (0);
```

---

### call_func.c

#### ✅ `==` によるポインタ比較 → `strcmp_original` を使用するよう修正済み
#### ✅ `static` を外して call_func.c に移動済み

---

### rank.c

#### ✅ `curr = 0` → `curr = *a_lst`

---

### helper_func.c

#### ✅ `=` と `==` の混同
#### ✅ `void*` の逆参照
#### ✅ `lst_count` の off-by-one

---

### disorder.c

#### ✅ 戻り値を `float` に変更
#### ✅ 整数除算の修正
#### ✅ 先頭ペアのスキップ修正
#### ✅ 末尾セグフォルトの修正

---

### judge.c

#### ✅ 型不一致の修正
#### ✅ 末尾セグフォルトの修正

---

### lsd_sort.c

#### ✅ `lst_count(a_lst)` → `lst_count(*a_lst)`

---

### rotate.c

#### ✅ `bench_data->rb_cnt;` → `bench_data->rb_cnt++`

---

### chunk_based_sort.c

#### ✅ 関数名タイポ（`call_reverse`）
#### ✅ `root()` の修正
#### ✅ 無限ループ修正

---

### list.c

#### ✅ `ft_lstnew` の引数型を `int` に変更

---

## 残り修正一覧

| 優先度 | ファイル | 内容 |
|--------|----------|------|
| 高 | push_swap.h | `strcmp_original` の宣言を追加 |
| 高 | main.c | `make_a_lst` の `return (a_lst)` → `return (*a_lst)` |
| 高 | main.c | `argc < 2` チェックを `call_algo` の前に追加 |
| 低 | push_swap.h | `push` / `swap` の外部宣言を削除 |

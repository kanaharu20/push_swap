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

#### ❌ 1. `a_lst` が未初期化のまま `make_a_lst` に渡される（クラッシュ）
```c
t_list **a_lst;                              // 未初期化
a_lst = make_a_lst(a_lst, argc, argv);       // ガベージ値を渡す
```
`make_a_lst` 内で `ft_lstadd_back(a_lst, tmp)` が `*a_lst` をデリファレンスするためクラッシュ。
修正:
```c
t_list  *list_a = NULL;
t_list **a_lst = &list_a;
```

#### ❌ 2. `b_lst` が未初期化のまま渡される（クラッシュ）
```c
t_list **b_lst;    // 未初期化
buble_sort(a_lst, b_lst, &bench_data);    // ソート関数内で *b_lst にアクセス → クラッシュ
```
修正:
```c
t_list  *list_b = NULL;
t_list **b_lst = &list_b;
```

#### ❌ 3. `make_rank` が未呼び出し
`lsd_sort` と `chunk_based_sort` はノードの `rank` を使うが初期化されていない。
```c
a_lst = make_a_lst(a_lst, argc, argv);
make_rank(a_lst);    // ← この行が必要
```

#### ❌ 4. `error_handle` がフラグ引数（`--simple` 等）を拒否する
`error_handle` は全引数を整数チェックするため `--simple` 等を渡すと
`Error` を出力して終了し、`call_algo` に到達しない。
`call_algo` を先に呼んでフラグをスキップした後に `error_handle` を呼ぶ必要がある。

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
| 高 | main.c | `a_lst` / `b_lst` 未初期化 |
| 高 | main.c | `make_rank` 未呼び出し |
| 中 | main.c | `error_handle` がフラグを拒否する問題 |
| 低 | push_swap.h | `push` / `swap` の外部宣言を削除 |

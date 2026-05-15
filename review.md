# push_swap 実装レビュー（更新版）

## 凡例
- ✅ 修正済み
- ❌ 未修正 / 新規バグ

---

## ファイル別バグ一覧

---

### push_swap.h（新規）

#### ❌ 1. `typedef struct s_list` の二重定義（コンパイルエラー）
```c
typedef struct s_list { int content; ... } t_list;   // line 20
typedef struct s_list { size_t total; ... } t_data;  // line 27 ← 同じタグ名
```
`struct s_list` を2回定義しているのでコンパイルエラーになる。
`typedef struct s_data { ... } t_data;` に変更する必要がある。

#### ❌ 2. `ft_lstnew` の宣言と実装の型不一致
```c
// ヘッダ
t_list *ft_lstnew(void *content);
// list.c の実装
t_list *ft_lstnew(int content);
```
ヘッダを `t_list *ft_lstnew(int content);` に変更する。

#### ❌ 3. `disorder` の戻り値型不一致
```c
// ヘッダ
int disorder(t_list **a_lst);
// disorder.c の実装
float disorder(t_list **a_lst);
```
ヘッダを `float disorder(t_list **a_lst);` に変更する。

---

### main.c

#### ✅ 1. 関数名タイポ（`call_alg` → `call_algo`）
#### ✅ 2. `make_a_lst` の戻り値なし
#### ✅ 3. `ft_lstadd_back` に三重ポインタを渡していた
#### ✅ 4. `detect_duplicate_values` の引数型不一致
#### ✅ 5. 文字列比較に `==` を使っていた（`strcmp_original` に修正済み）

#### ❌ 6. `*a_lst = NULL` → 未定義動作（クラッシュ）
```c
t_list **a_lst;
*a_lst = NULL;    // a_lst は未初期化 → デリファレンスで即クラッシュ
```
修正:
```c
t_list  *list_a = NULL;
t_list **a_lst = &list_a;
```

#### ❌ 7. `b_lst = NULL` → NULL デリファレンス
```c
t_list **b_lst;
b_lst = NULL;     // ソート関数内で *b_lst にアクセスするとクラッシュ
```
修正:
```c
t_list  *list_b = NULL;
t_list **b_lst = &list_b;
```

#### ❌ 8. `make_rank` が未呼び出し
`lsd_sort` と `chunk_based_sort` はノードの `rank` フィールドを使うが、
`make_a_lst` の後に `make_rank(a_lst)` を呼んでいないため rank が未初期化のまま。
```c
a_lst = make_a_lst(a_lst, argc, argv);
make_rank(a_lst);   // ← この行が必要
```

#### ❌ 9. `error_handle` がフラグ引数 (`--simple` 等) を拒否する
`error_handle` は argv を全て整数チェックするため、`--simple` などのフラグを渡すと
`Error` を出力してプログラムが終了する。フラグ機能が完全に動作しない。
`call_algo` を `error_handle` より前に呼び、フラグ引数を argv からスキップした後に
`error_handle` を呼ぶ必要がある。

---

### call_func.c（新規）

#### ❌ 1. `==` によるポインタ比較（常に false）+ main.c の static 版と重複
```c
if (argv[1] == "--simple")   // ポインタ比較 → 常に false
```
main.c に `static int call_algo` が既にあり、こちらは正しく `strcmp_original` を使っている。
call_func.c の `call_algo` は呼ばれないデッドコードだが、バグが残っているため混乱の原因になる。
ファイルごと削除するか、内容を main.c の static 版に統一する。

---

### rank.c

#### ✅ `curr = 0` → `curr = *a_lst`

---

### helper_func.c

#### ✅ 1. `=` と `==` の混同
#### ✅ 2. `void*` を逆参照していた
#### ✅ 3. `lst_count` の off-by-one

---

### disorder.c

#### ✅ 1. 戻り値の型を `float` に変更
#### ✅ 2. 整数除算で小数部が消える問題
#### ✅ 3. 最初のペアをスキップしていた
#### ✅ 4. 末尾でセグフォルト（ループ条件修正）

---

### judge.c

#### ✅ 1. 型不一致
#### ✅ 2. 末尾でセグフォルト

---

### lsd_sort.c（新規）

#### ❌ 1. `lst_count` の引数型不一致
```c
size = lst_count(a_lst);    // a_lst は t_list**、lst_count は t_list* を期待
```
`lst_count(*a_lst)` に変更する。

---

### chunk_based_sort.c

#### ✅ 1. 関数名タイポ（`call_reverse`）
#### ✅ 2. `root()` が非完全平方数で -1 を返していた
#### ✅ 3. `chunk_based_sort2` の無限ループ

---

### list.c

#### ✅ `ft_lstnew` の引数型を `int` に変更

---

## 優先修正順序

| 優先度 | ファイル | 内容 |
|--------|----------|------|
| 高 | push_swap.h | `struct s_list` 二重定義（コンパイルエラー） |
| 高 | push_swap.h | `ft_lstnew` / `disorder` 宣言型不一致 |
| 高 | main.c | `*a_lst = NULL` 未定義動作 / `b_lst = NULL` |
| 高 | main.c | `make_rank` 未呼び出し |
| 高 | lsd_sort.c | `lst_count(a_lst)` → `lst_count(*a_lst)` |
| 中 | main.c | `error_handle` がフラグを拒否する問題 |
| 低 | call_func.c | ポインタ比較・デッドコードの整理 |

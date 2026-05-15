# push_swap 実装レビュー（更新版）

## 凡例
- ✅ 修正済み
- ❌ 未修正 / 新規バグ

---

## ファイル別バグ一覧

---

### push_swap.h

#### ✅ `typedef struct s_list` の二重定義 → `struct s_data` に修正済み

#### ❌ 1. `ft_lstnew` の宣言と実装の型不一致（コンパイルエラー）
```c
// ヘッダ（line 53）
t_list *ft_lstnew(void *content);
// list.c の実装
t_list *ft_lstnew(int content);
```
ヘッダを `t_list *ft_lstnew(int content);` に変更する。

#### ❌ 2. `disorder` の戻り値型不一致（コンパイルエラー）
```c
// ヘッダ（line 103）
int disorder(t_list **a_lst, t_data *bench_data);
// disorder.c の実装
float disorder(t_list **a_lst, t_data *bench_data);
```
ヘッダを `float disorder(...)` に変更する。

#### ❌ 3. `chunk_based_sort2` の宣言に `t_data *bench_data` が欠けている（コンパイルエラー）
```c
// ヘッダ（line 90-91）
void chunk_based_sort2(t_list **a_lst, t_list **b_lst, int count);
// chunk_based_sort.c の実装
void chunk_based_sort2(t_list **a_lst, t_list **b_lst, int count, t_data *bench_data);
```
ヘッダに `t_data *bench_data` を追加する。

#### ❌ 4. `make_a_lst` がヘッダに宣言されているが static かつ戻り値型不一致
```c
// ヘッダ（line 56）
t_list *make_a_lst(t_list **a_lst, int argc, char *argv[]);
// main.c の実装
static t_list **make_a_lst(t_list **a_lst, int argc, char *argv[]);
```
`static` 関数はヘッダに宣言不要。この行を削除する。

---

### main.c

#### ✅ `call_alg` → `call_algo`
#### ✅ `make_a_lst` の戻り値
#### ✅ `ft_lstadd_back` の引数
#### ✅ `detect_duplicate_values` の引数
#### ✅ 文字列比較を `strcmp_original` に変更

#### ❌ 1. `bench_data` が未初期化のポインタ（クラッシュ）
```c
t_data *bench_data;
reset(bench_data);    // bench_data はゴミ値 → デリファレンスでクラッシュ
```
修正:
```c
t_data bench_data;
reset(&bench_data);
```
以降の `bench_data` の使用箇所も `&bench_data` に変える。

#### ❌ 2. `*a_lst = NULL` → 未初期化ポインタのデリファレンス（クラッシュ）
```c
t_list **a_lst;
*a_lst = NULL;        // a_lst は未初期化 → 即クラッシュ
```
修正:
```c
t_list  *list_a = NULL;
t_list **a_lst = &list_a;
```

#### ❌ 3. `b_lst = NULL` → NULL デリファレンス（クラッシュ）
```c
t_list **b_lst;
b_lst = NULL;         // ソート関数内で *b_lst にアクセスするとクラッシュ
```
修正:
```c
t_list  *list_b = NULL;
t_list **b_lst = &list_b;
```

#### ❌ 4. `disorder` の呼び出しに第2引数が欠けている（コンパイルエラー）
```c
dis = disorder(a_lst);    // 第2引数 bench_data が必要
```
`dis = disorder(a_lst, bench_data);` にする（❌1 の修正後は `&bench_data`）。

#### ❌ 5. `make_rank` が未呼び出し
`lsd_sort` と `chunk_based_sort` はノードの `rank` を使うが一度も初期化されていない。
```c
a_lst = make_a_lst(a_lst, argc, argv);
make_rank(a_lst);    // ← この行が必要
```

#### ❌ 6. `error_handle` がフラグ引数（`--simple` 等）を拒否する
`error_handle` は argv を全て整数チェックするため `--simple` などを渡すと
`Error` を出力して終了する。フラグ機能が完全に動作しない。
`call_algo` を先に呼んでフラグをスキップした後に `error_handle` を呼ぶ必要がある。

---

### call_func.c

#### ❌ `==` によるポインタ比較（常に false）+ デッドコード
```c
if (argv[1] == "--simple")   // ポインタ比較 → 常に false
```
main.c に `static call_algo` が既に存在し `strcmp_original` を使っている。
call_func.c の `call_algo` は呼ばれないデッドコード。ファイルごと削除を推奨。

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

#### ✅ 全4項目修正済み

---

### judge.c

#### ✅ 全2項目修正済み

---

### lsd_sort.c

#### ❌ `lst_count` の引数型不一致（コンパイル警告/誤動作）
```c
size = lst_count(a_lst);    // a_lst は t_list**、lst_count は t_list* を期待
```
`size = lst_count(*a_lst);` に変更する。

---

### rotate.c

#### ❌ `rb_cnt` がインクリメントされていない（バグ）
```c
bench_data->rb_cnt;     // line 42: 値を読むだけで何もしない（no-op）
```
`bench_data->rb_cnt++;` が正しい。

---

### chunk_based_sort.c

#### ✅ 関数名タイポ（`call_reverse`）
#### ✅ `root()` の修正
#### ✅ 無限ループ修正

---

### list.c

#### ✅ `ft_lstnew` の引数型を `int` に変更

---

## 優先修正順序

| 優先度 | ファイル | 内容 |
|--------|----------|------|
| 高 | push_swap.h | `ft_lstnew` / `disorder` / `chunk_based_sort2` 宣言型不一致（コンパイルエラー） |
| 高 | main.c | `bench_data` 未初期化ポインタ |
| 高 | main.c | `*a_lst = NULL` / `b_lst = NULL` 未初期化ポインタ |
| 高 | main.c | `disorder` 呼び出しの引数不足（コンパイルエラー） |
| 高 | main.c | `make_rank` 未呼び出し |
| 高 | lsd_sort.c | `lst_count(a_lst)` → `lst_count(*a_lst)` |
| 中 | rotate.c | `bench_data->rb_cnt` → `bench_data->rb_cnt++` |
| 中 | main.c | `error_handle` がフラグを拒否する問題 |
| 低 | push_swap.h | `make_a_lst` の宣言を削除 |
| 低 | call_func.c | ポインタ比較・デッドコードの整理 |

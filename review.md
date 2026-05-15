# push_swap 実装レビュー

## 総評

コンパイルエラー・実行時クラッシュ・無限ループが複数あり、現状では動作しない。

---

## ファイル別バグ一覧

---

### main.c

#### 1. 関数名タイポ（コンパイルエラー）
```c
flag = call_alg(argv);   // ← call_algo が正しい
```

#### 2. make_a_lst の戻り値なし（未定義動作）
```c
static t_list *make_a_lst(...) {
    // エラー時は return (NULL) があるが、正常終了時の return がない
}
```
末尾に `return (*a_lst);` が必要。

#### 3. a_lst の型不一致
```c
t_list **a_lst = NULL;
a_lst = make_a_lst(a_lst, argc, argv);  // t_list* を t_list** に代入
```
`make_a_lst` の戻り値は `t_list *` なのに `t_list **` に代入している。
`a_lst` を `t_list *` にするか、ポインタ渡しに変える必要がある。

#### 4. ft_lstadd_back に三重ポインタを渡している
```c
ft_lstadd_back(&a_lst, tmp);  // a_lst は t_list** なので &a_lst は t_list***
```
`ft_lstadd_back(a_lst, tmp)` が正しい。

#### 5. detect_duplicate_values の引数型不一致
```c
detect_duplicate_values(*first, tmp)  // tmp は t_list* だが関数は int を期待
```
`detect_duplicate_values(*first, tmp->content)` にする必要がある。

#### 6. 文字列比較に == を使っている
```c
if (argv[1] == "--simple")   // ポインタ比較になるため常に false
```
`strcmp(argv[1], "--simple") == 0` が正しい。

---

### rank.c

#### curr = 0 でループに入らない（ランクが一切付かない）
```c
curr = 0;         // NULL を代入
while (curr)      // 最初から false → ループしない
```
`curr = *a_lst;` が正しい。この修正がない限りランクはすべて初期値のまま。

---

### helper_func.c

#### 1. = と == の混同（常に true になる）
```c
if (tmp->content = a)   // 代入。a が 0 でなければ常に true → 全要素が重複扱い
```
`tmp->content == a` が正しい。

#### 2. void* を間接参照している（コンパイルエラー）
```c
void delete(void *content) {
    (void)(*content);   // void* は dereference 不可
}
```
`(void)content;` が正しい。

#### 3. lst_count が n-1 を返す
```c
while (tmp->next != NULL)  // 最後の要素でカウントせず終了
```
5要素なら 4 を返す。`while (tmp != NULL)` にすれば正しく 5 を返す。
`lsd_sort` や `buble_sort` に影響し、最後の要素が処理されない。

---

### disorder.c

#### 1. 戻り値の型が int なのに float として使われている
```c
int disorder(t_list **a_lst)  // int を返す
// main.c では
float dis = disorder(a_lst);  // float で受け取っている
```
戻り値の型を `float` にする必要がある。

#### 2. 整数除算で小数部が消える
```c
return ((float)(mistakes / total_pairs));  // 先に整数除算してから float にキスト
```
`mistakes` が 2、`total_pairs` が 5 なら `2/5 = 0` → `0.0f` になる。
`return ((float)mistakes / total_pairs);` が正しい。

#### 3. 最初のペアをスキップしている
```c
tmp = *a_lst;
while (tmp->next != NULL)
{
    tmp = tmp->next;          // 最初にずらしてから比較
    if (tmp->content > tmp->next->content)  // 0番目と1番目の比較が飛ぶ
```
`tmp` を最初に進めてから比較するので、先頭ペアが比較されない。

#### 4. 末尾でセグフォルト
ループ条件は `tmp->next != NULL` だが、`tmp = tmp->next` した後に `tmp->next->content` にアクセスする。
`tmp` が最後の要素のとき `tmp->next == NULL` → クラッシュ。

---

### judge.c

#### 1. t_list** を t_list* に直接代入（型エラー）
```c
lst = a_lst;   // a_lst は t_list**、lst は t_list*
```
`lst = *a_lst;` が正しい。

#### 2. 末尾でセグフォルト
```c
while (lst != NULL)
{
    if (lst->rank > lst->next->rank ...  // lst が最後の要素なら lst->next == NULL
```
最後の要素で `lst->next->rank` にアクセスしてクラッシュ。
ループ条件を `while (lst != NULL && lst->next != NULL)` にする必要がある。

---

### chunk_based_sort.c

#### 1. 関数名タイポ（コンパイルエラー）
```c
call_reverse(a_lst, b_lst, rotate_count);  // 定義は call_revarse
```

#### 2. root() が非完全平方数で -1 を返す
要素数が 4, 9, 16 のような完全平方数でなければ `-1` を返す。
その後 `r = -1` で chunk_based_sort を実行するとループ条件が壊れる。
`sqrt()` を使うか、`ceil(sqrt(count))` を返すよう変更が必要。

#### 3. chunk_based_sort2 が無限ループ
```c
while (count >= 0)          // count が変化しない
{
    while (lst->next != NULL)  // lst も更新されない
    {
        if (count == lst->rank)
            break;
        rotate_count++;
    }
    ...
}
```
`count` のデクリメントと `lst` の更新が抜けている。

---

### list.c

#### ft_lstnew の引数型が void* だが content は int
```c
t_list *ft_lstnew(void *content)  // ヘッダ・実装ともに void*
node_new->content = content;       // t_list::content は int
```
`int` を `void *` に暗黙変換して渡しているため警告が出る。
`ft_lstnew(int content)` に変更するのが正しい。

---

## 優先修正順序

| 優先度 | ファイル | 内容 |
|--------|----------|------|
| 高 | rank.c | `curr = 0` → `curr = *a_lst` （ランクが付かない） |
| 高 | main.c | `call_alg` → `call_algo`、戻り値なし、型不一致 |
| 高 | helper_func.c | `=` → `==`、`void*` 逆参照、`lst_count` の off-by-one |
| 高 | chunk_based_sort.c | `call_reverse` タイポ、無限ループ |
| 中 | disorder.c | 型・整数除算・セグフォルト |
| 中 | judge.c | 型不一致・セグフォルト |
| 低 | list.c | `ft_lstnew` の引数型 |

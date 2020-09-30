# Satoru语法分析器

## 基础产生式

本标题下的所有产生式未经过消左递归、提取左公因子等处理，仅直观地反应文法规约，不能直接用于LL(1)文法。

### 语句

1. 语句块: $SentenceBlock\rarr \{SentenceList\}$
2. 语句序列: $SentenceList\rarr SentenceList|Sentence|\epsilon$
3. 基本语句: $Sentence\rarr Expr_0|Condition|Loop|Declear$

### 表达式

## 预处理产生式
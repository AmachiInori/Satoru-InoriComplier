# Satoru语法分析器

## 语法规约

### 基础产生式

本标题下的所有产生式未经过消左递归、提取左公因子等处理，仅直观地反应文法规约，不能直接用于LL(1)文法。

#### 基本结构

1. 语句块: $SentenceBlock\rarr \{SentenceList\}$
2. 语句序列: $SentenceList\rarr SentenceList|Sentence|\epsilon$
3. 语句

### 预处理产生式
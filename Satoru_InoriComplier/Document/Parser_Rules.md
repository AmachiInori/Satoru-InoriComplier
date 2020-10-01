# Satoru语法分析器

## 基础产生式

本标题下的所有产生式未经过消左递归、提取左公因子等处理，仅直观地反应文法规约，不能直接用于LL(1)文法。

### 文法、增广文法

$$Satoru\rarr SentenceBlock$$

### 语句

1. 语句块: $SentenceBlock\rarr \{SentenceList\}$
2. 语句序列: $SentenceList\rarr SentenceList\ |\ Sentence\ |\ \boldsymbol{\epsilon}$
3. 基本语句: $Sentence\rarr Expr_0\ |\ Condition\ |\ Loop\ |\ Declear$
4. 条件语句: $Condition\rarr \bold{if}(Expr_0)SentenceBlock\ ElseBlock$
5. 条件语句-Else块: $ElseBlock\rarr \bold{else}\ SentenceBlock\ |\ \bold{else}\ Condition\ |\ \boldsymbol{\epsilon}$
6. 循环语句
7. 声明语句

### 表达式

总共定义了0~9级的十类运算符，故有10个主要的表达式产生式，其中：

$$Expr_n\rarr Expr_n\ \bold{op_n}\ Expr_{n+1}\ |\ Expr_{n+1}(0 \leq n < 9)$$  
$$Expr_9\rarr Expr_9\ \bold{op_n}\ Factor\ |\ Factor$$  
$$Factor\rarr -Factor\ |\ (Expr_0)\ |\ Identifier\ |\ Const$$  
$$Const\rarr \bold{str}\ |\ \bold{num}$$
$$Identifier\rarr \bold{id}\ IdSuffix$$
$$IdSuffix\rarr .\bold{id}\ |\ :\bold{id}\ |\ (Parameters)\ |\ [Expr_0]\ |\ \boldsymbol{\epsilon}$$


## 预处理产生式
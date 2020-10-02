# Satoru语法分析器

## 基础产生式

本标题下的所有产生式未经过消左递归、提取左公因子等处理，仅直观地反应文法规约，不能直接用于LL(1)文法。

### 增广文法

$$Satoru\rarr SentenceList$$

### 语句

1. 语句块: $SentenceBlock\rarr \{SentenceList\}\ |\ \boldsymbol{\epsilon}$
2. 语句序列: $SentenceList\rarr SentenceList\ Sentence\ |\ \boldsymbol{\epsilon}$
3. 基本语句: $Sentence\rarr Expr_0\ |\ Condition\ |\ Loop\ |\ Declear\ |\ SentenceBlock$

#### 条件语句

1. 条件语句: $Condition\rarr \bold{if}(Expr_0)SentenceBlock\ ElseBlock$
2. 条件语句-Else块: $ElseBlock\rarr \bold{else}\ SentenceBlock\ |\ \bold{else}\ Condition\ |\ \boldsymbol{\epsilon}$

#### 循环语句

#### 声明语句

1. 声明语句: $Declear\rarr \bold{type}\ \bold{id}\ 
|\ \bold{type}\ \bold{id}\ Define\ |\ FuncDeclear$
2. 变量定义: $Define\rarr EquaDeclear\ |\ BrackDeclear$
3. 等号式定义: $EquaDeclear\rarr\ =\ Expr_0$
4. 功能化定义: $BrackDeclear\rarr (Parameters)$
5. 函数声明及定义: $FuncDeclear\rarr \bold{function}\ \ (ParameterList)\ \bold{id}:\bold{type}\ SentenceBlock$
6. 函数形参列: $ParameterList\rarr ParameterList, FCParameter\ |\ FCParameter$
7. 函数形参: $FCParameter\rarr \bold{type}\ \bold{id}$

### 表达式

总共定义了0~9级的十类运算符，故有10个主要的表达式产生式:

$Expr_n\rarr Expr_n\ \bold{op_n}\ Expr_{n+1}\ |\ Expr_{n+1}(0 \leq n < 9)$  
$Expr_9\rarr Expr_9\ \bold{op_n}\ Factor\ |\ Factor$  
$Factor\rarr -Factor\ |\ (Expr_0)\ |\ Identifier\ |\ Const$  
$Const\rarr \bold{str}\ |\ \bold{num}$  
$Identifier\rarr \bold{id}\ IdSuffix$  
$IdSuffix\rarr (Parameters)\ |\ [Expr_0]\ |\ \boldsymbol{\epsilon}$  
$Parameters\rarr Parameters\ ,Expr_0\ |\ Expr_0$  


## 预处理产生式
# Satoru�﷨������

## ��������ʽ

�������µ����в���ʽδ��������ݹ顢��ȡ�����ӵȴ�����ֱ�۵ط�Ӧ�ķ���Լ������ֱ������LL(1)�ķ���

### �����ķ�

$$Satoru\rarr SentenceList$$

### ���

1. ����: $SentenceBlock\rarr \{SentenceList\}\ |\ \boldsymbol{\epsilon}$
2. �������: $SentenceList\rarr SentenceList\ Sentence\ |\ \boldsymbol{\epsilon}$
3. �������: $Sentence\rarr Expr_0\ |\ Condition\ |\ Loop\ |\ Declear\ |\ SentenceBlock$

#### �������

1. �������: $Condition\rarr \bold{if}(Expr_0)SentenceBlock\ ElseBlock$
2. �������-Else��: $ElseBlock\rarr \bold{else}\ SentenceBlock\ |\ \bold{else}\ Condition\ |\ \boldsymbol{\epsilon}$

#### ѭ�����

#### �������

1. �������: $Declear\rarr \bold{type}\ \bold{id}\ 
|\ \bold{type}\ \bold{id}\ Define\ |\ FuncDeclear$
2. ��������: $Define\rarr EquaDeclear\ |\ BrackDeclear$
3. �Ⱥ�ʽ����: $EquaDeclear\rarr\ =\ Expr_0$
4. ���ܻ�����: $BrackDeclear\rarr (Parameters)$
5. ��������������: $FuncDeclear\rarr \bold{function}\ \ (ParameterList)\ \bold{id}:\bold{type}\ SentenceBlock$
6. �����β���: $ParameterList\rarr ParameterList, FCParameter\ |\ FCParameter$
7. �����β�: $FCParameter\rarr \bold{type}\ \bold{id}$

### ���ʽ

�ܹ�������0~9����ʮ�������������10����Ҫ�ı��ʽ����ʽ:

$Expr_n\rarr Expr_n\ \bold{op_n}\ Expr_{n+1}\ |\ Expr_{n+1}(0 \leq n < 9)$  
$Expr_9\rarr Expr_9\ \bold{op_n}\ Factor\ |\ Factor$  
$Factor\rarr -Factor\ |\ (Expr_0)\ |\ Identifier\ |\ Const$  
$Const\rarr \bold{str}\ |\ \bold{num}$  
$Identifier\rarr \bold{id}\ IdSuffix$  
$IdSuffix\rarr (Parameters)\ |\ [Expr_0]\ |\ \boldsymbol{\epsilon}$  
$Parameters\rarr Parameters\ ,Expr_0\ |\ Expr_0$  


## Ԥ�������ʽ
# Satoru�﷨������

## ��������ʽ

�������µ����в���ʽδ��������ݹ顢��ȡ�����ӵȴ�����ֱ�۵ط�Ӧ�ķ���Լ������ֱ������LL(1)�ķ���

### �ķ��������ķ�

$$Satoru\rarr SentenceBlock$$

### ���

1. ����: $SentenceBlock\rarr \{SentenceList\}$
2. �������: $SentenceList\rarr SentenceList\ |\ Sentence\ |\ \boldsymbol{\epsilon}$
3. �������: $Sentence\rarr Expr_0\ |\ Condition\ |\ Loop\ |\ Declear$
4. �������: $Condition\rarr \bold{if}(Expr_0)SentenceBlock\ ElseBlock$
5. �������-Else��: $ElseBlock\rarr \bold{else}\ SentenceBlock\ |\ \bold{else}\ Condition\ |\ \boldsymbol{\epsilon}$
6. ѭ�����
7. �������

### ���ʽ

�ܹ�������0~9����ʮ�������������10����Ҫ�ı��ʽ����ʽ�����У�

$$Expr_n\rarr Expr_n\ \bold{op_n}\ Expr_{n+1}\ |\ Expr_{n+1}(0 \leq n < 9)$$  
$$Expr_9\rarr Expr_9\ \bold{op_n}\ Factor\ |\ Factor$$  
$$Factor\rarr -Factor\ |\ (Expr_0)\ |\ Identifier\ |\ Const$$  
$$Const\rarr \bold{str}\ |\ \bold{num}$$
$$Identifier\rarr \bold{id}\ IdSuffix$$
$$IdSuffix\rarr .\bold{id}\ |\ :\bold{id}\ |\ (Parameters)\ |\ [Expr_0]\ |\ \boldsymbol{\epsilon}$$


## Ԥ�������ʽ
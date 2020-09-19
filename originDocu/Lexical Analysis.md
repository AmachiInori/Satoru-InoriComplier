# 词法分析器

## 基本架构

## 词法规约

`token`是基类
- `type` token类型，通过getTokenType()访问
- 构造函数传char类型的tokentype

`numToken`数字类 也是基类
- `exprValue`是模式匹配接受得到的字面字符串
- `numtype`是数字类型，char
- 构造函数传字面串和数字类型

`intToken`整数类 final 此处需要可移植性优化
整形量的规约是$((+|-)?digit^+U)$

`floatToken`浮点类 规约是
$((+|-)?digit^+.digit^+)|((+|-)?digit^+.digit^+(e|E)(+|-)?digit^+)$

默认底层实现使用补码表示，故以正数形式累加，以64位有符号整数(long long)保存
`if (value > LLONG_MAX / 10.0)`判断溢出，但不在构造函数里抛expection（否则就太业余了
标记下来，在`getValueNum()`里抛，`int_cstexpe_overflow`表示溢出异常

`stringToken`字符串字面量类，默认不要引号


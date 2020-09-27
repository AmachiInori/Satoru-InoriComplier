# Satoru词法分析器

## 词法规约

Satoru规定了如下几种词法单元：

### 常数字面量  

非终结符号定义请参看[DFA.md](DFA.md)

- 十进制有符号整数 $\bold{digit10}^+$
- 十进制无符号整数 $\bold{digit10}^+(\bold{U|u})$  
- 十进制浮点数 $\bold{digit10}^+.\bold{digit10}^+$
- 十进制指数浮点数$\bold{digit10}^+.\bold{digit10}^+(\bold{e|E})(\bold{+|-})?\bold{digit10}^+$
- 二进制有符号整数 $\bold{0}\bold{X}\bold{digit2}^+$
- 二进制无符号整数 $\bold{0}\bold{X}\bold{digit2}^+(\bold{U|u})$
- 十六进制有符号整数 $\bold{0}\bold{X}\bold{digit16}^+$
- 十六进制无符号整数 $\bold{0}\bold{X}\bold{digit16}^+(\bold{U|u})$

### 标识符

- $\bold{idChar}(\bold{idChar} | \bold{digit10})^*$

### 字符串字面量

- $\bold{"}(\bold{stringChar})^*\bold{"}$

### 字符字面量

- $\bold{'}(\bold{stringChar})^*\bold{'}$

### 运算符

- 仅可单字符出现的运算符 $\bold{compChar}$
- 可以单独出现、可以重复出现也可接续等号的运算符 $\bold{repeatableChar}(\bold{[sameChar]})?|\bold{repeatableChar}(\bold{=})?$
- 可以单独出现、但仅可接续等号的运算符 $\bold{doubleCompChar}(\bold{=})?$

## 其他

- Satoru词法分析采用**失配丢弃**策略，发现词法失配之后输出一个错误词法单元并从下一个字符重启词法分析。  
- 分隔符默认不特殊处理，但一般的状态转换边都不含有分隔符。
- Satoru词法分析使用最长匹配来去二义性  
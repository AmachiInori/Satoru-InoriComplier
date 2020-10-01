# Satoru词法分析器

## 状态转移

### 状态转移图

![状态转移图](Asset/DFAGraph.png)  

### 非终结符号定义

in `/Include/lexical_base.hpp`  

`doubleCompChar`->`inline bool isOpreatorCharOnlyDblWEqual(char _c)`  
`[samechar]`->与之前输入的符号相同的符号**或`=`**  
`repeatableChar`->`inline bool isReptbOperatorChar(char _c)`  
`compChar`->`inline bool isSingleOperatorChar(char _c)`  
`digit10`->`inline bool isDigit(char _c)`  
`digit2`->`inline bool isNum2Digit(char _c)`  
`digit16`->`inline bool isNum16Digit(char _c)`  
`idChar`->`inline bool isIdChar(char _c)`  
`stringChar`->所有大于零的字符常量  
# Satoru词法分析器

## 基本架构

### DFA.h DFA.cpp

这一组文件定义了词法分析所依赖的有限状态自动机。它通过头文件的交叉互联和友元权限来与词法分析主进程`lexAna`相连，同时构造和析构委托至`lexAna`。这个类使用了堆空间来存放词法单元并且在析构函数中开解这些堆空间，应注意在语法分析完成前不应主动调用lexAna的析构函数。

`host`->`lexAna* const` 指向主进程类，在构造函数中传入并赋值。  
`state`->`_DFAstate` 指明目前自动机的状态，初始值是`DFAstate::START`。  
`lastState`->`_DFAstate` 记录上一状态以支持向前看，初始值是`DFAstate::START`。  
`newedToken`->`std::vector<token*>` 记录所有堆空间中的`token`实例的指针，以供析构函数释放

`stateTo`->`inline void (_DFAstate)`  
state和laststate的更新，封装为内联函数以复用。只在本类内部调用。不抛出异常。  

`trans`->`bool (char)`  
状态转移。内含整个状态转移表。  
返回值为1表示状态转移接受，为0表示状态转移失败。  
有可能抛出异常的方法调用但是闭合的，不抛出异常。

`buildToken`->`token*(_ACCstate, std::string)`  
传入状态接受类型和接受的字符串，先在符号表中查找，如有则直接返回，如无则在堆中开辟空间，将指针压入`newedToken`并返回。  
不抛出异常。

`DFA`->`explicit {cons}(lexAna*)`  
构造函数。传入词法分析主类的指针。不允许抛出异常。  

`reset`->`inline void()`  
重置自动机状态，目前仅在`getToken()`中调用一次。不抛出异常。  

`getToken`->`token* ()`  
向主类的接口。返回一个指向下一词法单元的指针。方法本身不产生堆空间但调用的方法会产生。  
抛出`no_mode_matched`异常给`lexAna`来表示词法失配警告。  
处理主类`getNextChar()`方法产生的致命异常`fatal_can_not_open_file`并返回一个`nullptr`给`lexAna`表示词法分析错误。  
处理主类`pointReturn()`方法产生的致命异常`fatal_can_not_return_back`并返回一个`nullptr`给`lexAna`表示词法分析错误。  

### token.hpp

`token`  
词法单元基类  
`type`->`_tokenType` token类型，通过`getTokenType()`访问，  
词法单元种类标识：标识符 `ID = 1`, 常数字面量 `NUM = 2`, 字符串字面量 `STR = 3`, 保留字 `REMAIN = 4`, 运算符 `OPER = 5`  
特殊的词法单元种类：`type`为`0`表示输入结束，`type`为`-1`表示词法错误的词法单元，`type`为`-2`表示严重的词法分析故障，需要立即终止词法分析并析构类。  

`operaToken`  
运算符单元基类，继承自`token`  
`_otp`->`_operType`表示运算符种类，由传入的`std::string`经过基数256转10而来。  
此处未来可能需要建立一个(给人看的)表来方便语法分析的开发。  

`numToken`  
数字类，基类  
`exprValue`->`std::string` 模式匹配接受得到的字面字符串
`numtype`->`_numType` 数字类型，整形 `INT = 1`, 浮点 `FLT = 2`, 字符 `CHAR = 3`  
构造函数传入上述两个值

`intToken`  
整数类 / 字符类，final  
此处需要可移植性优化  
整形量的规约是$((+|-)?digit^+U)$  
`value`->`int64_t` 记录该词法单元的字面量大小  
`isGoodNumber`->`bool` 记录是否存在溢出  
`intToken(const std::string&)` 内置了字符串转整数的过程，适配整形输入
`intToken(const int64_t)` 适配字符类输入  
注意 目前对于溢出的限制还很宽松  
默认底层实现使用补码表示，故以正数形式累加，以64位有符号整数(long long)保存  
`if (value > LLONG_MAX / 10.0)`判断溢出，但不在构造函数里抛expection（否则就太业余了  
标记下来，在`getValueNum()`里抛，`int_cstexpe_overflow`表示溢出异常(现在的版本还没抛)  

`floatToken`浮点类 规约是
$((+|-)?digit^+.digit^+)|((+|-)?digit^+.digit^+(e|E)(+|-)?digit^+)$

`stringToken`字符串字面量类，默认不要引号

### lex.h lex.cpp

头部声明且定义了三个全局变量，是在本文件及`lexical.hpp`引用的三种特殊的`token`以供异常处理使用，且能方便地管理内存。  

`lexAna`是词法分析前端，直接操作文件句柄读取文件。  

`isRefilled`->`bool` 表示(非当前读取)的另一个缓冲区是否已经被填充。初始化为`false`(其实没关系)  
`lineNumber`->`size_t` 表示当前的行号，以供报错使用  
`lastLineNumber`->`size_t` 表示上一次成功读取时的行号，以供回退使用  
`listNumber, lastListNumber`->`size_t` 同理，列号  
`nowPoint`->`size_t` **刚刚被传入分析的缓冲区位置**，初始化为`-1`(`UINT32_MAX`)
`lastPoint`->`size_t` 上两次被传入分析的缓冲区位置，初始化为`-1`(`UINT32_MAX`)
`nowChar`->`char` 我也不知道设计这个是干嘛的 可能假酒喝多了 应该是回退用 别删  
`lastChar`->`char` 回退用的上一次成功读取时的字符  
`bufferSize`->`const size_t` 默认是4096，每一个buffer串的大小(是为了不在程序中出现乱七八糟的常数字面量)  
`isInfileGood`->`bool` 表示文件是否被正常打开，抛异常的基准，小心维护  
`idTable`->`std::unordered_map<std::string, token*>` 
简单符号表，用指针作`token`类的寻址依据，空间由`DFA`创建，记得别乱析构  
应当确保所有idTable中的元素均在堆空间
`infile`->`std::ifstream` 输入文件流，默认ios binary  
`fileName`->`std::string` 输入文件的地址  
`dfaProcess`->`DFA*` 自动机类的指针，初始化时new  
`bufferA, bufferB`->`std::string` 双缓冲区的缓冲区  

`_pointReturn`->`void()`  
回退的内层方法，用两层是为了打算处理异常，但现在用更外层处理了。  
抛出致命异常`fatal_can_not_return_back`  
虽然抛出异常，但遗憾的是目前这个方法现在没人调用  

`fillBuffer`->`void(std::string* _buf)`  
重新填满`_buf`指向的缓冲区  
不抛出异常

### lexical.hpp

是一个外部模块，封装了词法分析器并为语法分析提供词法分析器的中间接口和缓冲区。同时使用这个类，如后端接收到词法单元`-2`的致命错误，可以通过堆栈辗转开解来自动调用析构释放空间。 
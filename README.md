# Satoru: Inori Complier

## 这是什么?  

这是一个新的编程语言，还处于雏形阶段。  
不知道为什么突然想要写一个编程语言，然后就开始写了。  
编译原理太难辣！！  
（写到一半弃坑也说不定。  

宿主语言是C++，使用Visual Studio 2019构建和编译，以C++17标准编写

## 设计思想

- 简洁性：保持词法和语法的简洁易读  
- 复用性：一种运算符或保留字可以在多种场合实现多种功能；一种功能也可以由多种方式实现  
- 抽象性：基于复用性，一种功能的实现可以以上层内容概括，也可以通过底层实现构建更为高效的代码

## 关于命名

日文覚る的罗马字，意义是领会、领悟。  
来源于我的纸片人lp 东方Project的角色古明地さとり(Komeiji Satori)  
和本语言没多大关系，Python里也没有蛇，不是吗？  
小五世界第一！  

## 开发进度

- 2020.09.23 词法分析器基本完成并通过模块测试

## 文档目录

- [Satoru手册](Satoru_InoriComplier/Document/Satoru_Base.md)
- [文件结构](Satoru_InoriComplier/Document/File_Structure.md)

### 词法分析器

- [词法规约说明](Satoru_InoriComplier/Document/Lexical_Rules.md)
- [词法分析器的源代码文档](Satoru_InoriComplier/Document/Lexical_Analysis.md)
- [确定有限状态自动机的说明文档](Satoru_InoriComplier/Document/Lexical_DFA.md)
- [运算符定义](Satoru_InoriComplier/Document/Lexical_Symbol.md)

### 语法分析器

- [LL(1)文法产生式](Satoru_InoriComplier/Document/Parser_Rules.md)

## 关于

### 作者

Satoru之父(误)，努力脱离材料天坑的[@AmachiInori](http://amachi.com.cn)  

### 参考及鸣谢

- Alfred V.Aho, etc. 编译原理(第二版)
- Andrew W.Appel, etc. 现代编译原理-C语言描述(修订版)
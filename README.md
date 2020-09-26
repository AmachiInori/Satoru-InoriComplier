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

日文覚る的罗马音，意义是领会、领悟，与本语言的设计思想：一个启发性较强的简洁明快的语言相似。  
来源于我的纸片人lp 东方Project的角色古明地さとり(Komeiji Satori)  
小五世界第一！  

## 开发进度

- 2020.09.23 词法分析器基本完成并通过模块测试

## 文档目录

- [Satoru手册](document/Satoru_Base.md)

### 文件结构

- [文件结构](document/File_Structure.md)

### 词法分析器

- [词法规约说明](document/Lexical_Rules.md)
- [词法分析器的源代码文档](document/Lexical_Analysis.md)
- [确定有限状态自动机的说明文档](document/DFA.md)

## 关于作者

Satoru之父(误)  
努力脱离材料天坑的[@AmachiInori](http://amachi.com.cn)  
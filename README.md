# 《算法导论》中算法的C++实现
<!--
    作者：华校专
    email: huaxz1986@163.com
**  本文档可用于个人学习目的，不得用于商业目的  **
-->
本项目中的所有算法均来自于《算法导论》第三版

## 缘由
在学习算法导论的过程中，本人经过几次阅读做了两轮笔记之后发现，要想掌握算法的思想必须动手实践。
> 笔记扫描版地址：http://pan.baidu.com/s/1nvSt62H

> 所有笔记扫描版下载地址：http://pan.baidu.com/s/1boMsdUB

* 《算法导论》中的算法全部是用伪代码写的，因此大量的语言细节被忽略。比如边界条件的处理
* 在算法转换为代码过程中会对算法有着更深刻的理解

因此在去年底我在电脑上对算法导论的算法用C++实现了一遍。为了更好地促进学习，现在我将这些代码进行了整理（主要是增加了`Doxygen`注释，以及利用`gooletest`增加了测试代码）

## 结构

* 文件结构

```
src\
	dynamic_programming_algorithms : 动态规划算法
			longest_common_subsequence： 最长公共子序列算法
	google_test\           : gooletest框架的两个文件：gtest.h以及gtest_all.c
	sort_algorithms\       :所有排序算法
			bucket_sort: 桶排序
			count_sort:计数排序
			heap_sort：堆排序
			insert_sort：插入排序
			merge_sort:归并排序
			quick_sort：快速排序
			radix_sort：基数排序
	select_algorithms\     :顺序统计量选择算法
			randomized_select：随机选择的顺序统计量算法
			godd_select：最坏情况为O(n)的顺序统计量算法
	tree_algorithms\       :树算法
			binarytree:二叉树
			binarytreenode：二叉树结点
			searchtree:二叉搜索树	
	graph_algorithms\    ：图算法
			basic_graph\ :基本图算法
					graph_vertex：图的顶点
					graph_edge:图的边
					adjlist_graph：图的邻接表的表示法
					matrix_graph：图的矩阵表示法
		...(未完待续)
doc\      ：由doxygen自动生成的文档
Doxyfile  :doxygen配置文件
Introduction_to_Algorithms.pro :Qt项目配置文件
```
* 本项目是利用Qt开发，因此未给出Makefile文件
* 本项目所有算法都是用 `C++ Template`实现。
* 本项目所有算法都有测试代码。如快速排序在`quicksort.h`中，快速排序的测试代码在`quicksort_test.h`中，二者位于同一目录下
* 本项目所有的命名空间、函数、类以及必要的成员都打上了`doxygen`注释，可以方便的进行文档化

 **本文档仅用于个人学习目的，未经许可不得用于商业目的，转载请注明出处**

 **email: huaxz1986@163.com** 

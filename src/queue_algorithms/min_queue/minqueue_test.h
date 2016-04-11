/*
 * Copyright 2016- huaxz <huaxz1986@163.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: huaxz1986@163.com (huaxz)
 */
#ifndef MINQUEUE_TEST
#define MINQUEUE_TEST
#include"src/google_test/gtest.h"
#include"minqueue.h"

using IntroductionToAlgorithm::QueueAlgorithm::MinQueue;
namespace  {
    const int Q_NUM=10;
}


//!Node:用于测试的类型
struct Node
{
    Node(int k):key(k){}
    double key; /*!< key存放数据 */
};

//!MinQueueTest:测试类，用于为测试提供基础数据
/*!
*
* `MinQueueTest`是 `::testing::Test` 的子类。它主要用于为每一个`TEST_F`准备测试环境
*/
class MinQueueTest:public ::testing::Test
{
public:
    typedef std::function<bool (std::shared_ptr<int>,std::shared_ptr<int>)> Int_Compare_Type ; /*!< 当最小优先级队列存放的是int*数据时，相应的比较函数对象*/
    typedef std::function<int&(std::shared_ptr<int>)> Int_Get_Type; /*!< 当最小优先级队列存放的是int*数据时，获取key的函数对象*/
    typedef std::function<bool (std::shared_ptr<Node>,std::shared_ptr<Node>)> Struct_Compare_Type ;/*!< 当最小优先级队列存放的是Node*数据时，相应的比较函数对象*/
    typedef std::function<double&(std::shared_ptr<Node>)> Struct_Get_Type;/*!< 当最小优先级队列存放的是Node*数据时，获取key的函数对象*/
    typedef MinQueue<Node,double> Struct_MinQueue_Type;/*!< 存放的是int*数据的最小优先级队列，其关键字就是int本身 */
    typedef MinQueue<int,int> Int_MinQueue_Type;/*!< 存放的是Node*数据的最小优先级队列，Node的关键字是double类型 */
protected:
    void SetUp()
    {
        Struct_Compare_Type node_compare=[](std::shared_ptr<Node> first,std::shared_ptr<Node> second){return first->key<second->key;};
        Struct_Get_Type node_get=[](std::shared_ptr<Node> node)->double& {return node->key;};
        _strcut_minqueue=std::make_shared<Struct_MinQueue_Type>(node_compare,node_get);

        Int_Compare_Type int_compare=[](std::shared_ptr<int> first,std::shared_ptr<int>second){return *first<*second;};
        Int_Get_Type int_get=[](std::shared_ptr<int> node)->int&{return *node;};
        _int_minqueue=std::make_shared<Int_MinQueue_Type>(int_compare,int_get);
    }
    void TearDown(){}
    std::shared_ptr<Struct_MinQueue_Type> _strcut_minqueue;    /*!< 指向一个最小优先级队列*/
    std::shared_ptr<Int_MinQueue_Type> _int_minqueue;    /*!< 指向一个最小优先级队列*/

};
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_min`：测试`min()`成员方法
*/
TEST_F(MinQueueTest,test_min)
{
    EXPECT_FALSE(_strcut_minqueue->min());
    EXPECT_FALSE(_int_minqueue->min());
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_extract_min`：测试`extract_min()`成员方法
*/
TEST_F(MinQueueTest,test_extract_min)
{
    EXPECT_FALSE(_strcut_minqueue->min());
    EXPECT_FALSE(_int_minqueue->min());
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_insert`：测试`insert(...)`成员方法
*/
TEST_F(MinQueueTest,test_insert)
{
    for(int i=Q_NUM-1;i>=0;i--)
    {
        _strcut_minqueue->insert(std::make_shared<Node>(i));
        EXPECT_NEAR(_strcut_minqueue->min()->key,i,0.001)<<"i:"<<i;
    }
    EXPECT_NEAR(_strcut_minqueue->min()->key,0,0.001);
    for(int i=0;i<Q_NUM;i++)
    {
       EXPECT_NEAR(_strcut_minqueue->extract_min()->key,i,0.001)<<"i:"<<i;
    }

    for(int i=Q_NUM-1;i>=0;i--)
    {
        _int_minqueue->insert(std::make_shared<int>(i));
        EXPECT_EQ(*(_int_minqueue->min()),i)<<"i:"<<i;
    }
    EXPECT_EQ(*(_int_minqueue->min()),0);
    for(int i=0;i<Q_NUM;i++)
    {
       EXPECT_EQ(*(_int_minqueue->extract_min()),i)<<"i:"<<i;
    }
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_is_empty`：测试`is_empty()`成员方法
*/
TEST_F(MinQueueTest,test_is_empty)
{
    EXPECT_TRUE(_strcut_minqueue->is_empty());
    EXPECT_TRUE(_int_minqueue->is_empty());
    _strcut_minqueue->insert(std::make_shared<Node>(0));
    _int_minqueue->insert(std::make_shared<int>(0));
    EXPECT_FALSE(_strcut_minqueue->is_empty());
    EXPECT_FALSE(_int_minqueue->is_empty());
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_index_inqueue`：测试`index_inqueue(...)`成员方法
*/
TEST_F(MinQueueTest,test_index_inqueue)
{
    std::shared_ptr<Node> nodes[Q_NUM];
    std::shared_ptr<int> ints[Q_NUM];
    for(int i=0;i<Q_NUM;i++)
    {
        nodes[i]=std::make_shared<Node>(i);
        ints[i]=std::make_shared<int>(i);
    }
    for(int i=1;i<Q_NUM;i++)
    {
        EXPECT_EQ(_strcut_minqueue->insert(nodes[i]),i-1);
        EXPECT_EQ(_int_minqueue->insert(ints[i]),i-1);
    }
    EXPECT_EQ(_strcut_minqueue->index_inqueue(nodes[0]),-1);
    EXPECT_EQ(_int_minqueue->index_inqueue(ints[0]),-1);
    EXPECT_THROW(_strcut_minqueue->index_inqueue(std::shared_ptr<Node>()),std::invalid_argument);
    EXPECT_THROW(_int_minqueue->index_inqueue(std::shared_ptr<int>()),std::invalid_argument);
    for(int i=1;i<Q_NUM;i++)
    {
        EXPECT_EQ(_strcut_minqueue->index_inqueue(nodes[i]),i-1)<<"i:"<<i;
        EXPECT_EQ(_int_minqueue->index_inqueue(ints[i]),i-1)<<"i:"<<i;
    }
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_decreate_key`：测试`decreate_key(...)`成员方法。当`test_insert`测试通过时隐含着`test_decreate_key`测试通过
*/
TEST_F(MinQueueTest,test_decreate_key)
{
// test_insert测试通过，则test_decreate_key隐含着测试通过
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_setupHeap`：测试`setupHeap()`成员方法。该接口是堆排序中最大堆的遗留方法，因此这里不再测试
*/
TEST_F(MinQueueTest,test_setupHeap)
{
//该接口为遗留接口，因此这里不再测试
}
//!MinQueueTest:测试最小优先级队列
/*!
*
* `test_heapify`：测试`heapify(...)`成员方法。当`extract_min`测试通过时隐含着`test_heapify`测试通过
*/
TEST_F(MinQueueTest,test_heapify)
{
// extract_min测试通过，则test_decreate_key隐含着测试通过
}

#endif // MINQUEUE_TEST


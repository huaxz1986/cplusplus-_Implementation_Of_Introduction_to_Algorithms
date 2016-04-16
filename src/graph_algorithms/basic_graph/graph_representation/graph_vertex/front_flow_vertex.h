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
#ifndef FRONTFLOWVERTEX
#define FRONTFLOWVERTEX
#include"flow_vertex.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {


        //!List：链表数据结构
        /*!
        *
        * 链表包含两个数据成员：
        *
        * - head：指向链表头部的元素的强指针
        * - current:指向链表当前处理元素的强指针
        *
        */
        template<typename NodeType> struct List
        {
            std::shared_ptr<NodeType> head;/*!<  指向链表头部的元素的强指针*/
            std::shared_ptr<NodeType> current;/*!<  指向链表当前处理元素的强指针*/

            //!List默认构造函数
            /*!
            *
            * 默认构造函数完成两个设置：head设为空指针，current设为空指针
            *
            */
            List():head(std::shared_ptr<NodeType>()),current(std::shared_ptr<NodeType>()){}

            //!add:添加元素
            /*!
            *
            * \param element:被添加元素的强指针
            *
            * 若element为空指针则直接返回；否则将element添加到表头
            *
            */
            void add(std::shared_ptr<NodeType> element)
            {
                if(!element)
                    return;
                if(head) //链表非空
                {
                    element->next=head;
                    head=element;
                }else //链表为空
                {
                    head=element;
                }
            }
            //!front_of:链表指定元素前面的元素
            /*!
            *
            * \param element:指定的元素
            * \return:指定元素前面元素的强指针
            *
            * 若element为空指针则抛出异常。否则遍历列表。若找到指定元素，则返回其前面元素的指针；若找不到指定元素，
            * 则抛出异常
            *
            */
            std::shared_ptr<NodeType> front_of(std::shared_ptr<NodeType> element)const
            {
                if(!element)
                    throw std::invalid_argument("front_of error: element must not be null!");
                std::shared_ptr<NodeType> pre;
                std::shared_ptr<NodeType> cur=head;
                while(cur)
                {
                    if(element==cur)
                        break;
                    pre=cur;
                    cur=cur->next;
                }
                if(!cur)
                    throw std::invalid_argument("front_of error: element not in the list!");
                else return pre;
            }


            //!to_string：返回链表的字符串描述
            /*!
            * \return :链表的字符串描述
            *
            * 依次拼接各结点的字符串描述
            */
            std::string to_string() const
            {
                std::ostringstream os;
                os<<"list:\n";
                auto cur=head;
                while(cur)
                {
                    os<<cur->to_string()<<";\t";
                    cur=cur->next;
                }
                os<<"\ncurrent:\t";
                if(current)
                    os<<current->to_string();
                else os<<"nullptr";
                return os.str();
            }
        };

        //!ListNode：链表结点的数据结构
        /*!
        *
        * 链表结点包含两个数据成员：
        *
        * - value：链表结点保存数据的弱指针（因为该保存数据有个强指针指向本结点）
        * - next:指向本链表中当前结点的下一个结点的强指针
        *
        */
        template<typename ValueType> struct ListNode
        {
            //!ListNode默认构造函数
            /*!
            *
            * 默认构造函数完成两个设置：value设为空指针，next设为空指针
            *
            */
            ListNode():value(std::weak_ptr<ValueType>()),next(std::shared_ptr<ListNode>()){}
            std::weak_ptr<ValueType> value;/*!<  链表结点保存数据的弱指针*/
            std::shared_ptr<ListNode> next;/*!<  指向本链表中当前结点的下一个结点的强指针*/
            //!to_string：返回结点的字符串描述
            /*!
            * \return :顶点的字符串描述
            *
            * 主要是返回 `value`成员的字符串描述
            */
            std::string to_string() const
            {
                std::ostringstream os;
                os<<"list_node:";
                auto lock_v=value.lock();
                if(lock_v)
                    os<<lock_v->to_string();
                else os<<"nullptr";
                return os.str();
            }
        };


        //!FrontFlowVertex：relabel_to_front算法的图的结点的数据结构，算法导论26章26.4节
        /*!
        *
        * FrontFlowVertex 继承自 FlowVertex，它比FlowVertex顶点多了一个`N_List`数据成员，表示邻接链表
        *
        * relabel_to_front 算法中，每一个FrontFlowVertex顶点位于两个级别的链表中：
        *
        * - L 链表：最顶层的链表，L包含了所有的非源、非汇顶点
        * - u.N 链表：某个顶点u的邻接链表
        *
        *
        */
        template<typename KType> struct FrontFlowVertex:public FlowVertex<KType>
        {
            typedef KType KeyType;    /*!< 顶点存储数据的类型*/
            typedef int VIDType;      /*!< 顶点编号的数据类型*/

            List<ListNode<FrontFlowVertex>> N_List; /*!<  顶点的邻接链表*/

            //!默认构造函数
            FrontFlowVertex(){}
            //!显式构造函数，指定`key`
            /*!
            * \param  k:顶点存放的数据
            */
            explicit FrontFlowVertex(const KeyType&k):FlowVertex<KeyType>(k){}
            //!显式构造函数，指定`key`和编号
            /*!
            * \param  k:顶点存放的数据
            * \param  d:顶点的编号
            */
            FrontFlowVertex(const KeyType&k,VIDType d):FlowVertex<KeyType>(k,d){}

            //!to_string：返回顶点的字符串描述
            /*!
            * \return :顶点的字符串描述
            *
            * 在`FlowVertex`基类的基础上输出`N_List`信息
            */
            virtual std::string to_string() const
            {
                std::ostringstream os;
                os<<FlowVertex<KType>::to_string()<<"\t N_List:"<<N_List.to_string();
                return os.str();
            }
        };

    }
}
#endif // FRONTFLOWVERTEX


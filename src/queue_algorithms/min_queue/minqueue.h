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
#ifndef MINQUEUE
#define MINQUEUE
#include<vector>
#include<memory>
#include<functional>
#include"src/header.h"
using IntroductionToAlgorithm::GraphAlgorithm::unlimit;

namespace IntroductionToAlgorithm
{
    namespace QueueAlgorithm
    {

        //!MinQueue：最小优先级队列，算法导论第6章6.5节
        /*!
        *
        * 优先级队列是一种用来维护由一组元素构成集合S的数据结构，其中每个元素都有一个相关的值，称之为关键字。一个最小优先级队列支持以下操作：
        *
        * - insert(S,x):将元素x插入到集合S中。
        * - min(S):返回S中具有最小关键字的元素
        * - extract_min(S):去掉并返回S中具有最小关键字的元素
        * - decrease_key(S,x,k):将元素x的关键字值减小到k,这里要求k的值小于x的原始关键字
        *
        * 本算法的实现时，有以下几种变化：
        *
        * - 增加了以下的接口：
        *   - is_empty(S): 返回S是否为空
        *   - is_inqueue(S,x):判断元素x是否在S中
        *   - setupHeap(S):建立最小堆（由堆的接口遗留而来)
        *   - heapify(S,index):操作堆的指定结点使得它符合最小堆条件（由堆的接口遗留下来）
        * - 增加了队列容量属性。队列容量由`_data`的大小来表征。默认将`_data`大小设为0；可以显式提供`reseve_size`参数来设置`_data`的大小。
        *   队列容量用于限制队列大小。一旦队列已满，则下一次插入之前会将队列容量增加一倍；一旦队列不足队列的1/4，则一旦执行`extract_min`操作则将队列容量缩减至一半
        * - 增加了两个特殊的可调用对象，这两个方法的引入使得最小优先级队列不仅可以应用于class和struct类型，也可以应用于int,double等非类的类型
        *   - _getKey:是一个std::function<TKeyType&(std::shared_ptr<T>)>类型的对象，它可以接收std::shared_ptr<T>类型的参数，返回TKeyType类型的引用。
        *   其中队列保存的是T类型数据的强引用，TKeyType是T类型数据的关键字类型。通过_getKey可以获取队列数据的关键字的引用。
        *       - 对于class类型，TKeyType就是T对象的关键字类型，_getKey就是返回关键字的引用
        *       - 对于int等内置类型，TKeyType就是T本身。_getKey就是返回它自身的引用
        *   - _compare:是一个std::function<bool (std::shared_ptr<T>,std::shared_ptr<T>)>类型的对象，它用于队列中两个数据的大小比较。
        *
        */
        template<typename T,typename TKeyType>
        class MinQueue
        {
        public:
            typedef std::function<bool (std::shared_ptr<T>,std::shared_ptr<T>)> CompareType ; /*!< 一个可调用对象类型，该类型的对象可用于比较两个std::shared_ptr<T>的小于比较*/
            typedef std::function<TKeyType&(std::shared_ptr<T>)> GetKeyType; /*!< 一个可调用对象，该类型的对象可用于获取std::shared_ptr<T>的关键字，并修改该关键字（返回的是关键字的引用）*/
            //!显式构造函数
            /*!
            *  \param compare:一个可调用对象，可用于比较两个std::shared_ptr<T>对象的小于比较
            *  \param getKey：一个可调用对象，它的参数为std::shared_ptr<T>，返回TKey&。通过它的返回值可以获取T的key，也可以修改T的key
            *
            */
            MinQueue(CompareType compare,GetKeyType getKey):_size(0),_compare(compare),_getKey(getKey){}
            //!显式构造函数
            /*!
            * \param reseve_size:指定队列的初始容量
            * \param compare:一个可调用对象，可用于比较两个std::shared_ptr<T>对象的小于比较
            * \param getKey：一个可调用对象，它的参数为std::shared_ptr<T>，返回TKey&。通过它的返回值可以获取T的key，也可以修改T的key
            *
            */
            MinQueue(std::size_t reseve_size,CompareType compare,GetKeyType getKey):_size(0),_compare(compare),_getKey(getKey)
            {
                _data.resize(reseve_size);
            }
            //!min:返回最小值
            /*!
            * \return 最小值的强引用
            *
            * 根据最小堆的性质，队列的第一个值就是最小值的强引用。如果队列为空，则返回一个空引用
            *
            * - 时间复杂度 O(1)
            *
            */
            std::shared_ptr<T> min()
            {
                if(!_size)
                    return std::shared_ptr<T>();
                return _data[0];
            }
            //!extract_min:删除队列中最小值，并返回最小值
            /*!
            *  \return 最小值的强引用
            *
            * 根据最小堆的性质，队列的第一个值就是最小值的强引用。
            *
            *   - 如果队列为空，则返回一个空引用
            *   - 如果队列非空，则执行以下操作：
            *       - 交换队列的第一个元素和最后一个元素
            *       - 队列的`_size`自减
            *       - 此时队列的首个元素违反了最小堆性质，因此执行`heapify(0)`保持性质
            *       - 返回旧的首个元素
            *
            * 一旦队列长度不足容量的1/4，则将队列容量设置为队列长度的一倍（为了防止极端情况，如_size=0，此时将队列容量设为队列长度的一倍加上2）
            *
            * - 时间复杂度 O(h),h为堆的高度
            * - 原地操作
            */
            std::shared_ptr<T> extract_min()
            {
                if(!_size)
                    return std::shared_ptr<T>();
                auto result=_data[0];
                _data[0]=_data[_size-1];                
                _size--;
                heapify(0);
                if(_size<=_data.size()/4)
                    _data.resize(_size*2+2);
                return result;
            }
            //!insert:向队列中插入一个元素
            /*!
            * \param element: 待插入元素，如果元素为空引用则直接返回
            * \return: 插入的元素在队列中的位置。若元素为空指针则返回-1
            *
            * 插入之前首先判断队列是否已满。若队列已满，则将`_data`扩容为大小`_size*2+2`。
            *
            * - 若`_size==_data.size()`则说明队列已满
            *
            * 插入过程为：
            *
            * - 保留待插入元素的`key`，同时将待插入语元素的`key`设置为无穷大，并将待插入元素插入到队尾
            * - 执行`decreate_key(..)`操作
            *
            * 一旦队列已满，则将队列容量设置为队列长度的一倍（为了防止极端情况，如_size=0，此时将队列容量设为队列长度的一倍加上2）
            *
            * - 时间复杂度 O(h)
            * - 原地操作
            */

            int insert(std::shared_ptr<T> element)
            {
                if(! element)  return -1;
                if(_size==_data.size()) _data.resize(_size*2+2);
                int index=_size;
                _size++;
                _data[index]=element;
                TKeyType& k=_getKey(element);
                TKeyType old_k=k;
                k=unlimit<TKeyType>();
                decreate_key(index,old_k);
                return index;
            }
            //!is_empty:返回队列是否为空
            /*!
            * \return 队列是否为空
            *
            * 若队列的`_size`为0，则队列为空；否则队列不为空
            *
            * - 时间复杂度 O(1)
            *
            */
            bool is_empty()
            {
                return _size==0;
            }

            //!is_inqueue:返回指定元素是否在队列中
            /*!
            * \param element:待判定的元素，要求非空。若它为空引用则抛出异常
            * \return 指定元素在队列中的下标
            *
            * 从前到后依次遍历队列，如果队列中某个元素等于`element`，则返回非负整数值，
            * 代表它在队列的std::vector中的位置；否则返回-1
            *
            * - 时间复杂度 O(h)
            */
            int index_inqueue(std::shared_ptr<T> element)
            {
                if(!element) throw std::invalid_argument("is_inqueue error: element must not be nullptr!");
                for(std::size_t index=0;index<_size;index++)
                {
                    if(element==_data[index])
                        return index;
                }
                return -1;
            }
            //!decreate_key:缩减队列中某个元素的`key`
            /*!
            * \param element_index: 待缩减元素的下标
            * \param new_key：待缩减元素的新`key`，类型为TKey
            *
            * 缩减之前先判断缩减是否有效，若无效则抛出异常。
            *
            * - 若`element_index`超过了队列大小，则抛出异常
            * - 若`new_key`大于等于待缩减元素的`key`，则抛出异常
            *
            * 缩减过程为：
            *
            * - 将待缩减元素的`key`赋值为新值
            * - 不断的将该元素向父节点比较：
            *   - 若父节点较小，则终止比较过程
            *   - 若父节点较大，则交换当前节点与父节点，并将当前节点指向父节点进行下一轮比较
            *   - 若当前节点已经是队列首个元素，则终止比较过程
            *
            * - 时间复杂度 O(h)
            * - 原地操作
            */
            void decreate_key(std::size_t element_index,TKeyType new_key)
            {
                if(element_index>=_size)
                    throw std::invalid_argument("decreate_key error: element_index must less than _size!");
                if(new_key>_getKey(_data.at(element_index)))
                    throw std::invalid_argument("decreate_key error: new_key less _data.at(element_index)->key!");

                _getKey(_data.at(element_index))=new_key;
                bool valid;
                while(element_index!=0 )
                {
                    auto pIndex=_parentIndex(element_index,valid);
                    if(!valid) break;
                    if(_compare(_data.at(pIndex),_data.at(element_index))) break;
                    std::swap(_data.at(pIndex),_data.at(element_index));
                    element_index=pIndex;
                }
            }
            //!setupHeap:建堆
            /*!
            * \return void
            *
            * 从后一半的元素开始依次向前调用heapify操作（根据最小堆性质，除了最底层它是完全充满的）
            *
            * - 时间复杂度 O(nlogn)
            * - 原地操作
            */
            void setupHeap()
            {
                if(_size<=1)
                    return;
                int index=(_size-1)/2;
                while(index>=0)
                {
                    heapify(index);
                    index--;
                }
            }
            //!heapify：维持堆性质
            /*!
            * \param elementIndex : 要维持以该节点为根节点的子堆的堆性质
            * \return void
            *
            * 首先调用比较该节点与左右子节点的最小值。如果最小值为它本身，则维持了性质，返回；如果最小值不是它本身，那么必然为左、右子节点之一。
            * 将该最小节点（假设为左子节点）交换到根节点，然后以左子节点递归调用heapify操作
            *
            * - 时间复杂度 O(n)
            * - 原地操作
            */
            void heapify(std::size_t elementIndex)
            {
                if(elementIndex>=_size)
                    return;
                auto minIndex=elementIndex;
                bool left_valid=true;
                bool right_valid=true;
                auto leftIndex=_lchildIndex(elementIndex,left_valid);
                auto rightIndex=_rchildIndex(elementIndex,right_valid);

                if(left_valid)
                {
                    if( _compare(_data.at(leftIndex),_data.at(minIndex)))
                        minIndex=leftIndex;
                }
                if(right_valid)
                {
                    if( _compare(_data.at(rightIndex),_data.at(minIndex)))
                        minIndex=rightIndex;
                }
                if(minIndex!=elementIndex)
                {
                    std::swap(_data.at(elementIndex),_data.at(minIndex));
                    heapify(minIndex);
                }
            }
       protected:
            //!_parentIndex:返回一个节点的父节点位置
            /*!
            * \param elementIndex : 子节点位置
            * \param valid: 一个bool&值，用于返回，指示父节点是否有效
            * \return 父节点位置(std::size_t)
            *
            * 根据最小堆的性质，一个子节点elementIndex的父节点是它的位置(elementIndex-1)/2。
            *
            * - 超出堆大小的节点，其父节点无效
            *
            */
            std::size_t _parentIndex(std::size_t elementIndex,bool& valid)
            {
                if(elementIndex>=_size)
                {
                    valid=false; //无效结果
                    return 0;
                }
                valid=true; //有效结果
                if (elementIndex ==0) return 0; //根节点的父节点是自己
                else  return (elementIndex-1)>>1;
            }
            //!_lchildIndex:返回一个节点的左子节点位置
            /*!
            * \param elementIndex : 节点位置
            * \param valid: 一个bool&值，用于返回，指示子节点是否有效
            * \return 左子节点位置(std::size_t)
            *
            * 根据最小堆的性质，一个节点elementIndex的左子节点是它的位置(elementIndex/2)+1
            *
            * - 当最小堆大小为0、1时，它没有左子节点，左子节点无效
            * - 当左子节点超过堆大小时，它无效
            *
            */
            std::size_t _lchildIndex(std::size_t elementIndex,bool& valid)
            {
                if(_size<2)
                {
                    valid=false; //数组元素太少无效结果
                    return 0;
                }
                if(  elementIndex>((_size-2)>>1)  )
                {
                    valid=false;//超出范围，无效
                    return 0;
                }
                valid=true;
                return (elementIndex<<1)+1;
            }
            //!_rchildIndex:返回一个节点的右子节点位置
            /*!
            * \param elementIndex : 节点位置
            * \param valid: 一个bool&值，用于返回，指示子节点是否有效
            * \return 右子节点位置(std::size_t)
            *
            * 根据最小堆的性质，一个节点elementIndex的右子节点是它的位置(elementIndex/2)+2
            *
            * - 当最小堆大小为0、、1、2时，它没有右子节点，右子节点无效
            * - 当右子节点超过堆大小时，它无效
            *
            */
            std::size_t _rchildIndex(std::size_t elementIndex,bool& valid)
            {
                if(_size<3)
                {
                    valid=false; //数组元素太少无效结果
                    return 0;
                }
                if(  elementIndex>((_size-3)>>1)  )
                {
                    valid=false;//超出范围，无效
                    return 0;
                }
                valid=true;
                return (elementIndex<<1)+2;
            }
        private:
            std::vector<std::shared_ptr<T>> _data;  /*!< 最小优先级队列的数据*/
            std::size_t _size;  /*!<  堆大小*/
            CompareType _compare;  /*!< 一个可调用对象，可用于比较两个std::shared_ptr<T>的小于比较*/
            GetKeyType _getKey; /*!<  一个可调用对象，可用于获取std::shared_ptr<T>的关键字，并修改该关键字（返回的是关键字的引用）*/
        };
    }
}
#endif // MINQUEUE


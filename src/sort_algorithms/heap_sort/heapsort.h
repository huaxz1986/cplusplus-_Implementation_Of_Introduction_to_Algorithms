#ifndef HEAP_SORT
#define HEAP_SORT
namespace IntrodunctionToAlgorithm
{
    namespace SortAlgorithm
    {

    //!Sort_Heap：用于堆排序的堆，算法导论第6章
    /*!
    *
    * - 堆排序思想：假设对数组A[p...r]排序：首先将数组构建成一个最小堆（或者最大堆）。然后第一个元素就是堆中最小的元素。
    * 将第一个元素与最后一个元素交换，同时堆的规模缩减1，再将堆维持最小堆性质。不断循环最后得到一个排序好的数组    *
    * - 时间复杂度 O(nlogn)
    * - 原地排序
    *
    * 堆排序有两个重要操作：
    *
    * - heapify(index)操作：维持以index为根节点的子堆的性质。它比较index与其左右子节点的值，选取其最小的那个提升到index节点上。同时递归向下。具体见_heapify()方法说明
    * - setupHeap()操作： 建堆操作。它从堆的最低层向上层反复调用heapify操作进行建堆。
    */
        template<typename Iterator,typename Compare=std::less<typename std::iterator_traits<Iterator>::value_type>>
        class Sort_Heap
        {
        public:
            typedef typename std::iterator_traits<Iterator>::value_type T; /*!< 迭代器指向对象的值类型*/
            //!operator()
            /*!
            * \param from : 待排序序列的起始迭代器（也可以是指向数组中某元素的指针）
            * \param size: 待排序序列的长度
            * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
            * \return void
            *
            * 首先调用 _setupHeap()建堆。然后再反复抽取最小值到堆尾部，然后维持堆的性质。
            *
            * - 时间复杂度 O(nlogn)
            * - 原地排序
            */
            void operator () (const Iterator from, std::size_t size,Compare compare=Compare())
            {
                _from=from;
                _size=size;
                _setupHeap(compare);
                while(_size>0)
                {
                    std::swap(*_from,*(_from+_size-1));
                    _size--;
                    _heapify(0,compare);
                }
            }
        private:
            //!_setupHeap:建堆
            /*!
            * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
            * \return void
            *
            * 从后一半的元素开始依次向前调用heapify操作（根据最小堆性质，除了最底层它是完全充满的）
            *
            * - 时间复杂度 O(nlogn)
            * - 原地操作
            */
            void _setupHeap(Compare compare=Compare())
            {
                if(_size<=1)
                    return;
                int index=(_size-1)/2;
                while(index>=0)
                {
                    _heapify(index,compare);
                    index--;
                }
            }
            //!_heapify：维持堆性质
            /*!
            * \param elementIndex : 要维持以该节点为根节点的子堆的堆性质
            * \param compare: 一个可调用对象，可用于比较两个对象的小于比较，默认为std::less<T>
            * \return void
            *
            * 首先调用比较该节点与左右子节点的最小值。如果最小值为它本身，则维持了性质，返回；如果最小值不是它本身，那么必然为左、右子节点之一。
            * 将该最小节点（假设为左子节点）交换到根节点，然后以左子节点递归调用heapify操作
            *
            * - 时间复杂度 O(n)
            * - 原地操作
            */
            void _heapify(std::size_t elementIndex,Compare compare=Compare())
            {
                if(elementIndex>=_size)
                    return;
                auto maxIndex=elementIndex;
                bool left_valid=true;
                bool right_valid=true;
                auto leftIndex=_lchildIndex(elementIndex,left_valid);
                auto rightIndex=_rchildIndex(elementIndex,right_valid);

                if(left_valid)
                {
                    if( compare(*(_from+maxIndex),*(_from+leftIndex)))
                        maxIndex=leftIndex;
                }
                if(right_valid)
                {
                    if( compare(*(_from+maxIndex),*(_from+rightIndex)))
                        maxIndex=rightIndex;
                }
                if(maxIndex!=elementIndex)
                {
                    std::swap(*(_from+elementIndex),*(_from+maxIndex));
                    _heapify(maxIndex,compare);
                }
            }
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
            Iterator _from;/*!< 堆根节点位置*/
            std::size_t _size;/*!<  堆大小*/
        };
    }
}
#endif // HEAP_SORT


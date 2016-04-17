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
#ifndef KMP
#define KMP
#include<vector>
namespace IntroductionToAlgorithm {
    namespace StringMatchingAlgorithm{

        //! get_pai： KMP字符串匹配算法的预处理操作，算法导论第32章32.4节
        /*!
        * \param iterP_begin : 模式序列P的起始迭代器
        * \param iterP_end: 模式序列P的终止迭代器
        * \return: pai函数
        *
        * 算法步骤：
        *
        * - 初始化： pai[1]=0,k=0
        * - 遍历 q 从 2 到 m:（因为Pk必须是Pm的真子集，因此m从2开始）
        *   - 循环，条件为 k>0并且 P[k+1]!=P[q]；循环中执行 k=pai[k]（因为若P[k+1]=P[q]，则说明找到了Pk是Pm的真子集）
        *   - 若 P[k+1]==P[q]，则k=k+1并且pai[q]=k
        * - 返回 pai
        *
        *  >这里要求m>0；否则抛出异常
        */
        template<typename IteratorP>
        std::vector<int> get_pai(const IteratorP iterP_begin,const IteratorP iterP_end)
        {
            auto lenP=std::distance(iterP_begin,iterP_end);
            if(lenP<=0)
                throw std::invalid_argument("get_pai error:iterP_begin must < iterP_end");

            std::vector<int> pai(lenP,0);//pai[1]=0
            int k=0;
            for(int q=1;q<lenP;q++)//P[2...m]
            {
                while(k>0 && *(iterP_begin+k)!=*(iterP_begin+q))//右移直到P[k+1]==P[m]，这里从0计数，所以用*(iterP_begin+k)
                    k=pai[k];
                if(*(iterP_begin+k)==*(iterP_begin+q)) k++;//确实发生P[k+1]==P[m]，这里从0计数，所以用*(iterP_begin+k)
                pai[q]=k;
            }
            return pai;
        }
        //! kmp_match： KMP字符串匹配算法，算法导论第32章32.4节
        /*!
        * \param iterT_begin : 被文本序列T的起始迭代器
        * \param iterT_end: 文本序列T的终止迭代器
        * \param iterP_begin : 模式序列P的起始迭代器
        * \param iterP_end: 模式序列P的终止迭代器
        * \return: 有效偏移组成的 std::vector
        *
        * ## 字符串匹配
        *
        * 字符串匹配的形式化定义如下：假设文本是一个长度为n的数组 T[1...n]，而模式是一个长度为m的数组P[1...m]，
        * 其中m<=n。进一步假设P和T的元素都是来自一个有限字母集合M的字符。如M={0,1}或者M={a,b,c,...z}。
        * 字符数组P和T通常称为字符串。
        *
        * ## KMP 字符串匹配算法
        *
        * ### 算法原理
        *
        * #### 模式的前缀函数
        *
        * 模式的前缀函数 pai 包含了模式与它自身偏移进行匹配的信息。假设模式字符P[1...q]与文本字符T[s+1,...s+q]匹配，
        * s'是某个偏移量，s'>s。则对于某些k<q，满足：P[1...k]=T[s'+1,...s'+k]的最小s'>s，其中s'+k=s+q?
        *
        *    ----------------------------------------------------------
        * T  | 1 | 2 | 3 |.....|s+1|............| s+q |..............| n |  T[s+q]
        *    ----------------------------------------------------------
        *                        |<-----长度为q---->|
        *                      --------------------------------
        *                P     |  1  | 2 |.......| q |....| m | :Pq=P[1...q]
        *                      --------------------------------
        *
        *    ----------------------------------------------------------
        * T  | 1 | 2 | 3 |.....|s+1|..|s'+1|..........| s+q |..............| n |  T[s+q]
        *    ----------------------------------------------------------
        *                               |<-----长度为k---->|
        *                            ------------------------------------
        *                      P     |  1  | 2 |........| k |..|q|..| m | :Pk=P[1...k]
        *                            ------------------------------------
        *
        * 换句话说，已知Pq是T[s+q]的后缀，我们希望Pq的真前缀 Pk 也是T[s+q]的后缀。我们把在P前缀长度
        * 范围内的差值 q-k 加到s上即可得到新的偏移 s'=s+(q-k)。
        *
        * 可以用模式与它自身的比较来预先计算出这些必要的信息。前述可知Pk是T[s+q]的后缀，它也是Pq的真前缀，
        * 因此要求出 Pk是Pq的后缀的最大的k<q。于是这个新的偏移s'=s+(q-k)就是下一个可能的有效偏移。
        * 之所有求最大的k，就是为了是(q-k)尽可能小，从而不会漏过任何的可能的有效偏移。
        *
        * 模式P的前缀函数就是函数 pai:{1,2,...,m}--> {0,1,2,...,m-1}，满足：
        * pai[q]=max{k:k<q 且 Pk是Pq的后缀}。即pai[q]是Pq的真后缀P的最长前缀长度。
        *
        *
        * #### kmp 算法
        *
        * KMP 算法用到了辅助函数 pai，它在O(m)时间内根据模式预先计算出pai并且存放在数组pai[1...m]中。
        * 数组pai能够使我们按照需要即时计算出转移函数。
        *
        * 计算出pai数组之后，KMP算法从左到右扫描文本序列T，并从pai中获取转移函数。当状态结果为 m时，
        * 当前偏移为有效偏移点。
        *
        * ### 算法步骤
        *
        * #### 预处理算法（构造pai函数)
        *
        * - 初始化： pai[1]=0,k=0
        * - 遍历q 从 2 到 m:（因为Pk必须是Pm的真子集，因此m从2开始）
        *   - 循环，条件为 k>0并且 P[k+1]!=P[q]；循环中执行 k=pai[k]（因为若P[k+1]=P[q]，则说明找到了Pk是Pm的真子集）
        *   - 若 P[k+1]==P[q]，则k=k+1并且pai[q]=k
        * - 返回 pai
        *
        *
        * #### 匹配算法
        *
        * - 初始化 q=0
        * - 遍历i从1到n:
        *   - 循环，条件为 q>0 并且 P[q+1]!=T[i]；在循环中执行 q=pai[q]
        *   - 如果 P[q+1]==T[i] 则 q=q+1
        *   - 如果 q==m，则找到了有效偏移点。将有效偏移加入结果std::vector中。然后 q=pai[q](比如有这一句，否则后面P[q+1]会溢出)
        * - 返回结果std::vector
        *
        * >这里要求n>=0，m>=0(模式序列可以为空字符串)；否则抛出异常
        * >
        * >这里要文本序列T和模式序列P的元素类型相等，否则编译失败
        *
        *
        * ### 算法性能
        *
        * 计算前缀函数的运行时间为 O(m)，匹配时间为O(n)，总运行时间为 O(n)
        *
        */
        template<typename IteratorT,typename IteratorP>
        std::vector<int> kmp_match(const IteratorT iterT_begin,const IteratorT iterT_end,
             const IteratorP iterP_begin,const IteratorP iterP_end)
        {
            typedef typename std::iterator_traits<IteratorT>::value_type T1;
            typedef typename std::iterator_traits<IteratorP>::value_type T2;

            static_assert(std::is_same<T1, T2>::value,"finite_automaton_match error:sequence T and P must contain same type value!");

            auto lenT=std::distance(iterT_begin,iterT_end);
            auto lenP=std::distance(iterP_begin,iterP_end);
            if(lenT<0)
                throw std::invalid_argument("finite_automaton_match error:iterT_begin must <= iterT_end");
            if(lenP<=0)
                throw std::invalid_argument("finite_automaton_match error:iterP_begin must < iterP_end");

            std::vector<int> result;
            if(lenT<lenP) //模式串P较长，直接返回
                return result;

            //**********  预处理  **************
            auto pai=get_pai(iterP_begin,iterP_end);
            //*********** 匹配 ***************
            int q=0;
            for(int i=0;i<lenT;i++)
            {
                while(q>0 && *(iterP_begin+q)!=*(iterT_begin+i)) q=pai[q];//右移直到P[q+1]==T[i]，这里从0计数，所以用*(iterP_begin+q)
                if(*(iterP_begin+q)==*(iterT_begin+i)) q++;//确实发生P[q+1]==T[i]，这里从0计数，所以用*(iterP_begin+q)
                if(q==lenP)//找到有效偏移点
                {
                    result.push_back(i-lenP+1); //i左侧lenP的位置
                    q=pai[lenP-1];    //防止出现P[lenP+1]的情况出现，这里用pai[lenP-1]
                }
            }
            return result;
        }
    }
}
#endif // KMP


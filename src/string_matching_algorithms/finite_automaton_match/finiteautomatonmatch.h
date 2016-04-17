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
#ifndef AUTOMATONMATCH
#define AUTOMATONMATCH
#include<vector>
#include<ostream>
namespace IntroductionToAlgorithm {
    namespace StringMatchingAlgorithm{


        //! index_of_M ： 返回返回字符a，算法导论第32章32.3节
        /*!
        * \param beginM : 字符集序列M的起始迭代器
        * \param k_iter: 字符集序列M的终止迭代器
        * \param a: 文字 a
        * \return: 返回字符a
        *
        * 通过逐一比较来返回a在M中的位置。
        *
        * 如果a不在字符集M中，或者a在字符集M中有多个位置，则抛出异常
        *
        */
        template<typename Iterator> typename std::iterator_traits<Iterator>::difference_type
                                                index_of_M(Iterator beginM,Iterator endM,
                                              typename std::iterator_traits<Iterator>::value_type a)
        {
            auto len_M=std::distance(beginM,endM);
            if(len_M<0)
                throw std::invalid_argument("index_of_M error: must be endM>beginM!");

            auto iter=beginM;
            auto result_iter=endM;
            while(iter<endM)
            {
                if(*iter==a)
                {
                    result_iter=iter;
                    iter++;
                    break;
                }
                iter++;
            }
            std::ostringstream os;
            os<<a;
            while(iter<endM) //继续查找，有重复字符则抛出异常
            {
                if(*iter==a) throw std::invalid_argument(std::string("index_of_M error: M has dulplicate character ")+os.str()+"!");
                iter++;
            }
            if(result_iter==endM) throw std::invalid_argument(std::string("index_of_M error: M has no charactor ")+os.str()+"!");
            return std::distance(beginM,result_iter);
        }
        //! is_end_with： 返回Pk是否是( Pq a)的后缀，算法导论第32章32.3节
        /*!
        * \param begin : 模式序列P的起始迭代器
        * \param k_iter: Pk的终止迭代器
        * \param q_iter : Pq的终止迭代器
        * \param a: 文字 a
        * \return: Pk是否是( Pq a)的后缀
        *
        * 通过逐一比较来返回Pk是否是( Pq a)的后缀。
        *
        * > 要求k_iter>=begin,q_iter>=begin，否则抛出异常
        *
        * > 空字符串是所有字符串的有效后缀
        */
        template<typename Iterator> bool is_end_with(Iterator begin,Iterator k_iter,Iterator q_iter,
                                              typename std::iterator_traits<Iterator>::value_type a)
        {
            auto k=std::distance(begin,k_iter);
            auto q=std::distance(begin,q_iter);
            if(k<0||q<0)
                throw std::invalid_argument("is_end_with error:must be k_iter>=begin and q_iter>=begin!");

            if(k==0) return true; // 空字符串是所有字符串的后缀
            if(a!=*(k_iter-1)) return false; //P[k]!=a
            for(int i=0;i<k-1;i++)
                if(*(k_iter-2-i)!=*(q_iter-1-i))return false;  //P[k-i-1]!=P[q-i]
            return true;
        }


        //! get_delt： 获取模式字符串的转移函数，算法导论第32章32.3节
        /*!
        * \param P_begin : 模式序列P的起始迭代器
        * \param P_end: 模式序列P的终止迭代器
        * \param M_begin : 有限字符集的起始迭代器
        * \param M_end:有限字符集的终止迭代器
        * \param delta: 转移矩阵的引用，用于存放转移矩阵
        * \return: void
        *
        * 步骤：
        *
        * - 遍历P，q从0到m (因为q=0时，P_0=空字符串):
        *   - 对每个字符a属于有限字母集合a，寻找Pk是 (Pq a) 后缀的最大的k，则 delt(q,a)=k
        *
        * > 这里要求n>=0，m>=0(模式序列可以为空字符串)；否则抛出异常
        *
        * > 这里要求有限字符集M和模式序列P的元素类型相等，否则编译失败
        *
        *
        */
        template<typename PIterator,typename MIterator>
        void get_delta(const PIterator P_begin,const PIterator P_end,
                      const MIterator M_begin,const MIterator M_end,std::vector<std::vector<int>>&delta)
        {
            typedef typename std::iterator_traits<PIterator>::value_type T1;
            typedef typename std::iterator_traits<MIterator>::value_type T2;
            static_assert(std::is_same<T1, T2>::value,"get_delt error:mode sequence P and sequence M must contain same type value!");

            auto p_len=std::distance(P_begin,P_end);
            auto m_len=std::distance(M_begin,M_end);
            if(p_len<0)
                throw std::invalid_argument("finite_automaton_match error:P_begin must <= P_end");
            if(m_len<=0)
                throw std::invalid_argument("finite_automaton_match error:M_begin must < M_end");

            delta.clear(); //矩阵清零

            for(int q=0;q<=p_len;q++)
            {
                delta.push_back(std::vector<int>()); //添加一行

                auto m_iter=M_begin;
                while(m_iter<M_end)
                {
                    //*********** 寻找Pk是 (Pq a) 后缀的最大的k ***********
                    int k=std::min(p_len+1,q+2);
                    do{
                        k--;
                    }
                    while(!is_end_with(P_begin,P_begin+k,P_begin+q,*(m_iter)));
                    //******  delt(q,a)=k *******
                    delta[delta.size()-1].push_back(k);//最后一行中添加列数据
                    m_iter++;
                }
            }

        }

        //! finite_automaton_match： 有限自动机字符串匹配算法，算法导论第32章32.3节
        /*!
        * \param iterT_begin : 被文本序列T的起始迭代器
        * \param iterT_end: 文本序列T的终止迭代器
        * \param iterP_begin : 模式序列P的起始迭代器
        * \param iterP_end: 模式序列P的终止迭代器
        * \param iterM_begin : 有限字符集的起始迭代器
        * \param iterM_end: 有限字符集的终止迭代器
        * \return: 有效偏移组成的 std::vector
        *
        * ## 字符串匹配
        *
        * 字符串匹配的形式化定义如下：假设文本是一个长度为n的数组 T[1...n]，而模式是一个长度为m的数组P[1...m]，
        * 其中m<=n。进一步假设P和T的元素都是来自一个有限字母集合M的字符。如M={0,1}或者M={a,b,c,...z}。
        * 字符数组P和T通常称为字符串。
        *
        * ## 有限自动机 字符串匹配算法
        *
        * ### 算法原理
        *
        *
        * #### 有限自动机
        *
        * 定义有限自动机 AM 是一个5元组(Q,q_0,A,M,delt)，其中：
        *
        * - Q:为状态的有限集合
        * - q_0属于Q：为初始状态
        * - A是Q的子集：表示一个特殊的接受状态集合
        * - M：是有限的输入字母表
        * - delt:为 Q*M--> Q 的函数，称为有限自动机的转移函数。
        *
        * 有限自动机开始于状态 q_0，每次读入输入字符串的一个字符。如果有限自动机在状态q时读入了字符a，则它从状态q变成了状态 delt(q,a)，
        * 进行了一次转移。每当当前状态q属于A时，则说明状态机接受了迄今为止所读入的字符串。
        *
        * 有限自动机引入了一个函数 phai,称为终态函数。定义 M* 表示所有的有限长度的字符串的集合，该字符串是由所有字母表M中的字符组成。
        * 长度为0的空字符串记为e,e属于M*. phai 是从 M*到Q的函数，满足： pai(w)是有限自动机扫描字符串w后的终止状态。
        * 其中 w 属于 M*。因此当且仅当 phai(w)属于A时，有限自动机接受字符串 w。我们可以用转移函数定义 phai:
        *
        * - phai(e)=q_0
        * - phai(wa)=delt(phai(w),a), w属于M*,a属于M
        *
        *
        * #### 字符串匹配自动机
        *
        * 对于一个给定的模式P，我们可以在预处理阶段构造出一个字符串匹配自动机，根据模式构造出的自动机后，再利用它来搜寻文本字符串。
        * 首先定义一个辅助函数 sigma，称之为P的后缀函数。函数 sigma是一个 M*到{0,1,....m}上的映射：
        *
        * - sigma(x)=max{k:P_k是x的后缀}，即sigma(x)是x的后缀中，P的最长前缀的长度。
        *
        * 因为空字符串P0=e是每一个字符串的后缀，因此sigma(e)=0。对于一个长度为m的模式P，sigma(x)=m当且仅当P是x的后缀。
        *
        * 给定模式P[1...m]，其相应的字符串匹配自动机定义如下：
        *
        * - 状态集合Q为{0,1,...m}。开始状态q_0为0状态，并且只有状态m是唯一被接受的状态。
        * - 对任意状态q和字符a，转移函数 delt定义为： delt(q,a)=sigma(Pq a)
        *
        *
        * 考虑最近一次扫描T的字符。为了使得T的一个子串（以T[i]结尾的子串）能够和P的某些前缀Pj匹配，则前缀Pj必须是Ti的一个后缀。
        * 假设q=phai(Ti)，则读完Ti之后，自动机处于状态q。转移函数delt使用状态数q表示P的前缀和Ti后缀的最长匹配长度。也就是说，
        * 在状态q是， Pq是Ti的后缀，且q=sigma(Ti)。
        *
        *    ----------------------------------------------------------
        * T  | 1 | 2 | 3 |.....|i-q+1|...........| i |..............| n |  :Ti=T[1...i]
        *    ----------------------------------------------------------
        *                        |<-----长度为q---->|
        *                      --------------------------------
        *                P     |  1  | 2 |.......| q |....| m | :Pq=P[1...q]
        *                      --------------------------------
        *
        *
        * ### 算法步骤
        *
        * #### 预处理算法（构造delt函数)
        *
        * - 遍历P，q从0到m (因为q=0时，P_0=空字符串):
        *   - 对每个字符a属于有限字母集合a，寻找Pk是 (Pq a) 后缀的最大的k，则 delt(q,a)=k
        * - 返回 delt
        *
        * #### 匹配算法
        * - 遍历T，i从1到n:
        *   - 计算 q=delt(q,T[i])。如果 q==m，则偏移 i-m是有效偏移点，将 i-m 加入结果std::vector中
        *
        * >这里要求n>=0，m>=0(模式序列可以为空字符串)；否则抛出异常
        * >
        * >这里要文本序列T和模式序列P的元素类型相等，否则编译失败
        *
        *
        * ### 算法性能
        *
        * 有限自动机字符串匹配算法的预处理时间为O(m^3 |M|)，其中|M| 为有限字母集合的大小，匹配时间为O(n)
        *
        */
       template<typename IteratorT,typename IteratorP,typename IteratorM>
       std::vector<int> finite_automaton_match(const IteratorT iterT_begin,const IteratorT iterT_end,
             const IteratorP iterP_begin,const IteratorP iterP_end,
             const IteratorM iterM_begin,const IteratorM iterM_end)
       {
            typedef typename std::iterator_traits<IteratorT>::value_type T1;
            typedef typename std::iterator_traits<IteratorP>::value_type T2;
            typedef typename std::iterator_traits<IteratorM>::value_type T3;

            static_assert(std::is_same<T1, T2>::value,"finite_automaton_match error:sequence T and P must contain same type value!");
            static_assert(std::is_same<T1, T3>::value,"finite_automaton_match error:sequence T and M must contain same type value!");

            auto lenT=std::distance(iterT_begin,iterT_end);
            auto lenP=std::distance(iterP_begin,iterP_end);
            auto lenM=std::distance(iterM_begin,iterM_end);
            if(lenT<0)
                throw std::invalid_argument("finite_automaton_match error:iterT_begin must <= iterT_end");
            if(lenP<=0)
                throw std::invalid_argument("finite_automaton_match error:iterP_begin must < iterP_end");
            if(lenM<=0)
                throw std::invalid_argument("finite_automaton_match error:iterM_begin must < iterM_end");

            std::vector<int> result;
            if(lenT<lenP) //模式串P较长，直接返回
                return result;
            std::vector<std::vector<int>> delta;

            //**********  预处理  **************
            get_delta(iterP_begin,iterP_end,iterM_begin,iterM_end,delta);

            //*********** 匹配 ***************
            int q=0;
            for(int i=0;i<lenT;i++)
            {
                auto  T_i_index=index_of_M(iterM_begin,iterM_end,*(iterT_begin+i));
                q=delta[q][T_i_index];
                if(q==lenP)
                {
                    result.push_back(i-lenP+1); //[0,1,...i] ，其右侧长度为lenP的区间为[i-lenP+1,i-lenP+2,...i]
                }
            }
            return result;
       }
    }
}
#endif // AUTOMATONMATCH


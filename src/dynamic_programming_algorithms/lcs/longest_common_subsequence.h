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
#ifndef LONGESTCOMMONSUBSEQUENCE
#define LONGESTCOMMONSUBSEQUENCE
#include <type_traits>
#include<vector>
#include<iostream>
namespace  IntroductionToAlgorithm {
    namespace DynamicProgrammingAlgorithm
    {

    //! make_LCS 最长公共子序列的子算法：已知标记矩阵，求最长公共子序列
    /*!
     * \param begin : 第一个序列的起始迭代器
     * \param end: 第一个序列的终止迭代器
     * \param flag_matrix: 标记矩阵
     * \param seq1_index: 第一个子序列为X[0..seq1_index1]（从0计数）
     * \param seq2_index: 第二个子序列为Y[0..seq1_index2]（从0计数）
     * \param out_begin: 存放最长公共子序列结果的起始迭代器（注意必须是引用类型） （要求输出容器足够大可以存放结果）
     * \return 最长公共子序列的长度
     *
     * - 最长公共子序列算法思想，令 X=< x1,x2,...xm > Y=<y1,y2,...yn> 为两个序列， Z=<z1,z2,...zk>为X和Y的某一个最长公共子序列：
     *      - 如果 xm=yn，则zk=xm=yn,且Z(k-1)是X(m-1)和Y(n-1)的一个最长公共子序列：
     *      - 如果 xm != yn, 则如果 zk!=xm,意味着 Z是 X(m-1) 和 Y的一个最长公共子序列
     *      - 如果 xm != yn, 则如果 zk!=yn,意味着 Z是 Xm 和 Y(n-1)的一个最长公共子序列
     *
     *  在计算最长公共子序列过程中，顺便计算了标记矩阵。定义c[i,j]为Xi和Yj的最长公共子序列长度，则
     *
     * - c[i,j]= 0（若 i=0或j=0)
     * - c[i,j]=c[i-1,j-1]+1  (若i,j>0,且xi=yj)
     * - c[i,j]=max(c[i,j-1],c[i-1,j])(若x,j>0 且 xi!=yj)
     *
     * 其中：flag_matrix表征的是如何从c[i-1,j-1]、c[i,j-1]、c[i-1,j]这三者之一到达c[i,j]。即flag_matrix（i,j)对应的是矩阵：
     *
     *    | c[i][j]    c[i+1][j]    |
     *    |                         |
     *    | c[i+1][j]  c[i+1][j+1]  |
     *
     *      - 如果 xi=yj，则标记flag_matrix[i-1][j-1]为 11，表示<x1...xi>与<y1...yj>的最长公共子序列也是<x1...x(i-1)>与<y1...y(j-1)>的最长公共子序。此时递归至X(i-1)和Y(j-1)
     *      - 如果 xi！=yj，且c[i-1,j]> c[i,j-1]则标记flag_matrix[i-1][j-1] 为10，表示<x1...xi>与<y1...yj>的最长公共子序列也是<x1...x(i-1)>与<y1...yj>的最长公共子序。此时递归至X(i-1)和Yj
     *      - 如果 xi！=yj，且c[i,j-1]> c[i-1,j]则标记flag_matrix[i-1][j-1] 为01，表示<x1...xi>与<y1...yj>的最长公共子序列也是<x1...x>与<y1...y(j-1)>的最长公共子序。此时递归至Xi和Y(j-1)
     *
     * 算法时间复杂度O(m+n) ，空间复杂度 O(m*n)
     */
    template<typename Iterator,typename OutIterator> std::size_t
                      make_LCS(const Iterator begin,const Iterator end,
                      const std::vector<std::vector<int>>& flag_matrix,typename std::iterator_traits<Iterator>::difference_type seq1_index,
                              typename std::iterator_traits<Iterator>::difference_type seq2_index,
                               OutIterator& out_begin)
    {
        typedef typename std::iterator_traits<Iterator>::value_type T;
        typedef typename std::iterator_traits<OutIterator>::value_type Out_T;
        static_assert(std::is_same<T, Out_T>::value,"输入序列与输出序列必须包含相同类型的元素");
        std::size_t result=0;
        if(seq1_index<0||seq2_index<0)
            return result;
        if(flag_matrix[seq1_index][seq2_index]==11)  //两个子序列尾部相同
        {
            result+=(make_LCS(begin,end,flag_matrix,seq1_index-1,seq2_index-1,out_begin)+1);
            *out_begin=*(begin+seq1_index); //由于是从尾部向前打印，这里要递归调用之后输出
            out_begin++; //这里修改了out_begin,从而在不同迭代次数下，其值会发生改变
            return result;
        }else if(flag_matrix[seq1_index][seq2_index]==10)//表示c[i-1,j]较大，此时X[0...i]与Y[0...j]最长公共子序列也是X[0...i-1]与Y[0...j]最长公共子序列
        {
            result+=make_LCS(begin,end,flag_matrix,seq1_index-1,seq2_index,out_begin);
            return result;
        }else       //表示c[i,j-1]较大，此时X[0...i]与Y[0...j]最长公共子序列也是X[0...i]与Y[0...j-1]最长公共子序列
        {
            result+= make_LCS(begin,end,flag_matrix,seq1_index,seq2_index-1,out_begin);
            return result;
        }
    }

    //! longest_common_subsequence 算法导论第15章9.4 最长公共子序列
    /*!
     * \param first_begin : 第一个序列的起始迭代器
     * \param first_end: 第一个序列的终止迭代器
     * \param second_begin : 第二个序列的起始迭代器
     * \param second_end: 第二个序列的终止迭代器
     * \param out_begin: 结果迭代器的起始位置（要求输出容器足够大可以存放结果）
     * \return 最长公共子序列的长度
     *
     * - 最长公共子序列算法思想，令 X=< x1,x2,...xm > Y=<y1,y2,...yn> 为两个序列， Z=<z1,z2,...zk>为X和Y的某一个最长公共子序列：
     *      - 如果 xm=yn，则zk=xm=yn,且Z(k-1)是X(m-1)和Y(n-1)的一个最长公共子序列：
     *      - 如果 xm != yn, 则如果 zk!=xm,意味着 Z是 X(m-1) 和 Y的一个最长公共子序列
     *      - 如果 xm != yn, 则如果 zk!=yn,意味着 Z是 Xm 和 Y(n-1)的一个最长公共子序列
     *
     *  因此如果 xm=yn,我们递归求解 X(m-1)和Y(n-1)的最长公共子序列；如果xm != yn，我们求解X(m-1) 和 Y的一个最长公共子序列,以及Xm 和 Y(n-1)的一个最长公共子序列，
     * 这两个之中的最大值即为X和Y的最长公共子序列
     *
     * 定义c[i,j]为Xi和Yj的最长公共子序列长度，则 c[i,j]= 0（若 i=0或j=0) ;c[i-1,j-1]+1  (若i,j>0,且xi=yj)；max(c[i,j-1],c[i-1,j])(若x,j>0 且 xi!=yj)，
     * 通过动态规划方法从底向上计算
     *
     * - 时间复杂度：O(m*n)，空间复杂度O(m*n)
     */
        template<typename Iterator1,typename Iterator2,typename OutIterator>  std::size_t
                longest_common_subsequence(const Iterator1 first_begin,const Iterator1 first_end,
                                           const Iterator2 second_begin,const Iterator2 second_end,
                                           OutIterator out_begin)
        {
            typedef typename std::iterator_traits<Iterator1>::value_type T1;
            typedef typename std::iterator_traits<Iterator2>::value_type T2;
            typedef typename std::iterator_traits<OutIterator>::value_type T3;
            //typedef typename std::iterator_traits<Iterator1>::difference_type Distance;
            static_assert(std::is_same<T1, T2>::value,"两个序列必须包含相同类型的元素");
            static_assert(std::is_same<T1, T3>::value,"输入序列与输出序列必须包含相同类型的元素");
            auto len1=std::distance(first_begin,first_end);
            auto len2=std::distance(second_begin,second_end);
            if(len1<=0||len2<=0)
                return 0;
            auto rows=len1;
            auto columns=len2;
            //*******************  创建数据矩阵  *******************
            std::vector<std::vector<int>> c_matrix(rows+1); //c_matrix[i,j]为Xi和Yj的最长公共子序列长度，因为i,j可能为0，所以矩阵外扩一个单位
            for(int i=0;i<rows+1;i++)  // 矩阵大小 (rows+1)*(colums+1)
            {
                /*
                 * 这里大小为什么为 (m+1)*(n+1)：因为X序列的子序列可以为 空、<x1>、...<x1...xm>一共（m+1）个；Y序列的子序列有 (n+1)个
                 */
                c_matrix.at(i)=std::vector<int>(columns+1);
            }
            std::vector<std::vector<int>> flag_matrix(rows); //用于构造最长公共子序列，它存放的是从c[i-1][j-1]到c[i,j]的路径
            for(int i=0;i<rows;i++)// 矩阵大小 (rows)*(colums)
            {
                /*
                 * 这这里大小为什么为m*n:因为它表征的是如何从c[i-1,j-1]、c[i,j-1]、c[i-1,j]这三者之一到达c[i,j]。即flag_matrix（i,j)对应的是矩阵：
                 *    | c[i][j]    c[i+1][j]    |
                 *    |                         |
                 *    | c[i+1][j]  c[i+1][j+1]  |
                 */
                flag_matrix.at(i)=std::vector<int>(columns);
            }
            //**************　　初始化矩阵　****************************
            for(int i=0;i<rows+1;i++)  // c[i,j]= 0（若 i=0或j=0)
                   c_matrix[i][0]=0;
            for(int i=0;i<columns+1;i++)// c[i,j]= 0（若 i=0或j=0)
                   c_matrix[0][i]=0;
            //********************* 开始计算 ********************
            for(int r=1;r<rows+1;r++) //row=0,column=0已由初始化条件给出，这里从r=1,c=1开始
                for(int c=1;c<columns+1;c++)
                {
                       if( *(first_begin+r-1) ==*(second_begin+c-1))//c[i,j]=c[i-1,j-1]+1 (若i,j>0,且xi=yj)
                       {
                                c_matrix[r][c]=c_matrix[r-1][c-1]+1;
                                flag_matrix[r-1][c-1]=11;  //c[i,j]=c[i-1,j-1]+1，标记flag_matrix[i-1][j-1] 为11

                       }else if(c_matrix[r-1][c]>=c_matrix[r][c-1])//c[i,j]=max(c[i,j-1],c[i-1,j]) (若i,j>0,且xi=yj)
                       {
                                c_matrix[r][c]=c_matrix[r-1][c];
                                flag_matrix[r-1][c-1]=10; // 标记flag_matrix[i-1][j-1] 为10，表示c[i-1,j]较大
                       }else                   //c[i,j]=max(c[i,j-1],c[i-1,j]) (若i,j>0,且xi=yj)
                       {
                                c_matrix[r][c]=c_matrix[r][c-1];
                                flag_matrix[r-1][c-1]=1;// 标记flag_matrix[i-1][j-1] 为01，表示c[i,j-1]较大
                        }
                 }
            // 打印矩阵
//            std::cout<<"j: ";
//            for(int c=0;c<columns+1;c++)
//                std::cout<<"\tc: "<<c;
//            std::cout<<"\n";
//            for(int r=0;r<rows+1;r++)
//            {
//                std::cout<<"i:"<<r;
//                for(int c=0;c<columns+1;c++)
//                    std::cout<<"\t "<<c_matrix[r][c];
//                std::cout<<"\n";
//           }
//            std::cout<<"\n\n";
//            for(int c=0;c<columns;c++)
//                std::cout<<"j:\tc: "<<c;
//            std::cout<<"\n";
//            for(int r=0;r<rows;r++)
//            {
//                std::cout<<"i:"<<r;
//                for(int c=0;c<columns;c++)
//                    std::cout<<"\t "<<flag_matrix[r][c];
//                std::cout<<"\n";
//           }

            //*************  构造最长公共子序列  ****************
            return make_LCS(first_begin,first_end,flag_matrix,len1-1,len2-1,out_begin); //从尾部开始向前打印
        }

    }
}
#endif // LONGESTCOMMONSUBSEQUENCE


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
#ifndef MATRIX_SHORTEST_PATH
#define MATRIX_SHORTEST_PATH
#include<memory>
#include<array>
#include"src/header.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!extend_path：扩展一条边，算法导论25章25.1节
        /*!
        * \param L:初始L矩阵
        * \param W: 图的权重矩阵
        * \return: 扩展之后的L矩阵
        *
        * 该函数作为 matrix_shortest_path 的辅助函数
        * >这里要求 MatrixType是一个n*n的矩阵。如果MatrixType不是一个n*n的矩阵，则编译失败
        *
        * 算法步骤如下：
        *
        * - 外层循环 i 从 0...N-1(N次)
        *   - 内层循环 j 从 0...N-1(N次)
        *       - 将newL[i][j]设为正无穷，对所有的k,k 从 0...N-1(N次)，选取 L[i][k]+W[k][j]的最小值赋值给newL[i][j]
        * - 最终返回 newL
        *
        * 性能：时间复杂度 O(n^3)
        *
        */
        template<typename MatrixType> MatrixType extend_path(const MatrixType&L,const MatrixType&W)
        {
            typedef typename MatrixType::value_type::value_type ValueType;

            static_assert(std::tuple_size<MatrixType>::value==std::tuple_size<typename MatrixType::value_type>::value,"extend_path error:matrix must be N*N size!"); //必须是方阵
            std::size_t row_num=std::tuple_size<MatrixType>::value;
            std::size_t col_num=std::tuple_size<typename MatrixType::value_type>::value;

            MatrixType newL;
            for(int i=0;i<row_num;i++)
                for(int j=0;j<col_num;j++)
                {
                    newL[i][j]=unlimit<ValueType>();
                    for(int k=0;k<row_num;k++)
                    {
                        newL[i][j]=std::min(newL[i][j],L[i][k]+W[k][j]);
                    }
                }
            return newL;
        }



        //!matrix_shortest_path：返回所有节点对的最短路径的矩阵乘法算法。算法导论25章25.1节
        /*!
        *
        * \param graph:指定的有向图。它必须非空，否则抛出异常
        * \return: 一个n*n的矩阵(d_i_j)，其中 d_i_j 代表的是结点i到j的一条最短路径的权重
        *
        * ## 所有结点对的最短路径
        *
        * 给定一个带权重的有向图G=(V,E)，其权重函数为w:E->R，该函数将边映射到实值权重上。我们希望找到对于所有的结点对u,v属于V，找出一条从结点u
        * 到结点v的最短路径，以及这条路径的权重。
        *
        * 与单源最短路径不同中使用邻接表来表示图不同，本章的多数算法使用邻接矩阵来表示图。该矩阵代表的是一个有n个结点的有向图G=(V,E)的边的权重W=(w_i_j)，
        * 其中 w_i_j =:
        *
        *   - 0:若i=j
        *   - 有向边(i,j)的权重，若i!=j且(i,j)属于E
        *   - 正无穷，若 i!=j且(i,j)不属于E
        *
        * 我们允许存在负权重的边，目前仍然假定图中不存在权重为负值的环路。
        *
        * 本章讨论的所有结点对最短路径的算法的输出也是一个n*n的矩阵D=(d_i_j)，其中 d_i_j 代表的是结点i到j的一条最短路径的权重。
        *
        * 有时候为了解决所有结点对最短路径问题，我们不仅要计算出最短路径权重，还需要计算出前驱结点矩阵 II=(pai_i_j)，其中 pai_i_j在i=j或者从i到j
        * 不存在路径时为NIL，在其他情况下给出的是从结点i到结点j的某条最短路径上结点j的前驱结点。由矩阵II的第i行所诱导的子图应当是一棵根节点为i
        * 的最短路径树。
        *
        *
        * ## matrix_shortest_path 算法
        *
        * ### 算法原理
        *
        * matrix_shortest_path采用动态规划算法求解。考虑从结点i到j的一条最短路径p，假定p最多包含m条边，假定没有权重为负值的环路，且m为有限值。
        * 如果 i=j，则p的权重为0且不包含任何边；如果i和j不同，则将路径p分解为 i-->k(经过路径p')-->j，其中路径p'最多包含m-1条边。
        *
        * 定义 l_i_j<m>为从结点i到j的最多包含m条边的任意路径中的最小权重，则有：l_i_j<m>=
        *
        * - 0：如果i=j
        * - 正无穷:如果 i!=j
        *
        * 对于m>=1，我们有： l_i_j<m>=min(l_i_j<m-1>，min_(1<=k<=n){l_i_k<m-1>+w_k_j})=min_(1<=k<=n){l_i_k<m-1>+w_k_j}。
        * 如果图G不包含负值的环路，则对于每一对结点i,j，如果他们delt(i,j)<正无穷，则从i到j之间存在一条最短路径。由于该路径是简单路径，
        * 则包含的边最多为n-1条。因此delt(i,j)=l_i_j<n-1>=l_i_j<n>=...
        *
        * matrix_shortest_path算法根据输入矩阵W=(w_i_j)，计算出矩阵序列 L<1>，L<2>,...L<n-1>。最后的矩阵L<n-1>包含的是最短路径的权重。
        * 其中L<1>=W。算法的核心是extend_path函数，它将最近计算出的路径扩展了一条边
        *
        *
        * ### 算法步骤
        *
        * - 初始化：从图中获取权重矩阵 W
        * - 执行循环扩展L，其中 L<0>=W, L<k>=extend_path(L<k-1>,W)
        * - 最终返回 L<N-1>
        *
        * ### 算法性能
        *
        * 时间复杂度O(V^4)
        */
        template<typename GraphType> std::array<std::array<typename GraphType::EWeightType ,GraphType::NUM>,GraphType::NUM>
            matrix_shortest_path(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::EWeightType EWeightType;
            typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;

            if(!graph)
                throw std::invalid_argument("matrix_shortest_path error: graph must not be nullptr!");
            MatrixType W;
            //**************  从图中创建权重矩阵  ***************
            //****  这里不能直接从图的矩阵描述中提取，因为这里要求 w(i,i)=0，而图的矩阵描述中，结点可能有指向自己的边
            for(int i=0;i<GraphType::NUM;i++)
                for(int j=0;j<GraphType::NUM;j++)
                {
                    if(i==j) W[i][j]=0;
                    else
                    {
                        if(!graph->has_edge(i,j))
                            W[i][j]=unlimit<EWeightType>();
                        else
                            W[i][j]=graph->weight(i,j);
                    }
                 }
            //*********  计算 L <n-1> ***********
            MatrixType L=W; //L<0>
            for(int i=0;i<GraphType::NUM-2;i++) //扩展 N-2次
            {
                L=extend_path(L,W);
            }
            return L;
        }

        //!matrix_shortest_path：返回所有节点对的最短路径的矩阵乘法复平方算法。算法导论25章25.1节
        /*!
        *
        * \param graph:指定的有向图。它必须非空，否则抛出异常
        * \return: 一个n*n的矩阵(d_i_j)，其中 d_i_j 代表的是结点i到j的一条最短路径的权重
        *
        * ## 所有结点对的最短路径
        *
        * 给定一个带权重的有向图G=(V,E)，其权重函数为w:E->R，该函数将边映射到实值权重上。我们希望找到对于所有的结点对u,v属于V，找出一条从结点u
        * 到结点v的最短路径，以及这条路径的权重。
        *
        * 与单源最短路径不同中使用邻接表来表示图不同，本章的多数算法使用邻接矩阵来表示图。该矩阵代表的是一个有n个结点的有向图G=(V,E)的边的权重W=(w_i_j)，
        * 其中 w_i_j =:
        *
        *   - 0:若i=j
        *   - 有向边(i,j)的权重，若i!=j且(i,j)属于E
        *   - 正无穷，若 i!=j且(i,j)不属于E
        *
        * 我们允许存在负权重的边，目前仍然假定图中不存在权重为负值的环路。
        *
        * 本章讨论的所有结点对最短路径的算法的输出也是一个n*n的矩阵D=(d_i_j)，其中 d_i_j 代表的是结点i到j的一条最短路径的权重。
        *
        * 有时候为了解决所有结点对最短路径问题，我们不仅要计算出最短路径权重，还需要计算出前驱结点矩阵 II=(pai_i_j)，其中 pai_i_j在i=j或者从i到j
        * 不存在路径时为NIL，在其他情况下给出的是从结点i到结点j的某条最短路径上结点j的前驱结点。由矩阵II的第i行所诱导的子图应当是一棵根节点为i
        * 的最短路径树。
        *
        * ##  matrix_shortest_path_fast 算法
        *
        * ### 算法原理
        *
        * matrix_shortest_path_fast改进了算法matrix_shortest_path。因为我们的目标并不是计算所有的L<m>矩阵，我们感兴趣的仅仅是矩阵L<n-1>。
        * 由matrix_shortest_path过程定义的矩阵乘法是相关的，因此可以仅用t个矩阵乘积来计算矩阵L<n-1>，其中 n为大于lg(n-1)的最小整数。
        * 因此可以用复平方技术来计算上述矩阵序列：
        *
        * - L<1>=W
        * - L<2>=W^2=W.W
        * - L<4>=W^4=W^2.W^2
        * - L<8>=W^8=W^4.W^4
        * ....
        *
        *
        * ### 算法步骤
        *
        * - 初始化：从图中获取权重矩阵 W
        * - 执行循环扩展L，其中 L<0>=W, L<2*k>=extend_path(L<k>,L<k>)
        * - 最终返回 L<log(N-1)的上界整数>
        *
        * ### 算法性能
        * 时间复杂度O(V^3lgV)
        */
        template<typename GraphType> std::array<std::array<typename GraphType::EWeightType ,GraphType::NUM>,GraphType::NUM>
            matrix_shortest_path_fast(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::EWeightType EWeightType;
            typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;

            if(!graph)
                throw std::invalid_argument("matrix_shortest_path_fast error: graph must not be nullptr!");

            MatrixType W;
            //**************  从图中创建权重矩阵  ***************
            //****  这里不能直接从图的矩阵描述中提取，因为这里要求 w(i,i)=0，而图的矩阵描述中，结点可能有指向自己的边
            for(int i=0;i<GraphType::NUM;i++)
                for(int j=0;j<GraphType::NUM;j++)
                {
                    if(i==j) W[i][j]=0;
                    else
                    {
                        if(!graph->has_edge(i,j))
                            W[i][j]=unlimit<EWeightType>();
                        else
                            W[i][j]=graph->weight(i,j);
                    }
                 }
            //*********  计算 L <n-1> ***********
            MatrixType L=W;
            int m=1;
            while(m<GraphType::NUM-1)
            {
                L=extend_path(L,L);
                m=m<<1;
            }
            return L;
        }

    }
}
#endif // MATRIX_SHORTEST_PATH


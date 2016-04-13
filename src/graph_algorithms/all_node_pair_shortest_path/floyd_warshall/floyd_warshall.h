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
#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL
#include<memory>
#include"src/header.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!floyd_warshall：返回所有节点对的最短路径的floyd_warshall算法。算法导论25章25.2节
        /*!
        *
        * \param graph:指定的有向图。它必须非空，否则抛出异常
        * \return: 一个n*n的矩阵(d_i_j)与n*n的矩阵(p_i_j)的std::pair，其中 d_i_j 代表的是结点i到j的一条最短路径的权重,
        *   p_i_j 为从结点i到j的一条最短路径上j的前驱结点
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
        * ## floyd_warshall 算法
        *
        * ### 算法原理
        *
        * floyd_warshall也是采用一种动态规划算法来解决问题。假定图G中的所有结点为V={1,2,3...n},考虑其中的一个子集{1,2,...k}，这里k是某个小于n的整数。
        * 图中可以存在负权重的边，但是不能存在权重为负的环路。对于任意结点对i,j属于V，考虑从结点i到结点j的所有中间结点均取自集合{1,2,...k}的路径，并且假设p为其中权重最小的路径。
        *
        * - 若结点k不是路径p的中间结点，则路径p上的所有中间结点都属于集合{1,2,3,...k-1}。则结点i到j的中间结点取自集合{1,2,...k-1}
        * 的一条最短路径也是从结点i到j的中间结点取自{1,2...k)的一条最短路径
        * - 若结点k是路径p上的中间结点，则路径p分解为 i-->k(经过p1)-->j(经过p2)，则路径p1是结点i到k的中间结点取自集合{1,2...k-1}
        * 的一条最短路径。路径p2是结点k到j的中间结点取自集合{1,2,...k-1}的一条最短路径。
        *
        * 根据以上观测，设d_i_j<k>为从结点i到结点j的所有中间结点全部取自集合{1,2...k}的一条最短路径的权重。当k=0时，从结点i到j
        * 的一条不包含编号大于0的中间结点的路径将没有任何中间结点。这样的路径最多只有一条边，因此d_i_j<0>=w_i_j。因此d_i_j<k>为：
        *
        * - w_i_j：当k=0
        * - min(d_i_j<k-1>,d_i_k<k-1>+d_k_j<k-1>：当k>0
        *
        * 对任何路径来说，所有中间结点都属于集合{1,2,...n}，则矩阵D<n>=(d_i_j<n>)
        *
        * 我们可以在计算矩阵D<k>的同时计算出前驱矩阵II，即计算一个矩阵序列 II<0>,II<1>...II<k>。这里定义II<k>=(pai_i_j<k>)，
        * pai_i_j<k>为从结点i到j的一条所有中间结点都取自集合{1,2,...k}的最短路径上j的前驱结点。
        *
        * 当k=0时，从i到j的一条最短路径没有中间结点，因此 pai_i_j<0>=:
        *
        * - null:若i=j或者w_i_j=正无穷
        * - i ：若i!=j且w_i_j!=正无穷
        *
        * 对于 k>=1，若结点k不是路径p的中间结点，则路径p上的所有中间结点都属于集合{1,2,3,...k-1}，则 pai_i_j<k>=pai_i_j<k-1>;
        * 若结点k是路径p的中间结点,考虑路径 i-->k-->j，这里 k!=j，则pai_i_j<k>=pai_k_j<k-1>。因此当k>=1时，pai_i_j<k>=:
        *
        * - pai_i_j<k-1>：当d_i_j<k-1> <= d_i_k<k-1>+dk_j<k-1>
        * - pai_k_j<k-1>: 当 d_i_j<k-1> > d_i_k<k-1>+dk_j<k-1>
        *
        * ### 算法步骤
        *
        * - 初始化：从图中获取结果矩阵D，以及父矩阵P
        * - 外层循环 k 从 0..N-1(N次)
        *   - 新建 D<k>,P<k>，同时执行内层循环 i 从 0..N-1(N次)
        *   - 执行最内层循环 j 从 0..N-1(N次)
        *       - 根据递推公式对d_i_j<k>和p_i_j<k>赋值(此时D等于D<k-1>，P等于P<k-1>
        *   - 将D<k>赋值给D,P<k>赋值给P
        * - 返回 std::make_pair(D,P)
        *
        * ### 算法性能
        *
        * 时间复杂度 O(V^3)
        */
        template<typename GraphType>
        std::pair<
        std::array<std::array<typename GraphType::EWeightType ,GraphType::NUM>,GraphType::NUM>,
        std::array<std::array<typename GraphType::EWeightType ,GraphType::NUM>,GraphType::NUM>
        >
        floyd_warshall(std::shared_ptr<GraphType> graph)
        {
            typedef typename GraphType::EWeightType EWeightType;
            typedef std::array<std::array<EWeightType,GraphType::NUM>,GraphType::NUM> MatrixType;

            if(!graph)
                throw std::invalid_argument("floyd_warshall error: graph must not be nullptr!");
            //**************  初始化 D 和 P ************
            //****  这里不能直接从图的矩阵描述中提取，因为这里要求 w(i,i)=0，而图的矩阵描述中，结点可能有指向自己的边
            MatrixType D,P;
            for(int i=0;i<GraphType::NUM;i++)
                for(int j=0;j<GraphType::NUM;j++)
                {
                    if(i==j)
                    {
                        D[i][j]=0;
                        P[i][j]=-1;
                    }
                    else
                    {
                        if(!graph->has_edge(i,j))
                        {
                            D[i][j]=unlimit<EWeightType>();
                            P[i][j]=-1;
                        }
                        else
                        {
                            D[i][j]=graph->weight(i,j);
                            P[i][j]=i;
                        }
                    }
                 }
            //**************  计算矩阵D和前驱矩阵P ******************
            for(int k=0;k<GraphType::NUM;k++)
            {
                MatrixType newD; //  D<k>
                MatrixType newP; //  P<k>
                for(int i=0;i<GraphType::NUM;i++)
                {
                    for(int j=0;j<GraphType::NUM;j++)
                    {
                        // D中存放的是D<k-1>,P中存放的是P<k-1>
                        EWeightType sum=0;
                        if(D[i][k]==unlimit<EWeightType>()||D[k][j]==unlimit<EWeightType>()||D[i][k]+D[k][j]>=unlimit<EWeightType>())
                            sum=unlimit<EWeightType>();
                        else
                            sum=D[i][k]+D[k][j];

                        if(D[i][j]<=sum) // d_i_j<k-1> <= d_i_k<k-1>+d_k_j<k-1>
                        {
                           newD[i][j]= D[i][j]; //则 d_i_j<k> = d_i_j<k-1>
                           newP[i][j]= P[i][j]; //则 p_i_j<k> = p_i_j<k-1>
                        }
                        else  // d_i_j<k-1> > d_i_k<k-1>+d_k_j<k-1>
                        {
                            newD[i][j]= sum; //则 d_i_j<k> = d_i_k<k-1>+d_k_j<k-1>
                            newP[i][j]= P[k][j];         //则 p_i_j<k> = p_k_j<k-1>
                        }
                     }
                }
                D=newD;
                P=newP;
            }
            return std::make_pair(D,P);
        }
    }
}
#endif // FLOYD_WARSHALL


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
//! Namespace of IntrodunctionToAlgorithm
/*!
*
* 该命名空间内包含所有算法导论中的算法
*/
#include<string>
#include<iostream>

namespace IntrodunctionToAlgorithm
{
    //! Namespace of  SortAlgorithm
    /*!
    *
    * 该命名空间内包含所有排序算法
    */
    namespace SortAlgorithm
    {

    }
    //! Namespace of  SelectAlgorithm
    /*!
    *
    * 该命名空间内包含所有顺序统计量算法
    */
    namespace SelectAlgorithm {

    }
    //! Namespace of  DynamicProgrammingAlgorithm
    /*!
    *
    * 该命名空间内包含所有动态规划算法.动态规划的原理：
    *
    * - 最优子结构：即原问题的解依赖于子问题的解。
    * - 子问题无关：即原问题的解锁依赖的那些子问题是无关的，解耦的。
    * - 重叠子问题：即子问题的数量是有限的，即子问题的空间必须足够“小”。原问题的递归算法会反复求解相同的子问题，而不是一直生成新的字问题。
    * >对比分治法求解的情况：分治法通常在递归的每一步都生成一个全新的子问题。
    *
    * 动态规划算法通常利用重叠子问题的性质，对每一个子问题求解一次，将解存入一个表中，每当再次需要求解这个子问题时，直接查表。
    */
    namespace DynamicProgrammingAlgorithm {

    }

    //! Namespace of  TreeAlgorithm
    /*!
    *
    * 该命名空间内包含所有树算法
    */
    namespace TreeAlgorithm {

    }
}

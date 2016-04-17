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
#ifndef HEADERH
#define HEADERH
//! Namespace of IntrodunctionToAlgorithm
/*!
*
* 该命名空间内包含所有算法导论中的算法
*/
#include<algorithm>
#include<memory>
#include<vector>
#include<ostream>
namespace IntroductionToAlgorithm
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
    //! Namespace of  QueueAlgorithm
    /*!
    *
    * 该命名空间内包含所有队列算法
    */
    namespace QueueAlgorithm {


    }
    //! Namespace of  SetAlgorithm
    /*!
    *
    * 该命名空间内包含所有`Set`算法
    */
    namespace SetAlgorithm {


    }
    //! Namespace of  GraphAlgorithm
    /*!
    *
    * 该命名空间内包含所有图算法
    */
    namespace GraphAlgorithm
    {
        //!unlimit：返回正无穷的函数
        /*!
        *\return : 正无穷大的数
        *
        * 将本函数的返回值定义为正无穷。在算法导论图算法中，经常用到正无穷。通常对正无穷的操作是:
        *
        * - 将边的权重或者节点的`key`设为正无穷
        * - 对正无穷加、减一个有限的数，结果还是正无穷
        *
        * 这里将`std::numeric_limits<T>::max()/2`设为正无穷，考虑到正无穷加上一个较大的数必须保证不能溢出
        *
        */
        template<typename T> T unlimit()
        {
            return std::numeric_limits<T>::max()/2;
        }
        //!is_unlimit：判断是否正无穷
        /*!
        * \param t: 待判断的数
        * \return : 如果该数是正无穷大，则返回`true`，否则返回`false`
        *
        * 将本函数判断一个数是否正无穷；若是则返回true;若不是则返回false
        *
        * 这里将大于等于`std::numeric_limits<T>::max()/3`的数判断结果为正无穷
        * >因为考虑到正无穷减去一个数必须保证结果也是正无穷
        *
        */
        template<typename T> bool is_unlimit(T t)
        {
            return t>=std::numeric_limits<T>::max()/3;
        }

        //!get_path：获取两个顶点之间的路径
        /*!
        * \param v_from: 起始顶点
        * \param v_to: 终止顶点
        * \return : 两个顶点之间的路径包含的顶点的`id`序列
        *
        * 获取从`v_from`到`v_to`之间的一条路径，该路径用途经的顶点的`id`来表示，是一个`std::vector<typename VertexType::VIDType>`类型。
        *
        * 要求`v_from`与`v_to`非空，否则抛出异常
        */
        template<typename VertexType> std::vector<typename VertexType::VIDType> get_path(const std::shared_ptr<VertexType> v_from,const std::shared_ptr<VertexType> v_to)
        {
            if(!v_from||!v_to)
                throw std::invalid_argument("get_path error: vertex must not be null!");
            std::vector<typename VertexType::VIDType> result;
            if(v_from->id==v_to->id)
            {
                result.push_back(v_from->id);
            }else if(!v_to->parent)
            {
                return std::vector<typename VertexType::VIDType>();
            }else
            {
                std::vector<typename VertexType::VIDType> temp=get_path<VertexType>(v_from,v_to->parent);
                for(const auto& val:temp)
                    result.push_back(val);
                result.push_back(v_to->id);
            }
            return result;
        }

        //!matrix_string：获取矩阵的字符串描述
        /*!
        * \param matrix: 矩阵
        * \return : 矩阵的字符串描述
        *
        * 获取矩阵`matrix`的字符串描述。
        */
        template<typename MatrixType> std::string matrix_string(const MatrixType&matrix)
        {
            std::size_t row_num=std::tuple_size<MatrixType>::value;  //行数
            std::size_t col_num=std::tuple_size<typename MatrixType::value_type>::value;//列数
            std::ostringstream os;

            for(int i=0;i<row_num;i++)
            {
                os<<"\nrow["<<i<<"]:\t";
                for(int j=0;j<col_num;j++)
                    os<<matrix[i][j]<<"\t";
            }
            return os.str();
        }

    }
    //! Namespace of  StringMatchingAlgorithm
    /*!
    *
    * 该命名空间内包含所有字符串匹配算法
    */
    namespace StringMatchingAlgorithm {

   }
}
#endif // HEADERH

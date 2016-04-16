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
#ifndef DFSVERTEX
#define DFSVERTEX
#include"vertex.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!DFS_Vertex：用于深度优先搜索的顶点类型，算法导论22章22.3节
        /*!
        * 深度优先搜索的顶点类型继承自`Vertex`模板类型，它比`Vertex`多了四个数据成员：
        *
        * - `color`：顶点的颜色。顶点可以有三种颜色，分别为`DFS_Vertex::COLOR::BLACK`、`DFS_Vertex::COLOR::WHITE`、`DFS_Vertex::COLOR::GRAY`
        * - `parent`: 指向父顶点的强引用
        * - `discover_time`：顶点的发现时间
        * - `finish_time`：顶点的完成时间
        *
        * 广度优先搜索的顶点类型还支持以下两个操作：
        *
        * - `set_disovered(discover_t)`：发现本顶点
        * - `set_finished(finish_t)`：本顶点搜索完毕
        *
        */
        template<typename KType> struct DFS_Vertex:public Vertex<KType>
        {

             typedef int VIDType;      /*!< 顶点编号的数据类型*/
             typedef KType KeyType;  /*!< 顶点存储数据的类型*/
             enum class COLOR{WHITE,GRAY,BLACK}; /*!< 顶点颜色的枚举类型*/


             //!默认构造函数，将`color`设为白色，发现时间与完成时间默认为-1
             DFS_Vertex():color(COLOR::WHITE),discover_time(-1),finish_time(-1){}
             //!显式构造函数，指定`key`
             /*!
             * \param  k:顶点存放的数据
             *
             * 顶点的颜色默认设为白色，发现时间与完成时间默认为-1
             */
             explicit DFS_Vertex(const KeyType&k):
                 color(COLOR::WHITE),discover_time(-1),finish_time(-1),Vertex<KeyType>(k)
             {}
             //!显式构造函数，指定`key`和编号
             /*!
             * \param  k:顶点存放的数据
             * \param  d:顶点的编号
             *
             * 顶点的颜色默认设为白色，发现时间与完成时间默认为-1
             */
             DFS_Vertex(const KeyType&k,VIDType d):
                 color(COLOR::WHITE),discover_time(-1),finish_time(-1),Vertex<KeyType>(k,d)
             {}
             //!set_disovered：发现本顶点
             /*!
             *
             * \param discover_t:发现时间
             *
             * 发现本顶点要执行两个操作：
             *
             * - 将本顶点的颜色设为灰色
             * - 将本顶点的`discover_time`设为`discover_t`
             */
             void set_disovered(int discover_t)
             {
                 discover_time=discover_t;
                 color=COLOR::GRAY;
             }
             //!set_finished：设本顶点为搜索完毕状态
             /*!
             *
             * \param finish_t:完成时间
             *
             * 设本顶点为搜索完毕状态要执行两个操作：
             *
             * - 将本顶点的颜色设为黑色
             * - 将本顶点的`finish_time`设为`finish_t`
             */
             void set_finished(int finish_t)
             {
                 color=COLOR::BLACK;
                 finish_time=finish_t;
             }
             //!to_string：返回顶点的字符串描述
             /*!
             * \return :顶点的字符串描述
             *
             * 在`Vertex`基类的基础上输出`color`以及`parent`、`discover_time`以及`finish_time`信息。
             */
             std::string to_string()
             {
                std::ostringstream os;
                os<<Vertex<KeyType>::to_string()<<"\t color:";
                switch (color) {
                case COLOR::WHITE:
                    os<<"WHITE";
                    break;
                case COLOR::BLACK:
                    os<<"BLACK";
                    break;
                case COLOR::GRAY:
                    os<<"GRAY";
                    break;
                default:
                    throw std::invalid_argument(" to_string error:unknown color!");
                }
                os<<"\t parent-id:";
                if(parent) os<<parent->id;
                else os<<"nullptr";
                os<<"\t discover_time:"<<discover_time<<"\t finish_time:"<<finish_time;
                return os.str();
             }
             int discover_time;                      /*!< 顶点发现时间*/
             int finish_time;                        /*!< 顶点完成时间*/
             COLOR color;                            /*!< 顶点颜色*/
             std::shared_ptr<DFS_Vertex> parent;     /*!< 顶点父顶点的强引用*/
        };

    }
}
#endif // DFSVERTEX


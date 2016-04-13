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
#ifndef BFSVERTEX
#define BFSVERTEX

#include"vertex.h"
#include"src/header.h"
namespace IntroductionToAlgorithm
{
    namespace GraphAlgorithm
    {

        //!BFS_Vertex：用于广度优先搜索的顶点类型，算法导论22章22.2节
        /*!
        * 广度优先搜索的顶点类型继承自`Vertex`模板类型，它比`Vertex`多了两个数据成员：
        *
        * - `color`：顶点的颜色。顶点可以有三种颜色，分别为`BFS_Vertex::COLOR::BLACK`、`BFS_Vertex::COLOR::WHITE`、`BFS_Vertex::COLOR::GRAY`
        * - `parent`: 指向父顶点的强引用
        *
        * 广度优先搜索的顶点类型还支持以下两个操作：
        *
        * - `set_source()`：将本顶点设为源点
        * - `set_found(v_parent)`：发现本顶点
        *
        */
        template<typename KType> struct BFS_Vertex:public Vertex<KType>
        {

             typedef int VIDType;      /*!< 顶点编号的数据类型*/
             typedef KType KeyType;  /*!< 顶点存储数据的类型*/
             enum class COLOR{WHITE,GRAY,BLACK}; /*!< 顶点颜色的枚举类型*/


             //!默认构造函数，将`color`设为白色
             BFS_Vertex():color(COLOR::WHITE){}
             //!显式构造函数，指定`key`
             /*!
             * \param  k:顶点存放的数据
             *
             * 顶点的颜色默认设为白色
             */
             explicit BFS_Vertex(const KeyType&k):color(COLOR::WHITE),Vertex<KeyType>(k){}
             //!显式构造函数，指定`key`和编号
             /*!
             * \param  k:顶点存放的数据
             * \param  d:顶点的编号
             *
             * 顶点的颜色默认设为白色
             */
             BFS_Vertex(const KeyType&k,VIDType d):color(COLOR::WHITE),Vertex<KeyType>(k,d){}

             //!set_source：设本顶点为源点
             /*!
             *
             * 将本顶点设为源点要执行两个操作：
             *
             * - 将本顶点的颜色设为灰色
             * - 将本顶点的`parent`设为空
             */
             void set_source()
             {
                 color=COLOR::GRAY;
                 parent=std::shared_ptr<BFS_Vertex>();
                 this->key=0;
             }
             //!set_found：发现本顶点
             /*!
             *
             * \param v_parent:父顶点的强引用
             *
             * 发现本顶点要执行两个操作：
             *
             * - 将本顶点的颜色设为灰色
             * - 将本顶点的`parent`设为`v_parent`
             *
             * 这里要求`v_parent`非空。若`v_parent`为空则抛出异常
             */
             void set_found(std::shared_ptr<BFS_Vertex> v_parent)
             {
                 if(!v_parent)
                     throw std::invalid_argument("set_found error: v_parent must not be null!");
                 color=COLOR::GRAY;
                 parent=v_parent;
                 if(v_parent->key==unlimit<KeyType>()) this->key=v_parent->key;
                 else this->key=v_parent->key+1;

             }
             //!to_string：返回顶点的字符串描述
             /*!
             * \return :顶点的字符串描述
             *
             * 再`Vertex`基类的基础上输出`color`以及`parent`信息。
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
                return os.str();
             }

             COLOR color;                            /*!< 顶点颜色*/
             std::shared_ptr<BFS_Vertex> parent;     /*!< 顶点父顶点的强引用*/
        };
    }
}
#endif // BFSVERTEX


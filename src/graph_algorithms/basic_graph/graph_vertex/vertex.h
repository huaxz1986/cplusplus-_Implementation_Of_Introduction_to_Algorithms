#ifndef GRAPHVERTEX
#define GRAPHVERTEX
#include<memory>
#include<algorithm>
#include<sstream>
namespace IntrodunctionToAlgorithm
{
    namespace GraphAlgorithm
    {        
        //!Vertex：图的顶点，算法导论22章22.1节
        /*!
        *
        * 顶点是一个结构体的模板，模板类型为它存储的数据的类型。它主要包含三个数据：
        *
        *   - `key`:顶点存放的数据
        *   - `id`:顶点的编号（从0开始，负编号的节点为无效节点）。它是一个`const int`，一旦顶点初始化完毕就不可更改。
        *   - `parent_id`:父节点的编号。
        *
        * 默认情况下：`id`为-1,`parent_id`为-1，`key`为`T()`。
        *
        */
        template<typename KType> struct Vertex
        {
            typedef KType KeyType;    /*!< 顶点存储数据的类型*/
            typedef int VIDType;      /*!< 顶点编号的数据类型*/

            //!默认构造函数，将`key`设为`KType()`，编号设为-1，父节点编号设为-1
            Vertex():key(KType()),id(-1),parent_id(-1){}
            //!显式构造函数，指定`key`
            /*!
            * \param  k:顶点存放的数据
            */
            explicit Vertex(const KeyType&k):key(k),id(-1),parent_id(-1){}
            //!显式构造函数，指定`key`和编号
            /*!
            * \param  k:顶点存放的数据
            * \param  d:顶点的编号
            */
            Vertex(const KeyType&k,VIDType d):key(k),id(d),parent_id(-1){}

            //!to_string：返回顶点的字符串描述
            /*!
            * \return :顶点的字符串描述
            *
            * 依次输出顶点的`id`、`key`以及`parent_id`信息。
            */
            virtual std::string to_string() const
            {
                std::ostringstream os;
                os<<"vertex id:"<<id<<"\t key:";
                if(is_unlimit(key)) os<<" +OO ";
                else os<<key;
                os<<"\t parent_id:"<<parent_id;
                return os.str();
            }
            KeyType key;  /*!< 顶点存储数据*/
            const VIDType id;   /*!< 顶点id，一旦顶点生成则id不可变*/
            VIDType parent_id; /*!< 顶点的父节点id*/
        };
    }
}
#endif // GRAPHVERTEX


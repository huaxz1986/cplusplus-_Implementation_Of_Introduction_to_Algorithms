#ifndef BFS
#define BFS
#include<src/header.h>
#include"../graph_vertex/vertex.h"
#include"../graph/graph.h"
#include<queue>
#include<functional>
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
             enum class COLOR{WHITE,GRAY,BLACK}; /*!< 顶点颜色的枚举类型*/


             //!默认构造函数，将`color`设为白色
             BFS_Vertex():color(COLOR::WHITE){}
             //!显式构造函数，指定`key`
             /*!
             * \param  k:顶点存放的数据
             *
             * 顶点的颜色默认设为白色
             */
             explicit BFS_Vertex(const KType&k):color(COLOR::WHITE),Vertex<KType>(k){}
             //!显式构造函数，指定`key`和编号
             /*!
             * \param  k:顶点存放的数据
             * \param  d:顶点的编号
             *
             * 顶点的颜色默认设为白色
             */
             BFS_Vertex(const KType&k,VIDType d):color(COLOR::WHITE),Vertex<KType>(k,d){}

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
                 this->key=v_parent->key+1;
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
                os<<Vertex<KType>::to_string()<<"\t color:";
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

        //!breadth_first_search：广度优先搜索，算法导论22章xx节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \param source_id：广度优先搜索的源点`id`，必须有效。若无效则抛出异常
        * \param action:一个可调用对象，它在每次搜索到一个顶点后立即调用。其参数为被搜索到的顶点`id`。它默认是个空操作，即不执行任何操作。
        * \return:void
        *
        * `source_id`在以下情况下无效：
        *
        * - `source_id`不在区间`[0,N)`之间时，`source_id`无效
        * - `graph`中不存在某个顶点的`id`等于`source_id`时，`source_id`无效
        *
        *
        * 广度优先搜索：该算法维护已经发现结点和未发现结点的边界，沿着其广度方向向外扩展。每个结点有三种颜色：白色、灰色、黑色。
        * 白色结点表示未发现；灰色结点表示已发现但是未处理完成；黑色结点表示已处理完成。其中灰色结点就是边界。
        *
        * 给定图 G=(V,E)和一个可以识别的源点`s`。。所有的结点在一开始都被涂上白色。每个结点的颜色存放在属性`color`中；
        * 每个结点的前驱结点放在属性`parent`中。每个结点的属性`key`存放的是从源点到本结点的距离。该算法使用一个先进先出的队列Q来管理灰色结点集。
        *
        * - 将所有结点涂为白色，`key`属性设置为正无穷；
        * - 将源点涂为灰色，源点前驱设为空，源点的`key`设为0；
        * - 将源点加入队列Q中；Q中存放的都是已发现但是尚未处理完成的结点
        * - 循环直到队列Q为空，在循环中执行以下操作：
        *   - 取出队列Q头部的结点`v`
        *   - 对结点`v`的邻接表中的白色结点进行发现操作，并将这些结点加入队列Q中
        *   - 对结点`v`染成黑色；
        *
        * 算法的时间复杂度为 O(E+V)
        *
        * 最短路径：广度优先搜索能找出给定源结点s到所有可以到达的结点之间的距离。定义从源s到结点v之间的最短路径距离 delt(s,v) 为从结点s到v之间的所有路径里面最少的边数。
        * 如果从s到v没有路径，则 delt(s,v)=正无穷大 。我们定义从s到v之间的长度为 delt(s,v) 的路径为 s 到 v 的最短路径。可以证明：广度优先搜索可以正确计算出最短路径距离。
        *
        * 广度优先树：对于G=(V,E)和源点s，定义图G的前驱子图为 G_pai=(V_pai,E_pai)，其中 V_pai={ v属于V: v.parent!=NIL}并上{s}，E_pai={(v.parent,v):v属于(V_pai-{s})}。
        * 即V_pai由从源s可达的所有结点组成（包括s本身），E_pai由V_pai中去掉s之后的结点的入边组成，其中该入边的对端为结点的父结点。
        * BFS算法获取的前驱子图G_pai包含一条从源结点s到结点v的唯一简单路径，而且该路径也是图G里面从源s到v之间的一条最短路径，因此前驱子图也称为广度优先树。
        *
        */
    template<typename GraphType,typename Action=std::function< void(typename GraphType::VIDType)>> void breadth_first_search(std::shared_ptr<GraphType> graph,
                      typename GraphType::VIDType source_id,Action action=[](typename GraphType::VIDType){})
        {
            typedef typename GraphType::VType VertexType;
            typedef typename GraphType::VIDType VIDType;

            if(!graph)
                throw std::invalid_argument("breadth_first_search error: graph must not be nullptr!");
            if(source_id<0||source_id>=GraphType::NUM||!graph->vertexes.at(source_id))
                throw std::invalid_argument("breadth_first_search error: source_id muse belongs [0,N) and graph->vertexes[source_id] must not be nullptr!");

            std::queue<std::shared_ptr<VertexType>> v_queue;
            //************* 初始化顶点 ****************
            for(auto& v:graph->vertexes)
            {
                if(!v) continue;
                v->color=VertexType::COLOR::WHITE;
                v->key=unlimit<typename VertexType::KeyType>();
            }
            //************* 处理源顶点 ****************
            graph->vertexes.at(source_id)->set_source();
            v_queue.push(graph->vertexes.at(source_id));
            action(source_id);
            //************ 处理其他顶点 ***************
            while(!v_queue.empty())
            {
                auto front=v_queue.front();
                v_queue.pop();

                for(const auto& edge :graph->vertex_edge_tuples(front->id))
                {
                    VIDType next_id=std::get<1>(edge);
                    auto next_vertex=graph->vertexes.at(next_id);
                    if(next_vertex->color==VertexType::COLOR::WHITE)
                    {
                        next_vertex->set_found(front);
                        v_queue.push(next_vertex);
                        action(next_id);
                    }
                }
                front->color=VertexType::COLOR::BLACK;
            }
        }

    }
}


#endif // BFS


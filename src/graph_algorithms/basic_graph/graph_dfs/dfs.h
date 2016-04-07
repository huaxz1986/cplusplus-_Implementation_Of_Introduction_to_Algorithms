#ifndef DFS
#define DFS
#include<src/header.h>
#include"../graph_vertex/vertex.h"
#include"../graph/graph.h"
#include<functional>
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
             enum class COLOR{WHITE,GRAY,BLACK}; /*!< 顶点颜色的枚举类型*/


             //!默认构造函数，将`color`设为白色，发现时间与完成时间默认为-1
             DFS_Vertex():color(COLOR::WHITE),discover_time(-1),finish_time(-1){}
             //!显式构造函数，指定`key`
             /*!
             * \param  k:顶点存放的数据
             *
             * 顶点的颜色默认设为白色，发现时间与完成时间默认为-1
             */
             explicit DFS_Vertex(const KType&k):
                 color(COLOR::WHITE),discover_time(-1),finish_time(-1),Vertex<KType>(k)
             {}
             //!显式构造函数，指定`key`和编号
             /*!
             * \param  k:顶点存放的数据
             * \param  d:顶点的编号
             *
             * 顶点的颜色默认设为白色，发现时间与完成时间默认为-1
             */
             DFS_Vertex(const KType&k,VIDType d):
                 color(COLOR::WHITE),discover_time(-1),finish_time(-1),Vertex<KType>(k,d)
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
             * 再`Vertex`基类的基础上输出`color`以及`parent`、`discover_time`以及`finish_time`信息。
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
                os<<"\t discover_time:"<<discover_time<<"\t finish_time:"<<finish_time;
                return os.str();
             }
             int discover_time;                      /*!< 顶点发现时间*/
             int finish_time;                        /*!< 顶点完成时间*/
             COLOR color;                            /*!< 顶点颜色*/
             std::shared_ptr<DFS_Vertex> parent;     /*!< 顶点父顶点的强引用*/
        };


        //!visit：深度优先搜索的辅助函数，用于访问顶点，算法导论22章22.3节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \param v_id:待访问顶点的`id`，必须有效。如果无效则抛出异常
        * \param time:访问时刻，是一个引用参数，确保每次`visit`都访问同一个时钟。
        * \param pre_action:一个可调用对象，在每次发现一个顶点时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次对一个顶点搜索完成时调用，调用参数为该顶点的`id`以及完成时间`time`。默认为空操作，即不进行任何操作
        *
        * `v_id`在以下情况下无效：
        *
        * - `v_id`不在区间`[0,N)`之间时，`v_id`无效
        * - `graph`中不存在某个顶点的`id`等于`v_id`时，`v_id`无效
        *
        * 在每次对一个结点调用visit的过程中，结点v_id的初始颜色都是白色。然后执行下列步骤：
        *
        * - 将全局时间 time 递增
        * - 发现结点 v_id
        * - 对结点 v_id 的每一个相邻结点进行检查，在相邻结点是白色的情况下递归访问该相邻结点
        * - 当结点 v_id 的相邻结点访问完毕，则全局时间 time 递增，然后将结点 v_id 设置为完成状态
        *
        */
        template<typename GraphType,typename Action=std::function<void(typename GraphType::VIDType,int)>>
                    void visit(std::shared_ptr<GraphType> graph,typename GraphType::VIDType v_id,int&time,
                     Action pre_action=[](typename GraphType::VIDType,int){},Action post_action=[](typename GraphType::VIDType,int){})
        {
            if(!graph)
                throw std::invalid_argument("visit error: graph must not be nullptr!");
            if(v_id<0||v_id>=GraphType::NUM||!graph->vertexes.at(v_id))
                throw std::invalid_argument("visit error: v_id muse belongs [0,N) and graph->vertexes[v_id] must not be nullptr!");

            time++;
            //*******  发现本顶点 *****************
            pre_action(v_id,time);
            graph->vertexes.at(v_id)->set_disovered(time);
            //********  搜索本顶点相邻的顶点*************
            for(const auto&edge:graph->vertex_edge_tuples(v_id))
            {
                auto another_id=std::get<1>(edge);
                auto another_vertex=graph->vertexes.at(another_id);
                if(another_vertex->color==GraphType::VType::COLOR::WHITE)
                {
                    another_vertex->parent=graph->vertexes.at(v_id);
                    visit<GraphType,Action>(graph,another_id,time,pre_action,post_action);
                }
            }
            //*********** 完成本顶点的搜索
            time++;
            graph->vertexes.at(v_id)->set_finished(time);
            post_action(v_id,time);
        }

        //!depth_first_search：深度优先搜索，算法导论22章22.3节
        /*!
        * \param graph:指向图的强引用，必须非空。若为空则抛出异常
        * \param pre_root_action:一个可调用对象，在每次发现一个顶点且该顶点是深度优先森林的根节点时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param post_root_action:一个可调用对象，在每次对一个顶点搜索完成时且该顶点是深度优先森林的根节点时调用调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param pre_action:一个可调用对象，在每次发现一个顶点时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param post_action:一个可调用对象，在每次对一个顶点搜索完成时调用，调用参数为该顶点的`id`以及发现时间`time`。默认为空操作，即不进行任何操作
        * \param search_order:指定搜索顶点的顺序（不同的搜索顺序可能形成的深度优先森林不同)，如果为空则按照顶点的`id`顺序。默认为空
        * \return:void
        *
        * 深度优先搜索：深度优先搜索总是对最近才发现的结点v的出发边进行搜索，直到该结点的所有出发边都被发现为止。一旦结点v的所有出发边都被发现，则“回溯”到v的前驱结点（v是经过该结点才被发现的）。
        * 该过程一直持续到源结点可以达到的所有结点都被发现为止。如果还存在尚未发现的结点，则深度优先搜索将从这些未被发现的结点中任选一个作为新的源结点，并重复同样的搜索过程。该算法重复整个过程，
        * 直到图中的所有结点被发现为止。
        *
        * 深度优先搜索维护一个全局的时间。每个结点v有两个时间戳，discover_time记录了v第一次被发现的时间（v涂上灰色的时刻）；finish_time记录了搜索完成v的相邻结点的时间（v涂上黑色的时刻）。
        * 结点v在v.discover_time之前为白色，在v.discover_time之后与v.finish_time之前为灰色，在v.finish_time之后为黑色
        *
        * 深度优先搜索步骤：
        *
        * - 初始化：将所有结点染白色，并将它们的父结点置为空
        * - 将全局时间 time 置为0
        * - 遍历结点集V，取出结点v
        *   -若v是白色的（尚未发现），则调用 visit 操作
        *   > 当这里调用 visit 操作时，结点v会成为一棵树的根
        *   >
        *   > 深度优先搜索的结果会依赖于遍历结点集V的顺序。不同的遍历顺序得到的结果会不同
        *
        * 深度优先搜索性能：时间复杂度 O(V+E)
        *
        * 深度优先搜索的性质：证明请参考《算法导论》:
        *
        * - 深度优先搜索生成的前驱子图G_pai是一个由多棵树构成的森林
        * - 结点 v 是结点 u 在深度优先森林中的后代当且仅当结点v在结点u为灰色的时间段内被发现
        * - 结点的发现时间和完成时间具有括号化结构：如果以左括号"(u"来表示结点u被发现，以后括号"u)"表示结点u完成。则发现和完成的历史记载会形成一个规整的表达式。
        *   在深度优先搜索中，对于任意两个结点u和v来说，下面三种情况只有一种成立
        *       - 区间[u.discover_time,u.finish_time]与区间[v.discover_time,v.finish_time]完全分离。
        *         此时在深度优先森林中，结点u不是结点v的后代，结点v也不是结点u的后代
        *       - 区间[u.discover_time,u.finish_time]完全包含在[v.discover_time,v.finish_time]，此时在深度优先森林中，结点u是结点v的后代
        *       - 区间[v.discover_time,v.finish_time]完全包含在[u.discover_time,u.finish_time]，此时在深度优先森林中，结点v是结点u的后代
        *
        * 深度优先森林的边：对于在图G上运行深度优先搜索算法所生成的深度优先森林G_pai，可以定义四种类型的边：
        *
        *  - 树边：它是深度优先森林的边。若结点v是因深度优先算法对边(u,v)的搜索而首先被发现，则(u,v)是一条树边
        *  - 后向边： 后向边(u,v)将结点u连接到其深度优先树中某个祖先结点v。对于有向图的自循环，自循环被认为是后向边
        *  - 前向边： 将结点u连接到其在深度优先树中一个后代结点v
        *  - 横向边： 其他的边。这些边可以连接同一棵深度优先树中的结点（只要其中一个结点不是另外一个结点的祖先），也可以连接不同深度优先树中的两个结点。
        *
        * 在深度优先搜索中，当第一次搜索边(u,v)时：
        *
        * - 若结点v为白色，表明边(u,v)是一条树边
        * - 若结点v为灰色，表明边(u,v)是一条后向边
        * - 若结点v为黑色，表明边(u,v)是一条前向边或者横向边
        *   - 在 u.discover_time< v.discover_time 时，为前向边
        *   - 在 u.discover_time< v.discover_time 时，为横向边
        *
        * 在无向图中，每条边要么是树边，要么是后向边。从来不会出现前向边和横向边。
        *
        */
        template<typename GraphType,typename Action=std::function<void(typename GraphType::VIDType,int)>>
                    void  depth_first_search(std::shared_ptr<GraphType> graph,
                               Action pre_action=[](typename GraphType::VIDType,int){},
                               Action post_action=[](typename GraphType::VIDType,int){},
                               Action pre_root_action=[](typename GraphType::VIDType,int){},
                               Action post_root_action=[](typename GraphType::VIDType,int){},
                               const std::vector<typename GraphType::VIDType>& search_order=std::vector<typename GraphType::VIDType>())
        {
            typedef typename GraphType::VIDType VIDType;
            if(!graph)
                throw std::invalid_argument("depth_first_search error: graph must not be nullptr!");
            //************  创建真实的 search_order ****************
            std::vector<VIDType> real_search_order;
            if(!search_order.size())
            {
                for(int i=0;i<GraphType::NUM;i++)
                    real_search_order.push_back(i);
            }else
                real_search_order=search_order;

            //*************** 深度优先搜索 *************
            int time=0;
            for(const auto& v_id :real_search_order)
            {
                if(v_id<0||v_id>=GraphType::NUM||!graph->vertexes.at(v_id)) //顶点为空
                    continue;
                auto v=graph->vertexes.at(v_id);
                if(v->color==GraphType::VType::COLOR::WHITE)
                {
                    pre_root_action(v_id,time);
                    visit<GraphType,Action>(graph,v->id,time,pre_action,post_action);
                    post_root_action(v_id,time);
                }
            }
        }
   }
}


#endif // DFS


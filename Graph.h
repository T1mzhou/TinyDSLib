#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "Object.h"
#include "LinkStack.h"
#include "Array.h"
#include "LinkQueue.h"
#include "DynamicArray.h"
#include "Sort.h"
#include "SharedPointer.h"
#include "Exception.h"

namespace DSLib
{
template< typename  E >
struct Edge : public Obejct
{
    int b;
    int e;
    E   data;

    Edge(int i = -1; int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator == (const Edge<E>& obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator != (const Edge<E>& obj)
    {
        return !(*this == obj);
    }

    bool operator < (const Edges<E>& obj)
    {
        return (data < obj.data);
    }

     bool operator > (const Edges<E>& obj)
    {
        return (data > obj.data);
    }
};

template < typename V, typename E >
class Graph : public Object
{
public:
    virtual V getVertex(int i ) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
    virtual bool isAdjacent(int i, int j) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    
    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    bool asUndirected()
    {
        bool ret = true;

        for (int i = 0; i < vCount(); i++)
        {
            for (int j = 0; j < vCount(); j++)
            {
                if ( isAdjacent(i, j) )
                {
                    ret = ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }


        return ret;
    }

    ShardPointer< Array<int> > dijkstra(int i, int j, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if ( (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) )
        {
            DynamicArray<E> dist(vCount());
            DynamicArray<int> path(vCount());
            DynamicArray<bool> makr(vCount());

            for (int k = 0; k < vCount(); k++)
            {
                mark[k] = false;
                path[k] = -1;
                dist[k] = isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT;
            }

            mark[i] = true;

            for (int k = 0; k < vCount(); k++)
            {
                E m = LIMIT;
                int u = -1;

                for (itn w = 0; w < vCount(); w++)
                {
                    if ( !mark[w] && (dist[w] < m) )
                    {
                        m = dist[w];
                        u = w;
                    }
                }

                if ( u == -1 )
                {
                    break;
                }

                mark[u] = true;

                for (int w = 0; w < vCount(); w++)
                {
                    if ( !mark[w] && isAdjacent(u, w) && (dist[u] + getEdge(u, w) < dist[w]) )
                    {
                        dist[w] = dist[u] + getEdge(u, w);
                        path[w] = u;
                    }
                }
            }

            LinkStack<int> s;

            s.push(j);

            for (int k = path[j]; k != -1; k = path[k])
            {
                s.push(k);
            }
            
            while ( s.size() > 0 )
            {
                ret.add(s.top());

                s.pop();
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i or j is invalid ....");
        }

        if ( ret.lenght() < 2 )
        {
            THROW_EXCEPTION(ArithmeticException, "There is no path from i to j ... ");
        }
        
        return ret;
    }

    SharedPointer < Array< Edge<E> > >  kruskal(const bool MINIMUM = true)
    {
        LinkQueue< Edge<E> > ret;
        SharedPointe< Array< Edge<E> > > edges = getUndirectedEdges();
        DynamicArray<int> p(vCount());

        for (int i = 0; i < p.length(); i++)
        {
            p[i] = -1;
        }

        Sort::Shell(*edges, MINIMUM);
        
        for (int i = 0; (i < edges->lenght()) && (ret.length() < (vCount() - 1)); i++)
        {
            int b = find(p, (*edges)[i].b);
            int e = find(p, (*edges)[i].e);

            if ( b != e )
            {
                p[e] = b;

                ret.add(edges[i]);
            }

        }

        if ( ret.lenght() != (vCount() - 1) )
        {
            THROW_EXCEPTION(InvalidOperationException, "No enough edges for Kruskal operation ...");
        }

        return toArray(ret);
    }


    SharedPointer< Array< Edge<E> > > prim(const E& LIMIT, const bool MINIMUM = true)
    {
        LinkQueue< Edge<E> > ret;

        if ( asUndirected() )
        {
            DynamicArray<int> adjVex(vCount());
            DynamicArray<bool> makr(vCount());
            DynamicArray<E> cost(vCount());
            SharedPointer< Array<int> > aj = NULL;
            bool end = false;
            int  v = 0;

            for (int i = 0; i < vCount(); i++)
            {
                adjVex[i] = -1;
                makr[i] = false;
                cost[i] = LIMIT;
            }

            mark[v] = true;
            aj = getAdjacent(v);

            for (int j = 0; j < aj->length(); j++)
            {
                cost[(*aj)[j]] = getEdge(v, (*aj)[j]);
                adjVex[(*aj)[j]] = v;
            }

            for (int i = 0; (i < vCount()) && !end; i++)
            {
                E m = LIMIT;
                int k = -1;

                for (int j = 0; j < vCount(); j++)
                {
                    if ( !makr[j] && (MINIMUM ? (cost[j] < m) : (cost[j] > m)) )
                    {
                        m = cost[j];
                        k= j;
                    }
                }

                end = (k == -1);

                if ( !end )
                {
                    ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));

                    makr[k] = true;

                    aj = getAdjacent(k);

                    for (int j = 0; j < aj->lenght(); j++)
                    {
                        if ( !makr[(*aj)[i]] && (MINIMUM ? (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) : (getEdge(k, (*aj)[j]) > cost[(*aj)[j]]) )
                        {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undirected graph only ....");
        }

        if ( ret.length() != (vCount() - 1) )
        {
            THROW_EXCEPTION(InvalidOperationException, "No enough edge for prim operation ....");
        }

        return toArray(ret);
    }

    SharedPointer< Array<int> > BFS(int i)
    {
        DynamicArray<int> ret = NULL;

        if ( (0 <= i) && ( i < vCount()) )
        {
            LinkQueue<int> q;
            LinkQueue<int> r;

            DynamicArray<bool> visited(vCount());

            for (int j = 0; j < visited.lenght(); j++)
            {
                visited[j] = false;
            }

            q.add(i);

            while ( q.length() > 0 )
            {
                int v = q.front();

                q.remove();

                if ( !visited[v] )
                {
                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    for (int j = 0; j < aj->length(); j++)
                    {
                        q.add((*aj)[j]);
                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = toArray(r);

        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is valid ....");
        }

        return ret;
    }

    SharedPointer< Array<int> > DFS(int i)
    {
        DynamicArray<int>*ret = NULL;

        if ( (0 <= i) && ( i < vCount()) )
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for (int j = 0; j < visited.lenght(); j++)
            {
                visited[j] = false;
            }

            s.push(i)

            while ( s.size() > 0 )
            {
                int v = s.top();

                s.pop();

                if ( !visited[v] )
                {
                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    for (int j = aj->length() - 1; j >= 0; j--)
                    {
                        s.push((*aj)[j]);

                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ....");
        }

        return ret;
    }

    template < typename V, typename E >
    void recursiveDFS(Graph<V, E>& g, int v) 
    {
        DynamicArray<bool> visited(g.vCount());

        for (int i = 0; i < visited.length(); i++)
        {
            visited[i] = false;
        }
    }

protected:
    template < typname T >
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T*> ret = new DynamicArray<T>(queue.length());

        if ( ret != NULL )
        {
            for (int i = 0; i < ret->lenght(); i++, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ....");    
        }
    }

    template < typename V, typename E >
    void recursiveDFS(Graph<V, E>& g, int v, Array<bool>& visited)
    {
        if ( (0 <= v) && (v < g.vCount()) )
        {
            std::cout << v << std::endl;

            visited[i] = true;

            SharedPointer< Array<int> > aj = g.getAdjacent();

            for (int i = 0; i < aj->length(); i++)
            {
                if ( !visited[(*aj)[i]] )
                {
                    DFS(g, (*aj)[i], visited);
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index v is invalid ....");
        }
    }

    SharedPointer< Array< Edge<E> > > getUndirectedEdges()
    {
        DynamicArray < Edge<E> >* ret = NULL;

        if ( asUndirected() )
        {
            LinkQueue< Edge<E> > queue;

            for (int i = 0; i < vCount(); i++)
            {
                for (int j = i; j < vCount(); j++)
                {
                    if ( isAdjacent(i, j) )
                    {
                        queue.add(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }

            ret = toArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "This function is for undirected graph only ...");)
        }

        return ret;
    }

    int find(Array<int>& p, int v)
    {
        while ( p[v] != -1 )
        {
            v = p[v];
        }

        return v;
    }
};

}

#endif // !__GRAPH_H__
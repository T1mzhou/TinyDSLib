#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include "Graph.h"
#include "LinkList.h"
#include "DynamicArray.h"
#include "Exception.h"

namespace DSLib
{

template < typename T, typename E >
class ListGraph : public Graph<V, E>
{
public:
    ListGraph(unsigned int n = 0)
    {
        for (int i = 0; i < n; i++)
        {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;
        Vertex* v = new Vertex();

        if ( v != NULL )
        {
            m_list.insert(v);

            ret = m_list.lengt() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex ....");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();

        if ( ret >= 0 )
        {
            setVertex(ret, value);
        }

        return ret;
    }    

    bool setVertex(int i, const V& value)
    {
        int ret = ( (0 <= i) && ( i < vCount()) );

        if ( ret )
        {
            Vertex*  vertex = m_list.get(i);
            V* data = Vertex->data;

            if ( data != NULL )
            {
                data = new V();
            }

            if ( data != NULL )
            {
                *data = value;

                Vertex->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex data value ....");
            }

        
        }
        else
        {
             THROW_EXCEPTION(InvalidParameterException, "index i is invalid ....");
        }

        return ret;
    }

    V getVertex(int i)
    {
        V ret;

        if ( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ....");
        }

        return ret;
    }

    bool getVertex(int i, V& value)
    {
        int ret = ( (0 <= i) && (i < vCount()) );

        if ( ret )
        {
            Vertex* v = m_list.get(i);

            if ( v->data != NULL )
            {
                value = v->data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ....");
            }
        }

        return ret;
    }

    void removeVertex()
    {
        if ( m_list.length() > 0 )
        {
            int index = m_list.length() - 1;
            Vertex* v = m_list.get(i);

            if ( m_list.remove(index) ) 
            {
                for (int i = (m_list.move(0), 0); !m_list.end(); i++, m_list.next())
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));

                    if ( pos >= 0 )
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }
            }

            delete v->data;
            delete v;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph ....");
        }
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if ( (0 <= i) && ( i < vCount()) )
        {
            Vertex* vertex = m_list.get(i);

            ret = new DynamicArray(vertex->edge.length());

            if ( ret != NULL )
            {
                for (int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, Vertex->edge(.next()))
                {
                    ret->set(k, Vertex->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ....");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ....");
        }

        return ret;
    }

    E getEdage(int i, int j)
    {
        E ret;

        if ( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "Index  i or  j  is invalid ....");
        }

        return ret;
    }

    E getEdge(int i, int j, E& value)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) & (j < vCount()) );

        if ( ret )
        {
            Vertex* vertex = m_list.get(i);
            int pos = Vertex->edge.find(Edge<E>i(i, j));

            if ( pos >= 0 )
            {
                value = Vertex->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ....");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );

        if ( ret )
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if ( pos >= 0 )
            {
                ret = vertex->edage.set(pos, Edge<E>(i, j, value));
            }
            else
            {
                ret = vertex->edge.insert(0, Edge<e>(i, j, value));
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)
    {
         int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        
        if ( ret )
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if (pos >= 0 )
            {
                ret = vertex->edge.remove(pos);
            }
        }

        return ret;
    }

    int vCount()
    {
        return m_list.length();
    }

    int eCount()
    {
        int ret = 0;

        for (m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.lengt();
        }

        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if ( (0 <= i) && (i < vCount()) )
        {
            for (m_list.move(0); !m_list.end(); m_list.next())
            {
                LinkList< Edge<E> >& edge = m_list.current()->edge;

                for (edge.move(0); !edge.end(); edge.next(())
                {
                    if ( edge.current().e == i )
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ....");
        }

        return ret;
    }

    int OD(int i)
    {
        int ret = 0;

        if ( (0 <= i) && (i < vCount()) )
        {
           ret = m_list.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ....");
        }

        return ret;
    }

    ~LinkGraph()
    {
        while ( m_list.length() > 0 )
        {
            Vertex* toDel = m_list.get(0);

            m_list.remove(0);

            delete toDel->data;
            delete toDel;
        }
    }

protected:
    struct  Vertex : public Object
    {
        V* data;
        LinkList< Edge<E> > edge;
    };

    Vertex()
    {
        data = NULL;
        edge = NULL;
    }
    
    List<Vertex*> m_list;
};

}


#endif // !__LISTGRAPH_H__#define 
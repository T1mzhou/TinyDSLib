#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include "Graph.h"
#include "DynamicArray.h"
#include "Exception.h"

namespace DSLib
{

template < int N, typename V, typename E >
class MatrixGraph : public Graph<V, E>
{
public:
    MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for (int j = 0; j < vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }

        m_eCount = 0;
    }

    V getVertex(int i )
    {
        V ret;

        if ( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidOperationException, "Index i is invalid ...");
        }
    
        return ret;
    }

    bool getVertex(int i, V& value)
    {
        bool ret = ( (0 <= i ) && (i < vCount()) ) ;

        if ( ret )
        {
            if ( m_vertexes[i] != NULL )
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertexes");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ( (0 <= i ) && (i < vCount()) ) ;

        if ( ret )
        {
            V* data = m_vertexes[i];

            if ( data == NULL )
            {
                data = new V();
            }

            if ( data != NULL )
            {
                *data = value;

                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ....");
            }
            
        }

        return ret;

    }
    
    SharedPointer< Array<int> > getAdjacent(int i )
    {
        DynamicArray<int>* ret = NULL;

        if ( (0 <= i ) && (i < vCount()) )
        {
            for (int j = 0; j < vCount(); j++)
            {
                if ( m_edges[i][j] != NULL )
                {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);

            if ( ret != NULL )
            {
                for (int j = 0, k = 0; j < vCount(); j++)
                {
                    if ( m_edges[i][j] != NULL )
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new ret obeject ....");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "index i is invalid ....");
        }

        return ret;
    }

    E getEdge(int i, int j)
    {
        E ret = NULL;

        if ( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidOperationException, "index i or j is invalid ....");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        
        bool ret = ( (0 <= i) && (i <= vCount()) )  && ( (0 <= j) && (j < vCount()) );
        
        if ( ret )
        {
            if ( m_edges[i][J] != NULL )
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ....");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "index i or j is invalid ....");
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = ( (0 <= i) && ( i < vCount()) &&
                     (0 <= j) && ( j < vCount()) );

        if ( ret )
        {
            E* data = m_edges[i][j];

            if ( data == NULL )
            {
                data = new E();
            }
            
            if ( data != NULL )
            {
                *data = value;
                m_edges[i][j] = data;

                m_eCount++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new ret obeject ....");
            }
        }

        return ret;
    }



    bool removeEdge(int i, int j)
    {
        bool ret = ( (0 <= i) && ( i < vCount()) &&
                     (0 <= j) && ( j < vCount()) );

        if ( ret )
        {
            E* toDel = m_edges[i][j];

            m_edges[i][j] = NULL;

            if ( toDel != NULL )
            {
                m_eCount--;

                delete toDel;
            }
        }

        return ret;
    }

    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;

        if ( (0 <= i) && ( i < vCount()) )
        {
            for (int j = 0; j < vCount(); j++)
            {
                if ( m_edges[i][j] != NULL )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "index i is invalid ....");
        }

        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if ( (0 <= i) && ( i < vCount()) )
        {
            for (int j = 0; j < vCount(); j++)
            {
                if ( m_edges[j][i] != NULL )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "index i is invalid ....");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++)
        {
            for (int j = 0; j < vCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }

        m_eCount = 0;
    }


protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
};

}
#endif // !__MATRIXGRAPH_H__
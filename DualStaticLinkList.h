#ifndef __DUALSTATICLINKLIST_H__
#define __DUALSTATICLINKLIST_H__

#include "DualLinkList.h"
#include "Exception.h"

namespace DSLib
{
template < typename T >

class DualStaticLinkList : public DualLinkList<T>
{

};

}

#endif // !__DUALSTATICLINKLIST_H__

#ifndef __DUALCIRCLELIST_H__
#define __DUALCIRCLELIST_H__

#include "DualLinkList.h"
#include "Exception.h"

namespace DSLib
{
template < typename T >

class DualLinkList : public DualLinkList<T>
{

};

}

#endif // !__DUALCIRCLELIST_H__

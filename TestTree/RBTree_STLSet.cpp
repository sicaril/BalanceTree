#include "StdAfx.h"
#include "RBTree_STLSet.h"

RBTree_STLSet::RBTree_STLSet(void)
{
}

RBTree_STLSet::~RBTree_STLSet(void)
{
}

bool RBTree_STLSet::Insert(T& Data)
{
	Obj.insert( Data );
	return true;
}

bool RBTree_STLSet::Delete(T& Data)
{
	set<T>::iterator it = Obj.find(Data);
	if ( it != Obj.end() )
	{
		Obj.erase( it );
		return true;
	}
	return false;
}

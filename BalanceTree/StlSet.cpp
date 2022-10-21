#include "stdafx.h"
#include "StlSet.h"


StlSet::StlSet(void)
{
}


StlSet::~StlSet(void)
{
}

bool StlSet::Insert(T& Data)
{
	Obj.insert( Data );
	return true;
}

bool StlSet::Delete(T& Data)
{
	set<T>::iterator it = Obj.find(Data);
	if ( it != Obj.end() )
	{
		Obj.erase( it );
		return true;
	}
	return false;
}

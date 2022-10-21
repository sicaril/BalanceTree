#pragma once
#include "tree.h"
#include <set>
using namespace std;

class StlSet :
	public Tree
{
public:
	StlSet(void);
	virtual ~StlSet(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check(){return true;}
	char* GetTreeName(){return "Stl Set";}

private:
	set<T> Obj;
};


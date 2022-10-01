#pragma once
#include "Tree.h"
#include <set>
using namespace std;

class RBTree_STLSet : public Tree
{
public:
	RBTree_STLSet(void);
	~RBTree_STLSet(void);

public:

	virtual bool Insert(T& Data);

	virtual bool Delete(T& Data);

	virtual bool Check(){return true;}

	virtual char * GetTreeName(){return "RBtree StlSet";}

private:

	set<int> Obj;

};

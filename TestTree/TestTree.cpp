// TestTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include "AVLTree_Height.h"
#include "AVLTree_BFactor.h"
#include "AVLTree_Optimize.h"
#include <time.h>
#include <stdlib.h>
#include "RBTree_STLSet.h"
#include "RBTree.h"
#include "RBTree_Optimize.h"
#include <Windows.h>


#define ARRAY_SIZEOF( a ) ( sizeof(a) / sizeof( (a)[0] ) )

time_t g_tt;
int g_nRandom = 0;

#define NS_INIT_RAND	g_nRandom = (int)time(&g_tt);
#define NS_ADD_SAND		(++g_nRandom)
#define NS_INIT_SAND	srand( NS_ADD_SAND )
#define NS_RANDOM(x)	(rand()%(x))


#define	MAXSIZE		10000000
#define RANDOMSIZE	10000
#define CYCLESIZE	1000


//////////////////////////////////////////////////////////////////////////
// 性能测试
//////////////////////////////////////////////////////////////////////////

void TestTreePerformance(Tree* Obj, bool bInvertedOrderInsert = false, bool bInvertedOrderDelete = false, bool bUseDelete2 = false )
{
	DWORD dwCount = 0;

	dwCount = GetTickCount();

	if ( bInvertedOrderInsert )
	{
		for ( int i = MAXSIZE ; i >= 0; i-- )
		{
			Obj->Insert( i );
		}
	}
	else
	{
		for ( int i = 0 ; i <= MAXSIZE; i++ )
		{
			Obj->Insert( i );
		}
	}

	dwCount = GetTickCount() - dwCount;

	printf("%s\t Insert Time: %d  Tree Count %d \r\n", Obj->GetTreeName(), dwCount, Obj->Size());

	dwCount = GetTickCount();

	if ( bInvertedOrderDelete )
	{
		if ( bUseDelete2 == false )
		{
			for ( int i = MAXSIZE ; i >=0; i-- )
			{
				if( Obj->Delete( i ) == false )
					printf("Delete err %d \r\n", i);
			}
		}
		else
		{
			for ( int i = MAXSIZE ; i >=0; i-- )
			{
				if( Obj->Delete2( i ) == false )
					printf("Delete2 err %d \r\n", i);
			}
		}
	}
	else
	{
		if ( bUseDelete2 == false )
		{
			for ( int i = 0 ; i <= MAXSIZE ; i++ )
			{
				if( Obj->Delete( i ) == false )
					printf("Delete err %d \r\n", i);
			}
		}
		else
		{
			for ( int i = 0 ; i <= MAXSIZE ; i++ )
			{
				if( Obj->Delete2( i ) == false )
					printf("Delete2 err %d \r\n", i);
			}
		}
	}

	dwCount = GetTickCount() - dwCount;

	printf("%s\t Delete time: %d  Use Delete2: %d Tree Count %d\r\n", Obj->GetTreeName(), dwCount, bUseDelete2, Obj->Size());
}


//////////////////////////////////////////////////////////////////////////
//	合法性校验 
//////////////////////////////////////////////////////////////////////////

void CheckTreeRandomDelete(Tree* Obj)
{
	DWORD dwCount = 0;

	dwCount = GetTickCount();

	int nMax = RANDOMSIZE;

	NS_INIT_SAND;

	for ( int i = nMax ; i > 0 ; i-- )
	{
		int j = NS_RANDOM(nMax);
		Obj->Insert( j );

		if ( Obj->Check() == false )
			printf("Check %s Random Insert err! \r\n",Obj->GetTreeName());
	}

	dwCount = GetTickCount() - dwCount;

	if ( Obj->Check() == false )
		printf("Check %s Random Insert err! \r\n",Obj->GetTreeName());
	else
		printf("Check %s Random Insert success! Count %d \r\n",Obj->GetTreeName(),Obj->Size());

	if( Obj->m_root )
	{
		// set is NULL
		printf(" %s Tree Height %d left Tree Height %d Right Tree Height %d \r\n",
			Obj->GetTreeName(),
			GetNodeHeightDeep(Obj->m_root) + 1, 
			GetNodeHeightDeep(Obj->m_root->m_lchild) + 1, 
			GetNodeHeightDeep(Obj->m_root->m_rchild) + 1
			);
	}

	int iDelete = 0;
	for ( int i = nMax ; i > 0 ; i-- )
	{
		int j = NS_RANDOM(nMax);
		
		if( Obj->Delete( j ) )
			++iDelete;

		if ( Obj->Check() == false )
		{
			printf("Delete Check err! %d \r\n", j);
		}
	}

	printf("Check %s Random Delete over! Count %d Delete %d \r\n",Obj->GetTreeName(), Obj->Size(), iDelete);

	return;
}

bool _CheckTreeCycleDelete( Tree * Obj, int nBegin)
{
	bool bCheck = true;

	int nMin = CYCLESIZE;

	for ( int i = 0 ; i <= nMin; i++ )
	{
		Obj->Insert( i );
	}

	if ( Obj->Check() == false )
	{
		bCheck = false;
		printf("Check %s Cycle Insert err! Begin: %d \r\n",Obj->GetTreeName(), nBegin );
	}

	for ( int i = nBegin ; i >= 0; i-- )
	{
		
		if( Obj->Delete( i ) == false )
			printf("Delete err %d , Begin: %d \r\n", i, nBegin);

		if ( Obj->Check() == false )
		{
			bCheck = false;
			printf("Check %s Cycle Delete err! Begin: %d \r\n", Obj->GetTreeName(), nBegin );
		}
	}

	return bCheck;

}

void CheckTreeCycleDelete( Tree * Obj)
{
	printf("enter %s Cycle test \r\n",Obj->GetTreeName());
	for ( int i = CYCLESIZE; i >= 0; i--)
	{
		if( _CheckTreeCycleDelete(Obj, i) == false )
			printf("### Cycle Check %s error Begin %d \r\n", Obj->GetTreeName(), i);
	}
	printf("%s Cycle test end.\r\n",Obj->GetTreeName());
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void TestTreePerformance()
{
	AVLTree_Height		Obj_AVLTree_Height;
	AVLTree_BFactor		Obj_AVLTree_BFactor;
	AVLTree_Optimize	Obj_AVLTree_Optimize;
	RBTree_STLSet		Obj_RBTree_STLSet;
	RBTree				Obj_RBTree;
	RBTree_Optimize		Obj_RBTree_Optimize;

	Tree * Objs[] = {
		&Obj_AVLTree_Height, 
		&Obj_AVLTree_BFactor, 
		&Obj_AVLTree_Optimize, 
		&Obj_RBTree_STLSet,
		&Obj_RBTree, 
		&Obj_RBTree_Optimize 
	};

	printf(" --== TestTreePerformance Test ==-- \r\n");
	printf("Balance Tree Insert and Delete tests %d times \r\n", MAXSIZE);

	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	{
		TestTreePerformance( Objs[i] ,false, true );
	}

	TestTreePerformance( &Obj_RBTree, false, false, true );

}

void CheckTreeValidity()
{
	AVLTree_Height		Obj_AVLTree_Height;
	AVLTree_BFactor		Obj_AVLTree_BFactor;
	AVLTree_Optimize	Obj_AVLTree_Optimize;
	RBTree_STLSet		Obj_RBTree_STLSet;
	RBTree				Obj_RBTree;
	RBTree_Optimize		Obj_RBTree_Optimize;

	Tree * Objs[] = {
		&Obj_AVLTree_Height, 
		&Obj_AVLTree_BFactor, 
		&Obj_AVLTree_Optimize, 
		&Obj_RBTree_STLSet,
		&Obj_RBTree, 
		&Obj_RBTree_Optimize 
	};

	printf(" --== CheckTreeRandomDelete Test ==-- \r\n");
	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	{
		CheckTreeRandomDelete( Objs[i] );
	}

	printf(" --== CheckTreeCycleDelete Test ==-- \r\n");
	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	{
		Objs[i]->Clear();
		CheckTreeCycleDelete( Objs[i] );
	}

	return;

}

void TestTraverse()
{
	AVLTree_Height Obj;
	for ( int i = 0; i < 10 ; i++ )
	{
		Obj.Insert(i);
	}
	Obj.Traverse(Show);
	printf("\r\n");
	for ( int i = 10; i > 0 ;i-- )
	{
		Obj.Delete(i);
		Obj.Traverse(Show);
		printf("\r\n");
	}

	//RBTree Obj2;
	AVLTree_BFactor Obj2;
	for ( int i = 0; i < 10; i++ )
	{
		Obj2.Insert(i);
	}
	Obj2.Traverse(Show2);
	printf("\r\n");
	for ( int i = 10; i > 0 ;i-- )
	{
		Obj2.Delete(i);
		Obj2.Traverse(Show2);
		printf("\r\n");
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	//TestTraverse();

	TestTreePerformance();

	CheckTreeValidity();

	printf("Test over! \r\n");

	return 1;
}


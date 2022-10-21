// TestTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BSTree.h"
#include "BSTree2.h"
#include "AVLTree.h"
#include "AVLTree2.h"
#include "RBTree.h"
#include "RBTree2.h"
#include "RBTree3.h"
#include "StlSet.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>


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

void TestTreePerformance(Tree* Obj, bool bInvertedOrderInsert = false, bool bInvertedOrderDelete = false )
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
		for ( int i = MAXSIZE ; i >=0; i-- )
		{
			if( Obj->Delete( i ) == false )
				printf("### Delete err %d \r\n", i);
		}
	}
	else
	{
		for ( int i = 0 ; i <= MAXSIZE ; i++ )
		{
			if( Obj->Delete( i ) == false )
				printf("### Delete err %d \r\n", i);
		}
	}

	dwCount = GetTickCount() - dwCount;

	printf("%s\t Delete time: %d  Tree Count %d\r\n", Obj->GetTreeName(), dwCount, Obj->Size());
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
			printf("### Check %s\t Random Insert err! \r\n",Obj->GetTreeName());
	}

	dwCount = GetTickCount() - dwCount;

	if ( Obj->Check() == false )
		printf("### Check %s\t Random Insert err! \r\n",Obj->GetTreeName());
	else
		printf("Check %s\t Random Insert success! Count %d \r\n",Obj->GetTreeName(),Obj->Size());

	if( Obj->m_root )
	{
		// set is NULL
		printf(" %s\t Tree Height %d left Tree Height %d Right Tree Height %d \r\n",
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
			printf("### Delete Check err! %d \r\n", j);
		}
	}

	printf("Check %s\t Random Delete over! Count %d Delete %d \r\n",Obj->GetTreeName(), Obj->Size(), iDelete);

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
		printf("### Check %s\t Cycle Insert err! Begin: %d \r\n",Obj->GetTreeName(), nBegin );
	}

//  	Obj->Traverse(Show2);
//  	printf("\r\n");

	for ( int i = nBegin ; i >= 0; i-- )
	{

// 		if ( i == 28 && nBegin == 28 )
// 		{
// 			int cc = 0;
// 		}

		if( Obj->Delete( i ) == false )
			printf("### Delete err %d , Begin: %d \r\n", i, nBegin);

//  		Obj->Traverse(Show2);
//  		printf("\r\n");

		if ( Obj->Check() == false )
		{
			bCheck = false;
			printf("### Check %s Cycle Delete err! Begin: %d Err: %d\r\n", Obj->GetTreeName(), nBegin, i );
		}
	}

	return bCheck;

}

void CheckTreeCycleDelete( Tree * Obj)
{
	printf("enter %s Cycle test \r\n",Obj->GetTreeName());
	for ( int i = CYCLESIZE; i >= 0; i--)
	{
		Obj->Clear();
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
	BSTree				Obj_BSTree;
	BSTree2				Obj_BSTree2;	// Recursion
	AVLTree				Obj_AVLTree;
	AVLTree2			Obj_AVLTree2;	// Recursion
	RBTree				Obj_RBTree;
	RBTree2				Obj_RBTree2;	// Recursion
	RBTree3				Obj_RBTree3;	// Recursion
	StlSet				Obj_StlSet;

	Tree * Objs[] = {
		&Obj_BSTree,
		&Obj_BSTree2,
		&Obj_AVLTree,
		&Obj_AVLTree2,
		&Obj_RBTree,
		&Obj_RBTree2,
		&Obj_RBTree3,
		&Obj_StlSet
	};

	printf(" --== TestTreePerformance Test ==-- \r\n");
	printf("Balance Tree Insert and Delete tests %d times \r\n", MAXSIZE);

	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	{
		TestTreePerformance( Objs[i] ,false, true );
	}

	// 	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	// 	{
	// 		TestTreePerformance( Objs[i] ,false, false );
	// 	}
	// 
	// 	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	// 	{
	// 		TestTreePerformance( Objs[i] ,true, true );
	// 	}
	// 
	// 	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	// 	{
	// 		TestTreePerformance( Objs[i] ,true, false );
	// 	}

	return;

}

void CheckTreeValidity()
{
	BSTree				Obj_BSTree;
	BSTree2				Obj_BSTree2;	// Recursion
	AVLTree				Obj_AVLTree;
	AVLTree2			Obj_AVLTree2;	// Recursion
	RBTree				Obj_RBTree;
	RBTree2				Obj_RBTree2;	// Recursion
	RBTree3				Obj_RBTree3;	// Recursion

	Tree * Objs[] = {
		&Obj_BSTree,
		&Obj_BSTree2,
		&Obj_AVLTree,
		&Obj_AVLTree2,
		&Obj_RBTree,
		&Obj_RBTree2,
		&Obj_RBTree3
	};

	printf(" --== CheckTreeCycleDelete Test ==-- \r\n");
	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	{
		CheckTreeCycleDelete( Objs[i] );
	}

	printf(" --== CheckTreeRandomDelete Test ==-- \r\n");
	for ( int i = 0 ; i < ARRAY_SIZEOF(Objs); i++ )
	{
		Objs[i]->Clear();
		CheckTreeRandomDelete( Objs[i] );
	}

	return;

}

void TestTraverse()
{
	BSTree Obj;
	//AVLTree Obj;
	//RBTree Obj;
	int nMax = 30;
	for ( int i = 0; i <= nMax ; i++ )
	{
		Obj.Insert(i);
	}
	Obj.Traverse(Show2);
	printf("\r\n");
	for ( int i = nMax; i > 0 ;i-- )
	{
		Obj.Delete(i);
		Obj.Traverse(Show2);
		printf("\r\n");
	}

	return;
}


int _tmain(int argc, _TCHAR* argv[])
{
	CheckTreeValidity();

	TestTreePerformance();

	return 0;
}


#pragma once

typedef int T;

typedef void (*PF_Show)(T&);

typedef void (*PF_Show2)(T&,int);

#define NS_RED		0	// 插入的都是 RED
#define NS_BLACK	1



class TreeNode
{
public:
	TreeNode(void);
	TreeNode(T& Data);
	TreeNode(T& Data, TreeNode* Parent);
	~TreeNode(void);

	void Init();
	void Release();


public:
	TreeNode * m_Parent;
	TreeNode * m_lchild;
	TreeNode * m_rchild;
	T m_Data;

	union 
	{
		int m_height;
		int m_bf;
		int m_sign;
		int m_color;
	}u;

};

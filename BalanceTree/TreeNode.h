#pragma once

typedef int T;
typedef void (PF_Show)(T& Data);
typedef void (PF_Show2)(T& Data, int nSign);

#define NS_RED		0
#define NS_BLACK	1

class TreeNode
{
public:
	TreeNode(void);
	TreeNode(T& Data);
	~TreeNode(void);

	void Init();
	void Release();

public:
	int Height();
	int FixHeight();

public:
	T m_Data;
	TreeNode * m_lchild;
	TreeNode * m_rchild;
	TreeNode * m_parent;
	union{
		int m_height;
		int m_bf;
		int m_color;
		int m_sign;
	}u;
};

int GetNodeHeightDeep(TreeNode * Node);

bool IsLeftRed(TreeNode * Node);
bool IsRightRed(TreeNode * Node);
void SwapColor(TreeNode * Node);

// bool IsLeftRed(TreeNode * Node);
// bool IsRightRed(TreeNode * Node);

void Show(T& Data);
void Show2(T& Data, int nSign);
void ShowError(T& Data);

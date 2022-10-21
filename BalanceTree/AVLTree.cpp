#include "stdafx.h"
#include "AVLTree.h"


AVLTree::AVLTree(void)
{
}


AVLTree::~AVLTree(void)
{
}

TreeNode * AVLTree::SingleRotateWithLeft(TreeNode* Node)
{
	TreeNode * mid = Node->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	if ( Node->m_lchild )
		Node->m_lchild->m_parent = Node;

	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	mid->u.m_bf = 0;
	Node->u.m_bf = 0;

	return mid;
}

TreeNode * AVLTree::DoubleRotateWithLeft(TreeNode* Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * tmp = mid->m_rchild;

	Node->m_lchild = tmp->m_rchild;
	mid->m_rchild = tmp->m_lchild;

	if ( Node->m_lchild )
		Node->m_lchild->m_parent = Node;
	if ( mid->m_rchild )
		mid->m_rchild->m_parent = mid;

	tmp->m_lchild = mid;
	tmp->m_rchild = Node;

	tmp->m_parent = Node->m_parent;
	Node->m_parent = tmp;
	mid->m_parent = tmp;

	switch ( tmp->u.m_sign )
	{
	case 0:
		{
			mid->u.m_bf = 0;
			Node->u.m_bf = 0;
			break;
		}
	case -1:
		{
			mid->u.m_bf = 0;
			Node->u.m_bf = 1;
			break;
		}
	case 1:
		{
			mid->u.m_bf = -1;
			Node->u.m_bf = 0;
			break;
		}
	}
	tmp->u.m_bf = 0;

	return tmp;
}

TreeNode * AVLTree::SingleRotateWithRight(TreeNode* Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	if ( Node->m_rchild )
		Node->m_rchild->m_parent = Node;

	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	mid->u.m_bf = 0;
	Node->u.m_bf = 0;

	return mid;
}

TreeNode * AVLTree::DoubleRotateWithRight(TreeNode* Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * tmp = mid->m_lchild;

	Node->m_rchild = tmp->m_lchild;
	mid->m_lchild = tmp->m_rchild;

	if ( Node->m_rchild )
		Node->m_rchild->m_parent = Node;
	if ( mid->m_lchild )
		mid->m_lchild->m_parent = mid;

	tmp->m_lchild = Node;
	tmp->m_rchild = mid;

	tmp->m_parent = Node->m_parent;
	Node->m_parent = tmp;
	mid->m_parent = tmp;

	switch ( tmp->u.m_bf )
	{
	case 0:
		{
			mid->u.m_bf = 0;
			Node->u.m_bf = 0;
			break;
		}
	case -1:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = 1;
			break;
		}
	case 1:
		{
			Node->u.m_bf = -1;
			mid->u.m_bf = 0;
			break;
		}
	}
	tmp->u.m_bf = 0;

	return tmp;
}

bool AVLTree::Insert(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;

	while ( _cur )
	{
		if ( Data < _cur->m_Data )
		{
			_parent = _cur;
			_cur = _cur->m_lchild;
		}
		else if ( Data > _cur->m_Data )
		{
			_parent = _cur;
			_cur = _cur->m_rchild;
		}
		else
		{
			return false;
		}
	}

	_cur = new(std::nothrow) TreeNode(Data);
	if ( _cur == NULL )
		return false;
	_cur->m_parent = _parent;

	if ( _parent == NULL )
	{
		m_root = _cur;
		return true;
	}

	bool bLeft = false;
	if ( Data < _parent->m_Data )
	{
		bLeft = true;
		_parent->m_lchild = _cur;
	}
	else
	{
		_parent->m_rchild = _cur;
	}

	do 
	{
		int nHeight = _parent->u.m_height;

		if ( bLeft )
		{
			bLeft = false;

			--_parent->u.m_bf;
			if ( _parent->u.m_bf == 0 )
				break;

			if ( _parent->u.m_bf == -2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				if ( _cur->u.m_bf == -1 )
					*ppParent = SingleRotateWithLeft(_parent);
				else
					*ppParent = DoubleRotateWithLeft(_parent);
				break;
			}
		}
		else
		{
			++_parent->u.m_bf;
			if ( _parent->u.m_bf == 0 )
				break;

			if ( _parent->u.m_bf == 2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				if ( _cur->u.m_bf == 1 )
					*ppParent = SingleRotateWithRight(_parent);
				else
					*ppParent = DoubleRotateWithRight(_parent);
				break;
			}
		}
		
		_cur = _parent;
		_parent = _cur->m_parent;

		if ( _parent == NULL )
			break;
		
		if ( _cur == _parent->m_lchild )
			bLeft = true;

	} while (true);

	return true;
}

TreeNode * AVLTree::BalanceRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	if ( Node->m_lchild )
		Node->m_lchild->m_parent = Node;

	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	mid->u.m_bf = 1;
	Node->u.m_bf = -1;

	return mid;
}

TreeNode * AVLTree::BalanceRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	if ( Node->m_rchild )
		Node->m_rchild->m_parent = Node;
	
	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	mid->u.m_bf = -1;
	Node->u.m_bf = 1;

	return mid;
}

bool AVLTree::Delete(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;
	T _Data = Data;

	while ( _cur )
	{
		if ( _Data < _cur->m_Data )
		{
			_cur = _cur->m_lchild;
		}
		else if ( _Data > _cur->m_Data )
		{
			_cur = _cur->m_rchild;
		}
		else
		{
			if ( _cur->m_rchild == NULL )
				break;
			
			TreeNode * _min = FindMin(_cur->m_rchild);
			_cur->m_Data = _min->m_Data;
			_Data = _min->m_Data;
			_cur = _min;
		}
	}

	if ( _cur == NULL )
		return false;
	
	_parent = _cur->m_parent;
	TreeNode * tmp = _cur->m_lchild;
	if ( tmp )
		tmp->m_parent = _parent;
	
	delete _cur;

	if ( _parent == NULL )
	{	
		m_root = tmp;
		return true;
	}

	bool bLeft = false;
	if ( _cur == _parent->m_lchild )
	{
		bLeft = true;
		_parent->m_lchild = tmp;
	}
	else
	{
		_parent->m_rchild = tmp;
	}

	do 
	{
		if ( bLeft )
		{
			bLeft = false;
			++_parent->u.m_bf;

			if ( _parent->u.m_bf == 2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				switch (_parent->m_rchild->u.m_bf)
				{
				case 0:
					{
						*ppParent = BalanceRotateWithRight(_parent);
						break;
					}
				case 1:
					{
						*ppParent = SingleRotateWithRight(_parent);
						break;
					}
				case -1:
					{
						*ppParent = DoubleRotateWithRight(_parent);
						break;
					}
				}	
				_parent = *ppParent;
			}
		}
		else
		{
			--_parent->u.m_bf;

			if ( _parent->u.m_bf == -2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				switch (_parent->m_lchild->u.m_bf)
				{
				case 0:
					{
						*ppParent = BalanceRotateWithLeft(_parent);
						break;
					}
				case -1:
					{
						*ppParent = SingleRotateWithLeft(_parent);
						break;
					}
				case 1:
					{
						*ppParent = DoubleRotateWithLeft(_parent);
						break;
					}
				}
				_parent = *ppParent;
			}
		}

		if ( _parent->u.m_bf != 0 )
			break;

		_cur = _parent;
		_parent = _cur->m_parent;

		if ( _parent == NULL )
			break;
		
		if ( _cur == _parent->m_lchild )
			bLeft = true;

	} while (true);

	return true;
}

bool AVLTree::Check()
{
	return _Check(m_root, ShowError);
}

bool AVLTree::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetNodeHeightDeep( Node->m_lchild );
	int nRight = GetNodeHeightDeep( Node->m_rchild );

	if ( nLeft > nRight )
	{
		if ( Node->u.m_bf != -1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
		if ( nLeft - nRight > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}
	else
	{
		if ( nLeft == nRight)
		{
			if ( Node->u.m_bf != 0 )
			{
				if( pfShow != NULL )
					pfShow(Node->m_Data);
				return false;
			}
		}
		else if( nLeft < nRight )
		{
			if ( Node->u.m_bf != 1 )
			{
				if( pfShow != NULL )
					pfShow(Node->m_Data);
				return false;
			}
		}

		if ( nRight - nLeft > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool AVLTree::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}

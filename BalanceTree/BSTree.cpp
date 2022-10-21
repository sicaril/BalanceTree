#include "StdAfx.h"
#include "BSTree.h"

BSTree::BSTree(void)
{
}

BSTree::~BSTree(void)
{
}

TreeNode * BSTree::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	if( Node->m_lchild )
		Node->m_lchild->m_parent = Node;

	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height + 1;

	return mid;
}
TreeNode * BSTree::DoubleRotateWithLeft(TreeNode * Node)
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

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height;
	tmp->u.m_height = Node->u.m_height + 1;

	return tmp;
}
TreeNode * BSTree::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	if ( Node->m_rchild )
		Node->m_rchild->m_parent = Node;
	
	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height + 1;

	return mid;
}
TreeNode * BSTree::DoubleRotateWithRight(TreeNode * Node)
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

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height;
	tmp->u.m_height = Node->u.m_height + 1;

	return tmp;
}

bool BSTree::Insert(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;

	while( _cur )
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
		if ( nHeight == _parent->FixHeight() )
			break;

		if ( bLeft )
		{
			bLeft = false;
			if ( _parent->m_lchild->Height() - _parent->m_rchild->Height() == 2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				if ( _cur->m_lchild->Height() > _cur->m_rchild->Height() )
					*ppParent = SingleRotateWithLeft(_parent);
				else
					*ppParent = DoubleRotateWithLeft(_parent);
				break;
			}
		}
		else
		{
			if ( _parent->m_rchild->Height() - _parent->m_lchild->Height() == 2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				if ( _cur->m_rchild->Height() > _cur->m_lchild->Height() )
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

bool BSTree::Delete(T& Data)
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
		int nHeight = _parent->Height();

		if ( bLeft )
		{
			bLeft = false;
			if ( _parent->m_rchild->Height() - _parent->m_lchild->Height() == 2 )
			{
				TreeNode ** ppParent = GetParent(_parent);
				TreeNode * mid = _parent->m_rchild;
				if ( mid->m_rchild->Height() >= mid->m_lchild->Height() )
					*ppParent = SingleRotateWithRight(_parent);
				else
					*ppParent = DoubleRotateWithRight(_parent);
				_parent = *ppParent;
			}
		}
		else
		{
			if ( _parent->m_lchild->Height() - _parent->m_rchild->Height() == 2)
			{
				TreeNode ** ppParent = GetParent(_parent);
				TreeNode * mid = _parent->m_lchild;
				if ( mid->m_lchild->Height() >= mid->m_rchild->Height() )
					*ppParent = SingleRotateWithLeft(_parent);
				else
					*ppParent = DoubleRotateWithLeft(_parent);
				_parent = *ppParent;
			}
		}

		if ( nHeight == _parent->FixHeight() )
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

bool BSTree::Check()
{
	return _Check(m_root , ShowError);
}

bool BSTree::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	//int nLeft = GetHeight( Node->m_lchild );
	//int nRight = GetHeight( Node->m_rchild );

	int nLeft = Node->m_lchild->Height();
	int nRight = Node->m_rchild->Height();

	if ( nLeft > nRight )
	{
		if ( nLeft - nRight > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}
	else
	{
		if ( nRight - nLeft > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool BSTree::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}
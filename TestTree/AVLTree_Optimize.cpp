#include "StdAfx.h"
#include "AVLTree_Optimize.h"

AVLTree_Optimize::AVLTree_Optimize(void)
{
}

AVLTree_Optimize::~AVLTree_Optimize(void)
{
}

TreeNode ** AVLTree_Optimize::GetParentNode(TreeNode* Node)
{
	TreeNode * Parent = Node->m_Parent;

	if ( Parent == NULL )
		return &m_root;

	if( Node->m_Data < Parent->m_Data)
		return &Parent->m_lchild;
	else
		return &Parent->m_rchild;
}

TreeNode* AVLTree_Optimize::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;
	
	mid->m_Parent = Node->m_Parent;
	Node->m_Parent = mid;
	if ( Node->m_lchild )
		Node->m_lchild->m_Parent = Node;

	Node->u.m_bf = 0;
	mid->u.m_bf = 0;
	return mid;
}

TreeNode* AVLTree_Optimize::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	mid->m_Parent = Node->m_Parent;
	Node->m_Parent = mid;
	if ( Node->m_rchild )
		Node->m_rchild->m_Parent = Node;

	Node->u.m_bf = 0;
	mid->u.m_bf = 0;
	return mid;
}

TreeNode* AVLTree_Optimize::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_rchild;

	if ( temp->m_rchild )
		temp->m_rchild->m_Parent = Node;

	Node->m_lchild = temp->m_rchild;
	temp->m_rchild = Node;

	if ( temp->m_lchild )
		temp->m_lchild->m_Parent = mid;

	mid->m_rchild = temp->m_lchild;
	temp->m_lchild = mid;

	temp->m_Parent = Node->m_Parent;
	Node->m_Parent = temp;
	mid->m_Parent = temp;

	switch( temp->u.m_bf )
	{
	case 0:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = 0;
			break;
		}
	case -1:
		{
			Node->u.m_bf = 1;
			mid->u.m_bf = 0;
			break;
		}
	case 1:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = -1;
			break;
		}
	}

	temp->u.m_bf = 0;
	return temp;
}

TreeNode* AVLTree_Optimize::DoubleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_lchild;

	if(temp->m_rchild)
		temp->m_rchild->m_Parent = mid;

	mid->m_lchild = temp->m_rchild;
	temp->m_rchild = mid;

	if(temp->m_lchild)
		temp->m_lchild->m_Parent = Node;

	Node->m_rchild = temp->m_lchild;
	temp->m_lchild = Node;

	temp->m_Parent = Node->m_Parent;
	Node->m_Parent = temp;
	mid->m_Parent = temp;

	switch( temp->u.m_bf )
	{
	case 0:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = 0;
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

	temp->u.m_bf = 0;
	return temp;
}

bool AVLTree_Optimize::Insert(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;

	// Find
	while ( _cur )
	{
		if ( Data < _cur->m_Data )
		{
			_parent = _cur;
			_cur = _cur->m_lchild;
		}
		else if( Data > _cur->m_Data )
		{
			_parent = _cur;
			_cur = _cur->m_rchild;
		}
		else
		{
			return false;
		}
	}

	// Add
	_cur = new TreeNode(Data, _parent);
	if ( _cur == NULL )
		return false;

	if ( _parent == NULL ) // root
	{
		m_root = _cur;
		return true;
	}
	else
	{
		if ( Data < _parent->m_Data )
			_parent->m_lchild = _cur;
		else
			_parent->m_rchild = _cur;
	}

	// Fix
	while( _parent )
	{
		if ( _cur == _parent->m_lchild )
			--_parent->u.m_bf;
		else
			++_parent->u.m_bf;

		if ( _parent->u.m_bf == 0 )
			break;
		else if( _parent->u.m_bf == -1 || _parent->u.m_bf == 1 )
		{
			_cur = _parent;
			_parent = _cur->m_Parent;
		}
		else
		{
			TreeNode ** _grandpa = GetParentNode(_parent);
			if ( _parent->u.m_bf == -2 )
			{
				// 左旋
				if ( _cur->u.m_bf == -1 )
					*_grandpa = SingleRotateWithLeft(_parent);
				else
					*_grandpa = DoubleRotateWithLeft(_parent);
			}
			else
			{
				if ( _cur->u.m_bf == 1 )
					*_grandpa = SingleRotateWithRight( _parent );
				else
					*_grandpa = DoubleRotateWithRight( _parent );
			}

			break;
		}
	}

	return true;
}


TreeNode* AVLTree_Optimize::BalanceRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	bool lleft = IsLeaf( mid->m_lchild );
	bool rleft = IsLeaf( mid->m_rchild );

	// 3层 要么都为叶子 
	// 4层 要么都非叶子 

	if ( lleft && rleft )
	{
		// 左为空 右为空 左单旋 (3层结构)
		Node->m_lchild = mid->m_rchild;
		mid->m_rchild = Node;

		mid->m_Parent = Node->m_Parent;
		Node->m_Parent = mid;
		if ( Node->m_lchild )
			Node->m_lchild->m_Parent = Node;

		Node->u.m_bf = -1;
		mid->u.m_bf = 1;
	}
	else
	{
		// 左不空 左单旋
		Node->m_lchild = mid->m_rchild;
		mid->m_rchild = Node;

		mid->m_Parent = Node->m_Parent;
		Node->m_Parent = mid;
		if ( Node->m_lchild )
			Node->m_lchild->m_Parent = Node;
		
		// 右不空
		mid->u.m_bf = 1;
		Node->u.m_bf = -1;
	}
	return mid;
}

TreeNode* AVLTree_Optimize::BalanceRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	bool lleft = IsLeaf( mid->m_lchild );
	bool rleft = IsLeaf( mid->m_rchild );

	if ( rleft && lleft )
	{
		Node->m_rchild = mid->m_lchild;
		mid->m_lchild = Node;

		mid->m_Parent = Node->m_Parent;
		Node->m_Parent = mid;
		if ( Node->m_rchild )
			Node->m_rchild->m_Parent = Node;

		Node->u.m_bf = 1;
		mid->u.m_bf = -1;
	}
	else
	{
		// 左不空 右单旋
		Node->m_rchild = mid->m_lchild;
		mid->m_lchild = Node;

		mid->m_Parent = Node->m_Parent;
		Node->m_Parent = mid;
		if ( Node->m_rchild )
			Node->m_rchild->m_Parent = Node;
		
		mid->u.m_bf = -1;
		Node->u.m_bf = 1;
	}
	return mid;
}

bool AVLTree_Optimize::Delete(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;

	TreeNode * _min = NULL;
	T _Data = Data; 

	// Find
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
		else if( _Data == _cur->m_Data )
		{
			if ( _cur->m_rchild == NULL )
				break;

			_min = _cur->m_rchild;
			while( _min )
			{
				if ( _min->m_lchild == NULL )
					break;
				_min = _min->m_lchild;
			}

			// 循环删除（替换）最小值
			_cur->m_Data = _min->m_Data;
			_Data = _cur->m_Data;
			_cur = _min;
		}
	}

	if ( _cur == NULL )
		return false;

	// 必无右子树
	_parent = _cur->m_Parent;

	if ( _parent == NULL )
	{
		TreeNode * temp = _cur->m_lchild;

		delete _cur;
		m_root = temp;

		if( temp )
			temp->m_Parent = NULL;
	}
	else
	{
		// 非根节点 先不要破坏树结构 后续会用到 在下一个循环去删除
		_min = _cur;
	}

	// Delete
	while( _parent )
	{
		if ( _cur == _parent->m_lchild )
			++_parent->u.m_bf;
		else
			--_parent->u.m_bf;

		if ( _cur == _min )
		{
			TreeNode * temp = _cur->m_lchild;

			if ( _parent->m_lchild == _cur )
				_parent->m_lchild = temp;
			else
				_parent->m_rchild = temp;

			if( temp )
				temp->m_Parent = _parent;

			delete _cur;
		}
		
		if ( _parent->u.m_bf == 0 )
		{
			_cur = _parent;
			_parent = _parent->m_Parent; 
		}
		else if ( _parent->u.m_bf == 1 || _parent->u.m_bf == -1 )
		{
			break;
		}
		else
		{
			TreeNode ** _prev = GetParentNode(_parent);
			if ( _parent->u.m_bf == -2 )
			{
				// 删右调左
				switch( _parent->m_lchild->u.m_bf )
				{
				case 0:
					{
						* _prev = BalanceRotateWithLeft(_parent);
						break;
					}
				case -1:
					{
						* _prev = SingleRotateWithLeft(_parent);
						break;
					}
				case 1:
					{
						*_prev = DoubleRotateWithLeft( _parent );
						break;
					}
				}
			}
			else
			{
				// 删左调右
				switch( _parent->m_rchild->u.m_bf )
				{
				case 0:
					{
						* _prev = BalanceRotateWithRight(_parent);
						break;
					}
				case 1:
					{
						* _prev = SingleRotateWithRight(_parent);
						break;
					}
				case -1:
					{
						*_prev = DoubleRotateWithRight( _parent );
						break;
					}
				}
			}

			if ( (*_prev)->u.m_bf )
				break;
			
			// 为 0 ，层高变化，则需要向上调整
			_cur = *_prev;
			_parent = _cur->m_Parent;
		}
	}

	return true;
}

bool AVLTree_Optimize::Check()
{
	return _Check(m_root, ShowError);
}

bool AVLTree_Optimize::Check(PF_Show pfShow)
{
	return _Check(m_root, pfShow);
}

bool AVLTree_Optimize::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetNodeHeightDeep( Node->m_lchild );
	int nRight = GetNodeHeightDeep( Node->m_rchild );

	if ( nLeft > nRight )
	{
		if ( Node->u.m_bf != -1 )
		{
			if( pfShow )
				pfShow(Node->m_Data);
			return false;
		}
		if ( nLeft - nRight > 1 )
		{
			if( pfShow )
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
				if( pfShow )
					pfShow(Node->m_Data);
				return false;
			}
		}
		else if( nLeft < nRight )
		{
			if ( Node->u.m_bf != 1 )
			{
				if( pfShow )
					pfShow(Node->m_Data);
				return false;
			}
		}

		if ( nRight - nLeft > 1 )
		{
			if( pfShow )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool AVLTree_Optimize::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}
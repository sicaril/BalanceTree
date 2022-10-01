#include "StdAfx.h"
#include "RBTree_Optimize.h"

RBTree_Optimize::RBTree_Optimize(void)
{
}

RBTree_Optimize::~RBTree_Optimize(void)
{
}

inline bool IsLeftRed(TreeNode * Node)
{
	if ( Node->m_lchild && Node->m_lchild->u.m_color == NS_RED )
		return true;
	return false;
}

inline bool IsRightRed(TreeNode * Node)
{
	if ( Node->m_rchild && Node->m_rchild->u.m_color == NS_RED )
		return true;
	return false;
}

inline void AdjustColor(TreeNode * Node)
{
	Node->u.m_color = NS_RED;
	Node->m_lchild->u.m_color = NS_BLACK;
	Node->m_rchild->u.m_color = NS_BLACK;
}

TreeNode ** RBTree_Optimize::GetParentNode(TreeNode* Node)
{
	TreeNode * Parent = Node->m_Parent;

	if ( Parent == NULL )
		return &m_root;

	if( Node->m_Data < Parent->m_Data)
		return &Parent->m_lchild;
	else
		return &Parent->m_rchild;
}

TreeNode * RBTree_Optimize::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	mid->m_Parent = Node->m_Parent;
	Node->m_Parent = mid;

	if(Node->m_lchild)
		Node->m_lchild->m_Parent = Node;

	return mid;
}

TreeNode * RBTree_Optimize::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_lchild = temp->m_rchild;
	mid->m_rchild = temp->m_lchild;

	temp->m_lchild = mid;
	temp->m_rchild = Node;

	temp->m_Parent = Node->m_Parent;
	mid->m_Parent = temp;
	Node->m_Parent = temp;

	if ( Node->m_lchild )
		Node->m_lchild->m_Parent = Node;
	if ( mid->m_rchild )
		mid->m_rchild->m_Parent = mid;

	return temp;
}

TreeNode * RBTree_Optimize::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	mid->m_Parent = Node->m_Parent;
	Node->m_Parent = mid;
	if( Node->m_rchild )
		Node->m_rchild->m_Parent = Node;

	return mid;
}

TreeNode * RBTree_Optimize::DoubleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_lchild;

	Node->m_rchild = temp->m_lchild;
	mid->m_lchild = temp->m_rchild;

	temp->m_lchild = Node;
	temp->m_rchild = mid;

	temp->m_Parent = Node->m_Parent;
	mid->m_Parent = temp;
	Node->m_Parent = temp;

	if( Node->m_rchild )
		Node->m_rchild->m_Parent = Node;
	if( mid->m_lchild )
		mid->m_lchild->m_Parent = mid;

	return temp;
}

bool RBTree_Optimize::Insert(T& Data)
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
		m_root->u.m_color = NS_BLACK;
		return true;
	}
	else
	{
		if ( Data < _parent->m_Data )
			_parent->m_lchild = _cur;
		else
			_parent->m_rchild = _cur;
	}

	// ����
	while( _parent && _parent->u.m_color == NS_RED )
	{
		TreeNode * _grandpa = _parent->m_Parent;
		if ( _grandpa == NULL )
			break;

		if ( _parent == _grandpa->m_lchild )
		{
			if ( IsRightRed( _grandpa ) )
			{
				AdjustColor(_grandpa);
				_cur = _grandpa;
				_parent = _cur->m_Parent;
			}
			else
			{
				TreeNode ** _grandfa = GetParentNode(_grandpa);
				if ( _cur == _parent->m_lchild )
				{
					*_grandfa = SingleRotateWithLeft(_grandpa);
				}
				else
				{
					*_grandfa = DoubleRotateWithLeft(_grandpa);
				}

				(*_grandfa)->u.m_color = NS_BLACK;
				(*_grandfa)->m_rchild->u.m_color = NS_RED;

				break;
			}
		}
		else
		{
			if ( IsLeftRed( _grandpa ) )
			{
				AdjustColor(_grandpa);
				_cur = _grandpa;
				_parent = _cur->m_Parent;
			}
			else
			{
				TreeNode ** _grandfa = GetParentNode(_grandpa);
				if ( _cur == _parent->m_rchild )
				{
					*_grandfa = SingleRotateWithRight(_grandpa);	
				}
				else
				{
					*_grandfa = DoubleRotateWithRight(_grandpa);
				}

				(*_grandfa)->u.m_color = NS_BLACK;
				(*_grandfa)->m_lchild->u.m_color = NS_RED;

				break;
			}
		}	
	}

	m_root->u.m_color = NS_BLACK;
	return true;
}

bool RBTree_Optimize::Delete(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;

	TreeNode * _min = NULL;
	T  _Data = Data;

	while( _cur )
	{
		if ( _Data < _cur->m_Data )
		{
			_cur = _cur->m_lchild;
		}
		else if( _Data > _cur->m_Data )
		{
			_cur = _cur->m_rchild;
		}
		else if( _Data == _cur->m_Data )
		{
			// ѭ�� �ҵ� �ýڵ�� min 
			if ( _cur->m_rchild == NULL )
				break;

			_min = _cur;

			_cur = _cur->m_rchild;

			// Find Min
			while ( _cur->m_lchild )
			{
				_cur = _cur->m_lchild;
			}

			_min->m_Data = _cur->m_Data;
			_Data = _cur->m_Data;
		}
	}

	if ( _cur == NULL )
	{
		return false;
	}

	_min = _cur;
	_parent = _cur->m_Parent;

	if ( _parent == NULL )
	{
		TreeNode * tmp = _cur->m_lchild;

		delete _cur;

		m_root = tmp;

		if ( m_root )
		{
			m_root->m_Parent = NULL;
			m_root->u.m_color = NS_BLACK;
		}

		return true;
	}
	else
	{

		// ���Ϊ�� or Ϊ������ҶΪ��

		if ( _cur->u.m_color == NS_RED || IsLeftRed(_cur) )
		{
			TreeNode * tmp = _cur->m_lchild;

			if( _parent->m_lchild == _cur )
				_parent->m_lchild = tmp;
			else
				_parent->m_rchild = tmp;

			if ( tmp )
			{
				tmp->m_Parent = _cur->m_Parent;

				if ( tmp->u.m_color == NS_RED )	// �ں�ɾ�� ����
					tmp->u.m_color = NS_BLACK;
			}

			delete _cur;
			return true;
			
		}

		// ������Ҷ �� �ں� ��������ɾ��

	}

	// _cur Ϊ ���Ӽ��ٲ࣬ɾ�������ο���
	// https://www.cnblogs.com/bjorney/p/7956697.html

	bool bSign = true;
	
	while ( _parent && bSign )
	{
		if( _cur->u.m_color == NS_RED )	// ɾ���˺��Ӻ� ���ڼ��� 
		{
			_cur->u.m_color = NS_BLACK;
			break;
		}
		else
		{
			TreeNode ** _grandpa = GetParentNode(_parent);

			if ( _parent->m_lchild == _cur )
			{
				if ( _parent->m_rchild->u.m_color == NS_BLACK )
				{
					if ( IsRightRed(_parent->m_rchild) )
					{
						*_grandpa = SingleRotateWithRight(_parent);

						(*_grandpa)->u.m_color = (*_grandpa)->m_lchild->u.m_color;
						(*_grandpa)->m_lchild->u.m_color = NS_BLACK;
						(*_grandpa)->m_rchild->u.m_color = NS_BLACK;

						bSign = false;
					}
					else if ( IsLeftRed(_parent->m_rchild ) )
					{
						*_grandpa = DoubleRotateWithRight(_parent);

						(*_grandpa)->u.m_color = (*_grandpa)->m_lchild->u.m_color;
						(*_grandpa)->m_lchild->u.m_color = NS_BLACK;

						bSign = false;
					}
					else
					{
						// ��->�ں� or ��->��Ҷ��

						_parent->m_rchild->u.m_color = NS_RED;

						// ��������
					}

					if ( _cur == _min )
					{
						TreeNode * tmp = _cur->m_lchild;

						_parent->m_lchild = tmp;

						if ( tmp )
						{
							tmp->m_Parent = _cur->m_Parent;
						}

						delete _cur;
					}

					_cur = _parent;
					_parent = _cur->m_Parent;
				}
				else
				{
					// �� --> �� --> �ں�
					*_grandpa = SingleRotateWithRight(_parent);

					(*_grandpa)->u.m_color = NS_BLACK;
					(*_grandpa)->m_lchild->u.m_color = NS_RED;

					// ��������

				}
			}
			else
			{
				if ( _parent->m_lchild->u.m_color == NS_BLACK )
				{
					if ( IsLeftRed(_parent->m_lchild) )
					{
						*_grandpa = SingleRotateWithLeft(_parent);

						(*_grandpa)->u.m_color = (*_grandpa)->m_rchild->u.m_color;
						(*_grandpa)->m_lchild->u.m_color = NS_BLACK;
						(*_grandpa)->m_rchild->u.m_color = NS_BLACK;

						bSign = false;
					}
					else if ( IsRightRed(_parent->m_lchild ) )
					{
						*_grandpa = DoubleRotateWithLeft(_parent);

						(*_grandpa)->u.m_color = (*_grandpa)->m_rchild->u.m_color;
						(*_grandpa)->m_rchild->u.m_color = NS_BLACK;

						bSign = false;
					}
					else
					{
						// ˫�� or ��Ҷ��

						_parent->m_lchild->u.m_color = NS_RED;

						// ��������
					}

					if ( _cur == _min )
					{
						TreeNode * tmp = _cur->m_lchild;

						_parent->m_rchild = tmp;

						if ( tmp )
						{
							tmp->m_Parent = _cur->m_Parent;
						}

						delete _cur;
					}

					_cur = _parent;
					_parent = _cur->m_Parent;
				}
				else
				{
					// �� --> �� --> �ں�
					*_grandpa = SingleRotateWithLeft(_parent);

					(*_grandpa)->u.m_color = NS_BLACK;
					(*_grandpa)->m_rchild->u.m_color = NS_RED;

					// ��������
				}
			}
			
		}
	}

	m_root->u.m_color = NS_BLACK;
	return true;

}


bool RBTree_Optimize::Check()
{
	return _Check( m_root );
}

int RBTree_Optimize::GetBlackNodeLeft(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeLeft(Node->m_lchild) + nBlock;
}

int RBTree_Optimize::GetBlackNodeRight(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeRight(Node->m_rchild) + nBlock;
}

bool RBTree_Optimize::_Check(TreeNode * Node)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetBlackNodeLeft(Node->m_lchild);
	int nRight = GetBlackNodeRight(Node->m_rchild);

// 	if ( Node == m_root )
// 	{
// 		printf("left Black Node %d right Black Node %d \r\n",nLeft, nRight);
// 	}

	if( nLeft != nRight)
	{
		printf("left Black Node %d != right Black Node %d \r\n",nLeft, nRight);
		return false;
	}

	if ( Node->u.m_color == NS_RED )
	{
		if ( Node->m_lchild && Node->m_lchild->u.m_color == NS_RED )
		{
			printf("double L red %d-->%d \r\n", Node->m_Data, Node->m_lchild->m_Data );
			return false;
		}

		if ( Node->m_rchild && Node->m_rchild->u.m_color == NS_RED )
		{
			printf("double R red %d-->%d \r\n", Node->m_Data, Node->m_rchild->m_Data );
			return false;
		}
	}

	if ( _Check(Node->m_lchild) == false )
		return false;

	if ( _Check(Node->m_rchild) == false )
		return false;

	return true;
}

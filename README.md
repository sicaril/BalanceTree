# BalanceTree

本项目为平衡树的性能对比C++测试工程，非调用第三方库，包括：

AVL 基于节点高度差的增删逻辑，c++递归实现。
AVL 基于节点高度差的增删逻辑，c++非递归实现。
AVL 基于节点平衡因子的增删逻辑，c++递归实现。
AVL 基于节点平衡因子的增删逻辑，c++非递归实现。
RBT 红黑树的增删逻辑，包含C++多种递归删除方案的实现。
RBT 红黑树的增删逻辑，C++非递归的实现。
各平衡树的校验逻辑，及性能测试。

结论：顺序插入1000w数值，该代码中AVL增删速度要优于红黑树、STL::Set

对应的视频教程：https://space.bilibili.com/1700469421 

## Screenshots
<img width="470" height="308" src="https://github.com/sicaril/BalanceTree/blob/main/result.png"/>

## AVL
<img width="334" height="303" src="https://github.com/sicaril/BalanceTree/blob/main/Document/AVL%20%E5%B9%B3%E8%A1%A1%E5%9B%A0%E5%AD%90%20%E5%A2%9E%E5%88%A0.png"/>
<img width="461" height="252" src="https://github.com/sicaril/BalanceTree/blob/main/Document/AVL%20%E5%B9%B3%E8%A1%A1%E5%9B%A0%E5%AD%90%20%E5%88%A0%E9%99%A4(m%E4%B8%BA0).png"/>

## RBTree
<img width="569" height="426" src="https://github.com/sicaril/BalanceTree/blob/main/Document/RBT%20%E6%8F%92%E5%85%A5.jpg"/>

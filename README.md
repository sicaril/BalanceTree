# BalanceTree
AVL RBTree 红黑树 递归/非递归 增删函数 C++实现

之前仅是想了解下为啥 STL 中选择了红黑树，而非 AVL，两者性能差异有多少。

抽空实现了一些平衡树的增删代码，包括：

AVL 根据节点高度的的递归调用版（AVLTree_Height）

AVL 根据平衡因子的递归调用版(AVLTree_BFactor)

AVL 非递归调用版（AVLTree_Optimize）（性能明显要比递归版有所提高）

RBT 递归调用版（RBTree）（包括两种思路的递归删除函数）

RBT 非递归调用版（RBTree_Optimize）



经测试比对，AVL 的有序插入删除的效率并不比 set 差：


AVL 有录一些视频，感兴趣的可以关注：
https://space.bilibili.com/1700469421

纯玩而已，红黑树后续有时间可能也会录制，随缘 ~

对增删函数做了一些校验排查，若您发现代码有BUG可随时联系我 ~

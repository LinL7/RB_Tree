#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H

template <class T>
class RB_Tree_Node
{
public:
    RB_Tree_Node(T data_in);
    ~RB_Tree_Node(void);    /* C:no parameter */
    RB_Tree_Node* LChild;
    RB_Tree_Node* RChild;
    RB_Tree_Node* Parent;
    T data;
    int color_tag;      /* Red: 1, black: 0 */
};


#endif

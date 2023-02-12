#ifndef RB_TREE_H
#define RB_TREE_H

#include "RB_Tree_Node.h"

template<class T>
class RB_Tree
{
public:
    RB_Tree(T Root_Data);
    ~RB_Tree();
    void Left_Rotate(RB_Tree_Node<T>* current_data);
    void Right_Rotate(RB_Tree_Node<T>* current_data);
    void Insert(T insert data);
    int Delete_Node(T delete_data);
    void Fix_Tree(RB_Tree_Node<T>* current_Node);
    void Erase_Node(RB_Tree_Node<T>* node_Del);
    void Fix_Tree_Delete(RB_Tree_Node<T>* current_Node);
    RB_Tree_Node<T>* Find_Successor_Node(RB_Tree_Node<T>* current_Node);

public:
    RB_Tree_Node<T>* Root_Node;
};

#endif

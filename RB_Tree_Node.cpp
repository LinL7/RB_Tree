#include "RB_Tree_Node.h"

template <class T>
RB_Tree_Node<T>::RB_Tree_Node(T data_in):data(data_in),color_tag(0), LChild(NULL), RChild(NULL), Parent(NULL)
{
    data = data_in;
    color_tag = 1;
}

template <class T>
RB_Tree_Node<T>::~RB_Tree_Node(void)
{
}

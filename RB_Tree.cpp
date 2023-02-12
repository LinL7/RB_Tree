#include <stddef.h> /* NULL */
#include "RB_Tree.h"

template <class T>
RB_Tree<T>::RB_Tree(T Root_Data):Root_Node(NULL)
{
    if(Root_Node == NULL)
    {
        Root_Node = new RB_Tree_Node<T>(Root_Data);
        Root_Node->color_tag = 0;   /* root: black */
    }
}

template<class T>
RB_Tree<T>::~RB_Tree()
{
}

/* insert a node to RB_Tree */
template<class T>
void RB_Tree<T>::Insert(T insert_data)
{
    RB_Tree_Node<T>* temp_Node = Root_Node;
    /* find appropriate place to insert */
    while(temp_Node != NULL)
    {
        if(insert_data > temp_Node->data)
        {
            if(temp_Node->RChild == NULL)
            {
                temp_Node->RChild = new RB_Tree_Node<T>(insert_data);
                temp_Node->RChild->color_tag = 1;   /* insert node: Red */
                temp_Node->RChild->Parent = temp_Node;
                if(temp_Node->color_tag == 1)   /* when parent node color is black, no fix tree */
                {
                    Fix_Tree(temp_Node->RChild);
                }
                break;
            }
            else
            {
                temp_Node = temp_Node->RChild;
            }
        }
        else
        {
            if(temp_Node->LChild == NULL)
            {
                temp_Node->LChild = new RB_Tree_Node<T>(insert_data);
                temp_Node->LChild->color_tag = 1;
                temp_Node->LChild->Parent = temp_Node;
                if(temp_Node->color_tag == 1)   /* when parent node color is black, no fix tree */
                {
                    Fix_Tree(temp_Node->LChild);
                }
                break;
            }
            else
            {
                temp_Node = temp_Node->LChild;
            }
        }
    }
}

/* delete the aim node from RB_Tree */
template<class T>
int RB_Tree<T>::Delete_Node(T delete_data)
{
    RB_Tree_Node<T>* temp_Node = Root_Node;
    /* find the aim node */
    while(temp_Node->data != delete_data && temp_Node != NULL)
    {
        if(delete_data > temp_Node->data)
        {
            temp_Node = temp_Node->RChild;
        }
        else
        {
            temp_Node = temp_Node->LChild;
        }
    }
    if(temp_Node)
    {
        int color_tag = temp_Node->color_tag;
        if(temp_Node->LChild == NULL && temp_Node->RChild == NULL) 
        /* del_a: delete directly */
        {
            delete temp_Node;
        }
        else if(temp_Node->LChild == NULL && temp_Node->RChild != NULL)
        /* del_b_1: temp_node->*Child substitute temp_node->Parent->*Child */
        {
            if(temp_Node != Root_Node)
            {
                if(temp_Node->Parent->LChild == temp_Node)
                {
                    temp_Node->Parent->LChild = temp_Node->RChild;
                    temp_Node->RChild->Parent = temp_Node->Parent;
                }
                else
                {
                    temp_Node->Parent->RChild = temp_Node->LChild;
                    temp_Node->LChild->Parent = temp_Node->Parent;
                }
            }
            else
            {
                Root_Node = temp_Node->RChild;
                temp_Node->RChild->Parent = Root_Node;  /* Reset the Parent pointer */
            }
        }
        else if(temp_Node->LChild != NULL && temp_Node->RChild == NULL)
        /* del_b_2: like del_b_1 */
        {
            if(temp_Node != Root_Node)
            {
                if(temp_Node->Parent->LChild == temp_Node)
                {
                    temp_Node->Parent->LChild = temp_Node->LChild;
                    temp_Node->LChild->Parent = temp_Node->Parent;
                }
                else
                {
                    temp_Node->Parent->RChild = temp_Node->LChild;
                    temp_Node->LChild->Parent = temp_Node->Parent;
                }
            }
            else
            {
                Root_Node = temp_Node->LChild;
                temp_Node->LChild->Parent = Root_Node;  /* Reset the Parent pointer */
            }
        }
        else if(temp_Node->LChild != NULL && temp_Node->RChild != NULL)
        /* del_c: find successor node to substitute the aim node to delete */
        {
            RB_Tree_Node<T>* Successor_Node = Find_Successor_Node(temp_Node);
            if(temp_Node == temp_Node->Parent->LChild)
            {
                temp_Node->Parent->LChild = Successor_Node;
                Successor_Node->RChild = temp_Node->RChild;
                Successor_Node->LChild = temp_Node->LChild;
                Successor_Node->Parent = temp_Node->Parent;
                Successor_Node->color_tag = temp_Node->color_tag;
                if(Successor_Node->RChild)
                {
                    Successor_Node->Parent->LChild = Successor_Node->RChild;
                    Successor_Node->RChild->Parent = Successor_Node->Parent;
                }
            }
            else
            {
                temp_Node->Parent->RChild = Successor_Node;
                Successor_Node->RChild = temp_Node->RChild;
                Successor_Node->LChild = temp_Node->LChild;
                Successor_Node->Parent = temp_Node->Parent;
                Successor_Node->color_tag = temp_Node->color_tag;
                if(Successor_Node->RChild)
                {
                    Successor_Node->Parent->LChild = Successor_Node->RChild;
                    Successor_Node->RChild->Parent = Successor_Node->Parent;
                }
            }
        }

        if(color_tag == 0)
        {
            /* TODO: */
            Fix_Tree_Delete(temp_Node);
        }
    }
    else
    {
        return -1;
    }
   
    return 1;
}

/* After Insert, Fix Tree*/
template <class T>
void RB_Tree<T>::Fix_Tree(RB_Tree_Node<T>*current_Node)
{
    RB_Tree_Node<T>* temp_current_Node = current_Node;
    RB_Tree_Node<T>* uncle_Node;

    while(true)
    {
        if(temp_current_Node->Parent == NULL)
        {
            break;
        }
        if(temp_current_Node->Parent->color_tag == 0)
        {
            /* Insert_1: No Color Change and Rotate */
            break;
        }
        RB_Tree_Node<T>* parent_Node = temp_current_Node->Parent;
        RB_Tree_Node<T>* grandfa_Node = parent_Node->Parent;
        if(grandfa_Node)
        {
            if(parent_Node == grandfa_Node->LChild)
            {
                uncle_Node = grandfa_Node->RChild;
                if(uncle_Node)
                {
                    if(uncle_Node->color_tag == 1)
                    {
                        /* Insert_2: Color Change but no Rotate */
                        uncle_Node->color_tag = 0;
                        parent_Node->color_tag = 0;
                        grandfa_Node->color_tag = 1;
                        temp_current_Node = grandfa_Node;
                    }
                    else if(temp_current_Node == parent_Node->RChild)
                    {
                        /* Insert_3_LR: Left Rotate to Insert_3_LL: Color Change and Right Rotate */
                        temp_current_Node = temp_current_Node->parent_Node;
                        Left_Rotate(temp_current_Node);
                    }
                    else
                    {
                        /* Insert_3_LL: Color Change and Right Rotate */
                        parent_Node->color_tag = 0;
                        grandfa_Node->color_tag = 1;
                        Right_Rotate(grandfa_Node);
                    }
                }
                else
                {
                    if(temp_current_Node == parent_Node->RChild)
                    {
                        temp_current_Node = temp_current_Node->parent_Node;
                        Left_Rotate(temp_current_Node);
                    }
                    else
                    {
                        parent_Node->color_tag = 0;
                        grandfa_Node->color_tag = 1;
                        Right_Rotate(grandfa_Node);
                    }
                }
            }
            else
            {
                uncle_Node = grandfa_Node->LChild;
                if(uncle_Node)
                {
                    if(uncle_Node->color_tag == 1)
                    {   
                        uncle_Node->color_tag = 0;
                        parent_Node->color_tag = 0;
                        grandfa_Node->color_tag = 1;
                        temp_current_Node = grandfa_Node;
                    }
                    else if(temp_current_Node == parent_Node->LChild)
                    {
                        /* Insert_3_RL: ... */
                        temp_current_Node == parent_Node->LChild;
                        Right_Rotate(temp_current_Node);
                    }
                    else
                    {
                        /* Insert_3_RR: ... */
                        parent_Node->color_tag = 0;
                        grandfa_Node->color_tag = 1;
                        Left_Rotate(grandfa_Node);
                    }
                }
                else
                {
                    if(temp_current_Node == parent_Node->LChild)
                    {
                        temp_current_Node == parent_Node->LChild;
                        Right_Rotate(temp_current_Node);
                    }
                    else
                    {
                        parent_Node->color_tag = 0;
                        grandfa_Node->color_tag = 1;
                        Left_Rotate(grandfa_Node);
                    }

                }
            }
        }
    }
    
    Root_Node->color_tag = 0;
}

/* Left Rotate node */
template <class T>
void RB_Tree<T>::Left_Rotate(RB_Tree_Node<T>* current_Node)
{
    RB_Tree_Node<T>* rChild = current_Node->RChild;
    RB_Tree_Node<T>* parent_Node = current_Node->Parent;
    current_Node->RChild = rChild->LChild;
    rChild->Parent = parent_Node;
    if(parent_Node == NULL)
    {
        Root_Node = rChild;
    }
    else if(current_Node == parent_Node->LChild)
    {
        parent_Node->LChild =rChild;
    }
    else
    {
        parent_Node->rChild = rChild;
    }
    rChild->LChild = current_Node;
    current_Node->Parent = rChild;

}

/* Right Rotate node */
template <class T>
void RB_Tree<T>::Right_Rotate(RB_Tree_Node<T>* current_Node)
{
    RB_Tree_Node<T>* lChild= current_Node->LChild;
    RB_Tree_Node<T>* parent_Node = current_Node->parent_Node;
    current_Node->LChild = lChild->RChild;
    lChild->RChild =current_Node;
    if(parent_Node == NULL)
    {
        Root_Node = lChild;
    }
    else if(current_Node = parent_Node->LChild)
    {
        parent_Node->LChild = lChild;
    }
    else
    {
        parent_Node->RChild = lChild;
    }
    current_Node->Parent = lChild;
    lChild->parent_Node = parent_Node;

}

/* find the inorder successor node */
template<class T>
RB_Tree_Node<T>* RB_Tree<T>::Find_Successor_Node(RB_Tree_Node<T>* current_Node)
{
    RB_Tree_Node<T>* temp_Node = current_Node->RChild;
    while(temp_Node->LChild != NULL)
    {
        temp_Node = temp_Node->LChild;
    }
    return temp_Node;
}

/* free node */
template<class T>
void RB_Tree<T>::Erase_Node(RB_Tree_Node<T>* node_Del)
{
    if(node_Del->Parent && node_Del->Parent->LChild == node_Del)
    {
        node_Del->Parent->LChild = NULL;
    }
    else if(node_Del->Parent && node_Del->Parent->RChild == node_Del)
    {
        node_Del->Parent->RChild = NULL;
    }
    node_Del->Parent = NULL;
    node_Del->LChild = NULL;
    node_Del->RChild = NULL;
    node_Del->data = NULL;
    delete node_Del;
}

    

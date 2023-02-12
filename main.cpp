/*#include <tchar.h>  * _tmain(), _TCHAR */

#include "RB_Tree.h"

int main(int argc, char* argv[])
{
    RB_Tree<double>* m_RB_Tree = new RB_Tree<double>(1.0);
    for(int i = 2; i < 10; i++)
    {
        double a = i;
        m_RB_Tree->Insert(a);
    }
    for(int i = 9; i > 2; i--)
    {
        double a = i;
        m_RB_Tree->Delete_Node(a);
    }
    return 0;
}

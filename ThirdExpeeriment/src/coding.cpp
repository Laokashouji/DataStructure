#include <cstring>
#include "coding.h"

void encoding(Node root, char **coding_table, char code[], int t)
{
    if (root.is_leave())
    {
        code[t] = '\0';
        strcpy(coding_table[root.data()], code);
        return;
    }
    if (root.left() != NULL)
    {
        code[t] = 0;
        encoding(*(root.left()), coding_table, code, t + 1);
    }
    if (root.right() != NULL)
    {
        code[t] = 1;
        encoding(*(root.right()), coding_table, code, t + 1);
    }
    return;
}
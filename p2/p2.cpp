#include <iostream>
#include <cstdlib>
#include "p2.h"
#include "recursive.h"

using namespace std;

int size(list_t list)
{
    if (list_isEmpty(list))
    {
        return 0;
    }
    else
    {
        return (1 + size(list_rest(list)));
    }
}

int sum(list_t list)
{
    if (list_isEmpty(list))
    {
        return 0;
    }
    else
    {
        return list_first(list)+sum(list_rest(list));    
    }
}

int product(list_t list)
{
    if (list_isEmpty(list))
    {
        return 1;
    }
    else
    {
        return list_first(list)*product(list_rest(list));    
    }
}

int accumulate(list_t list, int (*fn)(int, int), int base)
{
    if (list_isEmpty(list))
    {
        return base;
    }
    else
    {
        return fn(list_first(list),accumulate(list_rest(list),fn,base));
    }
}

static list_t reverse_helper(list_t list,list_t list_return)
{
    if(!list_isEmpty(list))
    {
        return reverse_helper(list_rest(list),list_make(list_first(list),list_return));
    }
    return list_return;
}

list_t reverse(list_t list)
{
    return reverse_helper(list,list_make());
}

list_t list_make(list_t list,int n)
{
    return(reverse(list_make(n,reverse(list))));
}

static list_t append_helper(list_t first, list_t second)
{
    if (list_isEmpty(first))
    {
        return second;
    }
    return append_helper(list_rest(first),list_make(list_first(first),second));
}

list_t append(list_t first, list_t second)
{
    return append_helper(reverse(first),second);
}

list_t filter_odd(list_t list)
{
    if(list_isEmpty(list))
    {
        return list;
    }
    else if(list_first(list)%2 != 0)
    {
        return list_make(list_first(list),filter_odd(list_rest(list)));
    }
    else
    {
        return filter_odd(list_rest(list));
    }
}

list_t filter_even(list_t list)
{
    if(list_isEmpty(list))
    {
        return list;
    }
    else if(list_first(list)%2 == 0)
    {
        return list_make(list_first(list),filter_even(list_rest(list)));
    }
    else
    {
        return filter_even(list_rest(list));
    }
}

list_t filter(list_t list, bool (*fn)(int))
{
        if(list_isEmpty(list))
    {
        return list;
    }
    else if(fn(list_first(list)))
    {
        return list_make(list_first(list),filter(list_rest(list),fn));
    }
    else
    {
        return filter(list_rest(list),fn);
    }
}

static list_t insert_list_helper(list_t first, list_t second, list_t rest, unsigned int n)
{
    if (n > 0)
    {
        return (insert_list_helper(list_rest(first),second,list_make(rest,list_first(first)),n-1));
    }
    else
    {
        return append(append(reverse(first),second),reverse(rest));
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
    n = n > (unsigned)size(first) ? size(first) : n;
    return insert_list_helper(reverse(first),second,list_make(),size(first)-n);
}

list_t chop(list_t list, unsigned int n)
{
    if((unsigned)size(list) > n)
    {
        return list_make(list_first(list),chop(list_rest(list),n));
    }
    else
    {
        return list_make();
    }
}

int tree_sum(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return 0;
    }
    else
    {
        return tree_elt(tree)+ tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}

bool tree_search(tree_t tree, int key)
{
    if (tree_isEmpty(tree))
    {
        return false;
    }
    else if (tree_elt(tree) == key)
    {
        return true;
    }
    else
    {
        return tree_search(tree_left(tree),key)||tree_search(tree_right(tree),key);
    }
}

int depth(tree_t tree)
{
    if(tree_isEmpty(tree))
    {
        return false;
    }
    else
    {
        return 1+(depth(tree_left(tree))>depth(tree_right(tree))?depth(tree_left(tree)):depth(tree_right(tree)));
    }
}

int tree_min(tree_t tree)
{
    if(tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree)))
    {
        return tree_elt(tree);
    }
    else if (tree_isEmpty(tree_left(tree)))
    {
        return tree_elt(tree)<tree_min(tree_right(tree))?tree_elt(tree):tree_min(tree_right(tree));
    }
    else if (tree_isEmpty(tree_right(tree)))
    {
        return tree_elt(tree)<tree_min(tree_left(tree))?tree_elt(tree):tree_min(tree_left(tree));
    }
    else
    {
        int min1 = tree_min(tree_left(tree))<tree_min(tree_right(tree))?tree_min(tree_left(tree)):tree_min(tree_right(tree));
        return tree_elt(tree)<min1 ? tree_elt(tree):min1;
    }
}

list_t traversal(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return list_make();
    }
    else
    {
        return append((list_make(traversal (tree_left(tree)),tree_elt(tree))),traversal(tree_right(tree)));
    }
}

bool tree_hasPathSum(tree_t tree, int sum)
{
    if(tree_isEmpty(tree))
    {
        return (sum == 0);
    }
    else if(tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree)))
    {
        return tree_hasPathSum(tree_right(tree),sum-tree_elt(tree));
    }
    else if(!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
    {
        return tree_hasPathSum(tree_left(tree),sum-tree_elt(tree));
    }
    else
    {
        return (tree_hasPathSum(tree_left(tree),sum-tree_elt(tree))
              ||tree_hasPathSum(tree_right(tree),sum-tree_elt(tree)));
    }
}

bool covered_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A))
    {
        return true;
    }
    else if (tree_isEmpty(B))
    {
        return false;
    }
    else if (tree_elt(A) == tree_elt(B))
    {
        return covered_by(tree_left(A),tree_left(B))
              &&covered_by(tree_right(A),tree_right(B));
    }
    else
    {
        return false;
    }
}

static bool contained_by_helper(tree_t A, tree_t B) // check if they are exactly the same.
{
    if(tree_isEmpty(A)!=tree_isEmpty(B))
    {
        return false;
    }
    else if (tree_isEmpty(A) && tree_isEmpty(B))
    {
        return true;
    }
    else
    {
        if (tree_elt(A)!=tree_elt(B))
        {
            return false;
        }
        else
        {
            return contained_by_helper(tree_left(A),tree_left(B))&&contained_by_helper(tree_right(A),tree_right(B));
        }
    }
}


bool contained_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A))
    {
        return true;
    }
    else if (tree_isEmpty(B))
    {
        return false;
    }
    else if (tree_elt(A)==tree_elt(B))
    {
        if (contained_by_helper(A,B))
        {
            return true;
        }
    }
    return contained_by(A,tree_left(B))||contained_by(A,tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return tree_make(elt,tree_make(),tree_make());
    }
    else if (elt < tree_elt(tree))
    {
        if (tree_isEmpty(tree_left(tree)))
        {
            return tree_make(tree_elt(tree),tree_make(elt,tree_make(),tree_make()),tree_right(tree));
        }
        else
        {
            return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree));
        }
    }
    else
    {
        if (tree_isEmpty(tree_right(tree)))
        {
            return tree_make(tree_elt(tree),tree_left(tree),tree_make(elt,tree_make(),tree_make()));
        }
        else
        {
            return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));
        }
    }
}

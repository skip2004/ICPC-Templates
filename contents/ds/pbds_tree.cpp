#include <bits/extc++.h>
using namespace __gnu_pbds;
template<class T> // insert, erase, join, order_of_key, find_by_order(return iterator), order is 0-index
using Tree = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>

#endif

template < typename Product >
struct Bestsellers {

    class NodeOfAVL
    {
    public:

        NodeOfAVL ( size_t _key,
                    NodeOfAVL * _left,
                    NodeOfAVL * _right,
                    size_t _height,
                    size_t _countOfChildren,
                    size_t _sumOfChildren)
        {
            key             = _key;
            left            = _left;
            right           = _right;
            height          = _height;
            countOfChildren = _countOfChildren;
            sumOfChildren   = _sumOfChildren;
        }


        size_t key;
        NodeOfAVL * left;
        NodeOfAVL * right;
        size_t height;
        size_t countOfChildren;
        std::vector<Product> products;
        size_t sumOfChildren;

    };


    class AVL
    {
    public:
        // constructor
        AVL()
        {
            root = nullptr;
            amountOfNodes = 0;
        }
        // destructor
        ~AVL()
        {
            deleteSubTree ( root );
        }
        // AVLInsert
        void AVLInsert ( const std::pair<size_t, Product> & product )
        {
            root = insertSubtree( product, root );
        }
        // AVLRemove
        void AVLRemove(const std::pair<size_t, Product> & product)
        {
            root = removeNode(product, root, 0);
        }
        // rank
        size_t rank ( const std::pair<size_t, Product> & product ) const
        {
            return rankInSubtree ( product, root, 0);
        }
        // product
        Product & product ( size_t rank ) const
        {
            return productInSubtree ( rank, root );
        }
        // sold
        size_t sold ( size_t rank ) const
        {
            return soldInSubtree ( rank, root );
        }
        // soldFromTo in subtree
        size_t sold ( size_t from, size_t to ) const
        {
            if ( root == nullptr )
                throw std::out_of_range ("");

            return sumAfter ( from, root, 0 ) - sumAfter ( to, root, 0 ) + sold ( to );

        }
        // first_same
        size_t first_same ( size_t rank ) const {
            return rank - first_sameInSubtree(rank, root);
        }
        // last_same
        size_t last_same ( size_t rank ) const
        {
            return rank + last_sameInSubtree ( rank, root );
        }


        size_t amountOfNodes;
    private:
        NodeOfAVL * root;

        // last_sameInSubtree
        size_t last_sameInSubtree ( size_t rank, NodeOfAVL * vertex ) const
        {
            if ( vertex == nullptr )
                throw std::out_of_range ("");

            size_t counter = vertex -> right == nullptr ? 1 : vertex -> right -> countOfChildren + 2;
            if ( rank <= counter + vertex -> products . size () - 1 && rank >= counter )
            {
                return ( vertex -> products . size () + counter - 1 )  - rank;
            }
            if ( counter < rank )
            {
                size_t newRank = (rank - counter) - (vertex -> products . size() - 1);
                return last_sameInSubtree(newRank, vertex -> left);
            }
            return last_sameInSubtree(rank, vertex -> right);
        }


        // first_sameInSubtree
        size_t first_sameInSubtree ( size_t rank, NodeOfAVL * vertex ) const
        {
            if ( vertex == nullptr )
                throw std::out_of_range ("");

            size_t counter = vertex -> right == nullptr ? 1 : vertex -> right -> countOfChildren + 2;
            if ( rank <= counter + vertex -> products . size () - 1 && rank >= counter )
            {
                return rank - counter;
            }
            if ( counter < rank )
            {
                size_t newRank = (rank - counter) - (vertex -> products . size() - 1);
                return first_sameInSubtree(newRank, vertex -> left);
            }
            return first_sameInSubtree(rank, vertex -> right);
        }

        // sumAfter
        size_t sumAfter ( size_t rank, NodeOfAVL * vertex, size_t counter ) const
        {
            size_t ourRank = vertex -> right == nullptr ? 1 : vertex -> right -> countOfChildren + 2;
            if ( rank <= ourRank + vertex -> products . size () - 1 && rank >= ourRank )
            {
                return ( (rank - ourRank + 1) * vertex -> key ) + ( vertex -> right == nullptr ? 0 : vertex -> right -> sumOfChildren ) + counter;
            }
            if ( ourRank < rank )
            {
                size_t newRank = (rank - ourRank) - (vertex -> products . size() - 1);
                counter += vertex -> products . size () * vertex -> key + ( vertex -> right == nullptr ? 0 : vertex -> right -> sumOfChildren );
                return sumAfter(newRank, vertex -> left, counter);
            }
            return sumAfter(rank, vertex -> right, counter);

        }


        // soldInSubtree
        size_t soldInSubtree ( size_t rank, NodeOfAVL * vertex ) const
        {
            if ( vertex == nullptr )
                throw std::out_of_range ("");

            size_t counter = vertex -> right == nullptr ? 1 : vertex -> right -> countOfChildren + 2;
            if ( rank <= counter + vertex -> products . size () - 1 && rank >= counter )
            {
                return vertex -> key;
            }
            if ( counter < rank )
            {
                size_t newRank = (rank - counter) - (vertex -> products . size() - 1);
                return soldInSubtree(newRank, vertex -> left);
            }
            return soldInSubtree(rank, vertex -> right);
        }

        // productInSubtree
        Product & productInSubtree ( size_t rank, NodeOfAVL * vertex ) const
        {
            if ( vertex == nullptr )
                throw std::out_of_range ("");

            size_t counter = vertex -> right == nullptr ? 1 : vertex -> right -> countOfChildren + 2;
            if ( rank <= counter + vertex -> products . size () - 1 && rank >= counter )
            {
                return vertex -> products [rank - counter];
            }
            if ( counter < rank )
            {
                size_t newRank = (rank - counter) - (vertex -> products . size() - 1);
                return productInSubtree(newRank, vertex -> left);
            }
            return productInSubtree(rank, vertex -> right);
        }

        // rankIn
        size_t rankInSubtree ( const std::pair<size_t, Product> & product, NodeOfAVL * vertex, size_t counter ) const
        {
            if ( vertex == nullptr )
                throw std::out_of_range ("");
            if ( product . first < vertex -> key )
            {
                counter +=  ( vertex -> right == nullptr ? ( vertex -> products . size () ) : ( vertex -> right -> countOfChildren + 1 + vertex -> products . size () ) );
                return rankInSubtree( product, vertex -> left, counter );
            } else if ( product . first > vertex -> key )
            {
                return rankInSubtree( product, vertex -> right, counter );
            } else
            {
                counter += vertex -> right == nullptr ? 1 : vertex -> right -> countOfChildren + 2;
                if ( vertex -> products . size () > 1 )
                {
                    for (  auto iter = vertex -> products . begin (); iter != vertex -> products . end (); ++iter )
                    {
                        if ( *iter == product . second )
                        {
                            break;
                        }
                        counter++;
                    }
                }
                return counter;
            }
        }


        // removeNode
        NodeOfAVL * removeNode(const std::pair<size_t, Product> & product, NodeOfAVL *vertex, bool deleteWholeElement ) {
            NodeOfAVL *temp;

            // 404 not found
            if (vertex == nullptr) {
                return nullptr;
            } else if (product.first < vertex->key)        // finding the element left
            {
                vertex->left = removeNode(product, vertex->left, deleteWholeElement);
            } else if (product.first > vertex->key)        // finding the element right
            {
                vertex->right = removeNode(product, vertex->right, deleteWholeElement);
            } else if (vertex->left && vertex->right)        // element found with 2 children
            {
                if (  vertex -> products . size () > 1 )
                {
                    for (auto iter = vertex->products.begin(); iter != vertex->products.end(); ++iter)  // finding needed element
                    {
                        if (*iter == product.second)     // found needed element
                        {
                            vertex->products.erase(iter);
                            break;
                        }
                    }
                    amountOfNodes--;
                } else {
                temp = findMin(vertex -> right);
                vertex -> products = temp -> products;
                vertex -> key = temp -> key;
                vertex -> right = removeNode ( std::pair<size_t, Product>(vertex -> key, product .second ), vertex -> right, 1); // remove the last min list
                }
            }
            else {                              // 0 or 1 children
                if (deleteWholeElement || vertex->products.size() == 1)   // if deleteWhole (we don't care about count of products) or just one product we found
                {
                    temp = vertex;
                    if (vertex->right == nullptr) // if there is something
                    {
                        vertex = vertex->left;
                    } else if (vertex->left == nullptr) {
                        vertex = vertex->right;
                    }
                    amountOfNodes--;
                    delete temp;                    // delete needed element
                    temp = nullptr;
                } else  // we need to delete only one product
                {
                    for (auto iter = vertex->products.begin(); iter != vertex->products.end(); ++iter)  // finding needed element
                    {
                        if (*iter == product.second)     // found needed element
                        {
                            vertex->products.erase(iter);
                            break;
                        }
                    }
                    amountOfNodes--;
                }
            }

            if ( vertex == nullptr )
                return vertex;

            vertex -> height = whatIsHeight(vertex);
            vertex -> countOfChildren = whatIsCountOfChildren(vertex);
            vertex -> sumOfChildren = whatIsSumOfChildren(vertex);

            // Left node is deleted (delta = +2)
            if (whatIsDelta(vertex) == 2) // x -> delta == +2
            {
                if (whatIsDelta(vertex->right) == 1)  // y -> delta == + 1
                    return leftRotation(vertex);
                else if (whatIsDelta(vertex->right) == 0) // y -> delta == 0
                    return leftRotation(vertex);
                else            // y -> delta == - 1
                    return rightLeftRotate(vertex);
            } else if (whatIsDelta(vertex) == -2)
            {
                if (whatIsDelta(vertex -> left) == -1) // y -> delta == -1
                    return rightRotation(vertex);
                else if (whatIsDelta(vertex -> left) == 0) // y -> delta == 0
                    return rightRotation(vertex);
                else   // y -> delta == +1
                    return leftRightRotate(vertex);
            }

            return vertex;
        }


        // insertSubtree
        NodeOfAVL * insertSubtree (const std::pair<size_t, Product> & product, NodeOfAVL *vertex ) {

            if ( vertex == nullptr ) {
                amountOfNodes++;

                NodeOfAVL * tm = new NodeOfAVL ( product . first,
                                                 nullptr,
                                                 nullptr,
                                                 0,
                                                 0,
                                                 product . first);
                tm -> products . push_back ( product . second );
                vertex = tm;
                return vertex;
            } else if ( product . first < vertex -> key) // go left if newNode -> key is less
            {
                vertex->left = insertSubtree ( product, vertex->left ); // insert left

                if ( whatIsDelta ( vertex ) == -2) // if delta ( x ) == - 2
                {
                    if ( whatIsDelta( vertex -> left ) == -1)
                        vertex = rightRotation(vertex );
                    else
                        vertex = leftRightRotate(vertex );
                }
            } else if (product.first > vertex->key) // go right if newNode -> key is bigger
            {
                vertex->right = insertSubtree(product, vertex->right); // insert right
                if (whatIsDelta(vertex) == 2) // if delta ( x ) == 2
                {
                    if (whatIsDelta(vertex -> right) == 1)
                        vertex = leftRotation(vertex);
                    else
                        vertex = rightLeftRotate(vertex);
                }
            } else if ( product . first == vertex -> key ) // ==
            {
                vertex -> countOfChildren++;
                vertex -> sumOfChildren += vertex -> key;
                vertex -> products . push_back (product.second);
                amountOfNodes++;
                return vertex;
            }


            vertex -> height = whatIsHeight(vertex);
            vertex -> countOfChildren = whatIsCountOfChildren(vertex);
            vertex -> sumOfChildren = whatIsSumOfChildren ( vertex );

            return vertex;
        }


        // deleteSubTree
        void deleteSubTree ( NodeOfAVL * vertex )
        {
            if ( vertex == nullptr )
                return;
            if ( vertex -> left != nullptr )
                deleteSubTree(vertex->left);
            if ( vertex -> right != nullptr )
                deleteSubTree(vertex->right);
            delete vertex;
            vertex = nullptr;
        }

        // leftRotation
        NodeOfAVL * leftRotation(NodeOfAVL *x) {
            NodeOfAVL *y = x->right;
            x->right = y->left;
            y->left = x;

            x -> height = whatIsHeight(x);
            x -> countOfChildren = whatIsCountOfChildren(x);
            x -> sumOfChildren = whatIsSumOfChildren(x);
            y -> sumOfChildren = whatIsSumOfChildren(y);
            y -> height = whatIsHeight(y);
            y -> countOfChildren = whatIsCountOfChildren(y);
            return y;
        }

        // rightRotation
        NodeOfAVL *rightRotation(NodeOfAVL *x) {
            NodeOfAVL *y = x->left;
            x->left = y->right;
            y->right = x;

            x -> height = whatIsHeight(x);
            x -> countOfChildren = whatIsCountOfChildren(x);
            x -> sumOfChildren = whatIsSumOfChildren(x);
            y -> sumOfChildren = whatIsSumOfChildren(y);
            y -> height = whatIsHeight(y);
            y -> countOfChildren = whatIsCountOfChildren(y);
            return y;
        }

        // leftRightRotate
        NodeOfAVL *leftRightRotate(NodeOfAVL *x) {
            x->left = leftRotation(x->left);
            return rightRotation(x);
        }
        //rightLeftRotate
        NodeOfAVL *rightLeftRotate(NodeOfAVL *x) {
            x->right = rightRotation(x->right);
            return leftRotation(x);
        }
        // whatIsDelta
        int whatIsDelta ( NodeOfAVL * vertex )
        {
            if ( vertex == nullptr )
                return 0;

            return (vertex -> right == nullptr ? 0 : vertex -> right -> height + 1 ) - ( vertex -> left == nullptr ? 0 : vertex -> left -> height + 1 );
        }
        // whatIsHeight
        size_t whatIsHeight ( NodeOfAVL * vertex )
        {
            if ( vertex == nullptr )
                return 0;

            if ( vertex -> left == nullptr && vertex -> right == nullptr )
                return 0;

            return fmax((vertex->left == nullptr ? 0 : vertex->left->height),
                 (vertex->right == nullptr ? 0 : vertex->right->height)) + 1;

        }
        // whatIsCountOfChildren
        size_t whatIsCountOfChildren ( NodeOfAVL * vertex )
        {
            if ( vertex == nullptr )
                return 0;

            return (vertex -> left  == nullptr ? 0 : ( vertex -> left -> countOfChildren + 1) ) +
                   (vertex -> right == nullptr ? 0 : ( vertex -> right -> countOfChildren + 1) ) + ( vertex->products. size() - 1 );

        }
        // findMin
        NodeOfAVL * findMin ( NodeOfAVL * temp )
        {
            if ( temp == nullptr )
                return nullptr;
            else if ( temp -> left == nullptr )
                return temp;
            else
                return findMin ( temp -> left );
        }
        // whatIsSumOfChildren
        size_t whatIsSumOfChildren ( NodeOfAVL * vertex )
        {
            if ( vertex == nullptr )
                return 0;

            return (vertex -> left  == nullptr ? 0 : ( vertex -> left -> sumOfChildren ) ) +
                   (vertex -> right == nullptr ? 0 : ( vertex -> right -> sumOfChildren) ) + ( vertex->products. size() * vertex -> key );
        }
    };


    AVL treeProducts;
    std::unordered_map<Product, size_t> mapProducts;

    // The total number of tracked products
    size_t products() const
    {
        return treeProducts . amountOfNodes;
    }

    void sell(const Product& p, size_t amount)
    {
        auto iter = mapProducts . find(p);
        if ( iter != mapProducts . end () ) // we have found the element
        {
            treeProducts . AVLRemove (std::pair<size_t,Product>(iter -> second, p) );
            iter -> second += amount;
            treeProducts .AVLInsert(std::pair<size_t, Product>( iter -> second, p ));
        } else {                            // we have not found the element, we need to create a new one
            mapProducts . insert ( std::pair<Product, size_t> ( p, amount ) );
            treeProducts . AVLInsert(std::pair<size_t, Product> (amount, p) );
        }
    }

    // The most sold product has rank 1
    size_t rank(const Product& p) const
    {
        auto iter = mapProducts . find ( p );
        if ( iter != mapProducts . end () )
        {
            return treeProducts . rank ( std::pair<size_t, Product>(iter -> second, p) );
        } else {
            throw std::out_of_range ("");
        }
    }

    const Product & product (size_t rank) const
    {
        if ( rank < 1 || rank > treeProducts . amountOfNodes )
            throw std::out_of_range ("");
        else {
            return treeProducts . product ( rank );
        }
    }

    // How many copies of product with given rank were sold
    size_t sold(size_t rank) const
    {
        if ( rank < 1 || rank > treeProducts . amountOfNodes )
            throw std::out_of_range ("");
        else {
            return treeProducts . sold ( rank );;
        }
    }
    // The same but sum over interval of products (including from and to)
    // It must hold: sold(x) == sold(x, x)
    size_t sold(size_t from, size_t to) const
    {
        if ( from > to || from < 1 || from > treeProducts . amountOfNodes || to < 1 || to > treeProducts . amountOfNodes )
            throw std::out_of_range ("");
        else {
            return treeProducts . sold ( to,  from );
        }
    }

    // Bonus only, ignore if you are not interested in bonus
    // The smallest (resp. largest) rank with sold(rank) == sold(r)
    size_t first_same(size_t r) const {
        if (r < 1 || r > treeProducts.amountOfNodes)
            throw std::out_of_range("");
        else {
            return treeProducts . first_same ( r );
        }
    }

    size_t last_same(size_t r) const {
        if (r < 1 || r > treeProducts.amountOfNodes)
            throw std::out_of_range("");
        else {
            return treeProducts.last_same(r);
        }
    }


};

#ifndef __PROGTEST__

void test1() {
    Bestsellers<std::string> T;
    T.sell("coke", 32);
    T.sell("bread", 1);
    assert(T.products() == 2);
    T.sell("ham", 2);
    T.sell("mushrooms", 12);

    assert(T.products() == 4);
    assert(T.rank("ham") == 3);
    assert(T.rank("coke") == 1);
    assert(T.sold(1, 3) == 46);
    assert(T.product(2) == "mushrooms");

    T.sell("ham", 11);
    assert(T.products() == 4);
    assert(T.product(2) == "ham");
    assert(T.sold(2) == 13);
    assert(T.sold(2, 2) == 13);
    assert(T.sold(1, 2) == 45);
}

void test2() {
# define CATCH(expr) \
  try { expr; assert(0); } catch (const std::out_of_range&) { assert(1); };

    Bestsellers<std::string> T;
    T.sell("coke", 32);
    T.sell("bread", 1);

    CATCH(T.rank("ham"));
    CATCH(T.product(3));
    CATCH(T.sold(0));
    CATCH(T.sold(9));
    CATCH(T.sold(0, 1));
    CATCH(T.sold(3, 2));
    CATCH(T.sold(1, 9));



#undef CATCH
}

int main() {
    test1();
    test2();

}

#endif



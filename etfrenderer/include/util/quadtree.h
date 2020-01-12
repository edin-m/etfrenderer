#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <algorithm>

template <typename T, int OBJECTS_PER_NODE>
class Quadtree
{
private:

    Quadtree *m_ul, *m_ur, *m_dl, *m_dr;
    std::vector<T> objects;
public:
    Quadtree() :
        m_ul(NULL),
        m_ur(NULL),
        m_dl(NULL),
        m_dr(NULL)
    {

    }

    ~Quadtree()
    {
        if( m_ul != NULL )
            delete m_ul;
        if( m_ur != NULL )
            delete m_ur;
        if( m_dl != NULL )
            delete m_dl;
        if( m_dr != NULL )
            delete m_dr;
    }

    bool contains(const T& object)
    {
        if( std::find(objects.begin(),
                      objects.end(),
                      object) != objects.end())
            return true;

        return false;
    }

};

#endif // QUADTREE_H

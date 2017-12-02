#ifndef VECTOR_LIST_PROJECT_LIST_H
#define VECTOR_LIST_PROJECT_LIST_H

#include <memory>

template<typename T, class allocator>
class List
{
private:
    struct node
    {
        node();
        node(const T &data_b);
        T data_a;
        node *next;
        node *previous;
    };

    typename allocator::template rebind<node>::other nodeRebinded;
    size_t _size;
    node *head;
    node *tail;

public:

    List();
    ~List();

    List(const List &other);
    List &operator=(const List &other);

    void push_back(const T &adding);
    void remove(const T &removing);
    void insert(typename List <T, allocator>::iterator inserting, const T &value);

    size_t size()const;

    bool isEmpty();

    class iterator : public std::iterator<std::bidirectional_iterator_tag,node>
    {
    private:

    public:
        node *node_a;

        iterator(node* node_b = nullptr);

        T &operator*();

        bool operator==(const iterator &it) const;
        bool operator!=(const iterator &it) const;

        node *operator->()
        {
            return this->node_a;
        }

        iterator &operator++()
        {
            node_a = this->node_a->next;
            return *this;
        }

        iterator &operator++(int)
        {
            iterator temp = *this;
            this->node_a = this->node_a->next;
            return temp;

        }

        iterator &operator--()
        {
            node_a = this->node_a->previous;
            return *this;
        }

        iterator &operator--(int)
        {
            iterator temp = *this;
            this->node_a = this->node_a->previous;
            return temp;
        }
    };

    iterator begin() const
    {
        return iterator(this->head);
    }

    iterator end() const
    {
        return iterator(this->tail->next);
    }
};

template<typename T, class allocator>
List<T, allocator>::node::node() : data_a{ 0 }, next{ nullptr }, previous{ nullptr } {

}

template<typename T, class allocator>
List<T, allocator>::node::node(const T &data_b) : data_a{ data_b }, next{ nullptr }, previous{ nullptr } {

}

template<typename T, class allocator>
List<T, allocator>::iterator::iterator(List::node *node_b) : node_a{ node_b } {

}

template<typename T, class allocator>
T &List<T, allocator>::iterator::operator*() {
    return this->node_a->data_a;
}

template<typename T, class allocator>
bool List<T, allocator>::iterator::operator==(const List::iterator &it) const {
    return this->node_a == it.node_a;
}

template<typename T, class allocator>
bool List<T, allocator>::iterator::operator!=(const List::iterator &it) const {
    return this->node_a != it.node_a;
}

template<typename T, class allocator>
List<T, allocator>::List() : _size{ 0 }, head{ nullptr }, tail{nullptr} {

}

template<typename T, class allocator>
List<T, allocator>::~List() {
    node *walker = this->head;
    while (walker != this->tail)
    {
        node *walkerNext = walker->next;
        this->nodeRebinded.destroy(walker);
        this->nodeRebinded.deallocate(walker, 1);
        walker = walkerNext;
    }
    this->nodeRebinded.destroy(walker);
    this->nodeRebinded.deallocate(walker, 1);
}

template<typename T, class allocator>
List<T, allocator>::List(const List &other) {
    iterator it = other.begin();
    while (it != other.end())
    {
        this->push_back(*it);
        ++it;
    }
}

template<typename T, class allocator>
List<T, allocator> &List<T, allocator>::operator=(const List &other) {
    iterator it = other.begin();
    while (it != other.end())
    {
        this->push_back(*it);
        ++it;
    }
    return *this;
}

template<typename T, class allocator>
void List<T, allocator>::push_back(const T &adding) {
    node *node_b = this->nodeRebinded.allocate(1);
    this->nodeRebinded.construct(node_b, adding);
    if(this->head == nullptr)
        this->head = this->tail = node_b;
    else
    {
        node_b->previous = this->tail;
        this->tail->next = node_b;
        this->tail = node_b;
    }
    ++this->_size;
}

template<typename T, class allocator>
void List<T, allocator>::remove(const T &removing) {
    iterator walker = this->begin();
    while(walker != this->end())
    {
        if(*walker == removing)
        {
            if(walker.node_a == this->head)
            {
                this->head->next->previous = nullptr;
                this->head = walker.node_a->next;
                break;
            }
            else if (walker.node_a == this->tail)
            {
                this->tail->previous->next = nullptr;
                this->tail = walker.node_a->previous;
                break;
            }
            else
            {
                walker.node_a->next->previous = walker.node_a->previous;
                walker.node_a->previous->next = walker.node_a->next;
                break;
            }
        }
        ++walker;
    }
    this->nodeRebinded.destroy(walker.node_a);
    this->nodeRebinded.deallocate(walker.node_a, 1);
    --this->_size;
}

template<typename T, class allocator>
void List<T, allocator>::insert(typename List<T, allocator>::iterator inserting, const T &value) {
    node *node_b = this->nodeRebinded.allocate(1);
    this->nodeRebinded.construct(node_b, value);

    if (inserting.node_a != this->head)
        node_b->previous = inserting.node_a->previous;

    inserting.node_a->previous->next = node_b;
    inserting.node_a->previous = node_b;
    node_b->next = inserting.node_a;
    ++this->_size;
}


template<typename T, class allocator>
size_t List<T, allocator>::size() const
{
    return this->_size;
}

template<typename T, class allocator>
bool List<T, allocator>::isEmpty() {
    bool empty();
    {
        if (this->_size = 0)
            return true;
        else
            return false;
    }
}

#endif //VECTOR_LIST_PROJECT_LIST_H
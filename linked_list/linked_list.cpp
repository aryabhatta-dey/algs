#include <iostream>

template<typename T>
class LinkedList
{
    struct Node
    {
        T       data;
        Node*   prev;
        Node*   next;
    };

    Node*       head;
    Node*       tail;
    std::size_t length;

    public:
        LinkedList()            // Default Constructor
            : head(nullptr)
            , tail(nullptr)
            , length(0)
        {}

        // class destructor - delete all nodes
        ~LinkedList()
        {
            for (Node* loop = head; loop != nullptr;) {
                Node* old = loop;
                loop = loop->next;
                delete old;
            }
        }
        // Copy Constructor and Assignment.
        LinkedList(LinkedList const& copy)
            : head(nullptr)
            , tail(nullptr)
            , length(0)
        {
            // Loop over the other list.
            // Simply push each element into this list.
            for (Node* loop = copy.head; loop != nullptr; loop = loop->next) {
                push_back(loop->data);
            }
        }
        LinkedList& operator=(LinkedList const& rhs)
        {
            // Use the copy and swap idiom to do assignment.

            // 1. Copy the list using the copy constructor.
            LinkedList  copy(rhs);

            // 2. Swap the copy with the current object.
            swap(copy);

            // 3. When we go out of scope the `copy` object is
            //    destroyed. This releases the old object list
            return *this;
        }
        // Move Constructor and Assignment
        // For now we delete these. But we will␣
        // come back to this later.
        LinkedList(LinkedList&&) noexcept            = delete;
        LinkedList& operator=(LinkedList&&) noexcept = delete;

        // Swap
        // We want to swap two objects of type Linked List.
        void swap(LinkedList const& rhs) noexcept
        {
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
        }
        void push_back(T const& value)
        {
            if (tail) {
                // If the list is not empty add it to the back.
                // Simply create the node linked to the tail and
                // then move the tail to the new tail node.
                tail->next = new Node{value, tail, nullptr};
                tail = tail->next;
            }
            else {
                // If the list is empty.
                // Then the new node is both the head and tail
                head = tail = new Node{value, nullptr, nullptr};
            }
            length++;
        }
        void pop_back()
        {
            if (tail) {
                // Keep track of the old value.
                Node* old = tail;

                // Remove the last element from the list
                tail = tail->prev;
                tail->next = nullptr;
                length--;

                // Tidy up. Delete the old element.
                delete old;
            }
        }
        std::size_t size() const    {return length;}
        T const& back() const       {return tail->data;}
        T&       back()             {return tail->data;}

        // Front version equivalent of the back methods.
        void push_front(T&);
        void pop_front();
        T const& front() const;
        T&       front();

        // Unchecked accesses.
        T const& operator[](std::size_t index) const;
        T&       operator[](std::size_t index);

        // Checked accesses.
        T const& at(std::size_t index) const;
        T&       at(std::size_t index);
};

int main()
{
    LinkedList <int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    LinkedList <int> second(list);
    std::cout << second.back();
    second.pop_back();
    second.pop_back();
    std::cout << second.back() << std::endl;
}

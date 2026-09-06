#ifndef S21_STACK_H
#define S21_STACK_H

namespace s21 {

template <typename T>
class stack {
    using size_type = size_t;

   private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;

   public:
    stack() {
        head = nullptr;
        tail = nullptr;
    }
    ~stack() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    stack(std::initializer_list<T> const& items) {
        head = new Node(*(items.begin()));
        tail = new Node(*(items.begin()));

        for (auto it = items.begin() + 1; it != items.end(); it++) {
            Node* new_node = new Node(*it);
            new_node->next = head;
            head = new_node;
        }
    }
    void print_stack() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }
    // copy
    stack(const stack& q) {
        if (q.head == nullptr) return;
        head = new Node(q.head->value);
        Node* src_current = q.head->next;
        Node* dst_current = head;

        while (src_current != nullptr) {
            dst_current->next = new Node(src_current->value);
            dst_current = dst_current->next;
            src_current = src_current->next;
        }
    }  // move
    stack(stack&& q) {
        head = q.head;
        tail = q.tail;
    }
    // move
    stack operator=(stack&& q) {
        head = q.head;
        tail = q.tail;
    }

    T top() {
        if (empty()) throw std::runtime_error("Queue is empty");
        return (head->value);
    };

    bool empty() {
        if (head != nullptr) {
            return false;
        } else {
            return true;
        }
    }
    size_type size() {
        int num = 0;
        Node* src = head;
        while (src != nullptr) {
            num++;
            src = src->next;
        }
        return num;
    }
    void push(const T value) {
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
    }
    void pop() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void swap(stack& other) {
        Node* tempH = head;
        head = other.head;
        other.head = tempH;
    }
};

}  // namespace s21

#endif

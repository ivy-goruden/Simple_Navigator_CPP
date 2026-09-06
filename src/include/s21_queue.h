#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {

template <typename T>
class queue {
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
    queue() {
        head = nullptr;
        tail = nullptr;
    }
    ~queue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    queue(std::initializer_list<T> const& items) {
        head = new Node(*(items.begin()));
        Node* temp = head;

        for (auto it = items.begin() + 1; it != items.end(); it++) {
            Node* new_node = new Node(*it);
            temp->next = new_node;
            tail = new_node;
            temp = temp->next;
        }
    }
    void print_queue() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }
    // copy
    queue(const queue& q) {
        if (q.head == nullptr) return;
        head = new Node(q.head->value);
        tail = head;
        Node* src_current = q.head->next;
        Node* dst_current = head;

        while (src_current != nullptr) {
            dst_current->next = new Node(src_current->value);
            dst_current = dst_current->next;
            tail = dst_current;
            src_current = src_current->next;
        }
    }  // move
    queue(queue&& q) {
        head = q.head;
        tail = q.tail;
    }
    // move
    queue operator=(queue&& q) {
        Node* dst = head;
        Node* next = head->next;
        Node* src = q.front();
        while (src->value != nullptr) {
            dst->value = src->value;
            tail = dst;
            dst = dst->next;
            q.pop();
            Node* src = q.front();
        }
    }

    T front() {
        if (empty()) throw std::runtime_error("Queue is empty");
        return (head->value);
    };
    T back() {
        if (empty()) throw std::runtime_error("Queue is empty");
        return (tail->value);
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
        if (head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }
    void pop() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void swap(queue& other) {
        Node* tempH = head;
        Node* tempT = tail;
        head = other.head;
        tail = other.tail;
        other.head = tempH;
        other.tail = tempT;
    }
};

}  // namespace S21

#endif

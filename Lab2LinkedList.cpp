

#include <iostream>
using namespace std;
template<typename T>
class List {
public:
    List();
    ~List();
    void pop_front();
    void push_back(T data);
    void clear();
    int GetSize() { return size; }
    T& operator[](const int index);
    void push_front(T data);
    void insert(T data, int index);
    void remove_at(int index);
    void pop_back();
    void remove_every_n(int n);
    void sort();
    
private:

    template<typename T>
    struct Node {
    public:
        Node* pnext;
        T data;
        Node(T data = T(), Node* pnext = nullptr) {
            this->data = data;
            this->pnext = pnext;
        }
    };
    int size;
    Node<T> *head;
     
};

//конструктор класу Ліст який задає розмір 0 
template<typename T>
List<T>::List() {
    size = 0;
    head = nullptr;
}

//деструктор класу Ліст
template<typename T>
List<T>::~List() {
    clear();
}

//видалення першого елементу односвязного списку
template<typename T>
void List<T>::pop_front()
{
    Node<T> *temp = head;
    head = head->pnext;
    delete temp;
    size--;
}

//додавання елементу в кінець списку
template<typename T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
    }
    else {
        Node<T>* curr = this->head;
        while (curr->pnext!=nullptr) {
            curr = curr->pnext;
        }
        curr->pnext = new Node<T>(data);
    }
    size++;
}

//очищення усього списку
template<typename T>
void List<T>::clear()
{
    while (size) {
        pop_front();
    }
}

//перегрузка оператора [] 
template<typename T>
T& List<T>::operator[](const int index)
{
    int counter = 0;
    Node<T>* curr = this->head;
    while (curr != nullptr) {
        if (counter == index) {
            return curr->data;
        }
        curr = curr->pnext;
        counter++;
    }
}

//додавання елементу в початок списку
template<typename T>
void List<T>::push_front(T data)
{
    head = new Node<T>(data,head);
    size++;
}

//додавання елементу в список за індексом
template<typename T>
void List<T>::insert(T data, int index)
{
    if (index == 0) {
        push_front(data);
    }
    else {
        Node<T>* previous = this->head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->pnext;
        }
        Node<T>* newNode = new Node<T>(data, previous->pnext);
        previous->pnext = newNode;
        size++;
    }
    
}

//метод видалення елементу за індексом
template<typename T>
void List<T>::remove_at(int index)
{
    if (index == 0) {
        pop_front();
    }
    else {
        Node<T>* previous = this->head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->pnext;
        }
        Node<T>* to_delete = previous->pnext;
        previous->pnext = to_delete->pnext;
        delete to_delete;
        size--;
         
    }
}

//видалення останього елементу списку
template<typename T>
void List<T>::pop_back()
{
    remove_at(size - 1);
}

//видалення кожного n елементу списка
template<typename T>
void List<T>::remove_every_n(int n)
{
    if (n == 1) {
        while (GetSize()) {
            pop_front();
        }
    }
    else {
        for (int i = n - 1; i < GetSize(); i += n - 1) {
            remove_at(i);
        }
    }
}

//метод сортування за зростанням
template<typename T>
void List<T>::sort()
{
    Node<T>* ptr = head, * tmp = NULL, * prev = NULL;
    bool flag = false;
    do
    {
        flag = false;
        ptr = head;
        while (ptr->pnext)
        {
            if (ptr->data > ptr->pnext->data)
            {
                if (ptr == head)
                {
                    tmp = ptr;
                    ptr = tmp->pnext;
                    tmp->pnext = ptr->pnext;
                    ptr->pnext = tmp;
                    head = ptr;
                    flag = true;
                }
                else
                {
                    tmp = ptr;
                    ptr = tmp->pnext;
                    tmp->pnext = ptr->pnext;
                    ptr->pnext = tmp;
                    prev->pnext = ptr;
                    flag = true;
                }
            }
            prev = ptr;
            ptr = ptr->pnext;
        }
    } while (flag);
}

//склеювання листів
template<typename T>
List<T>* concatenate(List<T>** top, List<T>** top2) {
    char temp;
    temp = top2.pop_back();
    List<T>* pv = head(temp);
    while (*top2 != NULL) {
        char temp2 = pop(top2);
        push(&pv, temp2);
    }
    while (*top != NULL) {
        char temp2 = pop(top);
        push(&pv, temp2);
    }
    return pv;
}

//меню
int menu() {
    cout << "Choose action from list : " << endl;

    int res;
    cin >> res;

    return res;
}

int main()
{
    List<int> lst;
    lst.push_back(4);
    lst.push_back(9);
    lst.push_back(3);
    lst.push_back(1);
    lst.push_back(7);
    lst.push_back(4);
    lst.push_back(9);
    lst.sort();
    for (int i = 0; i < lst.GetSize(); i++) {
        cout << lst[i] << endl;
    }
}
    




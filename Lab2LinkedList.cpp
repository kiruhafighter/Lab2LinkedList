

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
    List(const List& other);
    
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


//конструктор копіювання листів
template<typename T>
List<T>::List(const List& other) {
    if (!other.head) {
        size = 0;
        head = nullptr;
        return;
    }

    head = new Node<T>(*other.head);
    Node<T>* cur = head;
    size = 1;

    for (Node<T>* t = other.head->pnext; t != nullptr; t = t->pnext) {
        cur->pnext = new Node<T>(*t);
        cur = cur->pnext;
        ++size;
    }
    cur->pnext = nullptr;
}

//меню
int menu() {
    cout << "Choose action from list : " << endl;
    cout << "1. Remove first" << endl;
    cout << "2. Add to the end" << endl;
    cout << "3. Clear" << endl;
    cout << "4. Get Size of List" << endl;
    cout << "5. Add to the beginning" << endl;
    cout << "6. Insert to position" << endl;
    cout << "7. Remove element number " << endl;
    cout << "8. Remove element from end of the List" << endl;
    cout << "9. Remove every n element from the List" << endl;
    cout << "10. Sort" << endl;
    cout << "11. Concatenate two lists" << endl;
    int res;
    cin >> res;
    return res;
}

int main()
{
    List<int> lst;
    lst.push_back(4);
    lst.push_back(99);
    lst.push_back(3);
    lst.push_back(12);
    lst.push_back(72);
    lst.push_back(4);
    lst.push_back(11);
    List<int> lst3;
    lst.push_back(99);
    lst.push_back(15);
    lst.push_back(11);
    lst.push_back(99);
    lst.push_back(12);
    lst.push_back(72);
    lst.push_back(30);

    /*List<int> lst2(lst);
    
    List<int> res;
    for (int i = 0; i < lst.GetSize(); i++) {
        res.push_back(lst[i]);
    }
    for (int j = 0; j < lst2.GetSize(); j++) {
        res.push_back(lst2[j]);
    }
    for (int i = 0; i < res.GetSize(); i++) {
        cout<<res[i]<<endl;
    }*/

    List<int> res;

    for (int i = 0; i < lst.GetSize(); i++) {
        for (int j = 0; j < lst3.GetSize(); j++) {
            if (lst[i] == lst3[j]) {
                
                res.push_back(lst[i]);
                
            }
        }
    }
    for (int i = 0; i < res.GetSize(); i++) {
        cout << res[i] << endl;
    }

}
    




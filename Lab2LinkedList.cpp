

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

//method for merging Lists
template<typename T>
List<T> Merge(List<T>lst1, List<T>lst2) {
    List<T> res;
    for (int i = 0; i < lst1.GetSize(); i++) {
        for (int j = 0; j < lst2.GetSize(); j++) {
            if (lst1[i] == lst2[j]) {

                res.push_back(lst1[i]);
                break;
            }
        }
    }
    return res;
}


//Concatenate Lists
template<typename T>
List<T> Concat(List<T>lst, List<T>lst2) {
    List<T> res;
    for (int i = 0; i < lst.GetSize(); i++) {
        res.push_back(lst[i]);
    }
    for (int j = 0; j < lst2.GetSize(); j++) {
        res.push_back(lst2[j]);
    }
    return res;
}


//Print
template<typename T>
void printList(List<T> lis) {
    for (int i = 0; i < lis.GetSize(); i++) {
        cout << lis[i] << " ";
    }
    cout << endl;
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
    cout << "11. Make a copy of list and print it" << endl;
    cout << "12. Concatenate two lists" << endl;
    cout << "13. Merge of two lists" << endl;
    cout << "14. Print" << endl;
    int res;
    cin >> res;
    return res;
}

int main()
{
    List<int> lst;
    lst.push_back(4);
    lst.push_back(99);
    lst.push_back(99);
    lst.push_back(12);
    lst.push_back(72);
    lst.push_back(30);
    List<int> lst3;
    lst3.push_back(99);
    lst3.push_back(15);
    lst3.push_back(11);
    lst3.push_back(99);
    lst3.push_back(12);
    lst3.push_back(72);
    lst3.push_back(30);

    List<int> lst2(lst);
    /*List<int> reik;*/
    /*List<int> resau;*/
    
    while (true) {
        
            
        switch (menu()) {
        case 1:
        {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc1;
            cin >> numc1;
            if (numc1 == 1) {
                lst.pop_front();
            }
            else if (numc1 == 2) {
                lst3.pop_front();
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 2:
        {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc2;
            cin >> numc2;
            if (numc2 == 1) {
                cout << "Write naumber to add " << endl;
                int numa2;
                cin >> numa2;
                lst.push_back(numa2);
            }
            else if (numc2 == 2) {
                cout << "Write naumber to add " << endl;
                int numa2;
                cin >> numa2;
                lst3.push_back(numa2);
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 3: 
        {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc3;
            cin >> numc3;
            if (numc3 == 1) {
                lst.clear();
            }
            else if (numc3 == 2) {
                lst3.clear();
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;

        case 4:
        {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc4;
            cin >> numc4;
            if (numc4 == 1) {
                cout << lst.GetSize() << endl;
            }
            else if (numc4 == 2) {
                cout << lst3.GetSize() << endl;
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 5: {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc5;
            cin >> numc5;
            if (numc5 == 1) {
                cout << "Write naumber to add " << endl;
                int numa5;
                cin >> numa5;
                lst.push_front(numa5);
            }
            else if (numc5 == 2) {
                cout << "Write naumber to add " << endl;
                int numa5;
                cin >> numa5;
                lst3.push_front(numa5);
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 6:
        {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc6;
            cin >> numc6;
            if (numc6 == 1) {
                cout << "Write naumber to add " << endl;
                int numa6;
                cin >> numa6;
                cout << "Write index to insert " << endl;
                int numi6;
                cin >> numi6;
                lst.insert(numa6, numi6);
            }
            else if (numc6 == 2) {
                cout << "Write naumber to add " << endl;
                int numa6;
                cin >> numa6;
                cout << "Write index to insert " << endl;
                int numi6;
                cin >> numi6;
                lst3.insert(numa6, numi6);
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 7:
        {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc7;
            cin >> numc7;
            if (numc7 == 1) {
                cout << "Write index to delete " << endl;
                int numi7;
                cin >> numi7;
                lst.remove_at(numi7);
            }
            else if (numc7 == 2) {
                cout << "Write index to delete " << endl;
                int numi7;
                cin >> numi7;
                lst3.remove_at(numi7);
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 8: {
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc8;
            cin >> numc8;
            if (numc8 == 1) {
                lst.pop_back();
            }
            else if (numc8 == 2) {
                lst3.pop_back();
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
            break;
        case 9:{
            system("cls");
            cout << "Choose list 1 or 2 :" << endl;
            int numc9;
            cin >> numc9;
            if (numc9 == 1) {
                cout << "Write n to delete every n element  " << endl;
                int numd9;
                cin >> numd9;
                lst.remove_every_n(numd9);
            }
            else if (numc9 == 2) {
                cout << "Write n to delete every n element  " << endl;
                int numd9;
                cin >> numd9;
                lst3.remove_every_n(numd9);
            }
            else {
                cout << "Wrong value " << endl;
            }
        }
                break;
            case 10:
            {
                system("cls");
                cout << "Choose list 1 or 2 :" << endl;
                int numc10;
                cin >> numc10;
                if (numc10 == 1) {
                    lst.sort();
                }
                else if (numc10 == 2) {
                    lst3.sort();
                }
                else {
                    cout << "Wrong value " << endl;
                }
            }
                break;
            case 11:
            {
                system("cls");
                cout << "Choose list 1 or 2 :" << endl;
                int numc11;
                cin >> numc11;
                if (numc11 == 1) {
                    List<int>newlst = List<int>(lst);
                    cout << "Copy of list 1 " << endl;
                    for (int i = 0; i < newlst.GetSize(); i++) {
                        cout << newlst[i] << " ";
                    }
                    cout << endl;
                }
                else if (numc11 == 2) {
                    List<int>newlst2 = List<int>(lst3);
                    cout << "Copy of list 2 " << endl;
                    for (int i = 0; i < newlst2.GetSize(); i++) {
                        cout << newlst2[i] << " ";
                    }
                    cout << endl;
                }
                else {
                    cout << "Wrong value " << endl;
                }
            }
                break;
            case 12:
            {
                List<int>resau = Concat(lst, lst3);
                cout << "Cancatenated Lists in one" << endl;
                for (int i = 0; i < resau.GetSize(); i++) {
                    cout << resau[i] << " ";
                }
                cout << endl;
            }
            break;
            case 13:
            {
                system("cls");
                List<int>reik = Merge(lst, lst3);
                cout << "Merged :" << endl;
                for (int i = 0; i < reik.GetSize(); i++) {
                    cout << reik[i] << " ";
                }
                cout << endl;
            }
                break;
            
            case 14:
            {
                system("cls");
                cout << "Choose from lists 1 and 2 :" << endl;
                int numc14;
                cin >> numc14;
                if (numc14 == 1) {
                    printList(lst);
                }
                else if (numc14 == 2) {
                    printList(lst3);
                }
                else {
                    cout << "Wrong value" << endl;
                }
            }
                break;
            

            

            }
        
        
        

    }




}
    




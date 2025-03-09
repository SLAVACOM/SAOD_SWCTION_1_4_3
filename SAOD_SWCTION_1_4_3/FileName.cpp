#include <iostream>
#include <string>

using namespace std;

struct List {
    string data;
    List* next;
};

struct ListOfLists {
    string name; // �������� ������
    List* head;
    ListOfLists* next;
};

ListOfLists* list = nullptr;

bool isEmpty() {
    return list == nullptr;
}

bool isEmptyList(List* l) {
    return l == nullptr;
}

int getListsCount() {
    int count = 0;
    ListOfLists* temp = list;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

ListOfLists* findListByName(const string& name) {
    ListOfLists* temp = list;
    while (temp != nullptr) {
        if (temp->name == name) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void printList() {
    if (isEmpty()) {
        cout << "������ ������� ������!" << endl;
        return;
    }
    cout << "����� ������� � ������: " << getListsCount() << endl;

    ListOfLists* temp = list;
    int listNumber = 1;
    while (temp != nullptr) {
        cout << "������ (" << temp->name<<"): ";
        int i = 1;
        if (!isEmptyList(temp->head)) {
			cout << endl;
            List* temp2 = temp->head;
            while (temp2 != nullptr) {
                cout << i << ". " << temp2->data << endl;
                temp2 = temp2->next;
                i++;
            }
        }
        else cout << " ������!" << endl;
       temp = temp->next;
    }
}

void addEmptyList(const string& name) {
    ListOfLists* newList = new ListOfLists;
    newList->name = name;
    newList->head = nullptr;
    newList->next = nullptr;

    if (isEmpty()) {
        list = newList;
        return;
    }

    ListOfLists* temp = list;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = newList;
}

void addElementToList(const string& name, const string& data) {
    if (isEmpty()) {
        cout << "������ ������� ������!" << endl;
        return;
    }

    ListOfLists* listToAdd = findListByName(name);
    if (listToAdd == nullptr) {
        cout << "������ ������ �� ����������!" << endl;
        return;
    }

    List* newElement = new List;
    newElement->data = data;
    newElement->next = nullptr;

    if (isEmptyList(listToAdd->head)) {
        listToAdd->head = newElement;
        return;
    }

    List* temp2 = listToAdd->head;
    while (temp2->next != nullptr) temp2 = temp2->next;
    temp2->next = newElement;
}

void deleteElementFromList(const string& name, const string& elementValue) {
    if (isEmpty()) {
        cout << "������ ������� ������!" << endl;
        return;
    }

    ListOfLists* listToDelete = findListByName(name);
    if (listToDelete == nullptr) {
        cout << "������ ������ �� ����������!" << endl;
        return;
    }

    if (isEmptyList(listToDelete->head)) {
        cout << "������ ������!" << endl;
        return;
    }

    List* temp2 = listToDelete->head;
    bool isFound = false;
    if (temp2->data == elementValue) {
        listToDelete->head = temp2->next;
        delete temp2;
        return;
    }

    while (temp2->next != nullptr) {
        if (temp2->next->data == elementValue) {
            List* temp3 = temp2->next;
            temp2->next = temp2->next->next;
            delete temp3;
            isFound = true;
            break;
        }
        temp2 = temp2->next;
    }
    if (!isFound) cout << "������� �� ������!" << endl;
}

void deleteList(const string& name) {
    if (isEmpty()) {
        cout << "������ ������� ������!" << endl;
        return;
    }

    ListOfLists* temp = list;
    ListOfLists* prev = nullptr;
    while (temp != nullptr && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "������ ������ �� ����������!" << endl;
        return;
    }

    if (prev == nullptr) list = temp->next;
    else prev->next = temp->next;
    

    List* temp2 = temp->head;
    while (temp2 != nullptr) {
        List* temp3 = temp2;
        temp2 = temp2->next;
        delete temp3;
    }

    delete temp;
}

void deleteAllLists() {
    if (isEmpty()) {
        cout << "������ ������� ������!" << endl;
        return;
    }

    ListOfLists* temp = list;
    while (temp != nullptr) {
        ListOfLists* temp2 = temp;
        temp = temp->next;

        List* temp3 = temp2->head;
        while (temp3 != nullptr) {
            List* temp4 = temp3;
            temp3 = temp3->next;
            delete temp4;
        }

        delete temp2;
    }
    list = nullptr;
}

void menu(bool& exit) {
    cout << "����:" << endl;
    cout << "1. �������� ������ ������" << endl;
    cout << "2. �������� ������� � ������" << endl;
    cout << "3. ������� ������� �� ������" << endl;
    cout << "4. ������� ������" << endl;
    cout << "5. ������� ��� ������" << endl;
    cout << "6. ������� ������" << endl;
    cout << "7. �����" << endl;
    cout << "�������� ��������: ";

    int choice = 0;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: {
            cout << "������� �������� ������: ";
            string name;
            getline(cin, name);
            addEmptyList(name);
            break;
        }
        case 2: {
            cout << "������� �������� ������: ";
            string name;
            getline(cin, name);
            cout << "������� �������� ��������: ";
            string value;
            getline(cin, value);
            addElementToList(name, value);
            break;
        }
        case 3: {
            cout << "������� �������� ������: ";
            string name;
            getline(cin, name);
            cout << "������� �������� ��������: ";
            string value;
            getline(cin, value);
            deleteElementFromList(name, value);
            break;
        }
        case 4: {
            cout << "������� �������� ������: ";
            string name;
            getline(cin, name);
            deleteList(name);
            break;
        }
        case 5: {
            deleteAllLists();
            break;
        }
        case 6: {
            printList();
            break;
        }
        case 7: {
            exit = true;
            break;
        }   
        default: {
            cout << "�������� ����!" << endl;
            break;
        }
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    bool exit = false;
    while (!exit) menu(exit);
    deleteAllLists(); 
    return 0;
}

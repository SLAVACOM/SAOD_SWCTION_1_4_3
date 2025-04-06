#include <iostream>
#include <string>

using namespace std;

struct List {
    string data;
    List* next;
	List* prev;
};

struct ListOfLists {
    string name;
    List* head;

    ListOfLists* next;
    ListOfLists* prev;
};

ListOfLists* list = nullptr;
 
static bool isEmpty() {
    return list == nullptr;
}

static bool isEmptyList(const List* l) {
    return l == nullptr;
}

static int getListsCount() {
    int count = 0;
    ListOfLists* temp = list;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

static ListOfLists* findListByName(const string& name) {
    ListOfLists* temp = list;
    while (temp != nullptr) {
        if (temp->name == name) return temp;
        temp = temp->next;
    }

    return nullptr;
}

static List* findElementByValue(List* head, const string& value) {
	List* temp = head;
	while (temp != nullptr) {
		if (temp->data == value) return temp;
		temp = temp->next;
	}
	return nullptr;
}

static void printList() {
    cout << endl;
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
    
        cout << endl;
    }
}

static void addEmptyList(const string& name, const bool isAfter, ListOfLists*& target) {
    ListOfLists* newList = new ListOfLists;
    newList->name = name;
    newList->head = nullptr;
    newList->next = nullptr;
    newList->prev = nullptr;

    if (isEmpty()) {
        cout << "C����� ������ ������ �������" << endl;
        list = newList;
        return;
    }

    if (isAfter) {
		newList->next = target->next;
		newList->prev = target;
		if (target->next) target->next->prev = newList;
		target->next = newList;
    }
    else {
		newList->prev = target->prev;
		newList->next = target;
        if (target->prev != nullptr) {
            target->prev->next = newList;
        }
        else list = newList;
        target->prev = newList;
    }
}               

static void addElementToList(const string& data, const bool isAfter, List*& target, ListOfLists*& list) {
    List* newElement = new List;
    newElement->data = data;

    if (!target) {
        newElement->next = nullptr;
        newElement->prev = nullptr;
        target = newElement;
        cout << "������ ������ ������� ������" << endl;
        return;
    }

    if (isAfter) {
        newElement->next = target->next;
        newElement->prev = target;
        if (target->next) target->next->prev = newElement;
        target->next = newElement;
    }
    else {
		newElement->prev = target->prev;
		newElement->next = target;
		if (target->prev != nullptr) target->prev->next = newElement;
		else list->head = newElement;
		target->prev = newElement;
        
    }
}


static void deleteElementFromList(List*& element, ListOfLists*& list){
	if (!element) {
		cout << "������� �� ������!" << endl;
		return;
	}

	if (element->prev) element->prev->next = element->next;
	else list->head = element->next;

	if (element->next) element->next->prev = element->prev;
	delete element;
	cout << "������� ������!" << endl;
}

static void deleteList(ListOfLists*& delList) {   
    if (!delList) {
        cout << "������ ������ �� ����������!" << endl;
        return;
    }

    List* currentElement = delList->head;

	while (currentElement) {
		List* temp = currentElement->next;
		deleteElementFromList(currentElement, delList);
        currentElement =  temp;
	}

	if (delList->prev) delList->prev->next = delList->next;
	else list = delList->next;
	
	if (delList->next) delList->next->prev = delList->prev;

    delete delList;
}

static void deleteAllLists() {
    if (isEmpty()) {
        cout << "������ ������� ������!" << endl;
        return;
    }

    while (list){
		ListOfLists* temp = list;
		list = temp->next;
        deleteList(temp);
    }
}

static void menu(bool& exit) {
    cout << endl << "����:" << endl;
    cout << "1. �������� ������ ������" << endl;
    cout << "2. �������� ������� � ������" << endl;
    cout << "3. ������� ������� �� ������" << endl;
    cout << "4. ������� ������" << endl;
    cout << "5. ������� ��� ������" << endl;
    cout << "6. ������� " << endl;
    cout << "7. �����" << endl;
    cout << "�������� ��������: ";

    int choice = 0;
    cin >> choice;
    cin.ignore();
    cin.clear();

    switch (choice) {
        case 1: {
            bool isAfter = true;
            ListOfLists* target = list;

            if (!isEmpty()) {
                target = nullptr;
                cout << "�� ������ �������� ��(0) ��� ����� (1):" << endl;
                cin >> isAfter;
                cin.ignore();
                cin.clear();

                cout << "������� �������� target-������: ";
                string name;
                getline(cin, name);
                target = findListByName(name);
                if (!target) {
                    cout << "������ ������ �� ����������!" << endl;
                    break;
                }
            }
            else cout << "������ ������, ������ ����� �������� � ������!" << endl;
            cout << "������� �������� ������ ������: ";

            string name;
            getline(cin, name);
            addEmptyList(name, isAfter, target);
            break;
        }
        case 2: {
        string input;
        bool isAfter = true;

        cout << "������� �������� ������ c������: ";
        getline(cin, input);
        ListOfLists* list = findListByName(input);

        if (list == nullptr) {
            cout << "������ ������ �� ����������!" << endl;
            break;
        }

        List* target = list->head;

        if (target) {
            cout << "������� �������� target-��������: ";
            getline(cin, input);

            target = findElementByValue(list->head, input);
            if (target == nullptr) {
                cout << "������ �������� �� ����������!" << endl;
                break;
            }
            
        }
        else cout << "������ ������ ������� ����� �������� � ������!" << endl;
        
        cout << "������� �������� ������ ��������: ";
        getline(cin, input);
        

        if (target != nullptr) {
            cout << "�� ������ �������� ��(0) ��� ����� (1):" << endl;
            cin >> isAfter;
            cin.ignore();
            cin.clear();
            addElementToList(input, isAfter, target, list);
        }
        else addElementToList(input, isAfter, list->head, list);
        break;
    }
        case 3: {
			string input;
            cout << "������� �������� ������ c������: ";
            getline(cin, input);
			
            ListOfLists* list = findListByName(input);
			if (list == nullptr) {
				cout << "������ ������ �� ����������!" << endl;
				break;
			}
            
            cout << "������� �������� �������� �������� ������ �������: ";
            getline(cin, input);
			List* target = findElementByValue(list->head, input);
			deleteElementFromList(target, list);
            break;
        }
        case 4: {
            cout << "������� �������� ������: ";
            string name;
            getline(cin, name);
			ListOfLists* target = findListByName(name);
            deleteList(target);
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

    cout << endl;}
}




int main() {
    setlocale(LC_ALL, "Russian");
    bool exit = false;
    while (!exit) menu(exit);
    deleteAllLists(); 
    return 0;
}

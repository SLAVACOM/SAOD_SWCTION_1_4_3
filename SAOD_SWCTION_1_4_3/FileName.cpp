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
        cout << "Список списков пустой!" << endl;
        return;
    }
    cout << "Всего списков в списке: " << getListsCount() << endl;

    ListOfLists* temp = list;
    int listNumber = 1;
    while (temp != nullptr) {
        cout << "Список (" << temp->name<<"): ";
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
        else cout << " Пустой!" << endl;
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
        cout << "Cоздан первый список списков" << endl;
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
        cout << "Создан первый элемент списка" << endl;
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
		cout << "Элемент не найден!" << endl;
		return;
	}

	if (element->prev) element->prev->next = element->next;
	else list->head = element->next;

	if (element->next) element->next->prev = element->prev;
	delete element;
	cout << "Элемент удален!" << endl;
}

static void deleteList(ListOfLists*& delList) {   
    if (!delList) {
        cout << "Такого списка не существует!" << endl;
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
        cout << "Список списков пустой!" << endl;
        return;
    }

    while (list){
		ListOfLists* temp = list;
		list = temp->next;
        deleteList(temp);
    }
}

static void menu(bool& exit) {
    cout << endl << "Меню:" << endl;
    cout << "1. Добавить пустой список" << endl;
    cout << "2. Добавить элемент в список" << endl;
    cout << "3. Удалить элемент из списка" << endl;
    cout << "4. Удалить список" << endl;
    cout << "5. Удалить все списки" << endl;
    cout << "6. Вывести " << endl;
    cout << "7. Выйти" << endl;
    cout << "Выберите действие: ";

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
                cout << "Вы хотите добавить до(0) или после (1):" << endl;
                cin >> isAfter;
                cin.ignore();
                cin.clear();

                cout << "Введите название target-списка: ";
                string name;
                getline(cin, name);
                target = findListByName(name);
                if (!target) {
                    cout << "Такого списка не существует!" << endl;
                    break;
                }
            }
            else cout << "Список пустой, список будет добавлен в начало!" << endl;
            cout << "Введите название нового списка: ";

            string name;
            getline(cin, name);
            addEmptyList(name, isAfter, target);
            break;
        }
        case 2: {
        string input;
        bool isAfter = true;

        cout << "Введите название списка cписков: ";
        getline(cin, input);
        ListOfLists* list = findListByName(input);

        if (list == nullptr) {
            cout << "Такого списка не существует!" << endl;
            break;
        }

        List* target = list->head;

        if (target) {
            cout << "Введите название target-элемента: ";
            getline(cin, input);

            target = findElementByValue(list->head, input);
            if (target == nullptr) {
                cout << "Такого элемента не существует!" << endl;
                break;
            }
            
        }
        else cout << "Список пустой элемент будет добавлен в начало!" << endl;
        
        cout << "Введите значение нового элемента: ";
        getline(cin, input);
        

        if (target != nullptr) {
            cout << "Вы хотите добавить до(0) или после (1):" << endl;
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
            cout << "Введите название списка cписков: ";
            getline(cin, input);
			
            ListOfLists* list = findListByName(input);
			if (list == nullptr) {
				cout << "Такого списка не существует!" << endl;
				break;
			}
            
            cout << "Введите значение элемента которого хотите удалить: ";
            getline(cin, input);
			List* target = findElementByValue(list->head, input);
			deleteElementFromList(target, list);
            break;
        }
        case 4: {
            cout << "Введите название списка: ";
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
            cout << "Неверный ввод!" << endl;
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

//
// Created by juanm on 24/04/2022.
//

#include <iostream>
#include <string>
#include <cstring>
#include "EmployeeList.h"
using namespace std;

EmployeeList::EmployeeList() {

    this->head = nullptr;

}

EmployeeList::~EmployeeList() {

    EmployeeNode* curr_next = this->head;

    while(curr_next != nullptr){
        curr_next = curr_next->next;

        this->head->employee->~Employee();
        this->head->designAnimal = nullptr;
        delete this->head;

        this->head = curr_next;
    }

}

EmployeeList::EmployeeList(const EmployeeList &copiedList) {

    EmployeeNode* newNode;
    EmployeeNode* curr = copiedList.head;

    this->head = nullptr;

    while(curr != nullptr){

        EmployeeNode* copiedNode = new EmployeeNode();

        copiedNode->employee = new Employee(*curr->employee);
        copiedNode->ID = curr->employee->get_IDEmployee();
        copiedNode->designAnimal = nullptr;

        if(this->head == nullptr){
            this->head = copiedNode;
        }else{
            newNode->next = copiedNode;
        }

        newNode = copiedNode;
        curr = curr->next;
    }

}

EmployeeList& EmployeeList::operator=(const EmployeeList &assignList) {

    if (this == &assignList) {
        return *this;
    }

    EmployeeNode *currList = this->head;

    while (currList != nullptr) {
        currList = currList->next;

        this->head->employee->~Employee();
        this->head->designAnimal = nullptr;
        delete this->head;

        this->head = currList;
    }

    EmployeeNode *currAssign = assignList.head;

    while (currAssign != nullptr) {

        EmployeeNode *copiedNode = new EmployeeNode();

        copiedNode->employee = new Employee(*currAssign->employee);
        copiedNode->designAnimal = nullptr;

        copiedNode->next = nullptr;

        if(this->head == nullptr){
            this->head = copiedNode;
        }else {
            currList->next = copiedNode;
        }

        currList = copiedNode;
        currAssign = currAssign->next;
    }

    return *this;
}

int EmployeeList::designatedAnimal(int IDEmployee) {

    EmployeeNode *curr, *prev;

    if(!findEmployee(IDEmployee, curr, prev)){
        cout << endl << "Error in function EmployeeList::designatedAnimal : The given ID is not on the list." << endl;
        exit(1);
    }

    if(curr->designAnimal != nullptr){
        return curr->designAnimal->get_habitatNo();
    }

    return 0;
}

int EmployeeList::chk_IDOrder(EmployeeNode *curr, EmployeeNode *curr_next, int IDEmployee) {

    if(curr_next != nullptr){

        if(curr->employee->get_IDEmployee() > IDEmployee){
            return 1;
        }else if(curr->employee->get_IDEmployee() < IDEmployee && curr_next->employee->get_IDEmployee() > IDEmployee){
            return 2;
        }else if(curr_next->employee->get_IDEmployee() < IDEmployee && curr_next->next == nullptr){
            return 3;
        }else if(curr->employee->get_IDEmployee() == IDEmployee){
            return 4;
        }else if(curr_next->employee->get_IDEmployee() == IDEmployee){
            return 5;
        }

    }else {

        if(curr->employee->get_IDEmployee() > IDEmployee){
            return 1;
        }else if(curr->employee->get_IDEmployee() < IDEmployee && curr->next == nullptr){
            return 3;
        }else if(curr->employee->get_IDEmployee() == IDEmployee){
            return 4;
        }

    }

    return 0;

}


bool EmployeeList::chk_ifnotifyEmp(EmployeeNode *curr, int currDay) {

    int food = curr->designAnimal->chk_food(currDay);
    int clean = curr->designAnimal->chk_cleaning(currDay);

    if(strcmp(curr->employee->get_Occupation(), "Caretaker") == 0){

        if(food == 2 || food == 3){
            curr->employee->get_notifications() += 1;
            return true;
        }

    }else if(strcmp(curr->employee->get_Occupation(), "Cleaner") == 0) {

        if (clean == 2) {
            curr->employee->get_notifications() += 1;
            return true;
        }

    }

    return false;
}

int EmployeeList::chk_notifications(EmployeeNode* &curr, EmployeeNode* &prev) {

    if(curr->employee->get_notifications() > 1){
        int animalNum = 0;
        if(strcmp(curr->employee->get_Occupation(), "Caretaker") == 0){
            animalNum = curr->designAnimal->get_habitatNo();
        }

        cout << endl << "The following employee is being fired due to a high amount of notifications: " << endl;
        curr->employee->print();

        removeNode(curr, prev);

        return animalNum;
    }
    return 0;

}


bool EmployeeList::findEmployee(int IDEmployee, EmployeeNode*& curr, EmployeeNode*& prev) const{

    curr = this->head;
    prev = nullptr;
    while(curr != nullptr){
        if(curr->ID == IDEmployee){
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool EmployeeList::findHabAnimal(int habNum, EmployeeNode*& curr, EmployeeNode*& prev) const{

    while(curr != nullptr){
        if(curr->habNum == habNum){
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;

}

void EmployeeList::addEmployee_inOrder(Employee* newEmployee, EmployeeNode* curr, int c) {

    EmployeeNode* newNode = new EmployeeNode();
    newNode->ID = newEmployee->get_IDEmployee();
    newNode->employee = newEmployee;
    newNode->designAnimal = nullptr;

    switch(c){

        case 0:
            this->head = newNode;
            newNode->next = nullptr;
            break;

        case 1:
            newNode->next = this->head;
            this->head = newNode;
            break;

        case 2:
            newNode->next = curr->next;
            curr->next = newNode;
            break;

        case 3:
            if(curr->next != nullptr){
                curr = curr->next;
            }
            curr->next = newNode;
            newNode->next = nullptr;
            break;

        default:
            cout << endl << " Error in function EmployeeList::addEmployee_inOrder : Undefined returning value for chk_IDOrder.";
            cout << endl;
            exit(1);
    }

}

void EmployeeList::removeNode(EmployeeNode *&curr, EmployeeNode *&prev) {

    if(curr == this->head){
        this->head = curr->next;
        prev = this->head;
    }else if(curr->next == nullptr){
        prev->next = nullptr;
    }else{
        prev->next = curr->next;
    }

    curr->designAnimal = nullptr;
    curr->employee->~Employee();
    delete curr;

}

int EmployeeList::get_numEmployees() {

    EmployeeNode *curr = this->head;
    int count = 0;

    while(curr != nullptr){
        count++;
        curr = curr->next;
    }

    return count;

}

bool EmployeeList::chk_Credentials(int IDEmployee, const char *name) {

    EmployeeNode* curr = this->head;

    int c;
    while (curr != nullptr){
        c = chk_IDOrder(curr, curr->next, IDEmployee);
        if( c > 3){
            cout << endl << "Error in function EmployeeList::chk_Credentials : Employee with specified ID already exists." << endl;
            return false;
        }

        if(strcmp(curr->employee->get_name(), name) == 0){
            cout << endl << "Error in function EmployeeList::chk_Credentials : Employee with specified name already exists." << endl;
            return false;
        }

        curr = curr->next;
    }

    return true;
}

void EmployeeList::addEmployee(int IDEmployee, const char *name, const char *Occupation) {

    Employee* newEmployee = new Employee(IDEmployee, name, Occupation);

    insertEmployee(newEmployee);

}

void EmployeeList::insertEmployee(Employee *newEmployee) {

    if(this->head == nullptr){
        addEmployee_inOrder(newEmployee, this->head, 0);
        return;
    }

    EmployeeNode* curr = this->head;

    int c;
    while(curr != nullptr){

        c = chk_IDOrder(curr, curr->next, newEmployee->get_IDEmployee());
        if(c > 0){
            addEmployee_inOrder(newEmployee, curr, c);
            return;
        }
        curr = curr->next;

    }

}

bool EmployeeList::assignAnimal(int IDEmployee, AnimalHab *designAnimal) {

    EmployeeNode* curr = this->head;

    int c;
    while(curr != nullptr){

        c = chk_IDOrder(curr, curr->next, IDEmployee);
        if(c > 3){

            if(c == 5){
                curr = curr->next;
            }
            if(curr->designAnimal == nullptr){
                curr->designAnimal = designAnimal;
                curr->habNum = designAnimal->get_habitatNo();
                return true;
            }else {
                cout << endl << "Error: Specified employee already has a designated animal." << endl;
                return false;
            }

        }
        curr = curr->next;
    }

    cout << endl << "Error: Couldn't find specified employee with ID for assigning animal." << endl;
    return false;

}

bool EmployeeList::chk_assignPossibletoEmployee(int IDEmployee) {

    EmployeeNode *curr, *prev;
    findEmployee(IDEmployee, curr, prev);

    if( curr->designAnimal != nullptr){
        cout << endl << "Error in function EmployeeList::chk_assignPossibletoEmployee : ";
        cout << "The specified employee already has a designated animal." << endl;
        return false;
    }

    return true;
}

Employee* EmployeeList::ret_assignEmployee(int IDEmployee) {

    EmployeeNode *curr, *prev;
    if(!findEmployee(IDEmployee, curr, prev)){
        return nullptr;
    }

    return curr->employee;
}

int EmployeeList::EmployeeOccupation(int IDEmployee) {

    EmployeeNode *curr, *prev;
    if(!findEmployee(IDEmployee, curr, prev)){
        return 0;
    }

    if(strcmp(curr->employee->get_Occupation(), "Caretaker") == 0){
        return 1;
    }else if(strcmp(curr->employee->get_Occupation(), "Cleaner") == 0){
        return 2;
    }else {
        cout << endl << "Error in EmployeeList::EmployeeOccupation : Specified employee has no occupation." << endl;
        return 0;
    }

}

int EmployeeList::removeEmployee(int IDEmployee) {

    EmployeeNode *curr, *prev;
    int habNum = 0;

    if(findEmployee(IDEmployee, curr, prev)){
        if( (strcmp(curr->employee->get_Occupation(), "Caretaker") == 0) && (curr->designAnimal != nullptr) ){
            habNum = curr->designAnimal->get_habitatNo();
        }

        cout << endl << "The following employee is being fired: " << endl;
        curr->employee->print();
        removeNode(curr, prev);
        return habNum;
    }

    return -1;

}

int EmployeeList::chk_allEmployees() {

    EmployeeNode *curr = this->head, *prev = nullptr;
    int animalNum = 0;

    while(curr != nullptr){

        animalNum = chk_notifications(curr, prev);
        if(animalNum > 0){
            return animalNum;
        }

        if(curr == nullptr && prev == this->head){
            curr = this->head;
        }else if(curr == nullptr && prev != nullptr){
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }

    }

    return 0;

}

void EmployeeList::print(){

    EmployeeNode* curr = this->head;

    while(curr != nullptr){
        curr->employee->print();
        if(curr->designAnimal == nullptr){
            cout << "Designated Animal: none" << endl;
        }else {
            cout << "Designated Animal: " << curr->designAnimal->get_Species() << endl;
        }
        curr = curr->next;
    }

}

int EmployeeList::get_headEmpID() {
    int headID = this->head->employee->get_IDEmployee();
    return headID;
}

int EmployeeList::get_nextEmployee(int IDEmployee) {

    EmployeeNode *curr, *prev;
    if(!findEmployee(IDEmployee, curr, prev)){
        cerr << endl << "Error: The specified ID is not on the list." << endl;
        exit(1);
    }

    curr = curr->next;
    if(curr == nullptr){
        return 0;
    }

    return curr->employee->get_IDEmployee();

}

bool EmployeeList::feed(int IDEmployee, int currDay, int amount) {

    EmployeeNode* curr, *prev;

    if(!findEmployee(IDEmployee, curr, prev)){
        cout << endl << "Error in function EmployeeList::feed : Specified ID is not on the list." << endl;
        return false;
    }

    if(curr->designAnimal == nullptr){
        cout << endl << "Error in function EmployeeList::feed : Specified ID does not have a designated animal." << endl;
        return false;
    }

    if(strcmp(curr->employee->get_Occupation(), "Caretaker") == 0){
        amount = amount + curr->designAnimal->get_foodReceived();
        curr->designAnimal->set_foodReceived(amount);
        curr->designAnimal->set_foodLastTime(currDay);

        return true;
    }else{
        cout << endl << "Error in EmployeeList::feed : Specified Employee cannot give food to designated animal." << endl;
        return false;
    }


}

bool EmployeeList::allFeed(int currDay, int amount) {

    EmployeeNode *curr = this->head;

    while(curr != nullptr){

        if(strcmp(curr->employee->get_Occupation(), "Caretaker") == 0 && curr->designAnimal != nullptr){
            if(!feed(curr->employee->get_IDEmployee(), currDay, amount)){
                return false;
            }
        }

        curr = curr->next;
    }

    return true;
}

bool EmployeeList::clean(int IDEmployee, int currDay, int amount) {

    EmployeeNode* curr, *prev;

    if(!findEmployee(IDEmployee, curr, prev)){
        cout << endl << "Error in function EmployeeList::clean : Specified ID is not on the list." << endl;
        return false;
    }

    if(curr->designAnimal == nullptr){
        cout << endl << "Error in function EmployeeList::clean : Specified employee has no designated animal." << endl;
        return false;
    }

    if(strcmp(curr->employee->get_Occupation(), "Cleaner") == 0){
        amount = amount + curr->designAnimal->get_habitatCleaned();
        curr->designAnimal->set_habitatCleaned(amount);
        curr->designAnimal->set_cleanLastTime(currDay);
        return true;
    }else{
        cout << endl << "Error in EmployeeList::clean : Specified Employee cannot give food to designated animal." << endl;
        return false;
    }

}

bool EmployeeList::allClean(int currDay, int amount) {

    EmployeeNode *curr = this->head;

    while(curr != nullptr){

        if(strcmp(curr->employee->get_Occupation(), "Cleaner") == 0 && curr->designAnimal != nullptr){
            if(!clean(curr->ID,currDay, amount)){
                return false;
            }
        }

        curr = curr->next;
    }

    return true;
}

void EmployeeList::notify(int habitatNum, int currDay) {

    EmployeeNode* curr = this->head, *prev = nullptr;

    while(curr != nullptr){

        if(findHabAnimal(habitatNum, curr, prev)){
            if(chk_ifnotifyEmp(curr, currDay)){
                cout << endl << "The following employee received a notification: ";
                curr->employee->print();
            }

            curr = curr->next;
        }

    }

}

void EmployeeList::chk_forKilledEmployee(int IDEmployee) {

    if(IDEmployee == 0){
        return;
    }

    EmployeeNode *curr, *prev;

    if(findEmployee(IDEmployee, curr, prev)){
        if(curr == this->head){
            this->head = curr->next;
        }else if(curr->next == nullptr){
            prev->next = nullptr;
        }else{
            prev->next = curr->next;
        }

        curr->designAnimal = nullptr;
        curr->employee = nullptr;
        delete curr;
    }else{
        cout << endl << "Error in function EmployeeList::chk_forKilledEmployee : ";
        cout << "The specified ID does not correspond to any employee on the list." << endl;
    }

}

void EmployeeList::deassignateAnimal(int habitatNum) {

    EmployeeNode *curr = this->head, *prev = nullptr;

    if(!findHabAnimal(habitatNum, curr, prev)){
        cout << endl << "No employee was assigned to specified animal." << endl;
        return;
    }

    do{

        curr->designAnimal = nullptr;
        curr = curr->next;
        findHabAnimal(habitatNum, curr, prev);

    }while(curr != nullptr);

}
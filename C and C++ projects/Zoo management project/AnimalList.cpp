//
// Created by juanm on 24/04/2022.
//

#include "AnimalList.h"
#include <cstring>
#include <iostream>
using namespace std;

AnimalList::AnimalList() {

    this->head = nullptr;

}

AnimalList::~AnimalList() {

    AnimalNode* curr_next = this->head;

    while(curr_next != nullptr){
        curr_next = curr_next->next;

        this->head->animal->~AnimalHab();
        this->head->Caretaker = nullptr;
        delete this->head;

        this->head = curr_next;
    }

}

AnimalList::AnimalList(const AnimalList& copiedList){

    AnimalNode* newNode;
    AnimalNode* curr = copiedList.head;

    this->head = nullptr;

    while(curr != nullptr){

        AnimalNode* copiedNode = new AnimalNode();

        copiedNode->animal = new AnimalHab(*curr->animal);
        copiedNode->Caretaker = nullptr;

        copiedNode->next = nullptr;

        if(this->head == nullptr){
            this->head = copiedNode;
        }else{
            newNode->next = copiedNode;
        }

        newNode = copiedNode;
        curr = curr->next;
    }

}

AnimalList& AnimalList::operator=(const AnimalList &assignList) {

    if(this == &assignList){
        return *this;
    }

    AnimalNode* currList = this->head;

    while(currList != nullptr){
        currList = currList->next;

        this->head->animal->~AnimalHab();
        this->head->Caretaker = nullptr;
        delete this->head;

        this->head = currList;
    }

    AnimalNode* currAssign = assignList.head;

    while(currAssign != nullptr){

        AnimalNode* copiedNode = new AnimalNode();

        copiedNode->animal = new AnimalHab(*currAssign->animal);
        copiedNode->Caretaker = nullptr;

        copiedNode->next = nullptr;

        if(this->head == nullptr){
            this->head = copiedNode;
        }else{
            if(currList == nullptr){
                cout << endl << "In function: AnimalList::operator= : pointer accessed may be null" << endl;
                exit(1);
            }
            currList->next = copiedNode;
        }

        currList = copiedNode;
        currAssign = currAssign->next;
    }

    return *this;
}

int AnimalList::chk_habitat(AnimalNode *curr, AnimalNode *curr_next, int habitatNum) {

    if(curr_next != nullptr){

        if(curr->animal->get_habitatNo() > habitatNum){ // New Animal habitat at the beginning.
            return 1;
        }else if(curr->animal->get_habitatNo() < habitatNum && curr_next->animal->get_habitatNo() > habitatNum){ // New habitat animal in the middle.
            return 2;
        }else if(curr_next->animal->get_habitatNo() < habitatNum && curr_next->next == nullptr){ // New habitat animal at the end.
            return 3;
        }else if(curr->animal->get_habitatNo() == habitatNum){ // Current habitat already exists.
            return 4;
        }else if(curr_next->animal->get_habitatNo() == habitatNum){ // Next habitat already exists.
            return 5;
        }

    }else{ // curr_next is nullptr

        if(curr->animal->get_habitatNo() > habitatNum){ // New habitat animal at the beginning.
            return 1;
        }else if(curr->animal->get_habitatNo() < habitatNum && curr->next == nullptr){ // New habitat animal at the end.
            return 3;
        }else if(curr->animal->get_habitatNo() == habitatNum){ // Current habitat already exists.
            return 4;
        }

    }

    return 0;

}

bool AnimalList::findHabitat(int habNum, AnimalNode *&curr, AnimalNode *&prev) {

    curr = this->head;
    prev = nullptr;
    while(curr != nullptr){
        if(curr->animal->get_habitatNo() == habNum){
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;
}

void AnimalList::removeNode(AnimalNode*& curr, AnimalNode*& prev) {

    if(curr == this->head){
        this->head = curr->next;
    }else if(curr->next == nullptr){
        prev->next = nullptr;
    }else{
        prev->next = curr->next;
    }

    curr->animal->~AnimalHab();
    curr->Caretaker = nullptr;
    delete curr;

    if(prev == nullptr){
        curr = nullptr;
    }else{
        curr = prev->next;
    }

}

int AnimalList::chk_AnimalFood(AnimalNode* curr, int currDay) {

    int food = curr->animal->chk_food(currDay);

    if( food == 2 || food == 3){ // Caretaker is notified.
        return 1;
    }else if( food == 1 || food == 4){ // Caretaker is killed.
        return 2;
    }

    return 0;

}

int AnimalList::chk_AnimalClean(AnimalNode *curr, int currDay) {

    int clean = curr->animal->chk_cleaning(currDay);

    if(clean == 1 || clean == 4){ // Animal escapes.
        return 2;
    }else if( clean == 2){ // Cleaner is notified.
        return 1;
    }else if( clean == 3) { // Animal escapes.
        return 3;
    }

    return 0;
}

void AnimalList::addHabitat_inOrder(AnimalHab *newHabitat, AnimalNode *curr, int c) {

    AnimalNode* newNode = new AnimalNode();

    newNode->animal = newHabitat;
    newNode->Caretaker = nullptr;

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
            cout << endl << "Error in function AnimalList::addHabitat_inOrder : undefined value for parameter c." << endl;
            exit(1);
            break;
    }
}

void AnimalList::insertHab(AnimalHab *newHabitat) {

    AnimalNode* curr = nullptr;

    if(this->head == nullptr){
        addHabitat_inOrder(newHabitat, curr, 0);
        return;
    }

    curr = this->head;
    int c;
    while(curr != nullptr){

        c = chk_habitat(curr, curr->next, newHabitat->get_habitatNo());
        if(c > 0){
            addHabitat_inOrder(newHabitat, curr, c);
            return;
        }

        curr = curr->next;
    }

}

int AnimalList::get_numAnimalHab() {

    AnimalNode *curr = this->head;
    int count = 0;

    while(curr != nullptr){
        count++;
        curr = curr->next;
    }

    return count;
}

void AnimalList::addAnimalHab(int habitatNum, const char *Species, int foodFreq, int cleanFreq, int day) {

    AnimalNode* curr, *prev;
    if(findHabitat(habitatNum, curr, prev)){
        cout << endl << "Error in function AnimalList::addAnimalHab : the habitat already exists." << endl;
        return;
    }

    AnimalHab* newHabitat = new AnimalHab(habitatNum,Species,foodFreq,cleanFreq,day);

    insertHab(newHabitat);

}

void AnimalList::addAnimalHab(AnimalHab* habitat) {

    AnimalNode *curr, *prev;
    if(findHabitat(habitat->get_habitatNo(), curr, prev)){
        cout << endl << "Error in function AnimalList::addAnimalHab : the habitat already exists." << endl;
        return;
    }

    insertHab(habitat);

}

int AnimalList::removeAnimalHabitat(int habitatNum) {
    int habNum;

    AnimalNode *curr, *prev;
    if(findHabitat(habitatNum, curr, prev)){
        habNum = curr->animal->get_habitatNo();

        cout << endl << "The following Animal Habitat is being removed: " << endl;
        curr->animal->print();

        removeNode(curr, prev);
        return habNum;
    }

    return -1;

}

void AnimalList::AnimalEscapes(int habitatNum) {

    AnimalNode *curr, *prev;
    if(!findHabitat(habitatNum, curr, prev)){
        cout << endl << "Error in function AnimalList::AnimalEscapes : the specified habitat number is not on the list." << endl;
        exit(1);
    }

    cout << endl << "The following animal escaped: " << endl;
    curr->animal->print();
    removeNode(curr, prev);

}

int AnimalList::AnimalKills(int habitatNum) {

    AnimalNode *curr, *prev;
    if(!findHabitat(habitatNum, curr, prev)){
        cout << endl << "Error in function AnimalList::AnimalKills : the specified habitat number is not on the list." << endl;
        exit(1);
    }

    if(curr->Caretaker ==  nullptr){
        cout << endl << "The reported animal has no assigned caretaker." << endl;
        return 0;
    }

    int ID = curr->Caretaker->get_IDEmployee();

    cout << endl << "The employee " << curr->Caretaker->get_name() << " was killed by " <<  curr->animal->get_Species();
    cout << endl;
    curr->Caretaker->print();
    curr->Caretaker->~Employee();
    curr->Caretaker = nullptr;
    return ID;

}

bool AnimalList::set_Caretaker(int habitatNum, Employee* caretaker) {

    if(strcmp(caretaker->get_Occupation(), "Caretaker") != 0){
        cout << endl << "Error in function AnimalList::chk_Caretaker :: The specified employee is not of occupation Caretaker" << endl;
        return false;
    }

    AnimalNode *curr, *prev;
    if(findHabitat(habitatNum, curr, prev)){
        if(curr->Caretaker == nullptr){
            curr->Caretaker = caretaker;
            return true;
        }else{
            cout << endl << "Error in function AnimalList::set_Caretaker : The habitat number specified already has an assigned Caretaker."<< endl;
            return false;
        }

    }else{
        cout << endl << "Error in function AnimalList::set_Caretaker : The habitat number specified is not found." << endl;
    }

    return false;

}

AnimalHab* AnimalList::ret_assignAnimalHab(int habitatNum) {

    AnimalNode *curr, *prev;
    if(!findHabitat(habitatNum, curr, prev)){
        return nullptr;
    }

    return curr->animal;
}

bool AnimalList::deassignCaretaker(int habNum) {

    if(habNum == 0){
        return true;
    }

    AnimalNode *curr, *prev;

    if(!findHabitat(habNum, curr, prev)){
        cout << endl << "Error in function AnimalList::deassignCaretaker : The specified animal number is not on the list." << endl;
        return false;
    }

    curr->Caretaker = nullptr;
    return true;

}

int AnimalList::get_numHabHead() {
    int num;

    if(this->head == nullptr){
        cout << endl << "The Animal List has no animals in it." << endl;
        return 0;
    }else{
        num = this->head->animal->get_habitatNo();
    }

    return num;
}

int AnimalList::get_nextAnimalHab(int currHab) {

    AnimalNode *curr, *prev;
    if(!findHabitat(currHab, curr, prev)){
        cerr << endl << "Error in function AnimalList::get_nextAnimalHab : the habitat number specified is not on the list.";
        cerr << endl;
        exit(1);
    }

    curr = curr->next;
    if(curr == nullptr){
        return 0;
    }
    return curr->animal->get_habitatNo();

}

int AnimalList::chk_AnimalsCondition(int habNum, int currDay) {

    if(habNum == 0){
        return 0;
    }

    AnimalNode *curr = this->head, *prev;
    int miss = 0;

    if(!findHabitat(habNum, curr, prev)){
        cout << endl << "Error in AnimalList::chk_AnimalsCondition : The specified habitat number is not on the list." << endl;
        exit(1);
    }

    while(curr != nullptr){

        miss = chk_AnimalFood(curr, currDay);
        miss += chk_AnimalClean(curr, currDay);

        if(miss > 0){
            return curr->animal->get_habitatNo();
        }

        curr = curr->next;
    }

    return 0;

}

int AnimalList::case_AnimalCondition(int habNum, int currDay, int k) {

    AnimalNode *curr, *prev;
    if(!findHabitat(habNum, curr, prev)){
        cout << endl << "Error in function AnimalList::case_AnimalCondition : the specified habitat number is not on the list";
        cout << endl;
        return 0;
    }

    int Case = 0;

    if(k == 0){
        Case = chk_AnimalFood(curr, currDay);
        if(Case ==  1){
            cout << endl << "The habitat of animals: " << curr->animal->get_Species() << " received excessive amount of food." << endl;
        }else if(Case == 2){
            cout << endl << "The habitat of animals: " << curr->animal->get_Species() << " didn't receive food in the specified period.";
            cout << endl;
        }

    }else if(k == 1){
        Case = chk_AnimalClean(curr, currDay);
        if(Case == 1){
            cout << endl << "The habitat: " << curr->animal->get_Species() << " was cleaned in excess." << endl;
        }else if(Case == 2){
            cout << endl << "The habitat: " << curr->animal->get_Species() << " was not cleaned in the specified period." << endl;
        }else if(Case == 3) {
            cout << endl << "The habitat: " << curr->animal->get_Species() << " was cleaned overly in excess." << endl;
        }

    }else {
        cout << endl << "Error in function AnimalList::case_AnimalCondition : Undefined value for parameter k." << endl;
        exit(1);
    }

    return Case;

}

void AnimalList::new_day(int currDay) {

    int amount;
    AnimalNode *curr = this->head;

    while(curr != nullptr){

        if(curr->animal->chk_foodPeriod(currDay)){
            amount = curr->animal->get_foodReceived();
            amount -= 1;
            curr->animal->set_foodReceived(amount);
        }

        if(curr->animal->chk_cleaningPeriod(currDay)){
            amount = curr->animal->get_habitatCleaned();
            amount -= 1;
            curr->animal->set_habitatCleaned(amount);
        }

        curr = curr->next;

    }
}

void AnimalList::print() {

    AnimalNode* curr = this->head;

    while(curr != nullptr){

        curr->animal->print();
        if(curr->Caretaker == nullptr){
            cout << "Caretaker : none " << endl;
        }else {
            cout << "Caretaker : " << curr->Caretaker->get_name() << endl;
        }
        curr = curr->next;

    }

}
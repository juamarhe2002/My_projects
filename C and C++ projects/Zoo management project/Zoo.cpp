//
// Created by juanm on 24/04/2022.
//

#include "Zoo.h"
#include <cstring>
#include <iostream>
using namespace std;

Zoo::Zoo() {

    this->animalList = new AnimalList();
    this->employeeList = new EmployeeList();

    this->currDay = 0;

}

Zoo::~Zoo() {

    this->animalList->~AnimalList();
    this->employeeList->~EmployeeList();

}

Zoo::Zoo(const Zoo &copiedZoo) {

    this->animalList = new AnimalList(*copiedZoo.animalList);
    this->employeeList = new EmployeeList(*copiedZoo.employeeList);

    int employee = copiedZoo.employeeList->get_headEmpID();
    int animal;

    while(employee != 0){

        animal = copiedZoo.employeeList->designatedAnimal(employee);
        assignAnimalEmployee(animal, employee);
        employee = copiedZoo.employeeList->get_nextEmployee(employee);

    }

    this->currDay = copiedZoo.currDay;

}

int Zoo::get_currDay() const {
    int ret = this->currDay;
    return ret;
}

void Zoo::set_currDay(int Day) {

    if(Day < this->currDay){
        cout << endl << "Error in function Zoo::currDay : The newly specified day is before the actual one." << endl;
        exit(1);
    }

    this->currDay = Day;

}

int Zoo::get_numberElements() {
    int total;

    total = this->employeeList->get_numEmployees();
    total += this->animalList->get_numAnimalHab();

    return total;
}

bool Zoo::chk_Occupation(const char *Occupation) {

    if(strcmp(Occupation, "Caretaker") == 0){
        return true;
    }else if(strcmp(Occupation, "Cleaner") == 0){
        return true;
    }

    return false;
}

void Zoo::hireEmployee(int IDEmployee, const char *name, const char *Occupation) {

    if(IDEmployee <= 0){
        cout << endl << "Error in function Zoo::hireEmployee : The specified ID cannot be less or equal to 0." <<  endl;
        return;
    }

    if(!this->employeeList->chk_Credentials(IDEmployee, name)){
        return;
    }

    if(!chk_Occupation(Occupation)){
        cout << endl << "Error: The occupation specified is misspelled or incorrect." << endl;
        return;
    }

    Employee* newEmployee = new Employee(IDEmployee, name, Occupation);

    this->employeeList->insertEmployee(newEmployee);

}

void Zoo::fireEmployee(int IDEmployee) {

    int habNum = this->employeeList->removeEmployee(IDEmployee);

    if( habNum == -1){
        cout << endl << "Error in function Zoo::fireEmployee : The specified employee is not on the list." << endl;
        return;
    }

    this->animalList->deassignCaretaker(habNum);

}

void Zoo::newAnimalHabitat(int habitatNum, const char *Species, int foodFreq, int cleanFreq) {

    if( foodFreq <= 0){
        cout << endl << "Error in function Zoo::newAnimalHabitat : Food frequency of an animal cannot be zero or below." << endl;
        return;
    }else if( cleanFreq <= 0){
        cout << endl << "Error in function Zoo::newAnimalHabitat : Clean frequency of an animal cannot be zero or below." << endl;
        return;
    }

    AnimalHab* newHabitat = new AnimalHab(habitatNum, Species, foodFreq, cleanFreq, this->currDay);

    this->animalList->addAnimalHab(newHabitat);

}

void Zoo::removeAnimalHabitat(int habitatNum) {
    int habNum = this->animalList->removeAnimalHabitat(habitatNum);

    if(habNum == -1){
        cout << endl << "Error in function Zoo::removeAnimalHabitat : the habitat number is not on the list." << endl;
        return;
    }

    this->employeeList->deassignateAnimal(habNum);

}

void Zoo::assignAnimalEmployee(int habitatNum, int IDEmployee) {

    if(habitatNum == 0){
        return;
    }

    int occ = this->employeeList->EmployeeOccupation(IDEmployee);
    Employee *assignEmployee = this->employeeList->ret_assignEmployee(IDEmployee);

    if(assignEmployee == nullptr || occ == 0){
        cout << endl << "Error in Zoo::assignAnimalEmployee : The specified ID is not on the employee list." << endl;
        return;
    }

    AnimalHab* assignHab = this->animalList->ret_assignAnimalHab(habitatNum);
    if(assignHab == nullptr){
        cout << endl << "Error in function Zoo::assignAnimalEmployee : The specified habitat number is not on the list." << endl;
        return;
    }

    if(!this->employeeList->chk_assignPossibletoEmployee(IDEmployee)){
        cout << endl << "Error in function Zoo::assignAnimalEmployee : Assignation not possible." << endl;
        return;
    }

    if(occ == 1){
        if(!this->animalList->set_Caretaker(habitatNum, assignEmployee)){
            cout << endl << "Error  in function Zoo::assignAnimalEmployee : Assignation not possible to given animal." << endl;
            return;
        }
    }

    if(!this->employeeList->assignAnimal(IDEmployee, assignHab)){
        cout << endl << "Error in function Zoo::assignAnimalEmployee : Assignation not possible to given employee." << endl;
        return;
    }
}

void Zoo::workFeeding(int amount) {

    if(!this->employeeList->allFeed(this->currDay, amount)){
        cout << endl << "Error in function Zoo::workFeeding : Not all the Caretakers were able to feed their animals." << endl;
        return;
    }

}

void Zoo::employeeFeeds(int IDEmployee, int amount) {

    if(!this->employeeList->feed(IDEmployee, this->currDay, amount)){
        cout << endl << "Error in function Zoo::employeeFeeds : Feeding was not possible." << endl;
        return;
    }

}

void Zoo::workCleaning(int amount) {

    if(!this->employeeList->allClean(this->currDay, amount)){
        cout << endl << "Error in function Zoo::workCleaning : Not all Cleaners were able to clean their animals." << endl;
        return;
    }

}

void Zoo::employeeCleans(int IDEmployee, int amount) {

    if(!this->employeeList->clean(IDEmployee, this->currDay, amount)){
        cout << endl << "Error in function Zoo::employeeCleans : Cleaning was not possible." << endl;
        return;
    }

}

void Zoo::AnimalsCondition(int day) {

    if(this->currDay != day){
        set_currDay(day);
    }

    int reported = this->animalList->get_numHabHead();
    int food = 0, clean = 0;
    int nextHab, killed;

    while( reported != 0 ){

        food = this->animalList->case_AnimalCondition(reported, this->currDay, 0);
        clean = this->animalList->case_AnimalCondition(reported, this->currDay, 1);
        nextHab = this->animalList->get_nextAnimalHab(reported);

        if(food == 1 || clean == 1) {
            this->employeeList->notify(reported, this->currDay);
        }

        if(food == 2){
            killed = this->animalList->AnimalKills(reported);
            this->employeeList->chk_forKilledEmployee(killed);
        }

        if(clean == 2 || clean == 3){
            this->animalList->AnimalEscapes(reported);
            this->employeeList->deassignateAnimal(reported);
        }

        reported = this->animalList->chk_AnimalsCondition(nextHab, this->currDay);

    }

}

void Zoo::DayPasses(int newDay) {

    if(this->currDay != newDay){
        set_currDay(newDay);
    }

    this->animalList->new_day(this->currDay);

    int animalHab;

    do{

        animalHab = this->employeeList->chk_allEmployees();
        if(!this->animalList->deassignCaretaker(animalHab)){
            cout << endl << "Error in function Zoo::DayPasses : De-asignation of Caretaker was not possible." << endl;
            return;
        }

    }while(animalHab != 0);

}

void Zoo::print(){

    cout << endl << "..........Employee List........" << endl;

    this->employeeList->print();

    cout << endl << "..........Animal List.........." << endl;

    this->animalList->print();

}
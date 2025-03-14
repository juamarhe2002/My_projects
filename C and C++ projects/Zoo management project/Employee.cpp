//
// Created by juanm on 23/04/2022.
//

#include "Employee.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

Employee::Employee(int IDEmployee, const char *name, const char *Occupation) {

    this->IDEmployee = IDEmployee;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->Occupation = new char[strlen(Occupation) + 1];
    strcpy(this->Occupation, Occupation);
    this->notifications = 0;

}

Employee::~Employee() {

    //print();
    delete[] this->name;
    delete[] this->Occupation;

}

Employee::Employee(const Employee &copiedEmployee) {

    this->IDEmployee = copiedEmployee.IDEmployee;
    this->name = new char[strlen(copiedEmployee.name) + 1];
    strcpy(this->name, copiedEmployee.name);
    this->Occupation = new char[strlen(copiedEmployee.Occupation) + 1];
    strcpy(this->Occupation, copiedEmployee.Occupation);
    this->notifications = copiedEmployee.notifications;

}

int Employee::get_IDEmployee() const {
    int retID = this->IDEmployee;
    return retID;
}

const char* Employee::get_name() const {
    const char* retName = this->name;
    return retName;
}

const char* Employee::get_Occupation() const {
    const char* retOcc = this->Occupation;
    return retOcc;
}

int & Employee::get_notifications(){

    return this->notifications;

}

void Employee::print() {

    cout << endl << "ID: " << this->IDEmployee << endl;
    cout << "Name: " << this->name <<  endl;
    cout << "Occupation: " << this->Occupation <<  endl;
    cout << "Number of notifications: " << this->notifications <<  endl;

}

//
// Created by juanm on 17/05/2022.
//

#include "TestCases.h"
#include <iostream>
using namespace std;

bool TestAnimalsCondition_normalDay(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestAnimalsCondition_normalDay ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "-------------------------- Testing day without notifications (Day 1)--------------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestAnimalsCondition_normalDay ******************************" << endl;

    return true;

}

bool TestAnimalsCondition_notifyCaretaker(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestAnimalsCondition_notifyCaretaker ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "-------------------------- Notifying Caretaker beginning --------------------------" << endl;

    cout << endl << "Setting proper environment (Employee 1)." << endl;
    Auto.employeeFeeds(1, 2);
    Dyn->employeeFeeds(1, 2);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Notifying Caretaker middle --------------------------" << endl;

    cout << endl << "Setting proper environment (Employee 3)." << endl;
    Auto.employeeFeeds(3, 2);
    Dyn->employeeFeeds(3, 2);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Notifying Caretaker end --------------------------" << endl;

    cout << endl << "Setting proper environment (Employee 7)." << endl;
    Auto.employeeFeeds(7, 2);
    Dyn->employeeFeeds(7, 2);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Notifying Caretaker with no designated animal --------------------------" << endl;

    cout << endl << "Setting proper environment (Employee 5)." << endl;
    Auto.employeeFeeds(5, 2);
    Dyn->employeeFeeds(5, 2);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestAnimalsCondition_notifyCaretaker ******************************" << endl;


    return true;
}

bool TestAnimalsCondition_notifyCleaner(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestAnimalsCondition_notifyCleaner ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "-------------------------- Notifying Cleaners --------------------------" << endl;

    cout << endl << "Setting proper environment (Employees 2, 4, 6)." << endl;
    Auto.employeeCleans(2, 2);
    Dyn->employeeCleans(2, 2);
    Auto.employeeCleans(4, 2);
    Dyn->employeeCleans(4, 2);
    Auto.employeeCleans(6, 2);
    Dyn->employeeCleans(6, 2);

    cout << endl << "Running for all cases: (Beginning, middle, end) and repeated animal in another Cleaner 8." << endl;

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();


    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestAnimalsCondition_notifyCleaner ******************************" << endl;

    return true;
}

bool TestAnimalsCondition_killCaretaker(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestAnimalsCondition_killCaretaker ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "-------------------------- Killing Caretaker beginning --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.set_currDay(1);
    Dyn->set_currDay(1);
    Auto.employeeFeeds(3, 0);
    Dyn->employeeFeeds(3, 0);
    Auto.employeeFeeds(7, 0);
    Dyn->employeeFeeds(7, 0);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(2);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(2);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Killing Caretaker middle --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.employeeFeeds(7, 0);
    Dyn->employeeFeeds(7, 0);
    Auto.workCleaning(0);
    Dyn->workCleaning(0);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(3);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(3);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Killing Caretaker end --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.fireEmployee(8);
    Dyn->fireEmployee(8);
    Auto.workCleaning(0);
    Dyn->workCleaning(0);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(4);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(4);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestAnimalsCondition_killCaretaker ******************************" << endl;

    return true;
}

bool TestAnimalsCondition_escapedAnimal(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestAnimalsCondition_escapedAnimal ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "-------------------------- Animal Escapes beginning --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.employeeCleans(2,3);
    Dyn->employeeCleans(2,3);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Animal Escapes middle --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.set_currDay(3);
    Dyn->set_currDay(3);
    Auto.workFeeding(0);
    Dyn->workFeeding(0);
    Auto.workCleaning(0);
    Dyn->workCleaning(0);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(3);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(3);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Animal Escapes end --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.employeeCleans(6, 3);
    Dyn->employeeCleans(6, 3);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(3);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(3);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Animal Escapes with multiple Cleaners and killing Caretaker --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;
    Auto.set_currDay(6);
    Dyn->set_currDay(6);

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(6);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(6);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "-------------------------- Animal Escapes from list with no animals --------------------------" << endl;

    cout << endl << "Setting proper environment." << endl;

    cout << endl << "Auto" << endl;
    Auto.AnimalsCondition(6);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->AnimalsCondition(6);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestAnimalsCondition_escapedAnimal ******************************" << endl;

    return true;

}
//
// Created by juanm on 14/05/2022.
//

#include "TestCases.h"
#include "Zoo.h"
#include <cassert>
#include <iostream>
using namespace std;

bool TestZoo_numberElements(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_numberElements ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "Original number of elements (11)" << endl;
    assert(11 == Auto.get_numberElements());
    assert(11 == Dyn->get_numberElements());

    cout << endl << "Number of elements 9" << endl;
    Auto.fireEmployee(1);
    Auto.removeAnimalHabitat(2);
    Dyn->fireEmployee(1);
    Dyn->removeAnimalHabitat(2);

    assert(9 == Auto.get_numberElements());
    assert(9 == Dyn->get_numberElements());

    cout << endl << "Number of elements 12" << endl;
    Auto.hireEmployee(9, "AutoEmp9", "Caretaker");
    Auto.hireEmployee(10, "AutoEmp10", "Cleaner");
    Auto.hireEmployee(11, "AutoEmp11", "Caretaker");
    Dyn->hireEmployee(9, "DynEmp9", "Caretaker");
    Dyn->hireEmployee(10, "DynEmp10", "Cleaner");
    Dyn->hireEmployee(11, "DynEmp11", "Caretaker");

    assert(12 == Auto.get_numberElements());
    assert(12 == Dyn->get_numberElements());

    cout << endl << "No elements on AnimalList" << endl;
    Auto.removeAnimalHabitat(4);
    Auto.removeAnimalHabitat(5);
    Auto.removeAnimalHabitat(6);
    Dyn->removeAnimalHabitat(4);
    Dyn->removeAnimalHabitat(5);
    Dyn->removeAnimalHabitat(6);

    assert(9 == Auto.get_numberElements());
    assert(9 == Dyn->get_numberElements());

    cout << endl << "No elements on EmployeeList but nonempty AnimalList" << endl;
    Auto.~Zoo();
    Dyn->~Zoo();
    Dyn = new Zoo();
    Auto.newAnimalHabitat(2, "AutoAnimal2", 1, 2);
    Dyn->newAnimalHabitat(2, "DynAnimal2", 1, 2);

    assert(1 == Auto.get_numberElements());
    assert(1 == Dyn->get_numberElements());

    cout << "No elements on the lists" << endl;
    Auto.removeAnimalHabitat(2);
    Dyn->removeAnimalHabitat(2);

    assert(0 == Auto.get_numberElements());
    assert(0 == Dyn->get_numberElements());

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_numberElements ******************************" << endl;

    return true;
}

bool TestZoo_wrongHireEmployee(Zoo Auto, Zoo* Dyn){

    cout << endl << "********************* Start : TestZoo_wrongHireEmployee ******************************" << endl;

    cout << endl << "Adding a new employee with an ID of 0 or less." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(0, "AutoEmp0", "Caretaker");
    Auto.hireEmployee(-1, "AutoEmp-1", "Caretaker");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(0, "DynEmp0", "Cleaner");
    Dyn->hireEmployee(-1, "DynEmp-1", "Cleaner");
    Dyn->print();

    cout << endl << "Adding a new employee with the same ID at the beginning, middle and end." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(2, "RepAutoEmp1", "Caretaker");
    Auto.hireEmployee(4, "RepAutoEmp3", "Caretaker");
    Auto.hireEmployee(6, "RepAutoEmp5", "Caretaker");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(2, "RepDynEmp1", "Cleaner");
    Dyn->hireEmployee(4, "RepDynEmp3", "Cleaner");
    Dyn->hireEmployee(6, "RepDynEmp5", "Cleaner");
    Dyn->print();

    cout << endl << "Adding a new employee with the same name at the beginning, middle and end." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(8, "AutoEmp1", "Caretaker");
    Auto.hireEmployee(9, "AutoEmp3", "Caretaker");
    Auto.hireEmployee(10, "AutoEmp5", "Caretaker");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(8, "DynEmp1", "Cleaner");
    Dyn->hireEmployee(9, "DynEmp3", "Cleaner");
    Dyn->hireEmployee(10, "DynEmp5", "Cleaner");
    Dyn->print();

    cout << endl << "Adding a new employee with a wrong or misspelled occupation." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(9, "AutoEmp9", "Farmer");
    Auto.hireEmployee(10, "AutoEmp10", "Takercare");
    Auto.hireEmployee(11, "AutoEmp11", "Nerclea");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(9, "DynEmp9", "Farmer");
    Dyn->hireEmployee(10, "DynEmp10", "Takercare");
    Dyn->hireEmployee(11, "DynEmp11", "Nerclea");
    Dyn->print();

    cout << endl << "********************* END : TestZoo_wrongHireEmployee ******************************" << endl;

    return true;
}

bool TestZoo_fireEmployee(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_fireEmployee ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "Removing an element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.fireEmployee(1);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->fireEmployee(1);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing an element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.fireEmployee(5);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    Dyn->fireEmployee(5);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing an element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.fireEmployee(8);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    Dyn->fireEmployee(8);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing a non existent element." << endl;
    cout << endl << "Auto" << endl;
    Auto.fireEmployee(0);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    Dyn->fireEmployee(0);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Leaving a list empty." << endl;
    cout << endl << "Auto" << endl;
    Auto.fireEmployee(2);
    Auto.fireEmployee(3);
    Auto.fireEmployee(4);
    Auto.fireEmployee(6);
    Auto.fireEmployee(7);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    Dyn->fireEmployee(2);
    Dyn->fireEmployee(3);
    Dyn->fireEmployee(4);
    Dyn->fireEmployee(6);
    Dyn->fireEmployee(7);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing from an empty list." << endl;
    cout << endl << "Auto" << endl;
    Auto.fireEmployee(3);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    Dyn->fireEmployee(3);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_fireEmployee ******************************" << endl;

    return true;

}

bool TestZoo_wrongNewAnimalHabitat(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_wrongNewAnimalHabitat ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "Adding a new element with food frequency less or equal to zero." << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(9, "AutoAnimal9F", 0, 2);
    Auto.newAnimalHabitat(10, "AutoAnimal10F", -1, 2);
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->newAnimalHabitat(9, "DynAnimal9F", 0, 2);
    Dyn->newAnimalHabitat(10, "DynAnimal10F", -1, 2);
    Dyn->print();

    cout << endl << "Adding a new element with clean frequency less or equal to zero." << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(9, "AutoAnimal9C", 1, 0);
    Auto.newAnimalHabitat(10, "AutoAnimal10C", 1, -1);
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->newAnimalHabitat(9, "DynAnimal9C", 1, 0);
    Dyn->newAnimalHabitat(10, "DynAnimal10C", 1, -1);
    Dyn->print();

    cout << endl << "Adding a new element with the same Habitat number at the beginning, middle and end." << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(2, "RepAutoAnimal2", 1, 2);
    Auto.newAnimalHabitat(4, "RepAutoAnimal4", 1, 2);
    Auto.newAnimalHabitat(6, "RepAutoAnimal6", 1, 2);
    Auto.print();
    cout << endl << "List 1" << endl;
    Dyn->newAnimalHabitat(2, "RepDynAnimal2", 1, 2);
    Dyn->newAnimalHabitat(4, "RepDynAnimal4", 1, 2);
    Dyn->newAnimalHabitat(6, "RepDynAnimal6", 1, 2);
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_wrongNewAnimalHabitat ******************************" << endl;

    return true;
}

bool TestZoo_removeAnimalHabitat(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_removeAnimalHabitat ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "Removing an element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(2);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->removeAnimalHabitat(2);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing an element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(5);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->removeAnimalHabitat(5);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing an element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(6);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->removeAnimalHabitat(6);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing an element that is not in the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(1);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->removeAnimalHabitat(1);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing all elements from the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(4);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->removeAnimalHabitat(4);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "Removing element from empty list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(6);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->removeAnimalHabitat(6);
    cout << endl << "Dyn (After removal)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_removeAnimalHabitat ******************************" << endl;

    return true;
}

bool TestZoo_assignAnimalEmployee(Zoo &Auto, Zoo* &Dyn){

    cout << endl << "********************* Start : TestZoo_assignAnimalEmployee ******************************" << endl;

    cout << endl << "Assigning of non existent Employee." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(6,9);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(6, 9);
    Dyn->print();

    cout << endl << "Assigning of non existent AnimalHab." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(9,7);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(9, 7);
    Dyn->print();

    cout << endl << "--------------------Assigning Caretakers to the animals.--------------------------" << endl;

    cout << endl << "Caretaker 1 and AnimalHab 2 assigned (beginning)." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(2,1);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(2, 1);
    Dyn->print();

    cout << endl << "Caretaker 3 and AnimalHab 4 assigned (middle)." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(4,3);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(4, 3);
    Dyn->print();

    cout << endl << "Caretaker 7 and AnimalHab 6 assigned (end)." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(6,7);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(6, 7);
    Dyn->print();

    cout << endl << "Assigning Caretaker to AnimalHab that already has a Caretaker." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(2,5);
    Auto.assignAnimalEmployee(4,5);
    Auto.assignAnimalEmployee(6,5);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(2, 5);
    Dyn->assignAnimalEmployee(4, 5);
    Dyn->assignAnimalEmployee(6, 5);
    Dyn->print();

    cout << endl << "Assigning AnimalHab to Caretaker that already has an AnimalHab." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(5,1);
    Auto.assignAnimalEmployee(5,3);
    Auto.assignAnimalEmployee(5,7);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(5, 1);
    Dyn->assignAnimalEmployee(5, 3);
    Dyn->assignAnimalEmployee(5, 7);
    Dyn->print();

    cout << endl << "--------------------Assigning Cleaners to the animals.--------------------------" << endl;

    cout << endl << "Cleaner 2 and AnimalHab 2 assigned (beginning)." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(2,2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(2, 2);
    Dyn->print();

    cout << endl << "Cleaner 4 and AnimalHab 4 assigned (middle)." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(4,4);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(4, 4);
    Dyn->print();

    cout << endl << "Cleaner 6 and AnimalHab 6 assigned (end)." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(6,6);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(6, 6);
    Dyn->print();

    cout << endl << "Assigning AnimalHab to Cleaner that already has an AnimalHab." << endl;
    cout << endl << "Auto" << endl;
    Auto.assignAnimalEmployee(5,2);
    Auto.assignAnimalEmployee(5,4);
    Auto.assignAnimalEmployee(5,6);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->assignAnimalEmployee(5, 2);
    Dyn->assignAnimalEmployee(5, 4);
    Dyn->assignAnimalEmployee(5, 6);
    Dyn->print();

    cout << endl << "Creating a new Cleaner and assigning it to an animal that already has a Cleaner" << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(8, "AutoEmp8", "Cleaner");
    Auto.assignAnimalEmployee(4, 8);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(8, "DynEmp8", "Cleaner");
    Dyn->assignAnimalEmployee(4, 8);
    Dyn->print();

    cout << endl << "********************* END : TestZoo_assignAnimalEmployee ******************************" << endl;

    return true;
}

bool TestZoo_feeding(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_feeding ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    Auto.set_currDay(1);
    Dyn->set_currDay(1);

    cout << endl << "------------------------Testing feeding individually with employeeFeeds------------------------" << endl;

    cout << endl << "Feeding animal at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeFeeds(1, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeFeeds(1,2);
    Dyn->print();

    cout << endl << "Feeding animal at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeFeeds(3, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeFeeds(3,2);
    Dyn->print();

    cout << endl << "Feeding animal at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeFeeds(7, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeFeeds(7,2);
    Dyn->print();

    cout << endl << "Non existent employee feeding." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeFeeds(10, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeFeeds(10,2);
    Dyn->print();

    cout << endl << "Caretaker without an assigned animal feeding" << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeFeeds(5, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeFeeds(5,2);
    Dyn->print();

    cout << endl << "Cleaner feeding an animal" << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeFeeds(6, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeFeeds(6,2);
    Dyn->print();

    cout << endl << "------------------------Testing full feeding with workFeeding------------------------" << endl;

    cout << endl << "Auto (before)" << endl;
    Auto.print();
    cout << endl << "Auto (after)" << endl;
    Auto.workFeeding(2);
    Auto.print();

    cout << endl << "Dyn (before)" << endl;
    Dyn->print();
    cout << endl << "Dyn (after)" << endl;
    Dyn->workFeeding(2);
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_feeding ******************************" << endl;

    return true;
}

bool TestZoo_cleaning(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_cleaning ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    Auto.set_currDay(2);
    Dyn->set_currDay(2);

    cout << endl << "------------------------Testing cleaning individually with employeeCleans------------------------" << endl;

    cout << endl << "Cleaning animal at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeCleans(2, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeCleans(2,2);
    Dyn->print();

    cout << endl << "Cleaning animal at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeCleans(4, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeCleans(4,2);
    Dyn->print();

    cout << endl << "Cleaning animal at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeCleans(6, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeCleans(6,2);
    Dyn->print();

    cout << endl << "Repeated cleaning of animal with another cleaner (habitat 4)." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeCleans(8, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeCleans(8,2);
    Dyn->print();

    cout << endl << "Non existent Employee cleaning" << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeCleans(12, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeCleans(12,2);
    Dyn->print();

    cout << endl << "Caretaker cleaning an animal." << endl;
    cout << endl << "Auto" << endl;
    Auto.employeeCleans(7, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->employeeCleans(7,2);
    Dyn->print();

    cout << endl << "Cleaner without a designated animal cleaning." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(10, "AutoEmp10", "Cleaner");
    Auto.employeeCleans(10, 2);
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(10, "DynEmp10", "Cleaner");
    Dyn->employeeCleans(10,2);
    Dyn->print();

    cout << endl << "------------------------Testing full cleaning with workCleaning------------------------" << endl;

    cout << endl << "Auto (before)" << endl;
    Auto.print();
    cout << endl << "Auto (after)" << endl;
    Auto.workCleaning(2);
    Auto.print();

    cout << endl << "Dyn (before)" << endl;
    Dyn->print();
    cout << endl << "Dyn (after)" << endl;
    Dyn->workCleaning(2);
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_cleaning ******************************" << endl;

    return true;

}

bool TestZoo_AnimalsCondition(Zoo Auto, Zoo* DynC){

    cout << endl << "********************* Start : TestZoo_AnimalsCondition ******************************" << endl;

    TestAnimalsCondition_normalDay(Auto, DynC);

    TestAnimalsCondition_notifyCaretaker(Auto, DynC);

    TestAnimalsCondition_notifyCleaner(Auto, DynC);

    TestAnimalsCondition_killCaretaker(Auto, DynC);

    TestAnimalsCondition_escapedAnimal(Auto, DynC);

    cout << endl << "********************* END : TestZoo_AnimalsCondition ******************************" << endl;

    return true;

}

bool TestZoo_DayPasses(Zoo Auto, Zoo *DynC) {

    cout << endl << "********************* Start : TestZoo_DayPasses ******************************" << endl;

    cout << endl << "Copying dynamically allocated memory." << endl;
    Zoo* Dyn = new Zoo(*DynC);
    Dyn->print();

    cout << endl << "--------------------- End of Day (Day 1) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(1);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(1);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- End of Day (Day 2) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(2);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(2);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- Firing employee at the beginning ---------------------" << endl;

    cout << endl << "Setting proper environment" << endl;
    Auto.set_currDay(3);
    Dyn->set_currDay(3);
    Auto.workFeeding(1);
    Dyn->workFeeding(1);
    Auto.employeeCleans(2,1);
    Auto.employeeCleans(4, 1);
    Auto.employeeCleans(6, 1);
    Dyn->employeeCleans(2, 1);
    Dyn->employeeCleans(4, 1);
    Dyn->employeeCleans(6, 1);
    Auto.employeeFeeds(1, 1);
    Dyn->employeeFeeds(1,1);
    Auto.AnimalsCondition(3);
    Auto.AnimalsCondition(3);
    Dyn->AnimalsCondition(3);
    Dyn->AnimalsCondition(3);

    cout << endl << "--------------------- Day passes (Day 3) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(3);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(3);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- Firing employee at the middle ---------------------" << endl;

    cout << endl << "Setting proper environment" << endl;
    Auto.DayPasses(4);
    Dyn->DayPasses(4);
    Auto.DayPasses(5);
    Dyn->DayPasses(5);
    Auto.set_currDay(6);
    Dyn->set_currDay(6);
    Auto.workFeeding(1);
    Dyn->workFeeding(1);
    Auto.employeeCleans(2,1);
    Auto.employeeCleans(4, 1);
    Auto.employeeCleans(6, 1);
    Dyn->employeeCleans(2, 1);
    Dyn->employeeCleans(4, 1);
    Dyn->employeeCleans(6, 1);
    Auto.employeeCleans(6, 1);
    Dyn->employeeCleans(6, 1);
    Auto.AnimalsCondition(6);
    Auto.AnimalsCondition(6);
    Dyn->AnimalsCondition(6);
    Dyn->AnimalsCondition(6);

    cout << endl << "--------------------- Day passes (Day 6) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(6);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(6);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- Firing employee at the end ---------------------" << endl;

    cout << endl << "Setting proper environment" << endl;
    Auto.DayPasses(7);
    Dyn->DayPasses(7);
    Auto.DayPasses(8);
    Dyn->DayPasses(8);
    Auto.set_currDay(9);
    Dyn->set_currDay(9);
    Auto.workFeeding(1);
    Dyn->workFeeding(1);
    Auto.workCleaning(1);
    Dyn->workCleaning(1);
    Auto.AnimalsCondition(9);
    Auto.AnimalsCondition(9);
    Dyn->AnimalsCondition(9);
    Dyn->AnimalsCondition(9);

    cout << endl << "--------------------- Day passes (Day 9) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(9);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(9);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- Firing employees with designated animals ---------------------" << endl;

    cout << endl << "Setting proper environment" << endl;
    Auto.set_currDay(11);
    Dyn->set_currDay(11);
    Auto.workFeeding(1);
    Dyn->workFeeding(1);
    Auto.workCleaning(1);
    Dyn->workCleaning(1);
    Auto.AnimalsCondition(11);
    Dyn->AnimalsCondition(11);
    Auto.AnimalsCondition(11);
    Dyn->AnimalsCondition(11);

    cout << endl << "--------------------- Day passes (Day 11) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(11);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(11);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- Day passing with no animals ---------------------" << endl;

    cout << endl << "Setting proper environment" << endl;
    Auto.DayPasses(13);
    Dyn->DayPasses(13);
    Auto.AnimalsCondition(14);
    Dyn->AnimalsCondition(14);

    cout << endl << "--------------------- Day passes (Day 14) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(14);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(14);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "--------------------- Day passing with empty lists ---------------------" << endl;

    cout << endl << "Setting proper environment" << endl;
    Auto.fireEmployee(5);
    Auto.fireEmployee(7);
    Dyn->fireEmployee(5);
    Dyn->fireEmployee(7);

    cout << endl << "--------------------- Day passes (Day 15) ---------------------" << endl;

    cout << endl << "Auto" << endl;
    Auto.DayPasses(15);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->DayPasses(15);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "//////////////Eliminating dynamically allocated memory//////////////" << endl;
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "********************* END : TestZoo_DayPasses ******************************" << endl;

    return true;
}


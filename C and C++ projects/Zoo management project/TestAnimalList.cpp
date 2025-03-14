//
// Created by juanm on 8/05/2022.
//

#include <iostream>
#include "TestCases.h"
#include "Employee.h"
#include "AnimalList.h"
using namespace std;

void testBasicAnimalList(){

    cout << endl << "Basic tests Animal List" << endl;

    AnimalList Auto;
    AnimalList* List1 = new AnimalList();

    cout << endl << "Auto: Adding a new animal to the empty list (full info)." << endl;
    Auto.addAnimalHab(5, "AutoAnimal5", 1, 2, 1);
    Auto.print();

    cout << endl << "List1 : Adding a new animal to the empty list (full info)." << endl;
    List1->addAnimalHab(5, "DynAnimal5", 1, 2, 1);
    List1->print();

    cout << endl << "Adding a new element at the beginning of the list (full info)." << endl;
    cout << endl << "Auto" << endl;
    Auto.addAnimalHab(2, "AutoAnimal2", 1, 2, 1);
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addAnimalHab(2, "DynAnimal2", 1, 2, 1);
    List1->print();

    cout << endl << "Adding a new element at the middle of the list (full info)." << endl;
    cout << endl << "Auto" << endl;
    Auto.addAnimalHab(4, "AutoAnimal4", 1, 2, 1);
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addAnimalHab(4, "DynAnimal4", 1, 2, 1);
    List1->print();

    cout << endl << "Adding a new element at the end of the list (full info)." << endl;
    cout << endl << "Auto" << endl;
    Auto.addAnimalHab(6, "AutoAnimal6", 1, 2, 1);
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addAnimalHab(6, "DynAnimal6", 1, 2, 1);
    List1->print();

    cout << endl << "Adding a new element with the same Habitat number at the beginning, middle and end (full info)." << endl;
    cout << endl << "Auto" << endl;
    Auto.addAnimalHab(2, "RepAutoAnimal2", 1, 2, 1);
    Auto.addAnimalHab(4, "RepAutoAnimal4", 1, 2, 1);
    Auto.addAnimalHab(6, "RepAutoAnimal6", 1, 2, 1);
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addAnimalHab(2, "RepDynAnimal2", 1, 2, 1);
    List1->addAnimalHab(4, "RepDynAnimal4", 1, 2, 1);
    List1->addAnimalHab(6, "RepDynAnimal6", 1, 2, 1);
    List1->print();

    cout << endl << "Assigning employee of occupation Cleaner at the beginning, middle and end of the list." << endl;
    cout << endl << "Auto" << endl;
    Employee AutoEmpCleaner(0, "AutoEmpCleaner", "Cleaner");
    Auto.set_Caretaker(2, &AutoEmpCleaner);
    Auto.set_Caretaker(4, &AutoEmpCleaner);
    Auto.set_Caretaker(6, &AutoEmpCleaner);
    Auto.print();
    cout << endl << "List 1" << endl;
    Employee* DynEmpCleaner = new Employee(0, "DynEmpCleaner", "Cleaner");
    List1->set_Caretaker(2, DynEmpCleaner);
    List1->set_Caretaker(4, DynEmpCleaner);
    List1->set_Caretaker(6, DynEmpCleaner);
    List1->print();

    cout << endl << "Assigning employee at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Employee AutoEmployee1(1, "AutoEmp1", "Caretaker");
    Auto.set_Caretaker(2, &AutoEmployee1);
    Auto.print();
    cout << endl << "List 1" << endl;
    Employee* DynEmployee1 = new Employee(1, "DynEmp1", "Caretaker");
    List1->set_Caretaker(2, DynEmployee1);
    List1->print();

    cout << endl << "Assigning employee at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Employee AutoEmployee2(2, "AutoEmployee2", "Caretaker");
    Auto.set_Caretaker(4, &AutoEmployee2);
    Auto.print();
    cout << endl << "List 1" << endl;
    Employee* DynEmployee2 = new Employee(2, "DynEmployee2", "Caretaker");
    List1->set_Caretaker(4, DynEmployee2);
    List1->print();

    cout << endl << "Assigning employee at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Employee AutoEmployee3(3, "AutoEmployee3", "Caretaker");
    Auto.set_Caretaker(6, &AutoEmployee3);
    Auto.print();
    cout << endl << "List 1" << endl;
    Employee* DynEmployee3 = new Employee(3, "DynEmployee3", "Caretaker");
    List1->set_Caretaker(6, DynEmployee3);
    List1->print();

    cout << endl << "Reassigning employee at the beginning, middle and end of the list." << endl;
    cout << endl << "Auto" << endl;
    Employee AutoRepEmp(0, "AutoRepEmp", "Caretaker");
    Auto.set_Caretaker(2, &AutoRepEmp);
    Auto.set_Caretaker(4, &AutoRepEmp);
    Auto.set_Caretaker(6, &AutoRepEmp);
    Auto.print();
    cout << endl << "List 1" << endl;
    Employee* DynRepEmp = new Employee(0, "DynRepEmp", "Caretaker");
    List1->set_Caretaker(2, DynRepEmp);
    List1->set_Caretaker(4, DynRepEmp);
    List1->set_Caretaker(6, DynRepEmp);
    List1->print();

    cout << endl << "Removing an element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(2);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeAnimalHabitat(2);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Removing an element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(5);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeAnimalHabitat(5);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Removing an element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(6);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeAnimalHabitat(6);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Removing an element that is not in the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeAnimalHabitat(1);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeAnimalHabitat(1);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Eliminating lists with the destructor." << endl;
    cout << endl << "Auto" << endl;
    Auto.~AnimalList();
    cout << endl << "List 1" << endl;
    List1->~AnimalList();

    cout << endl << "After eliminating the lists with the destructor." << endl;
    cout << endl << "Auto" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->print();


    cout << endl << "END............................................................" << endl;

}

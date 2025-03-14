//
// Created by juanm on 5/05/2022.
//

#include "TestCases.h"

#include <iostream>
#include "Employee.h"
#include "AnimalHab.h"
#include "EmployeeList.h"
using namespace std;

void testAll_EmployeeList(){

    Employee* CareTaker1 =  new Employee(1, "Pepe Mujica", "Caretaker");
    Employee* Cleaner1 = new Employee(2, "Luis Marcos", "Cleaner");

    AnimalHab* Lion = new AnimalHab(1, "Lion", 1, 2, 1);

    cout << endl << "Employees" << endl;
    CareTaker1->print();
    Cleaner1->print();
    cout << endl << "AnimalHab" << endl;
    Lion->print();

    EmployeeList Auto;
    EmployeeList* List1 = new EmployeeList();

    cout << endl << "Auto: Adding a new employee to the empty list." << endl;
    Auto.addEmployee(4, "AutoEmp4", "Cleaner");
    Auto.print();

    cout << endl << "List1 : Adding a new employee to the empty list." << endl;
    List1->addEmployee(4, "DynEmp4", "Caretaker");
    List1->print();

    cout << endl << "Adding a new element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.addEmployee(1, "AutoEmp1", "Caretaker");
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addEmployee(1, "DynEmp1", "Cleaner");
    List1->print();

    cout << endl << "Adding a new element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.addEmployee(3, "AutoEmp3", "Caretaker");
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addEmployee(3, "DynEmp3", "Cleaner");
    List1->print();

    cout << endl << "Adding a new element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.addEmployee(5, "AutoEmp5", "Caretaker");
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->addEmployee(5, "DynEmp5", "Cleaner");
    List1->print();

    cout << endl << "Assigning animal at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    AnimalHab AutoLion(1, "Lion", 1, 2, 1);
    Auto.assignAnimal(1, &AutoLion);
    Auto.print();
    cout << endl << "List 1" << endl;
    AnimalHab* Lion2 = new AnimalHab(1, "Lion", 1, 2, 1);
    List1->assignAnimal(1, Lion2);
    List1->print();

    cout << endl << "Assigning animal at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    AnimalHab AutoLion2(2, "Lion2", 1, 2, 1);
    Auto.assignAnimal(3, &AutoLion2);
    Auto.print();
    cout << endl << "List 1" << endl;
    AnimalHab* Lion3 = new AnimalHab(2, "Lion2", 1, 2, 1);
    List1->assignAnimal(3, Lion3);
    List1->print();

    cout << endl << "Assigning animal at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    AnimalHab AutoLion3(3, "Lion3", 1, 2, 1);
    Auto.assignAnimal(5, &AutoLion3);
    Auto.print();
    cout << endl << "List 1" << endl;
    AnimalHab* Lion4 = new AnimalHab(3, "Lion3", 1, 2, 1);
    List1->assignAnimal(5, Lion4);
    List1->print();

    cout << endl << "Reassigning animal at the beginning, middle and end of the list." << endl;
    cout << endl << "Auto" << endl;
    AnimalHab AutoRepLion(3, "RepLion", 1, 2, 1);
    Auto.assignAnimal(1, &AutoRepLion);
    Auto.assignAnimal(3, &AutoRepLion);
    Auto.assignAnimal(5, &AutoRepLion);
    Auto.print();
    cout << endl << "List 1" << endl;
    AnimalHab* DynRepLion = new AnimalHab(3, "RepLion", 1, 2, 1);
    List1->assignAnimal(1, DynRepLion);
    List1->assignAnimal(3, DynRepLion);
    List1->assignAnimal(5, DynRepLion);
    List1->print();

    cout << endl << "Assigning new employees to the lists with animals designated." << endl;
    cout << endl << "Auto" << endl;
    Auto.addEmployee(2, "AutoEmp2", "Cleaner");
    Auto.assignAnimal(2, &AutoLion);
    Auto.assignAnimal(4, &AutoLion2);
    Auto.addEmployee(6, "AutoEmp6", "Cleaner");
    Auto.assignAnimal(6, &AutoLion3);
    Auto.print();

    cout << endl << "List 1" << endl;
    List1->addEmployee(2, "DynEmp2", "Caretaker");
    List1->assignAnimal(2, Lion2);
    List1->assignAnimal(4, Lion3);
    List1->addEmployee(6, "DynEmp6", "Caretaker");
    List1->assignAnimal(6, Lion4);
    List1->print();

    cout << endl << "Employees of occupation Caretaker give food to their designated animal." << endl;
    cout << endl << "Auto" << endl;
    cout << endl << "Beginning" << endl;
    Auto.feed(1, 2, 1);
    cout << endl << "Designated animal" << endl;
    AutoLion.print();
    cout << endl << "Middle" << endl;
    Auto.feed(3,2, 1);
    cout << endl << "Designated animal" << endl;
    AutoLion2.print();
    cout << endl << "End" << endl;
    Auto.feed(5, 2, 2);
    cout << endl << "Designated animal" << endl;
    AutoLion3.print();

    cout << endl << "List 1" << endl;
    cout << endl << "Beginning" << endl;
    List1->feed(2,2,1);
    cout << endl << "Designated animal" << endl;
    Lion2->print();
    cout << endl << "Middle" << endl;
    List1->feed(4,2,1);
    cout << endl << "Designated animal" << endl;
    Lion3->print();
    cout << endl << "End" << endl;
    List1->feed(6,2,2);
    cout << endl << "Designated animal" << endl;
    Lion4->print();

    cout << endl << "Employees of occupation Cleaner give food to their designated animal." << endl;
    cout << endl << "Auto" << endl;
    cout << endl << "Beginning" << endl;
    Auto.feed(2, 2, 1);
    cout << endl << "Designated animal" << endl;
    AutoLion.print();
    cout << endl << "Middle" << endl;
    Auto.feed(4,2, 1);
    cout << endl << "Designated animal" << endl;
    AutoLion2.print();
    cout << endl << "End" << endl;
    Auto.feed(6, 2, 1);
    cout << endl << "Designated animal" << endl;
    AutoLion3.print();

    cout << endl << "List 1" << endl;
    cout << endl << "Beginning" << endl;
    List1->feed(1,2,1);
    cout << endl << "Designated animal" << endl;
    Lion2->print();
    cout << endl << "Middle" << endl;
    List1->feed(3,2,1);
    cout << endl << "Designated animal" << endl;
    Lion3->print();
    cout << endl << "End" << endl;
    List1->feed(5,2,1);
    cout << endl << "Designated animal" << endl;
    Lion4->print();

    cout << endl << "Employees of occupation Cleaner clean their designated animal." << endl;
    cout << endl << "Auto" << endl;
    cout << endl << "Beginning" << endl;
    Auto.clean(2,2,1);
    cout << endl << "Designated animal" << endl;
    AutoLion.print();
    cout << endl << "Middle" << endl;
    Auto.clean(4,2,1);
    cout << endl << "Designated animal" << endl;
    AutoLion2.print();
    cout << endl << "End" << endl;
    Auto.clean(6,2,1);
    cout << endl << "Designated animal" << endl;
    AutoLion3.print();

    cout << endl << "List 1" << endl;
    cout << endl << "Beginning" << endl;
    List1->clean(1,2,1);
    cout << endl << "Designated animal" << endl;
    Lion2->print();
    cout << endl << "Middle" << endl;
    List1->clean(3,2,1);
    cout << endl << "Designated animal" << endl;
    Lion3->print();
    cout << endl << "End" << endl;
    List1->clean(5,2,1);
    cout << endl << "Designated animal" << endl;
    Lion4->print();

    cout << endl << "Employees of occupation Caretaker clean their designated animal." << endl;
    cout << endl << "Auto" << endl;
    cout << endl << "Beginning" << endl;
    Auto.clean(1,2,1);
    cout << endl << "Designated animal" << endl;
    AutoLion.print();
    cout << endl << "Middle" << endl;
    Auto.clean(3,2,1);
    cout << endl << "Designated animal" << endl;
    AutoLion2.print();
    cout << endl << "End" << endl;
    Auto.clean(5,2,1);
    cout << endl << "Designated animal" << endl;
    AutoLion3.print();

    cout << endl << "List 1" << endl;
    cout << endl << "Beginning" << endl;
    List1->clean(2,2,1);
    cout << endl << "Designated animal" << endl;
    Lion2->print();
    cout << endl << "Middle" << endl;
    List1->clean(4,2,1);
    cout << endl << "Designated animal" << endl;
    Lion3->print();
    cout << endl << "End" << endl;
    List1->clean(6,2,1);
    cout << endl << "Designated animal" << endl;
    Lion4->print();

    cout << endl << "Notifying employees for their wrongdoings in their jobs." << endl;
    cout << endl << "Auto" << endl;
    Auto.notify(1,2);
    Auto.notify(2,2);
    Auto.notify(3,2);
    cout << endl << "After" << endl;
    Auto.print();

    cout << endl << "List 1" << endl;
    List1->notify(1,2);
    List1->notify(2,2);
    List1->notify(3,2);
    cout << endl << "After" << endl;
    List1->print();

    cout << endl << "Creating a second list with the copy of the first one (Auto to AutoCopy and List 1 to List 2)" << endl;
    EmployeeList AutoCopy(Auto);
    //AutoCopy = Auto;
    cout << endl << "AutoCopy" << endl;
    AutoCopy.print();

    EmployeeList* List2 = new EmployeeList(*List1);
    cout << endl << "List 2" << endl;
    List2->print();

    cout << endl << "In newly created lists Employees of occupation Caretaker give food to their designated animal." << endl;
    cout << endl << "AutoCopy" << endl;
    AutoCopy.feed(1, 2, 1);
    AutoCopy.feed(3,2, 1);
    AutoCopy.feed(5, 2, 1);
    cout << endl << "List 2" << endl;
    List2->feed(2,2,1);
    List2->feed(4,2,1);
    List2->feed(6,2,1);

    cout << endl << "In newly crated lists Employees of occupation Cleaner clean their designated animal." << endl;
    cout << endl << "AutoCopy" << endl;
    AutoCopy.clean(2,2,1);
    AutoCopy.clean(4,2,1);
    AutoCopy.clean(6,2,1);
    cout << endl << "List 2" << endl;
    List2->clean(1,2,1);
    List2->clean(3,2,1);
    List2->clean(5,2,1);

    cout << endl << "In newly created lists: Notifying employees for their wrongdoings in their jobs." << endl;
    cout << endl << "AutoCopy" << endl;
    AutoCopy.notify(1,2);
    AutoCopy.notify(2,2);
    AutoCopy.notify(3,2);
    cout << endl << "After" << endl;
    AutoCopy.print();

    cout << endl << "List 2" << endl;
    List2->notify(1,2);
    List2->notify(2,2);
    List2->notify(3,2);
    cout << endl << "After" << endl;
    List2->print();

    cout << endl << "Removing an element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeEmployee(1);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeEmployee(1);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Removing an element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeEmployee(4);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeEmployee(4);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Removing an element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.removeEmployee(5);
    cout << endl << "Auto (after removal)" << endl;
    Auto.print();
    cout << endl << "List 1" << endl;
    List1->removeEmployee(5);
    cout << endl << "List1 (After removal)" << endl;
    List1->print();

    cout << endl << "Eliminating lists with the destructor." << endl;
    cout << endl << "Auto" << endl;
    Auto.~EmployeeList();
    cout << endl << "AutoCopy" << endl;
    AutoCopy.~EmployeeList();
    cout << endl << "List 1" << endl;
    List1->~EmployeeList();
    cout << endl << "List 2" << endl;
    List2->~EmployeeList();

    cout << endl << "After eliminating the lists with the destructor." << endl;
    cout << endl << "Auto" << endl;
    Auto.print();
    cout << endl << "AutoCopy" << endl;
    AutoCopy.print();
    cout << endl << "List 1" << endl;
    List1->print();
    cout << endl << "List 2" << endl;
    List2->print();

}
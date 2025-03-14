#include <iostream>
#include "Zoo.h"

#include "TestCases.h"
using namespace std;

int main() {

    testAll_EmployeeList();
    testBasicAnimalList();

    Zoo Auto;
    Zoo* Dyn = new Zoo();

    cout << endl << "Initializing Employee Lists *****************************************************" << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(5, "AutoEmp5", "Caretaker");
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(5, "DynEmp5", "Caretaker");
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "Initializing Animal Lists ********************************************************" << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(5, "AutoAnimal5", 1, 2);
    cout << endl << "Auto (After)" << endl;
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->newAnimalHabitat(5, "DynAnimal5", 1, 2);
    cout << endl << "Dyn (After)" << endl;
    Dyn->print();

    cout << endl << "Assigning more elements to Employee List *****************************************" << endl;
    cout << endl << "Adding a new element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(2, "AutoEmp2", "Cleaner");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(2, "DynEmp2", "Cleaner");
    Dyn->print();

    cout << endl << "Adding a new element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(4, "AutoEmp4", "Cleaner");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(4, "DynEmp4", "Cleaner");
    Dyn->print();

    cout << endl << "Adding a new element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(6, "AutoEmp6", "Cleaner");
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(6, "DynEmp6", "Cleaner");
    Dyn->print();

    cout << endl << "Assigning more elements to Animal List *****************************************" << endl;
    cout << endl << "Adding a new element at the beginning of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(2, "AutoAnimal2", 1, 2);
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->newAnimalHabitat(2, "DynAnimal2", 1, 2);
    Dyn->print();

    cout << endl << "Adding a new element at the middle of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(4, "AutoAnimal4", 1, 2);
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->newAnimalHabitat(4, "DynAnimal4", 1, 2);
    Dyn->print();

    cout << endl << "Adding a new element at the end of the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.newAnimalHabitat(6, "AutoAnimal6", 1, 2);
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->newAnimalHabitat(6, "DynAnimal6", 1, 2);
    Dyn->print();

    cout << endl << "Inserting new employees of occupation caretaker to the list." << endl;
    cout << endl << "Auto" << endl;
    Auto.hireEmployee(1, "AutoEmp1", "Caretaker");
    Auto.hireEmployee(3, "AutoEmp3", "Caretaker");
    Auto.hireEmployee(7, "AutoEmp7", "Caretaker");
    Auto.print();

    cout << endl << "Dyn" << endl;
    Dyn->hireEmployee(1, "DynEmp1", "Caretaker");
    Dyn->hireEmployee(3, "DynEmp3", "Caretaker");
    Dyn->hireEmployee(7, "DynEmp7", "Caretaker");
    Dyn->print();

    TestZoo_numberElements(Auto, Dyn);

    TestZoo_wrongHireEmployee(Auto, Dyn);

    TestZoo_wrongNewAnimalHabitat(Auto, Dyn);

    TestZoo_assignAnimalEmployee(Auto, Dyn);

    TestZoo_feeding(Auto, Dyn);

    TestZoo_cleaning(Auto, Dyn);

    TestZoo_AnimalsCondition(Auto, Dyn);

    TestZoo_DayPasses(Auto, Dyn);

    TestZoo_fireEmployee(Auto, Dyn);

    TestZoo_removeAnimalHabitat(Auto, Dyn);

    cout << endl << "Eliminating lists with the destructor. ***********************************************" << endl;
    cout << endl << "Auto" << endl;
    Auto.~Zoo();
    cout << endl << "Dyn" << endl;
    Dyn->~Zoo();

    cout << endl << "After elimination ********************************************************************" << endl;
    cout << endl << "Auto" << endl;
    Auto.print();
    cout << endl << "Dyn" << endl;
    Dyn->print();

    cout << endl << "END : Main ............................................................................" << endl;

}

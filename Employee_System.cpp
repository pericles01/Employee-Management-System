#include "Database.h"
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using smartDB = std::shared_ptr<Records::Database>;

uint32_t displayMenu();
smartEmp findEmployee(smartDB db);
void doHire(smartDB db);
void doFire(smartDB db);
void doPromote(smartDB db);
void doDemote(smartDB db);

int main()
{

    smartDB employeeDB = std::make_unique<Records::Database>();
    bool done = true;
    while (done)
    {
        uint32_t selection = displayMenu();
        switch (selection)
        {
        case 0:
            std::cout << "Quitting..." << std::endl;
            done = false;
            break;
        case 1:
            doHire(employeeDB);
            break;
        case 2:
            doFire(employeeDB);
            break;
        case 3:
            doPromote(employeeDB);
            break;
        case 4:
            employeeDB->displayAll();
            break;
        case 5:
            employeeDB->displayPartTimeEmployees();
            break;
        case 6:
            employeeDB->displayFullTimeEmployees();
            break;
        default:
            std::cout << "Please select the right listed option" << std::endl;
            break;
        }
    }
    return 0;
}

uint32_t displayMenu()
{
    uint32_t selection;
    std::cout << std::endl;
    std::cout << "Employee Database" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "1) Hire a new employee" << std::endl;
    std::cout << "2) Fire an employee" << std::endl;
    std::cout << "3) Promote an employee" << std::endl;
    std::cout << "4) List all employees" << std::endl;
    std::cout << "5) List all part time employees" << std::endl;
    std::cout << "6) List all full time employees" << std::endl;
    std::cout << "0) Quit" << std::endl;
    std::cout << std::endl;
    std::cout << "---> ";

    std::cin >> selection;
    std::cout << std::endl;
    return selection;
}

smartEmp findEmployee(smartDB db)
{
    uint32_t employeeId, selection;
    std::string firstName, lastName;
    bool found = false;
    bool exit = false;
    smartEmp employee;
    do {
        std::cout << "Find employee options" << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << "1) Find by employee ID" << std::endl;
        std::cout << "2) Find by employee first name & last name " << std::endl;
        std::cout << "3) Return to menu " << std::endl;
        std::cout << std::endl;
        std::cout << "---> ";
        std::cin >> selection;
        std::cout << std::endl;

        if (selection == 1)
        {
            std::cout << "Enter the employee Id: ";
            std::cin >> employeeId;
            std::cout << std::endl;
            employee = db->getEmployee(employeeId);
        }
        else if (selection == 2)
        {
            std::cout << "Enter the employee firstname: ";
            std::cin >> firstName;
            std::cout << std::endl;
            std::cout << "Enter the employee lastname: ";
            std::cin >> lastName;
            std::cout << std::endl;
            employee = db->getEmployee(firstName, lastName);
        }
        else if (selection == 3)
            exit = true;

        if (employee)
        {
            found = true;
            exit = true;
        }
        else
            std::cout << "Repeat the search please or return to menu" << std::endl;
        std::cout << " " << std::endl;
    } while (!(found || exit));

    return employee;

}

void doHire(smartDB db)
{
    std::string firstName, lastName, position, type;
    std::cout << "Hire new employee" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Enter the employee's first name: ";
    std::cin >> firstName;
    std::cout << std::endl;
    std::cout << "Enter the employee's last name: ";
    std::cin >> lastName;
    std::cout << std::endl;
    std::cout << "Enter the employee's position: ";
    std::cin >> position;
    std::cout << std::endl;
    std::cout << "Is that a full time employee? (yes / no): ";
    std::cin >> type;
    std::cout << std::endl;
    db->addEmployee(firstName, lastName, position, (type == "yes" || type == "Yes")? 1:0);
    std::cout << "Employee '"<< firstName <<" "<< lastName <<"' hired & added to employee database" << std::endl;
}
void doFire(smartDB db)
{
    std::cout << "Fire employee" << std::endl;
    std::cout << "-----------------" << std::endl;
    auto employee = findEmployee(db);
    if(employee)
    {
        db->fireEmployee(employee);
        std::cout << "Employee '" << employee->getFirstName() << " " << employee->getLastName() << "' fired" << std::endl;
    }
}
void doPromote(smartDB db)
{
    uint32_t raiseAmount;
    std::cout << "Promote employee" << std::endl;
    std::cout << "-----------------" << std::endl;
    auto employee = findEmployee(db);
    if (employee)
    {
        std::cout << "Input the raise salary amount (new salary = actual salary + raise amount): ";
        std::cin >> raiseAmount;
        std::cout << std::endl;
        employee->promote(raiseAmount);
        std::cout << "Employee '"<< employee->getFirstName()<<" "<< employee->getLastName()<<"' got promoted" << std::endl;
    }
}
void doDemote(smartDB db)
{
    uint32_t demoteAmount;
    std::cout << "Demote employee" << std::endl;
    std::cout << "-----------------" << std::endl;
    auto employee = findEmployee(db);
    if (employee)
    {
        std::cout << "Input the demote salary amount (new salary = actual salary - demote amount): ";
        std::cin >> demoteAmount;
        std::cout << std::endl;
        employee->demote(demoteAmount);
        std::cout << "Employee demoted" << std::endl;
    }
}

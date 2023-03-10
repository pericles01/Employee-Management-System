#include "Database.h"
#include <random>
#include <stdexcept>

namespace Records
{

Database::~Database() {
    delete con;
    delete stmt;
    
}

// establish connection to mySQL server & construct the employee's list based on saved DB data
void Database::setSQLConnection() {
    try {
        Emp employee;
        sql::Driver* driver = get_driver_instance();
        std::string user = "peri";
        std::string passwort = "PeriAtDassault01";

        con = driver->connect("tcp://127.0.0.1:3306", user, passwort);
        stmt = con->createStatement();
        con->setSchema("employee_system");

        sql::ResultSet* res = stmt->executeQuery("SELECT id, firstname, lastname, profession, salary, period FROM employee_record ORDER BY id ASC");
        while (res->next() && con->isValid()) {
            employee.setEmployeeNumber(stoi(static_cast<std::string>(res->getString("id"))));
            employee.setFirstName(static_cast<std::string>(res->getString("firstname")));
            employee.setLastName(static_cast<std::string>(res->getString("lastname")));
            employee.setProfession(static_cast<std::string>(res->getString("profession")));
            employee.setSalary(stoi(static_cast<std::string>(res->getString("salary"))));
            employee.setPeriod(stoi(static_cast<std::string>(res->getString("period"))));

            mEmployeeList.push_back(employee);
        }

        delete res;
        delete driver;
    }
    catch (sql::SQLException& e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line  »" << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

}

sql::Connection* Database::getSQLConnection() const {
    return con;
}

const std::vector<uint32_t> &Database::getIdList() const
{
    return mIdList;
}

void Database::setIdList(uint32_t &id)
{
    mIdList.push_back(id);
}

const std::vector<Emp> &Database::getEmployeeList() const
{
    return mEmployeeList;
}

void Database::setEmployeeList(const Emp &employee, const bool& remove)
{
    if (!remove) {
        mEmployeeList.push_back(employee);
        // save into DB
        std::string sqlStmt = "INSERT INTO employee_record (id, firstname, lastname, profession, salary, period) VALUES (";
        sqlStmt += std::to_string(employee.getEmployeeNumber());
        sqlStmt += ",'";
        sqlStmt += employee.getFirstName();
        sqlStmt += "','";
        sqlStmt += employee.getLastName();
        sqlStmt += "','";
        sqlStmt += employee.getProfession();
        sqlStmt += "','";
        sqlStmt += std::to_string(employee.getSalary());
        sqlStmt += "',";
        sqlStmt += std::to_string(employee.getPeriod());
        sqlStmt += ")";
        stmt->execute(sqlStmt);
    }
    else {
        mEmployeeList.erase(std::find(mEmployeeList.begin(), mEmployeeList.end(), employee));
        //delete from DB
        std::string sqlStmt = "DELETE FROM employee_record WHERE id=";
        sqlStmt += std::to_string(employee.getEmployeeNumber());
        stmt->execute(sqlStmt);
    }
}

void Database::addEmployee(const std::string &firstName, const std::string &lastName, const std::string& profession, const bool& isFullTime)
{
    Emp theEmployee = Emp(firstName, lastName, profession, isFullTime);
    uint32_t newId = generateNewId();
    theEmployee.setEmployeeNumber(newId);
    theEmployee.hire();
    setEmployeeList(theEmployee);
}

void Database::fireEmployee(smartEmp employee) 
{
    employee->fire();
    setEmployeeList(*employee, 1);
}

smartEmp Database::getEmployee(const uint32_t &employeeId)
{
    std::vector<Emp> empList = getEmployeeList();
    if (!empList.empty()) {


        for (const auto& employee : empList)
        {
            if (employee.getEmployeeNumber() == employeeId)
                return std::make_shared<Emp>(employee);
        }
        std::cout << "Employee with ID:"<<employeeId<< "not found in database." << std::endl;
        return nullptr;
    }
    else
    {
        std::cout << "No Employee in database yet." << std::endl;
        return nullptr;
    }
        
}

smartEmp Database::getEmployee(const std::string &firstName, const std::string &lastName)
{
    std::vector<Emp> empList = getEmployeeList();
    if (!empList.empty()) {
        for (const auto& employee : empList)
        {
            if (employee.getFirstName() == firstName && employee.getLastName() == lastName)
            {
                return std::make_shared<Emp>(employee);
            }
        }
        std::cout << "Employee: " << firstName <<", " <<lastName << " not found in database." << std::endl;
        return nullptr;
    }
    else {
        std::cout << "No Employee in database yet." << std::endl;
        return nullptr;
    }
}

const uint32_t Database::generateNewId()
{
    uint32_t newId;
    std::vector<uint32_t> idList = getIdList();
    bool repeat = false;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<uint32_t> distrib(kFirstId, 9999U);
    std::vector<uint32_t>::iterator it;
    do
    {
        //generate new Id
        newId = distrib(gen);
        it = std::find(idList.begin(), idList.end(), newId);
        //if new Id already in idList -> repeat=true else false
        if (it != idList.end())
        {
            repeat = true;
        }
        else
        {
            repeat = false;
            idList.push_back(newId);
        }

    } while (repeat);


    return newId;
}

void Database::displayAll() const
{
    std::cout << "Display all employees" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::vector<Emp> empList = getEmployeeList();
    if (!empList.empty())
    {
        for (const auto& employee : empList)
        {
            employee.display();
            std::cout << "" << std::endl;
        }
    }
    else
        std::cout << "No Employee in database yet." << std::endl;
}

void Database::displayPartTimeEmployees() const
{
    std::cout << "Display all part time employees" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::vector<Emp> empList = getEmployeeList();
    if (!empList.empty())
    {
        bool found = false;
        for (const auto& employee : empList)
        {
            if (employee.isFull())
            {
                found = true;
                employee.display();
                std::cout << "" << std::endl;
            }
        }
        if(found)
            std::cout << "No part time Employee in database yet." << std::endl;
    }
    else
        std::cout << "No Employee in database yet." << std::endl;
}

void Database::displayFullTimeEmployees() const
{
    std::cout << "Display all full time employees" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::vector<Emp> empList = getEmployeeList();
    if (!empList.empty())
    {
        bool found = false;
        for (const auto &employee : empList)
        {
            if (!employee.isFull())
            {
                found = true;
                employee.display();
                std::cout << "" << std::endl;
            }
        }
        if (found)
            std::cout << "No part time Employee in database yet." << std::endl;
    }
    else
        std::cout << "No Employee in database yet." << std::endl;
}
} // namespace Records

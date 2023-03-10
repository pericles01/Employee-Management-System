#pragma once
#include "Employee.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using Emp = Record::Employee;
using smartEmp = std::shared_ptr<Emp>;

namespace Records
{
constexpr uint32_t kFirstId = 1000;

class Database
{
public:
    Database() = default;
    ~Database();
    void addEmployee(const std::string &firstName, const std::string &lastName, const std::string& profession, const bool& isFullTime = true);
    void fireEmployee(smartEmp employee);
    smartEmp getEmployee(const uint32_t &employeeId);
    smartEmp getEmployee(const std::string &firstName, const std::string &lastName);
    void displayAll() const;
    void displayPartTimeEmployees() const;
    void displayFullTimeEmployees() const;
    const uint32_t generateNewId();
    const std::vector<uint32_t> &getIdList() const;
    void setIdList(uint32_t &id);
    const std::vector<Emp> &getEmployeeList() const;
    void setEmployeeList(const Emp &employee, const bool &remove=0);
    void setSQLConnection();
    sql::Connection* getSQLConnection() const;

private:
    std::vector<Emp> mEmployeeList;
    std::vector<uint32_t> mIdList{0};
    sql::Connection* con;
    sql::Statement* stmt;
};
} // namespace Records

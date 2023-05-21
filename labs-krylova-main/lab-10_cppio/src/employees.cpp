#include "employees.h"

namespace Employee {
    //EMPLOYEE
    Employee::Employee(const char *name, int32_t base_salary) {
        if (strlen(name) > 100) {
            throw std::runtime_error("The name is long");
        }
        _name = new char(strlen(name) + 1);
        strcpy(_name, name);
        _base_salary = base_salary;
    }

    Employee::Employee() {
        _name = nullptr;
        _base_salary = 0;
    }

    Employee::~Employee() {
        delete[] _name;
    }

    std::istream &Employee::read_text(std::istream &in) {
        char name[101];
        in >> name >> _base_salary;
        delete _name;
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
        return in;
    }

    std::ostream &Employee::write_text(std::ostream &out) const {
        out << "Name: " << _name << std::endl << "Base Salary: " << _base_salary << std::endl;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const Employee &e) {
        return e.write_text(out);
    }

    std::istream &operator>>(std::istream &in, Employee &e) {
        return e.read_text(in);
    }

    std::ifstream &operator>>(std::ifstream &in, Employee &e) {
        return e.read_binary(in);
    }

    std::ofstream &operator<<(std::ofstream &out, const Employee &e) {
        return e.write_binary(out);
    }


    std::ifstream &Employee::read_binary(std::ifstream &in) {
        char buffer[101];
        in >> BinManip::read_c_str(buffer, sizeof(char) * 101) >> BinManip::read_le_int32(_base_salary);
        if (strlen(buffer) > 100) {
            throw std::runtime_error("The name is long");
        }
        delete _name;
        _name = new char[strlen(buffer) + 1];
        strcpy(_name, buffer);
        return in;
    }

    std::ofstream &Employee::write_binary(std::ofstream &out) const {
        out << BinManip::write_c_str(_name) << BinManip::write_le_int32(_base_salary);
        return out;
    }


    //DEVELOPER
    Developer::Developer(const char *name, int32_t base_salary, bool has_bonus) : Employee(name, base_salary),
                                                                                  _has_bonus(has_bonus) {}


    Developer::Developer(std::istream &in) : Developer(){
        Developer::read_text(in);
    }

    Developer::Developer(std::ifstream &in) : Developer(){
        Developer::read_binary(in);
    }

    std::istream &Developer::read_text(std::istream &in) {
        Employee::read_text(in);
        in >> _has_bonus;
        return in;
    }

    std::ostream &Developer::write_text(std::ostream &out) const {
        out << "Developer" << std::endl;
        Employee::write_text(out);
        if (_has_bonus)
            return out << "Has bonus: +" << std::endl;
        return out << "Has bonus: -" << std::endl;
    }

    std::ifstream &Developer::read_binary(std::ifstream &in) {
        Employee::read_binary(in);
        in >> BinManip::read_bool(_has_bonus);
        return in;
    }

    std::ofstream &Developer::write_binary(std::ofstream &out) const {
        out << BinManip::write_le_int32(1);
        Employee::write_binary(out);
        out << BinManip::write_bool(_has_bonus);
        return out;
    }

    Developer::Developer() : Employee(), _has_bonus(false) {}



    //SALES_MANAGER

    SalesManager::SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price) : Employee(name,
                                                                                                                 base_salary),
                                                                                                        _sold_nm(
                                                                                                                sold_nm),
                                                                                                        _price(price) {}


    SalesManager::SalesManager(std::istream &in) : SalesManager() {
        SalesManager::read_text(in);
    }

    SalesManager::SalesManager(std::ifstream &in) : SalesManager() {
        SalesManager::read_binary(in);
    }

    std::istream &SalesManager::read_text(std::istream &in) {
        Employee::read_text(in);
        in >> _sold_nm >> _price;
        return in;
    }

    std::ostream &SalesManager::write_text(std::ostream &out) const {
        out << "Sales Manager" << std::endl;
        Employee::write_text(out);
        out << "Sold items: " << _sold_nm << std::endl << "Item price: " << _price << std::endl;
        return out;
    }

    std::ifstream &SalesManager::read_binary(std::ifstream &in) {
        Employee::read_binary(in);
        in >> BinManip::read_le_int32(_sold_nm) >> BinManip::read_le_int32(_price);
        return in;
    }

    std::ofstream &SalesManager::write_binary(std::ofstream &out) const {
        out << BinManip::write_le_int32(2);
        Employee::write_binary(out);
        out << BinManip::write_le_int32(_sold_nm) << BinManip::write_le_int32(_price);
        return out;
    }

    SalesManager::SalesManager() : Employee(), _sold_nm(0), _price(0) {}


    //EMPLYEESARRAY
    EmployeesArray::EmployeesArray() {
        _size = 0;
    }

    EmployeesArray::~EmployeesArray() {
        for (int i = 0; i < _size; ++i) delete _employees[i];
    }

    void EmployeesArray::add(const Employee *e) {
        _employees.push_back((Employee *) e);
        _size++;
    }

    int32_t EmployeesArray::total_salary() const {
        int32_t s = 0;
        for (int i = 0; i < _size; ++i) {
            s += _employees[i]->salary();
        }
        return s;
    }

    std::ostream &operator<<(std::ostream &out, const EmployeesArray &array) {
        for (int i = 0; i < array._size; ++i) {
            out << i + 1 << ". " << *array._employees[i];
        }
        out << "== Total salary: " << array.total_salary() << std::endl;
        return out;
    }

    std::istream &operator>>(std::istream &in, EmployeesArray &array) {
        int position;
        in >> position;
        Employee *e;
        if (position == 1) {
            e = new Developer(in);
        } else if (position == 2) {
            e = new SalesManager(in);
        } else {
            throw std::invalid_argument("Unexpected data.");
        }
        array.add(e);
        return in;
    }

    std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &array) {
        out << BinManip::write_le_int32((uint8_t) array._employees.size());
        for (int i = 0; i < array._size; ++i) {
            out << *array._employees[i];
        }
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, EmployeesArray &array) {
        int cnt;
        in >> BinManip::read_le_int32(cnt);
        for(int i = 0; i < cnt; ++ i) {
            int position;
            Employee *e;
            in >> BinManip::read_le_int32(position);
            if (position == 1) {
                e = new Developer(in);
            } else if (position == 2) {
                e = new SalesManager(in);
            } else {
                throw std::invalid_argument("Unexpected data.");
            }
            array.add(e);
        }
        return in;
    }

}
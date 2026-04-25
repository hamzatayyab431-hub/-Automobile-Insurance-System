#pragma once
#include <string>

class Staff {
protected:
    int id;
    std::string name;
    std::string username;
    std::string password;
public:
    Staff(int id, const std::string& name, const std::string& username, const std::string& password)
        : id(id), name(name), username(username), password(password) {}
    
    virtual ~Staff() = default;
    
    virtual std::string getRole() const = 0;
    
    int getId() const { return id; }
    const std::string& getName() const { return name; }
    const std::string& getUsername() const { return username; }
    
    bool checkPassword(const std::string& pass) const {
        return password == pass;
    }
    
    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

    std::string serialize() const {
        return std::to_string(id) + "," + 
               escape(name) + "," + 
               escape(username) + "," + 
               escape(password) + "," + 
               escape(getRole());
    }
};

class Manager : public Staff {
public:
    Manager(int id, const std::string& n, const std::string& u, const std::string& p)
        : Staff(id, n, u, p) {}
    std::string getRole() const override { return "Manager"; }
};

class Salesman : public Staff {
public:
    Salesman(int id, const std::string& n, const std::string& u, const std::string& p)
        : Staff(id, n, u, p) {}
    std::string getRole() const override { return "Salesman"; }
};

class Surveyor : public Staff {
public:
    Surveyor(int id, const std::string& n, const std::string& u, const std::string& p)
        : Staff(id, n, u, p) {}
    std::string getRole() const override { return "Surveyor"; }
};

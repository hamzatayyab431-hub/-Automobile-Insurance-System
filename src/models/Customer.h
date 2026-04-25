#pragma once
#include <string>

class Customer {
private:
    int id;
    std::string name;
    std::string contact;
    std::string address;
    std::string registrationDate;
    int salesmanId;

public:
    Customer() : id(0), salesmanId(0) {}

    Customer(int id, const std::string& name, const std::string& contact, 
             const std::string& address, const std::string& regDate, int salesmanId)
        : id(id), name(name), contact(contact), address(address), 
          registrationDate(regDate), salesmanId(salesmanId) {}
          
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getContact() const { return contact; }
    std::string getAddress() const { return address; }
    std::string getRegistrationDate() const { return registrationDate; }
    int getSalesmanId() const { return salesmanId; }

    // Setters
    void setId(int val) { id = val; }
    void setName(const std::string& val) { name = val; }
    void setContact(const std::string& val) { contact = val; }
    void setAddress(const std::string& val) { address = val; }
    void setRegistrationDate(const std::string& val) { registrationDate = val; }
    void setSalesmanId(int val) { salesmanId = val; }

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

    std::string serialize() const {
        return std::to_string(id) + "," + 
               escape(name) + "," + 
               escape(contact) + "," + 
               escape(address) + "," + 
               escape(registrationDate) + "," + 
               std::to_string(salesmanId);
    }
};

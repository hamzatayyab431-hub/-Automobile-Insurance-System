#pragma once
#include <string>

class Workshop {
private:
    int id;
    std::string name;
    std::string location;

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

public:
    Workshop() : id(0) {}

    Workshop(int id, const std::string& name, const std::string& location)
        : id(id), name(name), location(location) {}
          
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getLocation() const { return location; }

    // Setters
    void setId(int val) { id = val; }
    void setName(const std::string& val) { name = val; }
    void setLocation(const std::string& val) { location = val; }

    std::string serialize() const {
        return std::to_string(id) + "," + 
               escape(name) + "," + 
               escape(location);
    }
};

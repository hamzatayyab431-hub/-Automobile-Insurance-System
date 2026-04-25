#pragma once
#include <memory>
#include "../interfaces/IStaffRepository.h"

class AuthService {
private:
    IStaffRepository& staffRepo;

public:
    explicit AuthService(IStaffRepository& repo) : staffRepo(repo) {}

    std::shared_ptr<Staff> login(const std::string& username, const std::string& password) {
        auto allStaff = staffRepo.getAll();
        for (auto staff : allStaff) {
            if (staff->getUsername() == username && staff->checkPassword(password)) {
                return staff;
            }
        }
        return nullptr;
    }
};

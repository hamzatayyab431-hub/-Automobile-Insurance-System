#pragma once
#include <iostream>
#include "../services/CustomerService.h"
#include "../services/ClaimService.h"

#include <memory>

class SalesmanUI {
private:
    CustomerService& customerService;
    ClaimService& claimService;

public:
    SalesmanUI(CustomerService& custService, ClaimService& cService)
        : customerService(custService), claimService(cService) {}

    void render(std::shared_ptr<Staff> user) {
        int choice = 0;
        while (choice != 4) {
            std::cout << "\n--- Salesman Menu ---\n";
            std::cout << "1. Register Customer & Vehicle\n";
            std::cout << "2. Record Insurance Policy\n";
            std::cout << "3. File Claim\n";
            std::cout << "4. Logout\n";
            std::cout << "Choice: ";
            if (!(std::cin >> choice)) break; // Defensive generic failure check

            if (choice == 1) {
                std::string n, c, a, d, vn, vm, vmd;
                int vy;
                std::cout << "Name: "; std::getline(std::cin >> std::ws, n);
                std::cout << "Contact: "; std::getline(std::cin >> std::ws, c);
                std::cout << "Address: "; std::getline(std::cin >> std::ws, a);
                std::cout << "RegDate: "; std::getline(std::cin >> std::ws, d);
                
                auto cust = customerService.registerCustomer(user->getId(), n, c, a, d);
                std::cout << "Veh RegNo: "; if (!(std::cin >> vn)) break;
                std::cout << "Veh Make: "; if (!(std::cin >> vm)) break;
                std::cout << "Veh Model: "; if (!(std::cin >> vmd)) break;
                std::cout << "Veh Year: "; if (!(std::cin >> vy)) break;
                customerService.registerVehicle(cust.getId(), vn, vm, vmd, vy);
                std::cout << "Customer and Vehicle Registered!\n";
            }
            else if (choice == 2) {
                std::string vr, sd, ed;
                double p, cov;
                std::cout << "Veh RegNo: "; if (!(std::cin >> vr)) break;
                std::cout << "Start Date: "; if (!(std::cin >> sd)) break;
                std::cout << "End Date: "; if (!(std::cin >> ed)) break;
                std::cout << "Premium: "; if (!(std::cin >> p)) break;
                std::cout << "Coverage: "; if (!(std::cin >> cov)) break;
                customerService.recordPolicy(vr, sd, ed, p, cov);
                std::cout << "Policy recorded.\n";
            }
            else if (choice == 3) {
                int pno, wid;
                std::string dt, desc;
                std::cout << "Policy No: "; if (!(std::cin >> pno)) break;
                std::cout << "Date: "; if (!(std::cin >> dt)) break;
                std::cout << "Description: "; std::getline(std::cin >> std::ws, desc);
                std::cout << "Workshop ID (0 if none): "; if (!(std::cin >> wid)) break;
                claimService.fileClaim(user->getId(), pno, dt, desc, wid);
                std::cout << "Claim filed.\n";
            }
        }
    }
};

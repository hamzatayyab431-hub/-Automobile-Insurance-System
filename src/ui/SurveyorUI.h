#pragma once
#include <iostream>
#include <memory>
#include "../services/InspectionService.h"

class SurveyorUI {
private:
    InspectionService& inspectionService;

public:
    SurveyorUI(InspectionService& inspService)
        : inspectionService(inspService) {}

    void render(std::shared_ptr<Staff> user) {
        int choice = 0;
        while (choice != 2) {
            std::cout << "\n--- Surveyor Menu ---\n";
            std::cout << "1. Submit Inspection Report\n";
            std::cout << "2. Logout\n";
            std::cout << "Choice: ";
            if (!(std::cin >> choice)) break; // Defensive generic failure check

            if (choice == 1) {
                int cid;
                std::string d, desc;
                double cost;
                std::cout << "Claim ID: "; if (!(std::cin >> cid)) break;
                std::cout << "Date: "; if (!(std::cin >> d)) break;
                std::cout << "Description: "; std::getline(std::cin >> std::ws, desc);
                std::cout << "Est. Cost: "; if (!(std::cin >> cost)) break;
                try {
                    inspectionService.submitReport(user->getId(), cid, d, desc, cost);
                    std::cout << "Report submitted.\n";
                } catch (std::exception &e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        }
    }
};

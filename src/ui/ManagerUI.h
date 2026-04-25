#pragma once
#include <iostream>
#include <memory>
#include "../services/ReportService.h"
#include "../services/ClaimService.h"

class ManagerUI {
private:
    ReportService& reportService;
    ClaimService& claimService;

public:
    ManagerUI(ReportService& rs, ClaimService& cs)
        : reportService(rs), claimService(cs) {}

    void render(std::shared_ptr<Staff> user) {
        int choice = 0;
        while (choice != 5) {
            std::cout << "\n--- Manager Menu ---\n";
            std::cout << "1. View New Customers in a Month\n";
            std::cout << "2. View Pending Claims\n";
            std::cout << "3. Examine Inspection & Approve/Reject Claim\n";
            std::cout << "4. View Customer Claim History\n";
            std::cout << "5. Logout\n";
            std::cout << "Choice: ";
            if (!(std::cin >> choice)) break; // Defensive generic failure check

            if (choice == 1) {
                std::string month;
                std::cout << "Enter month (e.g., '04' or 'Jan'): ";
                if (!(std::cin >> month)) break;
                auto list = reportService.getNewCustomersInMonth(0, month);
                for (const auto& c : list) {
                    std::cout << c.getId() << " - " << c.getName() << " (" << c.getRegistrationDate() << ")\n";
                }
            } 
            else if (choice == 2) {
                auto pending = reportService.getPendingClaims();
                for (const auto& c : pending) {
                    std::cout << "Claim " << c.getClaimId() << " Policy " << c.getPolicyNo() << " Desc: " << c.getDescription() << "\n";
                }
            }
            else if (choice == 3) {
                int claimId;
                std::cout << "Enter Claim ID: ";
                if (!(std::cin >> claimId)) break;
                
                try {
                    auto rep = reportService.getInspectionReport(claimId);
                    std::cout << "Report found! Cost: " << rep.getEstimatedCost() << " Desc: " << rep.getDescription() << "\n";
                    int action;
                    std::cout << "1 to Approve, 2 to Reject: ";
                    if (!(std::cin >> action)) break;
                    std::string reason;
                    std::cout << "Reason: ";
                    std::getline(std::cin >> std::ws, reason);
                    
                    if (action == 1) claimService.approveClaim(user->getId(), claimId, reason);
                    else claimService.rejectClaim(user->getId(), claimId, reason);
                    std::cout << "Claim updated.\n";
                } catch (std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
            else if (choice == 4) {
                int cid;
                std::cout << "Enter Customer ID: ";
                if (!(std::cin >> cid)) break;
                auto hist = reportService.getClaimHistory(cid);
                for (const auto& h : hist) {
                    std::cout << "Claim " << h.getClaimId() << " Status: " << h.getStatus() << "\n";
                }
            }
        }
    }
};

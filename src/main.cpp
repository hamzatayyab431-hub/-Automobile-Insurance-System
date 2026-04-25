#include <iostream>

#include "dal/FileCustomerRepository.h"
#include "dal/FileVehicleRepository.h"
#include "dal/FilePolicyRepository.h"
#include "dal/FileClaimRepository.h"
#include "dal/FileReportRepository.h"
#include "dal/FileWorkshopRepository.h"
#include "dal/FileStaffRepository.h"

#include "services/AuthService.h"

#include "ui/ManagerUI.h"
#include "ui/SalesmanUI.h"
#include "ui/SurveyorUI.h"

int main() {
    // 1. Data Access Layer
    FileCustomerRepository custRepo;
    FileVehicleRepository vehRepo;
    FilePolicyRepository polRepo;
    FileClaimRepository claimRepo;
    FileReportRepository repRepo;
    FileWorkshopRepository shopRepo;
    FileStaffRepository staffRepo;
    
    // Seed initial staff if database is empty
    if (staffRepo.getAll().empty()) {
        staffRepo.seedInitial();
    }

    // 2. Business Services Layer
    AuthService authService(staffRepo);
    CustomerService custService(custRepo, vehRepo, polRepo);
    ClaimService claimService(claimRepo, shopRepo, polRepo);
    InspectionService inspService(repRepo, claimRepo);
    ReportService repService(custRepo, claimRepo, repRepo, vehRepo, polRepo);

    // 3. User Interface Layer
    ManagerUI managerUI(repService, claimService);
    SalesmanUI salesmanUI(custService, claimService);
    SurveyorUI surveyorUI(inspService);

    std::cout << "======================================\n";
    std::cout << "  Automobile Insurance System   \n";
    std::cout << "======================================\n";
    
    while (true) {
        std::string user, pass;
        std::cout << "\nLogin (username): ";
        if (!(std::cin >> user) || user == "exit") break;
        std::cout << "Password: ";
        if (!(std::cin >> pass)) break;

        std::shared_ptr<Staff> loggedInUser = authService.login(user, pass);
        if (!loggedInUser) {
            std::cout << "Invalid credentials.\n";
            continue;
        }

        std::string role = loggedInUser->getRole();
        std::cout << "\nWelcome " << loggedInUser->getName() << " (" << role << ")!\n";

        if (role == "Manager") {
            managerUI.render(loggedInUser);
        } else if (role == "Salesman") {
            salesmanUI.render(loggedInUser);
        } else if (role == "Surveyor") {
            surveyorUI.render(loggedInUser);
        }
    }

    return 0;
}

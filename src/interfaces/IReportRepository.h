#pragma once
#include "IReadRepository.h"
#include "IWriteRepository.h"
#include "../models/InspectionReport.h"
#include <vector>

class IReportRepository : public IReadRepository<InspectionReport>,
                          public IWriteRepository<InspectionReport> {
public:
    virtual ~IReportRepository() = default;
    virtual InspectionReport findByClaim(int claimId) = 0;
};

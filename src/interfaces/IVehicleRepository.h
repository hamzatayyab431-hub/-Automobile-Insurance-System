#pragma once
#include "IReadRepository.h"
#include "IWriteRepository.h"
#include "IDeleteRepository.h"
#include "../models/Vehicle.h"

class IVehicleRepository : public IReadRepository<Vehicle, std::string>,
                           public IWriteRepository<Vehicle, std::string>,
                           public IDeleteRepository<Vehicle, std::string> {
public:
    virtual ~IVehicleRepository() = default;
};

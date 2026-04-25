#pragma once

template <typename T, typename ID = int>
class IWriteRepository {
public:
    virtual ~IWriteRepository() = default;
    virtual ID save(const T& entity) = 0;
    virtual void update(const T& entity) = 0;
};

/**
 * @file DataStorage.hpp
 * @date   2025-01-12
 * @author Lankow
 * @version 1.0
 */
#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include <Arduino.h>
#include <vector>
#include <memory>
#include "EmulatedData.hpp"

class DataStorage
{
    public:
        explicit DataStorage();

        void updateAll();
        void printAll() const;

    private:
        std::vector<std::unique_ptr<IEmulatedData>> m_emulatedDataList;
};
#endif // DATA_STORAGE_HPP
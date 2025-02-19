/**
 * @file BtHandler.hpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */
#ifndef BlUETOOTH_HANDLER_HPP
#define BlUETOOTH_HANDLER_HPP

#include <Arduino.h>
#include <memory>
#include "BluetoothSerial.h"
#include "OBDHandler.hpp"

class BtHandler
{
public:
    BtHandler(std::shared_ptr<OBDHandler> obdHandler);

    void initialize();
    void cyclic();

private:
    BluetoothSerial m_btSerial;
    std::shared_ptr<OBDHandler> m_obdHandler;
    std::string getOBD2PIDResponse(const std::string &request);
};
#endif // BlUETOOTH_HANDLER_HPP
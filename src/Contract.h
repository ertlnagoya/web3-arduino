//
// Created by Kawai Kenta on 2022/09/11.
//

#ifndef ARDUINO_WEB3_CONTRACT_H
#define ARDUINO_WEB3_CONTRACT_H

#include <Arduino.h>
#include <Web3.h>

class Contract
{

public:
    typedef struct
    {
        String from;
        String gasPrice;
        long gas;
    } Options;
    Options options;

public:
    Contract(Web3 *_web3, const String &address);
    void SetPrivateKey(const uint8_t *key);
    void SetAccount(const String &account);
    void SetGasPrice(const String &gasPrice);
    void SetGas(long gas);
    String SetupContractData(const String &args_format, ...);
    String Call(const String &data);
    String SendTransaction(const String &data);

private:
    Web3 *web3;
    String contractAddress;
    const uint8_t *privateKey;

private:
    String GenerateContractBytes(const String &func);
    String GenerateBytesForInt(const int32_t value);
    String GenerateBytesForUint(const uint32_t value);
    String GenerateBytesForAddress(const String &value);
    String GenerateBytesForString(const String &value);
    String GenerateBytesForBytes(const String &value);
};

#endif // ARDUINO_WEB3_CONTRACT_H

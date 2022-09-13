//
// Created by Okada, Takahiro on 2018/02/04.
//

#ifndef ARDUINO_WEB3_WEB3_H
#define ARDUINO_WEB3_WEB3_H

#include <Arduino.h>

using namespace std;

class Web3
{
public:
    Web3(const String &_host, const String &_path);
    String Web3ClientVersion();
    String Web3Sha3(const String &data);
    int NetVersion();
    bool NetListening();
    long int NetPeerCount();
    String EthProtocolVersion();
    String EthSyncing();
    bool EthMining();
    double EthHashrate();
    long long int EthGasPrice();
    void EthAccounts();
    long int EthBlockNumber();
    long long int EthGetBalance(const String &address);
    long int EthGetTransactionCount(const String &address);
    String EthCall(const String &from, const String &to, const String &data);
    String EthSendTransaction(const String &from, const String &to, const String &data);
    String EthSendSignedTransaction(const String &data, const uint32_t dataLen);

private:
    String exec(const String &data);
    String generateJson(const String &method, const String &params);
    int getInt(const String &json);
    long int getLongbyHex(const String &json);
    long long int getLLbyHex(const String &json);
    double getDouble(const String &json);
    bool getBool(const String &json);
    String getString(const String &json);

private:
    String host;
    String path;
};

#endif // ARDUINO_WEB3_WEB3_H

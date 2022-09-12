//
// Created by Okada, Takahiro on 2018/02/04.
//

#include "Web3.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

// TODO 初期化処理を挟む or httpclientに書き換える
HTTPClient client;
DynamicJsonDocument doc(2048);

Web3::Web3(const String &_host, const String &_path)
{
    host = _host;
    path = _path;
}

// TODO: we need deconstrucotor for free DynamicJsonDocument

String Web3::Web3ClientVersion()
{
    String m = "web3_clientVersion";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getString(output);
}

String Web3::Web3Sha3(const String &data)
{
    String m = "web3_sha3";
    String p = "[\"" + data + "\"]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getString(output);
}

int Web3::NetVersion()
{
    String m = "net_version";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getInt(output);
}

bool Web3::NetListening()
{
    String m = "net_listening";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getBool(output);
}

long int Web3::NetPeerCount()
{
    String m = "net_peerCount";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getLongbyHex(output);
}

String Web3::EthProtocolVersion()
{
    String m = "eth_protocolVersion";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getString(output);
}

String Web3::EthSyncing()
{
    String m = "eth_syncing";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getString(output);
}

bool Web3::EthMining()
{
    String m = "eth_mining";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getBool(output);
}

double Web3::EthHashrate()
{
    String m = "eth_hashrate";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getDouble(output);
}

long long int Web3::EthGasPrice()
{
    String m = "eth_gasPrice";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getLLbyHex(output);
}

void Web3::EthAccounts()
{
    // TODO
}

long int Web3::EthBlockNumber()
{
    String m = "eth_blockNumber";
    String p = "[]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getLongbyHex(output);
}

long long int Web3::EthGetBalance(const String &address)
{
    String m = "eth_getBalance";
    String p = "[\"" + address + "\",\"latest\"]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getLLbyHex(output);
}

long int Web3::EthGetTransactionCount(const String &address)
{
    String m = "eth_getTransactionCount";
    String p = "[\"" + address + "\",\"latest\"]";
    String input = generateJson(m, p);
    String output = exec(input);
    return getLongbyHex(output);
}

String Web3::EthCall(const String &from, const String &to, const String &data)
{
    String m = "eth_call";
    String p = "[{\"from\":\"" + from + "\",\"to\":\"" + to + "\",\"data\":\"" + data + "\"}, \"latest\"]";
    String input = generateJson(m, p);
    return exec(input);
}

String Web3::EthSendTransaction(const String &from, const String &to, const String &data)
{
    String m = "eth_sendTransaction";
    String p = "[{\"from\":\"" + from + "\",\"to\":\"" + to + "\",\"data\":\"" + data + "\"}]";
    String input = generateJson(m, p);
    return exec(input);
}

String Web3::EthSendSignedTransaction(const String &data, const uint32_t dataLen)
{
    String m = "eth_sendRawTransaction";
    String p = "[\"" + data + "\"]";
    String input = generateJson(m, p);
    return exec(input);
}

// -------------------------------
// Private

String Web3::generateJson(const String &method, const String &params)
{
    return "{\"jsonrpc\":\"2.0\",\"method\":\"" + method + "\",\"params\":" + params + ",\"id\":0}";
}

String Web3::exec(const String &data)
{
    if (client.begin(path) == false)
    {
        return "connection error";
    }
    // Make a HTTP request:

    client.addHeader("Content-Type", "application/json");
    client.addHeader("Connection", "close");
    int status = client.POST(data);

    if (status < 0)
    {
        return client.errorToString(status).c_str();
    }
    return client.getString();
}

int Web3::getInt(const String &json)
{
    deserializeJson(doc, json);
    int value = doc["result"].as<signed int>();
    doc.clear();
    return value;
}

long int Web3::getLongbyHex(const String &json)
{
    deserializeJson(doc, json);
    const char *value = doc["result"].as<const char *>();
    doc.clear();
    return strtol(value, NULL, 0);
}

long long int Web3::getLLbyHex(const String &json)
{
    deserializeJson(doc, json);
    const char *value = doc["result"].as<const char *>();
    doc.clear();
    return strtoll(value, NULL, 0);
}

double Web3::getDouble(const String &json)
{
    deserializeJson(doc, json);
    double value = doc["result"].as<double>();
    doc.clear();
    return value;
}

bool Web3::getBool(const String &json)
{
    deserializeJson(doc, json);
    bool value = doc["result"].as<bool>();
    doc.clear();
    return value;
}

String Web3::getString(const String &json)
{
    deserializeJson(doc, json);
    String value = doc["result"].as<String>();
    doc.clear();
    return value;
}

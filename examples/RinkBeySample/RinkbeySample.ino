#include <WiFi.h>
#include <Web3.h>
#include <Contract.h>

#define USE_SERIAL Serial

#define ENV_SSID     "ENV_SSID"
#define ENV_WIFI_KEY "ENV_WIFI_KEY"
string MY_ADDRESS = "MY_ADDRESS";   //#define MY_ADDRESS "MY_ADDRESS"
#define contract_address "CONTRACT_ADDRESS"
string CONTRACT_ADDRESS = "CONTRACT_ADDRESS";   //#define CONTRACT_ADDRESS "CONTRACT_ADDRESS"
string INFURA_HOST = "rinkeby.infura.io";   //#define INFURA_HOST "rinkeby.infura.io"
string INFURA_PATH = "INFURA_PATH";   //#define INFURA_PATH "INFURA_PATH"

const char PRIVATE_KEY[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

Web3 web3(&INFURA_HOST, &INFURA_PATH);     //Web3 web3(INFURA_HOST, INFURA_PATH);

void web3_example();
void eth_call_example();
void eth_send_example();

void setup() {
    USE_SERIAL.begin(115200);

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.begin(ENV_SSID, ENV_WIFI_KEY);

    // attempt to connect to Wifi network:
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        // wait 1 second for re-trying
        delay(1000);
    }

    USE_SERIAL.println("Connected");
    
    web3_example();
    eth_call_example();
    eth_send_example();
}

void loop() {
    // put your main code here, to run repeatedly:
}

void web3_example() {
    string result = web3.Web3ClientVersion();
    USE_SERIAL.println("web3_ClientVersion");
    USE_SERIAL.println(result.c_str());    //USE_SERIAL.println(result);

    string src = "0x68656c6c6f20776f726c64";
    result = web3.Web3Sha3(&src);
    USE_SERIAL.println("web3_sha3");
    USE_SERIAL.println(result.c_str());   //USE_SERIAL.println(result);
}

void eth_call_example() {
    Contract contract(&web3, &CONTRACT_ADDRESS);   // Contract contract(&web3, CONTRACT_ADDRESS);
    strcpy(contract.options.from, MY_ADDRESS);
    strcpy(contract.options.gasPrice,"2000000000000");
    contract.options.gas = 5000000;
    string func = "get()";
    string param = contract.SetupContractData(&func);
    string result = contract.Call(&param);
    USE_SERIAL.println(result.c_str());
}

void eth_send_example() {
    Contract contract(&web3, &CONTRACT_ADDRESS);  // Contract contract(&web3, CONTRACT_ADDRESS);
    contract.SetPrivateKey((uint8_t*)PRIVATE_KEY);
    uint32_t nonceVal = (uint32_t)web3.EthGetTransactionCount(&MY_ADDRESS); //uint32_t nonceVal = (uint32_t)web3.EthGetTransactionCount((char *)MY_ADDRESS);
    uint32_t gasPriceVal = 141006540;
    uint32_t  gasLimitVal = 3000000;
    string toStr = contract_address;  //uint8_t toStr[] = CONTRACT_ADDRESS;
    string valueStr = "0x00";   //uint8_t valueStr[] = "0x00";
    uint8_t dataStr[100];
    memset(dataStr, 0, 100);
    string func = "set(uint256)";
    string p = contract.SetupContractData(&func, 123);
    string result = contract.SendTransaction(nonceVal, gasPriceVal, gasLimitVal, &toStr, &valueStr, &p); 
    USE_SERIAL.println("ETH_SEND_TRANSACTION_COMPLITE");
    USE_SERIAL.println(result.c_str());    //USE_SERIAL.println(result);
}

## web3-arduino

![img](https://user-images.githubusercontent.com/891384/36104056-4994f600-1054-11e8-94f4-9f067610a6bf.png)

- What is this library?

  - This is an Arduino (or ESP32) library to use web3 on Ethereum platform.

- What is Arduino?
  - Arduino is an open source computer hardware and software.
  - https://www.arduino.cc/
- What is ESP32?
  - ESP32 is a series of low cost, low power system on a chip microcontrollers with integrated Wi-Fi and dual-mode Bluetooth.
  - https://www.espressif.com/en/products/hardware/esp32/overview
- What is web3?
  - Web3 is the Ethereum compatible API which implements the Generic JSON RPC spec. Originally Javascript version is developed.
  - https://github.com/ethereum/web3.js/
- What is Ethereum?
  - Ethereum is a decentralized platform for applications that run exactly as programmed without any chance of fraud, censorship or third-party interference.
  - https://www.ethereum.org/

## Environment

- Confirmed device
  - ESP-WROOM-32
- Used Ethereum client
  - localhost (hardhat)

## Installation

1. download the zip file from `Clone or download` button on Github.
2. launch Arduino IDE.
3. `Sketch` -> `Include Library` -> `Add .ZIP file` -> select downloaded zip file.
4. Then you can use this from Arduino IDE.

## Example

Please refer `examples` directory.

### setup

```C++
String account = "0xf39Fd6e51aad88F6F4ce6aB8827279cffFb92266";
String contract_address = "0x5FbDB2315678afecb367f032d93F642f64180aa3";

Web3 web3("localhost", "http://192.168.0.9:8545/");
```

### call web3 methods

```C++
Serial.println(web3.Web3ClientVersion());
Serial.println(web3.Web3Sha3("0x68656c6c6f20776f726c64"));
Serial.println(web3.NetVersion());
Serial.println(web3.NetListening());
Serial.println(web3.NetPeerCount());
Serial.println(web3.EthProtocolVersion());
Serial.println(web3.EthSyncing());
Serial.println(web3.EthMining());
Serial.println(web3.EthGasPrice());
Serial.println(web3.EthBlockNumber());
Serial.println(web3.EthGetBalance(account));
Serial.println(web3.EthGetTransactionCount(account));
```

### `call` to Contract

```C++
Contract contract(&web3, contract_address);
contract.SetPrivateKey(PRIVATE_KEY);
contract.SetAccount(account);
```

### `sendTransaction` to Contract

```C++
String retrieve_code = contract.SetupContractData("f", "retrieve()");
Serial.println(contract.Call(retrieve_code));

String store_code = contract.SetupContractData("fu", "store(uint256)", 123);
Serial.println(contract.SendTransaction(store_code));

Serial.println(contract.Call(retrieve_code));
```

## Dependency

- [ArduinoJson] (https://arduinojson.org/)
- [HTTPClient] (https://www.arduino.cc/reference/en/libraries/httpclient/)
- [ESP32-Arduino](https://github.com/espressif/arduino-esp32)

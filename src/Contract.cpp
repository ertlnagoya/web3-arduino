//
// Created by Kawai Kenta 2022/09/11.
//

#include <Contract.h>
#include <Web3.h>
#include <Arduino.h>

/**
 * Public functions
 * */
Contract::Contract(Web3 *_web3, const String &address)
{
    web3 = _web3;
    contractAddress = address;
    options.gas = 0;
    options.from = "";
    options.gasPrice = "0";
}

void Contract::SetPrivateKey(const uint8_t *key)
{
    privateKey = key;
}

void Contract::SetAccount(const String &account)
{
    options.from = account;
}

void Contract::SetGasPrice(const String &gasPrice)
{
    options.gasPrice = gasPrice;
}

void Contract::SetGas(const long gas)
{
    options.gas = gas;
}

String Contract::SetupContractData(const String &args_format, ...)
{
    String data = "";
    va_list args;
    va_start(args, args_format);
    for (int i = 0; i < args_format.length(); i++)
    {
        char c = args_format[i];
        if (c == 'f')
        {
            data += GenerateContractBytes(va_arg(args, const char *));
        }
        else if (c == 'u')
        {
            data += GenerateBytesForUint(va_arg(args, uint32_t));
        }
        else if (c == 'i')
        {
            data += GenerateBytesForInt(va_arg(args, int32_t));
        }
        else if (c == 'a')
        {
            data += GenerateBytesForAddress(va_arg(args, const char *));
        }
        else if (c == 's')
        {
            data += GenerateBytesForString(va_arg(args, const char *));
        }
        else if (c == 'b')
        {
            data += GenerateBytesForBytes(va_arg(args, const char *));
        }
    }
    va_end(args);
    return data;
}

String Contract::Call(const String &data)
{
    return web3->EthCall(options.from, contractAddress, data);
}

String Contract::SendTransaction(const String &data)
{
    return web3->EthSendTransaction(options.from, contractAddress, data);
}

/**
 * Private functions
 * */
String Contract::GenerateContractBytes(const String &func)
{
    String in = "0x";
    char intmp[8];
    memset(intmp, 0, 8);
    for (int i = 0; i < func.length(); i++)
    {
        char c = func[i];
        sprintf(intmp, "%x", c);
        in = in + intmp;
    }
    String out = web3->Web3Sha3(in);
    return out.substring(0, 10);
}

String Contract::GenerateBytesForUint(const uint32_t value)
{
    String hex_val = String(value, HEX);
    String zero_padding = "";
    for (int i = 0; i < 64 - hex_val.length(); i++)
    {
        zero_padding += "0";
    }
    return zero_padding + hex_val;
}

String Contract::GenerateBytesForInt(const int32_t value)
{
    char output[70];
    memset(output, 0, sizeof(output));

    // check number of digits
    char dummy[64];
    int digits = sprintf(dummy, "%x", value);

    // fill 0 and copy number to string
    char fill[2];
    if (value >= 0)
    {
        sprintf(fill, "%s", "0");
    }
    else
    {
        sprintf(fill, "%s", "f");
    }
    for (int i = 2; i < 2 + 64 - digits; i++)
    {
        sprintf(output, "%s%s", output, fill);
    }
    sprintf(output, "%s%x", output, value);
    return String(output);
}

String Contract::GenerateBytesForAddress(const String &value)
{
    size_t digits = value.length() - 2;

    String zeros = "";
    for (int i = 2; i < 2 + 64 - digits; i++)
    {
        zeros = zeros + "0";
    }
    String tmp = value.substring(2);
    return zeros + tmp;
}

String Contract::GenerateBytesForString(const String &value)
{
    String right = GenerateBytesForBytes(value);
    String left = String(value.length(), HEX);
    String zero_padding = "";
    for (int i = 0; i < 64 - left.length(); i++)
    {
        zero_padding += "0";
    }
    return zero_padding + left + right;
}

String Contract::GenerateBytesForBytes(const String &value)
{
    char output[70];
    memset(output, 0, sizeof(output));

    for (int i = 0; i < value.length(); i++)
    {
        sprintf(output, "%s%x", output, value[i]);
    }
    size_t remain = 32 - ((strlen(output) - 2) % 32);
    for (int i = 0; i < remain + 30; i++)
    {
        sprintf(output, "%s%s", output, "0");
    }

    return String(output);
}
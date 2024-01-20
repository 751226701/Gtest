#pragma once
#ifndef Y16_DECODE_H
#define Y16_DECODE_H

#include <ctime>
#include <cstring>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
using namespace std;

class TemperatureAnalyzer {
public:
    static void getTemp(const std::string& temp) {
        std::vector<short> short_temp;
        std::string decoded_temp = base64_decode(temp);
        const char* decode_byte_temp = decoded_temp.c_str();
        size_t count = decoded_temp.length() / 2;

        for (size_t i = 0; i < count; ++i) {
            /*short value = (decode_byte_temp[i * 2 + 1] << 8) | decode_byte_temp[i * 2];*/
            short value = (static_cast<uint8_t>(decode_byte_temp[i * 2 + 1]) << 8) | static_cast<uint8_t>(decode_byte_temp[i * 2]);
            short_temp.push_back(value);
        }

        short maxtemp = short_temp[0];
        short mintemp = short_temp[0];

        for (size_t i = 0; i < std::min(short_temp.size(), static_cast<size_t>(IMAGE_WIDTH * IMAGE_HEIGHT)); ++i)
        {
            if (maxtemp <= short_temp[i]) {
                maxtemp = short_temp[i];
            }
            if (mintemp >= short_temp[i]) {
                mintemp = short_temp[i];
            }
        }

        std::time_t now = std::time(nullptr);
        std::tm* time_info = std::localtime(&now);
        char time_str[100];
        std::strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S]", time_info);

        std::cout << time_str << " maxTemp: " << static_cast<double>(maxtemp) / 100.0 << std::endl;
        std::cout << time_str << " minTemp: " << static_cast<double>(mintemp) / 100.0 << std::endl;
        std::cout << std::endl;
    }

private:
    static const int IMAGE_WIDTH = 640;
    static const int IMAGE_HEIGHT = 512;

    static std::string base64_decode(const std::string& encoded_data) {
        BIO* bio = BIO_new(BIO_f_base64());
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
        BIO* mem = BIO_new_mem_buf(encoded_data.c_str(), encoded_data.length());
        bio = BIO_push(bio, mem);

        const size_t decode_length = encoded_data.length() * 3 / 4;
        char* buffer = new char[decode_length + 1];
        memset(buffer, 0, decode_length + 1);

        BIO_read(bio, buffer, encoded_data.length());
        std::string decoded_data(buffer);
        delete[] buffer;

        BIO_free_all(bio);
        return decoded_data;
    }
};

#endif  


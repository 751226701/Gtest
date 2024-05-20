#include <iostream>
#include <string>
#include <regex>
#include <curl/curl.h>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getStockPrice(const std::string& stockCode) {
    std::string url = "http://hq.sinajs.cn/list=" + stockCode;
    std::string data;

    CURL* curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        CURLcode res = curl_easy_perform(curl);

        
        if (res != CURLE_OK) {
            std::cerr << "Failed to get data: " << curl_easy_strerror(res) << std::endl;
        }

        
        curl_easy_cleanup(curl);
    }

    
    std::regex pattern("\"([^\"]*)\"");
    std::smatch matches;
    std::regex_search(data, matches, pattern);
    if (matches.size() > 1) {
        return matches[1];
    }
    else {
        return "N/A";
    }
}

int main() {
    std::string stockCode = "sh000001"; 
    std::string price = getStockPrice(stockCode);
    std::cout << "实时股价：" << price << std::endl;
    return 0;
}

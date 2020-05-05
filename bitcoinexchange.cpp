#include<iostream>
#include<memory>
#include<functional>
#include<array>
#include<cstdio>
#include "curl.h"
#include "json.hpp"
typedef std::unique_ptr<CURL,std::function<void(CURL* )>> CURL_ptr;
using namespace std;
extern "C" std::size_t dataHandler(const char* buffer,std::size_t size,std::size_t nmeb,std::string* userData)
{
    if(userData==nullptr)
    {
        return 0;
    }
    userData->append(buffer,(size*nmeb));
    return size*nmeb;
}
class CurlHandle
{
private:
    /* data */
    CURL_ptr curlptr;
    constexpr static auto deleter =[](CURL* c)
    {
        curl_easy_cleanup(c);
        curl_global_cleanup();
    };
    std::string data;
public:
    CurlHandle(): curlptr(curl_easy_init(), deleter){
         curl_global_init(CURL_GLOBAL_ALL);
         curl_easy_setopt(curlptr.get(),CURLOPT_WRITEFUNCTION,dataHandler);         
         curl_easy_setopt(curlptr.get(),CURLOPT_WRITEDATA,&data);         

    }
    void setUrl(std::string url)
    {
        curl_easy_setopt(curlptr.get(),CURLOPT_URL,url.c_str());
    }
    CURLcode fetch()
    {
        return curl_easy_perform(curlptr.get());
    }
    std::string getFetchedData()
    {
        return data;
    }
    //~CurlHandle();
};

class Bitcoin
{
    using json =nlohmann::json;
    private :
    CurlHandle curlHandle;
    static constexpr const char* API_URL="https://blockchain.info/ticker";

    public:
    Bitcoin(): curlHandle({})
    {
        curlHandle.setUrl(API_URL);
    }
    json fetchBitcoinData()
    {
        curlHandle.fetch();
        return json::parse(curlHandle.getFetchedData());
    }
};
int main()
{   
    using json=nlohmann::json;
    try{
        Bitcoin bitcoin;
        json bitcoinData=bitcoin.fetchBitcoinData();
        cout<<"1 BTC = \n";
        for(auto it=bitcoinData.begin();it!=bitcoinData.end();++it)
        {
            printf("\t(%3s)%10d %s/n",it.key().c_str(),it.value()["last"].get<int>(),it.value()["symbol"].get<string>().c_str());
        }
    }
    catch(...)
    {
        cerr<<"Failed To Fetch Bitcoin Exchange rates\n";
    }
}

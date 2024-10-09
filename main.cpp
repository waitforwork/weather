#include <iostream>
#include <curl/curl.h>
#include <string>
#include <fstream>

// функция, вызываемая cURL для записи полученых данных
using namespace std;
std::string curlBuffer;
size_t curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    size_t result = 0;
    if (buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

int main()
{
    // запрашиваемая страничка(путь до login screen)
    const char *url = "https://www.gismeteo.ru/weather-sankt-peterburg-4079/tomorrow/";
    // буфер для сохранения текстовых ошибок
    char curlErrorBuffer[CURL_ERROR_SIZE];
    CURL *curl = curl_easy_init();
    std::ofstream out_file;
    out_file.open("file_write.txt");
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlErrorBuffer);
        // задаем URL...
        curl_easy_setopt(curl, CURLOPT_URL, url);
        // переходить по "Location:" указаному в HTTP заголовке
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true); //Алекс: под вопросом надо ли...
        // не проверять сертификат удаленного сервера
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        // функция, вызываемая cURL для записи полученых данных
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
        // выполнить запрос
        CURLcode curlResult = curl_easy_perform(curl);
        // завершение сеанса
        curl_easy_cleanup(curl);
        if (curlResult != CURLE_OK)
        {
            std::cout << "Ошибка(" << curlResult << "): " << curlErrorBuffer << std::endl;
            return(-1);
        }

        //std::cout << curlBuffer << std::endl;
        std::string text=curlBuffer;
        if(out_file.is_open())
        {
            out_file << curlBuffer;
        }

        int test = text.find("<div class=\"day\">Завтра</div>"); //<div class="day">Завтра</div>
        std::string vrem_str;
        std::string date;
        std::string min_value;
        std::string max_value;
        vrem_str=text.substr(test-18,16);
        for (int i=0; i<15; i++)
        {
            if (vrem_str[i]=='0'||vrem_str[i]=='1'||vrem_str[i]=='2'||vrem_str[i]=='3'||vrem_str[i]=='4'||vrem_str[i]=='5'||vrem_str[i]=='6'||vrem_str[i]=='7'||vrem_str[i]=='8'||vrem_str[i]=='9')
                date+=vrem_str[i];
            if (vrem_str[i]=='<')
            {
                date+=' ';
                date+=vrem_str[i-6];
                date+=vrem_str[i-5];
                date+=vrem_str[i-4];
                date+=vrem_str[i-3];
                date+=vrem_str[i-2];
                date+=vrem_str[i-1];
            }
        }
        vrem_str=text.substr(test+220,8);
        for (int i=0; i<15; i++)
        {
            if (vrem_str[i]=='0'||vrem_str[i]=='1'||vrem_str[i]=='2'||vrem_str[i]=='3'||vrem_str[i]=='4'||vrem_str[i]=='5'||vrem_str[i]=='6'||vrem_str[i]=='7'||vrem_str[i]=='8'||vrem_str[i]=='9')
                min_value+=vrem_str[i];
        }
        vrem_str=text.substr(test+348,8);
        for (int i=0; i<15; i++)
        {
            if (vrem_str[i]=='0'||vrem_str[i]=='1'||vrem_str[i]=='2'||vrem_str[i]=='3'||vrem_str[i]=='4'||vrem_str[i]=='5'||vrem_str[i]=='6'||vrem_str[i]=='7'||vrem_str[i]=='8'||vrem_str[i]=='9')
                max_value+=vrem_str[i];
        }
        std::cout << "Температура днем " << date << ".: от " << min_value << " до " << max_value << " гр." << std::endl;
        // "<div class="day">Завтра</div>"
        //std::cout << pos << std::endl;

    }
    return 0;
}

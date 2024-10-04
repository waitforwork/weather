#include <iostream>
#include<curl/curl.h>
#include <string>

std::string get_http()
{
    CURL *curl;
    CURLcode res;
    std::string full_info;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // отключили сертификацию
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.gismeteo.ru/weather-sankt-peterburg-4079/tomorrow/");  //ищем слово Войти, там есть ссылка https://www.cyberforum.ru/auth.php
            // переходим на нее
        // example.com is redirected, so we tell libcurl to follow redirection
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);



        // Perform the request, res will get the return code
        std::cout << "\n\n\n\n\n\n================================================================\n\n\n\n" << std::endl;
        std::cout << curl_easy_perform(curl) <<std::endl;
        std::cout << "\n\n\n\n\n\n================================================================\n\n\n\n" << std::endl;
        /*res = curl_easy_perform(curl); //выводит результат
        // Check for errors
        if(res != CURLE_OK)
        {

            full_info=res;
                //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        }
        // always cleanup*/
        curl_easy_cleanup(curl);
    }
    return full_info;
}
void start_parse(std::string code_of_pages)
{

}

int main(void)
{
    start_parse(get_http());
return 0;
}

/*i#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
using std::string;
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int downloadurl(std::string URL,std::string localDirectory)
{
  CURL *curl_handle;
  static const char *pagefilename = localDirectory.c_str();
  FILE *pagefile;

  curl_global_init(CURL_GLOBAL_ALL);

// init the curl session
curl_handle = curl_easy_init();

// set URL to get here
curl_easy_setopt(curl_handle, CURLOPT_URL, URL.c_str());

// Switch on full protocol/debug output while testing
curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

// disable progress meter, set to 0L to enable it
curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

//  send all data to this function
curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

// open the file
pagefile = fopen(pagefilename, "wb");
if(pagefile)
{
    // write the page body to this file handle
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
    //get it!
    curl_easy_perform(curl_handle);
    // close the header file
    fclose(pagefile);
}
// cleanup curl stuff
curl_easy_cleanup(curl_handle);

curl_global_cleanup();

return 0;
}
void curlMainWindow::on_pushButton_clicked()
{
    downloadurl("https://img.zcool.cn/community/01ddc256eb71586ac7257d209712b7.jpg@1280w_1l_2o_100sh.jpg","./test.jpg");
}
*/

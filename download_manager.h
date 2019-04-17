
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <vector>

#include <cpr/cpr.h>

std::string _start_download(const std::string& url) {

    std::cout << "Downloading " << url << std::endl;
    auto r = cpr::Get(cpr::Url{url});
    return r.text;
}

class DownloadManager{
/*
Download files in parallel
*/

public:
    DownloadManager() {}

    void start_download(const std::string& url) {
        /* Schedule another file

        url - URL for HTTP request line
        */

        std::packaged_task<std::string(const std::string&)> ptask(_start_download);
        _downloads.push_back(ptask.get_future().share());

        std::thread thr(std::move(ptask), url);
        thr.detach();
    }

    typedef std::shared_future<std::string> FutureContents;

    const std::vector<FutureContents>&  downloads() const { 
        /* 
        Access results 
        */
        return _downloads; 
    }

private:
    std::vector<FutureContents> _downloads;    
};

void wait_all(const DownloadManager& down_man) {
    /*
    Wait all downloads finished
    */
    std::for_each(down_man.downloads().begin(), down_man.downloads().end(),
        [](const DownloadManager::FutureContents& ftr){ 
            std::cout << "wait" << std::endl;
            ftr.wait(); 
            } );
}



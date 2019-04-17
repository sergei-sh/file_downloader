
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <vector>

#include <cpr/cpr.h>

std::string _start_download(const std::string& url) {

    std::cout << "Downloading " << url << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    auto r = cpr::Get(cpr::Url{url});

    return r.text;
}

class DownloadManager{
public:
    DownloadManager() {}

    void start_download(const std::string& url) {

        std::packaged_task<std::string(const std::string&)> ptask(_start_download);
        _downloads.push_back(ptask.get_future().share());

        std::thread thr(std::move(ptask), url);
        thr.detach();
    }

    typedef std::shared_future<std::string> FutureContents;

    const std::vector<FutureContents>&  downloads() const { return _downloads; }

private:
    std::vector<FutureContents> _downloads;    
};

void wait_all(const DownloadManager& down_man) {
    std::for_each(down_man.downloads().begin(), down_man.downloads().end(),
        [](const DownloadManager::FutureContents& ftr){ 
            std::cout << "wait" << std::endl;
            ftr.wait(); 
            } );
}



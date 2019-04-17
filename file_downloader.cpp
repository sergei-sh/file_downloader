
#include <iostream>
#include <fstream>
#include <future>
#include <string>

#include "download_manager.h"

//TODO: pass as command-line arg
const std::string INPUT_FILE = "../file_list.txt";
const std::string OUTPUT_DIR = ".";

/* 
Demonstrate how DownloadManager works

TODO: add screen output of files with keyboard listing
*/
int main() {
    std::ifstream infile;
    infile.open(INPUT_FILE);
    if (!infile.is_open()) {
        std::cout << "Input file not open" << std::endl;
    }

    DownloadManager down_man;

    while (!infile.eof()) {
        std::string url_line;
        infile >> url_line;
        if (url_line.size()) {
            std::cout << "main " << url_line << std::endl;
            down_man.start_download(url_line);
        }
    }

    wait_all(down_man);    

    //just make sure we store data for multiple access
    std::cout << down_man.downloads()[0].get() << std::endl;
    std::cout << down_man.downloads()[1].get() << std::endl;
    std::cout << down_man.downloads()[0].get() << std::endl;

    return 0;
}

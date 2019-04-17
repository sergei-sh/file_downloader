
#include <iostream>
#include <fstream>
#include <future>
#include <string>

#include "download_manager.h"

const std::string INPUT_FILE = "file_list.txt";
const std::string OUTPUT_DIR = ".";

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
            std::cout << "main" << url_line << std::endl;
            down_man.start_download(url_line);
        }
    }

    wait_all(down_man);    

    return 0;
}

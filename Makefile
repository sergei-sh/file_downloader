file_downloader: file_downloader.o
	g++ -Wall -g -o file_downloader file_downloader.o -pthread
file_downloader.o: file_downloader.cpp download_manager.h
	g++ -Wall -g -c -std=c++1y file_downloader.cpp -lpthread 

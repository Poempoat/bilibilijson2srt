#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <dirent.h>
#include <cstring>

void Json_srt(const char* inputPath, const char* outputPath);

int main(int argc, char *argv[]) {
    std::cout << "Bilibili json2srt v1.0.0" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Usage: your_program -i input_file [-o output_file]" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << " json2srt -i input.json -o output.srt" << std::endl;
    std::cout << " " << std::endl;



    std::string inputFileName, outputFileName;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-i" && i + 1 < argc) {
            inputFileName = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFileName = argv[++i];
        }
    }

    if (inputFileName.empty()) {
        std::cerr << "Error: Input file not specified." << std::endl;
        return 1;
    }


    Json_srt(inputFileName.c_str(), outputFileName.c_str());
    std::cout.clear();
    std::cout << "Success" << std::endl;
    return 0;
}

void Json_srt(const char* inputPath, const char* outputPath) {
    std::ifstream openfile;
    std::string temp;
    std::string buffer;
    char Newname[256] = {0};

    openfile.open(inputPath, std::ios::in);
    int i = 0;
    while (inputPath[i] != '.') {
        Newname[i] = inputPath[i];
        i++;
    }
    

    if (outputPath != nullptr && outputPath[0] != '\0') {
        strcpy(Newname, outputPath);
    } else {
        strcat(Newname, ".srt");
    }

    std::ofstream outfile(Newname, std::ios::out);
    if (!openfile.is_open()) {
        std::cout << "Error opening file: " << inputPath << std::endl;
        return;
    }

    while (std::getline(openfile, temp)) {
        // Do something if needed
    }

    long int pbeigen = 0, pendl = 0, num, count = 0;
    float time;
    int hour, minute, second, millisecond;

    while (1) {
        count++;
        pbeigen = temp.find("from", pendl);
        if (pbeigen == -1) break;

        outfile << count << "\n";

        pendl = temp.find(",", pbeigen);
        num = pendl - pbeigen - 6;
        buffer = temp.substr(pbeigen + 6, num);

        time = std::stof(buffer);
        millisecond = (time - (int)time) * 1000;
        second = (int)time % 60;
        minute = (int)time / 60 % 60;
        hour = (int)time / 60 / 60 % 12;

        outfile << std::setfill('0') << std::setw(2) << hour << ":" << std::setw(2) << minute << ":" << std::setw(2) << second << "," << std::setw(3) << millisecond << " --> ";

        pbeigen = temp.find("to", pendl);
        pendl = temp.find(",", pbeigen);
        num = pendl - pbeigen - 4;
        buffer = temp.substr(pbeigen + 4, num);

        time = std::stof(buffer);
        millisecond = (time - (int)time) * 1000;
        second = (int)time % 60;
        minute = (int)time / 60 % 60;
        hour = (int)time / 60 / 60 % 12;

        outfile << std::setfill('0') << std::setw(2) << hour << ":" << std::setw(2) << minute << ":" << std::setw(2) << second << "," << std::setw(3) << millisecond << " \n ";

        pbeigen = temp.find("content", pendl);
        pendl = temp.find("\"}", pbeigen);
        num = pendl - pbeigen - 10;
        buffer = temp.substr(pbeigen + 10, num);

        outfile << buffer << "\n\n";

        if (pendl == -1)
            break;
    }
}


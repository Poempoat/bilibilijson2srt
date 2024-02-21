#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <dirent.h>
#include <cstring>
void Json_srt(const char* name);

int main() {
    // 无需 system("pause")，在 Linux 下运行会自动等待用户输入
    std::string inPath = "*.json";  // 待处理的json文件
    DIR *dir;
    struct dirent *ent;
    
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string filename = ent->d_name;
            if (filename.find(".json") != std::string::npos) {
                Json_srt(filename.c_str());
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return -1;
    }

    return 0;
}

void Json_srt(const char* name) {
    std::ifstream openfile;
    std::string temp;
    std::string buffer;
    char Newname[256] = {0};

    openfile.open(name, std::ios::in);
    int i = 0;
    while (name[i] != '.') {
        Newname[i] = name[i];
        i++;
    }
    strcat(Newname, ".srt");

    std::ofstream outfile(Newname, std::ios::out);
    if (!openfile.is_open()) {
        std::cout << "Error opening file: " << name << std::endl;
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


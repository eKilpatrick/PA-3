#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>

int LinearBackoff(int N) {
    int totalSlots = 0;
    int win_size = 2;
    int remaining_devices = N;

    while (remaining_devices != 0) {
        std::vector<int> randList(win_size, 0);

        for (int i = 0; i < remaining_devices; ++i) {
            int randNum = rand() % win_size;
            randList[randNum]++;
        }

        int lastSlot = 0;
        for (int i = 0; i < win_size; i++) {
            if (randList[i] == 1) {
                remaining_devices--;
                lastSlot = i;
            }
        }

        if (remaining_devices == 0) {
            totalSlots += lastSlot;
        } else {
            totalSlots += win_size;
        }

        win_size++;
    }
    return totalSlots;
}

int BinaryBackoff(int N) {
    int totalSlots = 0;
    int win_size = 2;
    int remaining_devices = N;

    while (remaining_devices != 0) {
        std::vector<int> randList(win_size, 0);

        for (int i = 0; i < remaining_devices; ++i) {
            int randNum = rand() % win_size;
            randList[randNum]++;
        }

        int lastSlot = 0;
        for (int i = 0; i < win_size; i++) {
            if (randList[i] == 1) {
                remaining_devices--;
                lastSlot = i;
            }
        }

        if (remaining_devices == 0) {
            totalSlots += lastSlot;
        } else {
            totalSlots += win_size;
        }

        win_size *= 2;
    }
    return totalSlots;
}

int LogLogBackoff(int N) {
    int totalSlots = 0;
    int win_size = 4;
    int remaining_devices = N;

    while (remaining_devices != 0) {
        std::vector<int> randList(win_size, 0);

        for (int i = 0; i < remaining_devices; i++) {
            int randNum = rand() % win_size;
            randList[randNum]++;
        }

        int lastSlot = 0;
        for (int i = 0; i < win_size; ++i) {
            if (randList[i] == 1) {
                remaining_devices--;
                lastSlot = i;
            }
        }

        if (remaining_devices == 0) {
            totalSlots += lastSlot;
        } else {
            totalSlots += win_size;
        }

        win_size = static_cast<int>(std::floor((1 + 1/(std::log2(std::log2(win_size)))) * win_size));
    }
    return totalSlots;
}

void writeToFile(const std::string& filename, int avgLatency) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << avgLatency << '\n';
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

void mainFunction() {
    std::ofstream linFile("linearLatency.txt");
    std::ofstream binFile("binaryLatency.txt");
    std::ofstream logFile("loglogLatency.txt");

    for (int num_devices = 100; num_devices <= 6000; num_devices += 100) {
        std::cout << "Running Test for N: " << num_devices << std::endl;

        int avgLinear= 0, avgBinary = 0, avgLogLog = 0;
        int sumLinear = 0, sumBinary = 0, sumLogLog = 0;
        for (int i = 0; i < 10; i++) {
            sumLinear += LinearBackoff(num_devices);
            sumBinary += BinaryBackoff(num_devices);
            sumLogLog += LogLogBackoff(num_devices);
        }

        avgLinear = sumLinear / 10;
        avgBinary = sumBinary / 10;
        avgLogLog = sumLogLog / 10;

        linFile << avgLinear << "\n";
        binFile << avgBinary << "\n";
        logFile << avgLogLog << "\n";
    }

    linFile.close();
    binFile.close();
    logFile.close();
}

int main() {
    mainFunction();
    return 0;
}
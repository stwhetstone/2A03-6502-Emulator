#include <fstream>
#include <string>
#include <sstream>

#include "rom.hpp"



ROM::Core::Core(Emulator::MainBus &t_bus) : bus(t_bus) {
    _size = 0;
}

void ROM::Core::textToByteFile(std::string fileName) {
    std::ifstream file(fileName + ".txt");
    std::ofstream outFile(fileName + ".asm");

    std::string fileText, curByte;
    std::getline(file, fileText);

    std::stringstream fileStream(fileText);

    while(std::getline(fileStream, curByte, ' ')) {
        _bytes.push_back(std::stoi(curByte, nullptr, 16));
    }

    outFile.write((char*)_bytes.data(), _bytes.size());

    _size = _bytes.size();
}



char ROM::Core::dataBusLoadByteFromPC(uint16_t pc) {
    if(pc > _size) {
        return -1;
    }

    bus.data = _bytes[pc];

    return 0;
}


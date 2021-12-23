#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class Settings {
public:
    Settings(int argc, char* argv[]) 
        : validState(false), 
        sizeConfigured(false),
        nameConfigured(false),
        multiplier(1000000),
        fileSize(0) {
        if (argc < 2) {
            return;
        }
        for (int i = 0; i < argc; i++) {
            if ( (std::string(argv[i]) == "--size") && ( (i+1) < argc) ) {
                int size(0);
                size = std::stoi(argv[i+1]);
                if ( size > 0) {
                    fileSize = size;
                    sizeConfigured = true;
                } 
            } else if ( (std::string(argv[i]) == "--name") && ( (i+1) < argc) ) {
                fileName = argv[i+1];
                nameConfigured = true;
            } else if ( std::string(argv[i]) == "--b" ) {
                multiplier = 1; 
            } else if ( std::string(argv[i]) == "--kb" ) {
                multiplier = 1000; 
            } else if ( std::string(argv[i]) == "--mb" ) {
                multiplier = 1000000; 
            }
        }
        validState = sizeConfigured && nameConfigured;
    }
    int getFileSize() const {
        return fileSize;
    }
    const std::string& getFileName() const {
        return fileName;
    }
    bool correctlyConfigured() const {
        return validState;
    }
    int getMultiplier() const {
        return multiplier;
    }
private:
    bool validState;
    bool sizeConfigured;
    bool nameConfigured;
    unsigned int fileSize;
    unsigned int multiplier;
    std::string fileName;
};

void createFile(const Settings& s) {
    const int numberOfBytesPerInteger(4);
    
    std::ofstream outFile(s.getFileName(), std::ios::binary);
    int numberOfIterations = ( s.getMultiplier() * s.getFileSize()) / numberOfBytesPerInteger; 
    for( int i = 0; i < numberOfIterations; i++) {
        outFile.write(reinterpret_cast<char*>(&i),sizeof(i));
    }
    outFile.close();
}

int main(int argc, char * argv[]) {

    Settings settings(argc, argv);
    
    std::cout << "Size : " << settings.getFileSize() << "\n";
    std::cout << "File Name : " << settings.getFileName() << "\n";

    if(settings.correctlyConfigured()) {
        createFile(settings);
    }    

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class FileRALL {
public:
    FileRALL(std::string filename){
        fileHandle = fopen(filename.c_str(), "r");
    };
    void readWriteFile()
        {
            //...
        }
    ~FileRALL() {
        fclose(fileHandle);
        //delete fileHandle;
        fileHandle = nullptr;
    };
private:
    FILE* fileHandle;
};


int main() {
    
    std::string filename = "D:/tabble/work2.txt";
    FileRALL file(filename);
    file.readWriteFile();
    //FILE* fileHandle;
    
    //fileHandle = fopen(filename.c_str(), "r");
    //
    ////read & write file
    //fclose(fileHandle);
    return 0;
}

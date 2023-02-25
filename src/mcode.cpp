#include <iostream>
#include <fstream>

#include "algs/rle.h"

using std::cout, std::endl;

constexpr u_int buffer_length = 1000;  // this buffer needs to be the same size as the buffer in rle.cpp


void encode(const int mode, std::ifstream &in_file, std::ofstream &out_file){
    char input_file_buffer[buffer_length] = {0 };

    while(in_file) {  // while in_file isn't errored
        // read part of file to buffer
        in_file.read(input_file_buffer, buffer_length);
        char out_file_buffer[buffer_length * 10];
        char *out_file_buffer_p;
        u_int out_data_length = 0;

        if(mode == 0){
            out_file_buffer_p = rle_compress(input_file_buffer, out_data_length);
        } else if (mode == 1) {
            out_file_buffer_p = rle_decompress(input_file_buffer, out_data_length);
        }

        // this is so weird. .write won't work properly directly with the pointer, it requires the pointer to be transferred into an array??? aren't pointers and arrays super similar / the same?
        for (u_int i = 0; i < out_data_length; ++i) {
            out_file_buffer[i] = out_file_buffer_p[i];
        }

        out_file.write (out_file_buffer, out_data_length);
    }


    if (mode == 0) {
        cout << "*quake announcer voice* FILE COMPRESSED!" << endl;
    } else if (mode == 1) {
        cout << "*quake announcer voice* DE- DE- DECOMPRESSED!" << endl;
    }

}

int main(int argc, char **argv){

    if (argc <= 1) {
        cout << "too few args." << endl;
        return 0;
    }

    // check if argv[1] is a valid file.
    char filename[256];  // 255 is typical max char length for filenames. 256 chars accounts for null byte.
    std::strcpy(filename, argv[1]);  // already a design decision has been made to use c-style strings and not c++ strings

    // if filename has a file suffix of .mrb, decompress it, otherwise compress it.
    int len = strlen(filename);
    char ext[5] = { filename[len-4], filename[len-3],filename[len-2],filename[len-1]}; // this is 5 chars long and not 4 because of the null byte! this is needed for comparing strings correctly.

    // open file
    std::ifstream in_file;
    std::ofstream out_file;

    in_file.open(std::string(filename), std::ios::binary|std::ios::in);

    if(!in_file.is_open()){
        cout << "file could not be opened." << endl;
        return 0;
    }

    if (strcmp(ext, ".mrb") == 0){
        filename[len-4] = 0;
    } else {
        filename[len] = '.';
        filename[len+1] = 'm';
        filename[len+2] = 'r';
        filename[len+3] = 'b';
        filename[len+4] = 0;
    }

    out_file.open(std::string(filename), std::ios::binary|std::ios::out);

    if(!out_file.is_open()){
        cout << "output file could not be opened." << endl;
        return 0;
    }

    if (strcmp(ext, ".mrb") != 0){
        cout << "compressing file!" << endl;
        encode(0, in_file, out_file);
    } else {
        cout << ".mrb (machine-readable binary) file detected! decompressing file." << endl;
        encode(1,in_file, out_file);
    }

    in_file.close();
    out_file.close();

    // delete old file? or hide it?

    return 0;
}
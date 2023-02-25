//
// Created by Malcolm Boyes on 2023-02-24.
//

#include <locale>

#include "rle.h"

constexpr u_int buffer_length = 1000;

char* rle_compress(const char file_buff[], u_int &compressed_data_length){

    char compressed_file_buff[buffer_length * 2] = {0 };

    // we will worry about optimization in a minute (smallest possible types, ensuring there isn't a buffer overflow)

    // read from the file_buff
    char curr_run = 1;  // implications: largest tracked run could be 255 (depending on char implementation)

    for (int i = 1; i < buffer_length; ++i) {
        if (file_buff[i] == 0) { break; }

        if (file_buff[i] == file_buff[i-1]){
            ++curr_run;
        } else {

            compressed_file_buff[compressed_data_length] = curr_run;
            compressed_file_buff[compressed_data_length+1] = file_buff[i-1];

            compressed_data_length+=2;
            curr_run = 1;

            if (i == (buffer_length - 1)){
                compressed_file_buff[compressed_data_length] = 1;
                compressed_file_buff[compressed_data_length+1] = file_buff[i];
            }

            // implement a feature that accounts for runs that extend beyond buffer

        }
    }

    return compressed_file_buff;

}

char* rle_decompress(const char file_buff[], u_int &decompressed_data_length){

    char decompressed_file_buff[buffer_length * 10] = {0 };

    for (int i = 0; i < buffer_length; ++i, ++i) {
        if (file_buff[i] == 0) { break; } // this will need to be removed when compressing real binary data. any null byte in binary data would stop compression!

        for (int j = 0; j < int(file_buff[i]); ++j){

            decompressed_file_buff[decompressed_data_length] = file_buff[i+1];

            ++decompressed_data_length;

        }

    }

    return decompressed_file_buff;

}
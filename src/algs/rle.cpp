//
// Created by Malcolm Boyes on 2023-02-24.
//

#include <locale>

#include "rle.h"

constexpr u_int buff_len = 1000;

char* rle_compress(const char file_buff[]){

    char compressed_file_buff[buff_len*2] = { 0 };

    // we will worry about optimization in a minute (smallest possible types, ensuring there isn't a buffer overflow)

    // read from the file_buff
    char curr_run = 1;  // implications: largest tracked run could be 255 (depending on char implementation)
    u_int i_cfb = 0;

    for (int i = 1; i < buff_len; ++i) {
        if (file_buff[i] == 0) { break; }

        if (file_buff[i] == file_buff[i-1]){
            ++curr_run;
        } else {

            compressed_file_buff[i_cfb] = curr_run;
            compressed_file_buff[i_cfb+1] = file_buff[i-1];

            i_cfb+=2;
            curr_run = 1;

            if (i == (buff_len - 1)){
                compressed_file_buff[i_cfb] = 1;
                compressed_file_buff[i_cfb+1] = file_buff[i];
            }

            // implement a feature that accounts for runs that extend beyond buffer

        }
    }

    return compressed_file_buff;

}

char* rle_decompress(const char file_buff[]){

    char decompressed_file_buff[buff_len*10] = { 0 };


    int k = 0;

    for (int i = 0; i < buff_len; ++i, ++i) {
        if (file_buff[i] == 0) { break; } // this will need to be removed when compressing real binary data. any null byte in binary data would stop compression!

        for (int j = 0; j < int(file_buff[i]); ++j){

            decompressed_file_buff[k] = file_buff[i+1];

            ++k;

        }

    }

    return decompressed_file_buff;

}
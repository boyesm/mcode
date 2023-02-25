//
// Created by Malcolm Boyes on 2023-02-24.
//

#ifndef MCODE_RLE_H
#define MCODE_RLE_H

char* rle_compress(const char file_buff[], u_int &compressed_data_length);

char* rle_decompress(const char file_buff[], u_int &decompressed_data_length);


#endif //MCODE_RLE_H

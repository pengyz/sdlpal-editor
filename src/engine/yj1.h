#pragma once
#include <cstdint>

/**
 * @brief DOS版解压函数
 *
 * @param Source
 * @param Destination
 * @param DestSize
 * @return int32_t
 */
int32_t YJ1_Decompress(const void* Source, void* Destination, int32_t DestSize);

/**
 * @brief Win95版解压函数
 *
 * @param Source
 * @param Destination
 * @param DestSize
 * @return int32_t
 */
int32_t YJ2_Decompress(const void* Source, void* Destination, int32_t DestSize);
#ifndef HAL_LFS_H
#define HAL_LFS_H

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint8_t  hal_lfs_read(uint32_t offset, uint32_t length, uint8_t *buffer);
uint8_t  hal_lfs_program(uint32_t offset, uint32_t length, uint8_t *buffer);
void     hal_lfs_erase(uint32_t offset, uint32_t length);//@param: offset,length(Note:4K Aligned)

#endif // HAL_LFS_H
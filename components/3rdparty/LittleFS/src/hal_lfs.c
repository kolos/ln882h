#include "hal_lfs.h"
#include "hal/hal_flash.h"

uint8_t hal_lfs_read(uint32_t offset, uint32_t length, uint8_t *buffer)
{
    return hal_flash_read(offset, length, buffer);
}

uint8_t hal_lfs_program(uint32_t offset, uint32_t length, uint8_t *buffer)
{
    return hal_flash_program(offset, length, buffer);
}

void hal_lfs_erase(uint32_t offset, uint32_t length)//@param: offset,length(Note:4K Aligned)
{
    hal_flash_erase(offset, length);
}

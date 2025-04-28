#include <stdint.h>
#include "port.h"
#include "ata.h"

// ATA Ports
#define ATA_DATA 0x1F0       // Data register
#define ATA_SECTOR_COUNT 0x1F2
#define ATA_LBA_LOW 0x1F3
#define ATA_LBA_MID 0x1F4
#define ATA_LBA_HIGH 0x1F5
#define ATA_DRIVE_SELECT 0x1F6
#define ATA_COMMAND 0x1F7
#define ATA_STATUS 0x1F7
#define ATA_ALT_STATUS 0x3F6
#define ATA_CONTROL 0x3F6

// ATA Commands
#define ATA_CMD_READ  0x20
#define ATA_CMD_WRITE 0x30

// ATA Status Flags
#define ATA_STATUS_ERR  0x01
#define ATA_STATUS_DRQ  0x08
#define ATA_STATUS_SRV  0x10
#define ATA_STATUS_DF   0x20
#define ATA_STATUS_RDY  0x40
#define ATA_STATUS_BSY  0x80

// Helper: Wait for the drive to be ready
static void ata_wait_ready() {
    while (port_byte_in(ATA_STATUS) & ATA_STATUS_BSY); // Wait for BSY to clear
}

// Low-level I/O functions
void ata_read_sector(uint32_t lba, void *buffer) {
    ata_wait_ready();

    port_byte_out(ATA_DRIVE_SELECT, 0xE0 | ((lba >> 24) & 0x0F)); // Select drive and LBA bits 24-27
    port_byte_out(ATA_SECTOR_COUNT, 1);                           // Read one sector
    port_byte_out(ATA_LBA_LOW, lba & 0xFF);                       // LBA bits 0-7
    port_byte_out(ATA_LBA_MID, (lba >> 8) & 0xFF);                // LBA bits 8-15
    port_byte_out(ATA_LBA_HIGH, (lba >> 16) & 0xFF);              // LBA bits 16-23
    port_byte_out(ATA_COMMAND, ATA_CMD_READ);                     // Send read command

    ata_wait_ready();
    while (!(port_byte_in(ATA_STATUS) & ATA_STATUS_DRQ));         // Wait for DRQ (data request)

    // Read 256 words (512 bytes) from the data port
    for (int i = 0; i < 256; i++) {
        ((uint16_t *)buffer)[i] = port_word_in(ATA_DATA);
    }
}

void ata_write_sector(uint32_t lba, const void *buffer) {
    ata_wait_ready();

    port_byte_out(ATA_DRIVE_SELECT, 0xE0 | ((lba >> 24) & 0x0F));  // Select drive and LBA bits 24-27
    port_byte_out(ATA_SECTOR_COUNT, 1);                           // Write one sector
    port_byte_out(ATA_LBA_LOW, lba & 0xFF);                       // LBA bits 0-7
    port_byte_out(ATA_LBA_MID, (lba >> 8) & 0xFF);                // LBA bits 8-15
    port_byte_out(ATA_LBA_HIGH, (lba >> 16) & 0xFF);              // LBA bits 16-23
    port_byte_out(ATA_COMMAND, ATA_CMD_WRITE);                    // Send write command

    ata_wait_ready();
    while (!(port_byte_in(ATA_STATUS) & ATA_STATUS_DRQ));         // Wait for DRQ (data request)

    // Write 256 words (512 bytes) to the data port
    for (int i = 0; i < 256; i++) {
        port_word_out(ATA_DATA, ((uint16_t *)buffer)[i]);
    }

    ata_wait_ready();
}
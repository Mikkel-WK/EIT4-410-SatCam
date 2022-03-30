#include <configs/zynq-common.h>
/*Required for uartless designs */
#ifndef CONFIG_BAUDRATE
#define CONFIG_BAUDRATE 115200
#ifdef CONFIG_DEBUG_UART
#undef CONFIG_DEBUG_UART
#endif
#endif

/*Dependencies for ENV to be stored in EEPROM. Ensure environment fits in eeprom size*/
#ifdef CONFIG_ENV_IS_IN_EEPROM
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN         1
#define CONFIG_SYS_I2C_EEPROM_ADDR             0x54
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS      4
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS  5
#define CONFIG_SYS_EEPROM_SIZE                 1024 /* Bytes */
#define CONFIG_SYS_I2C_MUX_ADDR                0x74
#define CONFIG_SYS_I2C_MUX_EEPROM_SEL          0x4
#endif

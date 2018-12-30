#ifndef CONSTANTS_H
#define CONSTANTS_H

//Chip select for SD
#define CHIP_SELECT 4
//Size buffer for ArduinoJSON
#define BUFFER_JSON 290
//Default message when serial receives some data without terminator.
#define DEFAULT_MESSAGE_TIMEOUT "ERR:MAX_TIMEOUT_REACH"
//Default delimiter request to split command and value.
#define DELIMITER ':'
//Max log file's size. When this size is reached, automatically log file will be removed and recreated.
#define MAX_SIZE_LOG 7000000000
//Files' name.
#define CONFIG_FILE "CONFIG.TXT"
#define LOG_FILE "LOG.TXT"
//If SYSERR shows, set how many times message will be print before reset.
#define COUNT_RESET 10
#define MAX_LINE_SIZE 255

#define COMMAND_START "START:OK"
#define COMMAND_RESET "RESET:OK"

#define SYSERR_FILE_NOT_FOUND "FILE_NOT_FOUND"
#define SYSERR_JSON_PARSE_FAILED "JSON_PARSE_FAILED"
#define SYSERR_BEGIN_SD_FAILED "BEGIN_SD_FAILED"
#define SYSERR_UNKNOWN "UNKNOWN"

#define PREFIX_GET "GET"
#define PREFIX_ACK "ACK"
#define PREFIX_LOG "LOG"

#define PREFIX_RESPONSE_OK "OK"
#define PREFIX_RESPONSE_ERR "ERR"

#define RESULT_KEY_NOT_FOUND "KEY_NOT_FOUND"
#define RESULT_IMPOSSIBLE_WRITE "IMPOSSIBLE_WRITE"
#define RESULT_WRITTEN "WRITTEN"
#define RESULT_BAD_REQUEST "BAD_REQUEST"

#endif

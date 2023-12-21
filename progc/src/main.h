#ifndef HEADER_MAIN
#define HEADER_MAIN

// max size for a name in the data
#define LINE_LENGTH 100
#define TOWN_NAME_LENGTH 50
#define DRIVER_NAME_LENGTH 50

// error code, labelized
typedef enum ErrorCode {
    CODE_OK,
    CODE_ARG_NULL,
    CODE_ARG_INVALID,
    CODE_FILE_OPEN_ERROR,
    CODE_FILE_READ_ERROR,
    CODE_FILE_CREATE_ERROR,
    CODE_FILE_WRITE_ERROR,
    CODE_FAILED_FUNCTION,

    CORE_UNKNOWN_ERROR
} ErrorCode;

#endif
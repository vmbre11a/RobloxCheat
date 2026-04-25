#pragma once

#include <ntifs.h>

#define log( msg , ... )				DbgPrintEx ( DPFLTR_IHVDRIVER_ID , DPFLTR_ERROR_LEVEL , msg , ##__VA_ARGS__)




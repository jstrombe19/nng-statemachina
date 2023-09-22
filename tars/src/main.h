#ifndef MAIN
#define MAIN

#include <stdlib.h>
#include <stdio.h>

#include "sub1.h"
#include "sub2.h"


struct tars_state {
    uint8_t app1_request_flag;
    long app1_last_heartbeat_timestamp;
    long app1_uptime;
    long app1_start_time;
    uint8_t app1_current_state;
};



#endif
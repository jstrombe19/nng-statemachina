#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

#include "main.h"

#define DATE "DATE"
#define UPTIME "UPTIME"
#define STATE "STATE"

void fatal (const char *function, int return_value) {
    fprintf(stderr, "%s: %s\n", function, nng_strerror(return_value));
    exit(1);
}

int app1_reqrep_nng_node(const char *url, int request_type) {
    nng_socket sock;
    int return_value;
    size_t buffer_size;
    char *buffer = NULL;

    if ((return_value = nng_req0_open(&sock)) != 0) {
        fatal("nng_socket", return_value);
    }
    if ((return_value = nng_dial(sock, url, NULL, 0)) != 0) {
        fatal("nng_dial", return_value);
    }

    switch (request_type)
    {
    case 0:
        printf("TARS: SENDING DATE REQUEST to APP1 %s\n", DATE);
        if ((return_value = nng_send(sock, DATE, strlen(DATE) + 1, 0)) != 0) {
            fatal("nng_send", return_value);
        }
        if ((return_value = nng_recv(sock, &buffer, &buffer_size, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", return_value);
        }

        printf("TARS: RECEIVED DATE %s\n", buffer);
        nng_free(buffer, buffer_size);
        nng_close(sock);
        
        break;
    
    case 1:
        printf("TARS: SENDING UPTIME REQUEST to APP1 %s\n", UPTIME);
        if ((return_value = nng_send(sock, UPTIME, strlen(UPTIME) + 1, 0)) != 0) {
            fatal("nng_send", return_value);
        }
        if ((return_value = nng_recv(sock, &buffer, &buffer_size, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", return_value);
        }

        printf("TARS: RECEIVED UPTIME %s\n", buffer);
        nng_free(buffer, buffer_size);
        nng_close(sock);
        
        break;

    case 2:
        printf("TARS: SENDING CURRENT STATE REQUEST TO APP1 %s\n", STATE);
        if ((return_value = nng_send(sock, STATE, strlen(STATE) + 1, 0)) != 0) {
            fatal("nng_send", return_value);
        }
        if ((return_value = nng_recv(sock, &buffer, &buffer_size, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", return_value);
        }

        printf("TARS: RECEIVED APP1 STATE %s\n", buffer);
        // TODO: UPDATE TARS STATE MACHINE HERE WITH APP1 CURRENT STATE
        nng_free(buffer, buffer_size);
        nng_close(sock);

        break;

    default:
        printf("TARS: INVALID REQUEST TYPE");
        break;
    }

    return 0;
}


int main (void) {
    printf("Hello, world from main!\n");

    char *s = (void *)malloc(100);

    sub1();
    sub2();

    // app1__reqrep_nng_node("ipc:///tmp/reqrep.ipc");
    app1_reqrep_nng_node("tcp://127.0.0.1:4001", 0);
    return 0;
}


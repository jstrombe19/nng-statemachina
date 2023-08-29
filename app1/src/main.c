#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

#include "main.h"

#define DATE "DATE"


void fatal (const char *function, int return_value) {
    fprintf(stderr, "%s: %d\n", function, return_value);
    exit(1);
}

char* date (void) {
    time_t now = time(&now);
    struct tm *info = localtime(&now);
    char *text = asctime(info);
    text[strlen(text) - 1] = '\0';  // remove '\n'
    return text;
}

int tars_reqrep_nng_node (const char *url) {
    nng_socket sock;
    int return_value;
    
    if ((return_value = nng_rep0_open(&sock)) != 0) {
        fatal("nng_rep0_open", return_value);
    }

    if ((return_value = nng_listen(sock, url, NULL, 0)) != 0) {
        fatal("nng_listen", return_value);
    }

    for (;;) {
        char *buffer = NULL;
        size_t buffer_size;
        if ((return_value = nng_recv(sock, &buffer, &buffer_size, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", return_value);
        }
        if ((buffer_size == (strlen(DATE) + 1)) && (strcmp(DATE, buffer) == 0)) {
            printf("APP1: RECEIVED DATE REQUEST FROM TARS\n");
            char *current_date = date();
            printf("APP1: SENDING DATE TO TARS %s\n", current_date);
            if ((return_value = nng_send(sock, current_date, strlen(current_date) + 1, 0)) != 0) {
                fatal("nng_send", return_value);
            }
        }
        nng_free(buffer, buffer_size);
    }
}

int main (void) {
    printf("Hello, world from app1 main!\n");

    // tars_reqrep_nng_node("ipc:///tmp/reqrep.ipc");
    tars_reqrep_nng_node("tcp://127.0.0.1:4001");

    return 0;
}


#include "../inc/server.h"

static int sd = 0;
static struct addrinfo *hostinfo = NULL;

void daemon_end(int sig) {
    close(sd);
    syslog(LOG_INFO, "daemon ended");
    closelog();
    freeaddrinfo(hostinfo);
    pthread_exit(NULL);
}

void set_signals(void) {
    struct sigaction act;
    act.sa_handler = daemon_end;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;

    if (sigaction(SIGTERM, &act, NULL) == -1) {
        syslog(LOG_ERR, "sigaction: %s", strerror(errno));
        daemon_end(-1);
    }
}

void daemon_start(void) {
    if (daemon(0, 0) == -1) {
        fprintf(stderr, "daemon: %s\n", strerror(errno));
        exit(-1);
    }

    openlog("mangodaemon", LOG_PID, LOG_LOCAL0);
    syslog(LOG_INFO, "daemon started");
}

void *client_handler(void *arg) {
    int *cd = arg;
    syslog(LOG_INFO, "AAAAAAAA, client %d", *cd);
    close(*cd);
    free(cd);
    pthread_exit(NULL);
}

void server_start(const char *node, const char *service) {
    // Get host info
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int gai_errno = getaddrinfo(node, service, &hints, &hostinfo);
    if (gai_errno) {
        syslog(LOG_ERR, "getaddrinfo: %s", gai_strerror(gai_errno));
        daemon_end(-1);
    }

    // Create socket
    if ((sd = socket(hostinfo->ai_family, hostinfo->ai_socktype, 0)) == -1) {
        syslog(LOG_ERR, "socket: %s", strerror(errno));
        daemon_end(-1);
    }

    // Bind
    if (bind(sd, hostinfo->ai_addr, hostinfo->ai_addrlen) == -1) {
        syslog(LOG_ERR, "bind: %s", strerror(errno));
        daemon_end(-1);
    }

    freeaddrinfo(hostinfo->ai_next);

    // Listen
    if (listen(sd, CLIENT_QUEUE_SIZE) == -1) {
        syslog(LOG_ERR, "listen: %s", strerror(errno));
        daemon_end(-1);
    }

    // Log
    syslog(LOG_INFO, "server node %s is listening on port %s", node, service);

    // Main loop
    while (1) {
        int ad = accept(sd, hostinfo->ai_addr, &hostinfo->ai_addrlen);
        if (ad == -1) {
            continue;
        }

        int *cd = malloc(sizeof(int));
        if (cd == NULL) {
            close(ad);
            syslog(LOG_ERR, "malloc: %s", strerror(errno));
            continue;
        }
        *cd = ad;

        pthread_t tid;
        int pthread_errno = pthread_create(&tid, NULL, client_handler, cd);
        if (pthread_errno == -1) {
            close(*cd);
            free(cd);
            syslog(LOG_ERR, "pthread_create: %s", strerror(pthread_errno));
        }
    }
}
 
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: ./server [node] [service]\n");
        exit(-1);
    }

    const char *node = argv[1];
    const char *service = argv[2];

    daemon_start();
    set_signals();
    server_start(node, service);

    return 0;
}

static int              connect_socket(t_zappy_communicator *this,
                                       t_communicator *communicator)
{
#ifndef __WIN32
    if ((communicator->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
#else
    if ((communicator->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
#endif
    {
        free(communicator);
        if (this != NULL)
            this->last_return_value = CANTOPENSOCKET;
        return (0);
    }
    return (1);
}

static int              connect_conf(t_zappy_communicator *this,
                                     t_communicator *communicator)
{
    memset(&communicator->socket_conf, 0, sizeof(sockaddr_in));
    communicator->socket_conf.sin_family = AF_INET;
    communicator->socket_conf.sin_port = htons(communicator->port);
    communicator->socket_conf.sin_addr.s_addr = inet_addr(communicator->ip);
    if (connect(communicator->socket,
                (const struct sockaddr *) &communicator->socket_conf,
                sizeof(struct sockaddr_in)) < 0) {
#ifndef __WIN32
        close(communicator->socket);
#endif
        free(communicator);
        if (this != NULL)
            this->last_return_value = CANTCONNECTTOHOST;
        return (0);
    }
    return (1);
}

static int              connect_fdopen(t_zappy_communicator *this,
                                       t_communicator *communicator)
{
#ifndef __WIN32
    if ((communicator->fsocket = fdopen(communicator->socket, "rb+")) == NULL)
    {
        close(communicator->socket);
        free(communicator);
        if (this != NULL)
            this->last_return_value = CANTCONVERTSOCKETTOFILE;
        return (0);
    }
#else
    communicator->fsocket = NULL;
#endif
    return (1);
}

static t_communicator   *connect_to_server(t_zappy_communicator *this,
                                           const char *host,
                                           uint16_t port)
{
    t_communicator      *com;
    int                 ipv4[4];
    struct in_addr      **addresses;

    if (init_communicator(&com, port, host) == NULL)
        return (NULL);
    if (!get_ipv4(host, ipv4))
    {
        if (!connect_get_ip_hostname(com, &addresses, host))
            return (connect_no_such_hostname(this, com), NULL);
        fprintf(stderr, "%s\n", strcpy(com->ip, inet_ntoa((*addresses)[0])));
    }
    else
        connect_apply_ip(com, host);
    if (!connect_socket(this, com) || !connect_conf(this, com) ||
        !connect_fdopen(this, com))
        return (NULL);
    if (this != NULL)
        this->communicator = com;
    com->status = 1;
    return (com);
}

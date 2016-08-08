static char         *zappy_recv(t_zappy_communicator *this)
{
    t_communicator  *communicator;
    fd_set          readfds;
    struct timeval  timeout;
    int             nbfds;
    char            *b;
    ssize_t         len;

    if (this == NULL || (timeout.tv_sec = 0) || !(timeout.tv_usec = 100))
        return (NULL);
    if ((communicator = this->communicator) == NULL)
        return (this->last_return_value = NOCOMMUNICATOR, NULL);
    if (!communicator->status)
        return (this->last_return_value = NOTCONNECTED, NULL);
    FD_ZERO(&readfds);
    FD_SET(communicator->socket, &readfds);
    if ((nbfds = select(communicator->socket + 1, &readfds, NULL, NULL,
                        &timeout)) > 0)
    {
        if ((b = malloc(4096)) == NULL)
            return (this->last_return_value = MEMFAILED, NULL);
        if ((len = recv(communicator->socket, b, 4095, 0)) <= 0)
            return (this->last_return_value = READERROR, free(b), NULL);
        return (b[len] = '\0', this->last_return_value = READSUCCESS, b);
    }
    return (this->last_return_value = NOTHINGTOREAD, NULL);
}

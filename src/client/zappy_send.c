static void         zappy_send_write(t_communicator *communicator,
                                     va_list *args,
                                     const char *format,
                                     ssize_t *val)
{
    va_list         transfer;
#ifdef __WIN32
    static char     *buffer = NULL;
    int             len;
#endif

    va_copy(transfer, *args);
#ifndef __WIN32
    *val = vfprintf(communicator->fsocket, format, transfer);
    fflush(communicator->fsocket);
#else
    if (buffer == NULL && (buffer = malloc(1000)) == NULL)
    {
        *val = 0;
        return;
    }
    len = vsnprintf(buffer, 1000, format, transfer);
    *val = send(communicator->socket, buffer, len, 0);
#endif
    va_end(*args);
}

static size_t       zappy_send(t_zappy_communicator *this, const char *format, ...)
{
    t_communicator  *communicator;
    va_list         args;
    ssize_t         val;

    va_start(args, format);
    communicator = (this == NULL) ? va_arg(args, void *) : this->communicator;
    if (communicator == NULL)
    {
        va_end(args);
        if (this != NULL)
            this->last_return_value = NOCOMMUNICATOR;
        return (0);
    }
    zappy_send_write(communicator, &args, format, &val);
    if (val < 0)
    {
        close(communicator->socket);
        if (this != NULL)
            this->last_return_value = CANTWRITEONSOCKET;
        return (0);
    }
    return (val);
}

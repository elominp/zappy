static void           disconnect_from_server(t_zappy_communicator *this, ...)
{
    t_communicator      *communicator;
    va_list             args;

    if (this == NULL)
    {
        va_start(args, this);
        communicator = va_arg(args, void *);
        va_end(args);
    }
    else
        communicator = this->communicator;
    if (communicator == NULL)
    {
        if (this != NULL)
            this->last_return_value = NOCOMMUNICATOR;
        return;
    }
#ifndef __WIN32
    fflush(communicator->fsocket);
    close(communicator->socket);
    fclose(communicator->fsocket);
#endif
    communicator->status = 0;
    return;
}
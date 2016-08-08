static int                  gnl_check_com(t_zappy_communicator *this)
{
    if (this->communicator == NULL)
    {
        this->last_return_value = NOCOMMUNICATOR;
        return (0);
    }
    return (1);
}

static int                  gnl_get_ndata(t_zappy_communicator *this,
                                          char **buf)
{
    char                    *nbuf;

    if ((nbuf = malloc(strlen(this->buffer) + strlen(*buf) + 1)) == NULL)
        return (this->last_return_value = MEMFAILED, free(*buf), 0);
    strcpy(nbuf, this->buffer);
    strcat(nbuf, *buf);
    free(this->buffer);
    free(*buf);
    this->buffer = nbuf;
    return (1);
}

static int                  gnl_get_data(t_zappy_communicator *this,
                                         char **buf)
{
    *buf = this->recv(this);
    if (*buf != NULL)
    {
        if (this->buffer == NULL || (this->buffer && this->buffer[0] == '\0'))
            this->buffer = *buf;
        else if (this->buffer && this->buffer[0] == '\0')
        {
            free(this->buffer);
            this->buffer = *buf;
        }
        else
        {
            if (!gnl_get_ndata(this, buf))
                return (0);
        }
    }
    else if (this->last_return_value == NOTCONNECTED ||
             this->last_return_value == READERROR)
        this->disconnect(this);
    return (1);
}

static char                 *gnl_line_extracted(t_zappy_communicator *this,
                                                char *buffer)
{
    size_t                  buffer_len;
    size_t                  line_len;

    buffer_len = strlen(this->buffer);
    buffer = malloc(buffer_len + 1);
    if (sscanf(this->buffer, "%[^\n]\n", buffer) > 0)
    {
        line_len = strlen(buffer) + 1;
        if (line_len < buffer_len)
            memmove(this->buffer, this->buffer + line_len, buffer_len - line_len + 1);
        if (line_len == buffer_len || this->buffer[0] == '\0')
        {
            free(this->buffer);
            this->buffer = NULL;
        }
        this->last_return_value = LINEEXTRACTED;
        return (buffer);
    }
    return (NULL);
}

static char                 *zappy_getnextline(t_zappy_communicator *this)
{
    char                    *buffer;
    char                    *res;

    if (this == NULL || !gnl_check_com(this))
        return (NULL);
    if (this->communicator->status && gnl_get_data(this, &buffer))
    if (this->buffer && (this->communicator == NULL ||
                         (this->communicator && !this->communicator->status)))
    {
        buffer = this->buffer;
        this->buffer = NULL;
        return (buffer);
    }
    if (this->buffer && (res = gnl_line_extracted(this, buffer)) != NULL)
        return (res);
    this->last_return_value = NOLINETOEXTRACT;
    return (NULL);
}
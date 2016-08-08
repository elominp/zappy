static void        *init_communicator(t_communicator **communicator,
                                      uint16_t port,
                                      const char *host)
{
    if (host == NULL ||
        (*communicator = malloc(sizeof(**communicator))) == NULL)
        return (NULL);
    memset(*communicator, 0, sizeof(**communicator));
    (*communicator)->port = port;
    (*communicator)->host = strdup(host);
    (*communicator)->status = 0;
    return (*communicator);
}

static int              get_ipv4(const char *host, int *ipv4)
{
    if (sscanf(host, "%d.%d.%d.%d", &ipv4[0], &ipv4[1], &ipv4[2],
               &ipv4[3]) != 4 ||
        ipv4[0] < 0 || ipv4[0] > 255 || ipv4[1] < 0 || ipv4[1] > 255 ||
        ipv4[2] < 0 || ipv4[2] > 255 || ipv4[3] < 0 || ipv4[3] > 255)
        return (0);
    return (1);
}

static void             connect_no_such_hostname(t_zappy_communicator *this,
                                                 t_communicator *communicator)
{
    free(communicator);
    if (this != NULL)
        this->last_return_value = NOSUCHHOSTNAME;
}

static int              connect_get_ip_hostname(t_communicator *com,
                                                struct in_addr ***addresses,
                                                const char *host)
{
    if ((com->hostent_ptr = gethostbyname(host)) == NULL ||
        (*addresses = (struct in_addr **)com->hostent_ptr->h_addr_list) == NULL ||
        (*addresses)[0] == NULL)
        return (0);
    return (1);
}

static void             connect_apply_ip(t_communicator *communicator,
                                         const char *host)
{
    strcpy(communicator->ip, host);
    communicator->hostent_ptr = NULL;
}

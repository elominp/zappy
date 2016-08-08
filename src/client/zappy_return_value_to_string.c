static const char *str_errors_return_values[] =
        {
                "No such hostname",
                "Can't open socket",
                "Can't connect to host",
                "Can't convert socket to file",
                "No communicator",
                "Can't write on socket",
                "Not connected to any host",
                "Memory error",
                "Read error"
        };

static const char *str_info_return_values[] =
        {
                "Read successful",
                "Nothing to read",
                "Line extracted",
                "No line to extract found"
        };

static const char           *return_value_to_string(t_zappy_communicator *this, ...)
{
    int                       return_value;
    va_list                   args;

    if (this == NULL)
    {
        va_start(args, this);
        return_value = va_arg(args, int);
        va_end(args);
    }
    else
        return_value = this->last_return_value;
    if (!return_value)
        return ("");
    return ((return_value < 0) ?
            str_errors_return_values[(return_value * -1) - 1] :
            str_info_return_values[return_value - 1]);
}
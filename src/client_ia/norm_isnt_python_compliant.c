static PyObject             *py_return_value_to_string(PyObject *self,
                                                       PyObject *args)
{
    t_zappy_communicator    *communicator;
    const char              *str;

    (void)self;
    if ((communicator = get_zappy_communicator(args)) == NULL)
        return (Py_None);
    str = communicator->return_value_to_string(communicator);
    return (Py_BuildValue("s", str));
}

static PyObject             *py_send(PyObject *self, PyObject *args)
{
    PyObject                *capsule;
    t_zappy_communicator    *communicator;
    char *str;

    (void)self;
    if (!PyArg_ParseTuple(args, "Os", &capsule, &str))
    {
        fprintf(stderr, "Can't get arguments\n");
        return (Py_INCREF(Py_False), Py_False);
    }
    if ((communicator = PyCapsule_GetPointer(capsule, CAPSULE_NAME)) == NULL)
    {
        fprintf(stderr, "Can't get communicator\n");
        return (Py_INCREF(Py_False), Py_False);
    }
    if (!communicator->send(communicator, str))
    {
        fprintf(stderr, "Data weren't fully send\n");
        return (Py_INCREF(Py_False), Py_False);
    }
    return (Py_INCREF(Py_True), Py_True);
}

static PyObject             *py_getnextline(PyObject *self, PyObject *args)
{
    t_zappy_communicator    *communicator;
    char                    *str;

    (void)self;
    if ((communicator = get_zappy_communicator(args)) == NULL)
        return (Py_BuildValue("s", ""));
    if ((str = communicator->getnextline(communicator)) == NULL)
        return (Py_BuildValue("s", ""));
    return (Py_BuildValue("s", str));
}

static PyObject             *py_status(PyObject *self, PyObject *args)
{
    t_zappy_communicator    *communicator;

    (void)self;
    if ((communicator = get_zappy_communicator(args)) == NULL)
        return (Py_INCREF(Py_False), Py_False);
    if (communicator->communicator == NULL || !communicator->communicator->status)
        return (Py_INCREF(Py_False), Py_False);
    return (Py_INCREF(Py_True), Py_True);
}


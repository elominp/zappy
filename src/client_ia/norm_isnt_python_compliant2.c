static t_zappy_communicator *get_zappy_communicator(PyObject *args)
{
    PyObject                *capsule;
    t_zappy_communicator    *communicator;

    if (!PyArg_ParseTuple(args, "O", &capsule))
    {
        fprintf(stderr, "Can't get capsule\n");
        return (NULL);
    }
    if ((communicator = PyCapsule_GetPointer(capsule, CAPSULE_NAME)) != NULL)
        return (communicator);
    fprintf(stderr, "Can't get communicator\n");
    return (NULL);
}

static PyObject             *py_create_zappy_communicator(PyObject *self,
                                                          PyObject *args)
{
    t_zappy_communicator    *communicator;
    PyObject                *capsule;

    (void)self;
    (void)args;
    communicator = create_zappy_communicator();
    if ((capsule = PyCapsule_New(communicator, CAPSULE_NAME, NULL)) == NULL)
    {
        fprintf(stderr, "Can't encapsulate communicator\n");
        return (Py_None);
    }
    return (Py_BuildValue("O", capsule));
}

static PyObject             *py_delete_zappy_communicator(PyObject *self,
                                                          PyObject *args)
{
    t_zappy_communicator    *communicator;

    (void)self;
    if ((communicator = get_zappy_communicator(args)) != NULL)
        delete(communicator);
    return (Py_None);
}

static PyObject             *py_connect(PyObject *self, PyObject *args)
{
    PyObject                *capsule;
    t_zappy_communicator    *communicator;
    char                    *host;
    unsigned int            port;

    (void)self;
    if (!PyArg_ParseTuple(args, "Osi", &capsule, &host, &port))
    {
        fprintf(stderr, "Can't get arguments\n");
        return (Py_None);
    }
    if ((communicator = PyCapsule_GetPointer(capsule, CAPSULE_NAME)) == NULL)
    {
        fprintf(stderr, "Can't get communicator\n");
        return (Py_INCREF(Py_False), Py_False);
    }
    if (communicator->connect(communicator, host, port) == NULL)
    {
        fprintf(stderr, "Can't connect to host\n");
        return (Py_INCREF(Py_False), Py_False);
    }
    return (Py_INCREF(Py_True), Py_True);
}

static PyObject             *py_disconnect(PyObject *self, PyObject *args)
{
    t_zappy_communicator    *communicator;

    (void)self;
    if ((communicator = get_zappy_communicator(args)) != NULL)
        communicator->disconnect(communicator);
    return (Py_None);
}
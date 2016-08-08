#include <python2.7/Python.h>
#include "zappy_communicator.h"
#include "norm_isnt_python_compliant2.c"
#include "norm_isnt_python_compliant.c"

static PyMethodDef zappy_methods[] =
{
    {
        "createZappyCommunicator",
        py_create_zappy_communicator,
        METH_VARARGS | METH_NOARGS,
        "Instanciate C Zappy Communicator object."
    },
    {
        "deleteZappyCommunicator",
        py_delete_zappy_communicator,
        METH_VARARGS,
        "Destructor for C Zappy Communicators objects"
    },
    {
        "connectZappy",
        py_connect,
        METH_VARARGS,
        "Connect Zappy Communicator to host"
    },
    {
       "disconnectZappy",
        py_disconnect,
        METH_VARARGS,
        "Disconnect Zappy Communicator from host"
    },
    {
        "returnValueToString",
        py_return_value_to_string,
        METH_VARARGS,
        "Convert numeric return value from last call to human readable string"
    },
    {
        "sendToHost",
        py_send,
        METH_VARARGS,
        "Send string to host"
    },
    {
        "getNextLine",
        py_getnextline,
        METH_VARARGS,
        "Extract next line"
    },
    {
        "statusZappy",
        py_status,
        METH_VARARGS,
        "Return if the communicator is connected to an host"
    },
    {
        NULL,
        NULL,
        0,
        NULL
    }
};

PyMODINIT_FUNC  initzappy_communicator(void)
{
    PyObject    *m;

    m = Py_InitModule("zappy_communicator", zappy_methods);
    if (m == NULL)
        fprintf(stderr, "Unable to init zappy communicator module");
}

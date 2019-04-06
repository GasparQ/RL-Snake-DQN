#include <cmath>
# define _hypot hypot
#include <Python.h>
#include "widget.h"
#include <QApplication>

static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    return Py_None;
}

static PyMethodDef SpamMethods[] = {
    {"system",  spam_system, METH_O,
     "Execute a shell command."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam",   /* name of module */
    "", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void)
{
    return PyModule_Create(&spammodule);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeWidget w;

    w.init();

    w.show();

    return a.exec();
}

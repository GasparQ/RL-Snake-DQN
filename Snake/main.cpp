#include <cmath>
# define _hypot hypot
#include <Python.h>
#include <QDebug>
#include "widget.h"
#include <QApplication>

static PyObject *step(PyObject *self, PyObject *args)
{
    qDebug() << "HELLO";
    return Py_None;
}

static PyObject *make(PyObject *self, PyObject *args)
{
    qDebug() << "HELLO";
    return Py_None;
}

static PyObject *reset(PyObject *self, PyObject *args)
{
    qDebug() << "HELLO";
    return Py_None;
}

static PyMethodDef SpamMethods[] = {
    {"step",  step, METH_O, "Execute a shell command."},
    {"reset",  reset, METH_NOARGS, "Execute a shell command."},
    {"make",  make, METH_O, "Execute a shell command."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "pySnake",   /* name of module */
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

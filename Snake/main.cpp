#include <cmath>
# define _hypot hypot
#include <Python.h>
#include <QDebug>
#include <windows.h>
#include <iostream>
#include "widget.h"
#include <QApplication>
#include <QSemaphore>

QSemaphore g_sem;
SnakeWidget *w = nullptr;

DWORD WINAPI myThread(LPVOID lpParameter)
{
    int argc =0;
    char **argv = NULL;
    QApplication a(argc, argv);

    w = new SnakeWidget();


    w->show();

    g_sem.release(1);

    return a.exec();
}

PyObject *createEnv() {
    std::vector<SnakeGame::CellType> const &cells = w->getObservation();
    auto it =cells.begin();
    auto end = cells.end();

    PyObject *list = PyList_New(0);

    while (it != end) {
        PyList_Append(list, PyFloat_FromDouble((*it)));
        ++it;
    }
    return list;
}


static PyObject *step(PyObject *self, PyObject *args)
{
    double action = PyFloat_AsDouble(args);
    SnakeWidget::Action actionConv = SnakeWidget::NONE;
    if (action == 0)
        actionConv = SnakeWidget::NONE;
    else if (action == 1)
        actionConv = SnakeWidget::UP;
    else if (action == 2)
        actionConv = SnakeWidget::DOWN;
    else if (action == 3)
        actionConv = SnakeWidget::RIGHT;
    else if (action == 4)
        actionConv = SnakeWidget::LEFT;



    w->step(actionConv);

    PyObject *list = PyList_New(0);
    PyList_Append(list, createEnv());
    PyList_Append(list, PyFloat_FromDouble(0));
    PyList_Append(list, PyBool_FromLong(w->isSnakeGameOver() == true ? 1 : 0));
    return list;
}

static PyObject *make(PyObject *self, PyObject *args)
{
    CreateThread(0, 0, myThread,NULL, 0, NULL);
    g_sem.acquire(1);
    return Py_None;
}

static PyObject *reset(PyObject *self, PyObject *args)
{
    w->init();
    return createEnv();
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
PyInit_pySnake(void)
{
    return PyModule_Create(&spammodule);
}

//int main(int argc, char *argv[])
//{

//}

//
// Copyright 2015 riteme
//

#include <python2.7/Python.h>  // Run python
#include <iostream>
#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include "./share.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv) {
    cout.sync_with_stdio(false);  // do not sync with c stdio.`

    Py_Initialize();

    // make sure python has inited.
    if (!Py_IsInitialized()) {
        cout << "ERROR: Cannot initialize Python." << endl;
        return EXIT_FAILURE;
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    PyObject *mod, *func_hello_world, *func_ask;
    mod = func_hello_world = func_ask = nullptr;

    // load module.
    mod = PyImport_ImportModule("a");
    if (mod == nullptr) {
        cout << "ERROR: Cannot load the module 'a'." << endl;
        return EXIT_FAILURE;
    }

    // find function hello_world.
    func_hello_world =
                PyObject_GetAttrString(mod, "hello_world");
    if (func_hello_world == nullptr) {
        cout << "ERROR: Cannot find function 'hello_world'."
             << endl;
        return EXIT_FAILURE;
    }

    // find function ask.
    func_ask = PyObject_GetAttrString(mod, "ask");
    if (func_ask == nullptr) {
        cout << "ERROR: Cannot find function 'ask'."
             << endl;
    }

    // call hello_world.
    PyEval_CallObject(func_hello_world, nullptr);

    // call ask.
    PyObject *args = PyTuple_New(1);
    PyObject *ret = nullptr;
    char *result = nullptr;
    PyTuple_SetItem(args, 0,
                    Py_BuildValue("s", "What's your name?"));
    ret = PyEval_CallObject(func_ask, args);
    result = PyString_AsString(ret);
    cout << "Your name is " << result << "." << endl;

    // share a lib.
    set(2);  // set a is 2.
    PyObject *pysetfunc = nullptr;
    pysetfunc = PyObject_GetAttrString(mod, "set_a");
    if (pysetfunc == nullptr) {
        cout << "ERROR: Cannot find function 'set_a'."
             << endl;
        return EXIT_FAILURE;
    }
    PyObject *setargs = PyTuple_New(1);
    PyTuple_SetItem(setargs, 0,
                    Py_BuildValue("i", 3));
    PyEval_CallObject(pysetfunc, setargs);

    cout << "a: " << get() << endl;

    Py_Finalize();

    return EXIT_SUCCESS;
}


/* PCAPIFY
 * A simple program to load a python script given as an argument
 * that defines the function 'process', and calls it with each
 * packet obtained from libpcap.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <Python.h>
#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>

/* Signal Handling */
void sigproc();

int main(int argc, char *argv[])
{
    signal(SIGINT, &sigproc);

    FILE *pyFile;
    PyObject *pDict, *pFunc, *main_module;
    PyObject *pArgs, *pValue;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s pythonfile device\n", argv[0]);
        return 1;
    }

    Py_Initialize();
    if(!(pyFile = fopen(argv[1], "r"))) {
      fprintf(stderr, "%s could not be opened: %s\n", argv[1], strerror(errno));
      return 1;
    }

    PyRun_SimpleFile(pyFile, argv[1]);
    // Get a reference to the main module.
    if(!(main_module = PyImport_AddModule("__main__"))) {
      fprintf(stderr, "Epic Fail.  Could not import the main module.\n");
      return 1;
    }
    
    // Get the main module's dictionary and make a copy of it.
    

    if ((pDict = PyModule_GetDict(main_module)) != NULL) {
        pFunc = PyDict_GetItemString(pDict, "process");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
          char ebuf[PCAP_ERRBUF_SIZE];
          pcap_t * pcap_handle = NULL;
          struct pcap_pkthdr pcap_header;
          if(!(pcap_handle = pcap_open_live(argv[2], 1540, 0, 0, ebuf))) {
            fprintf(stderr, "pcap_open_live failed with: %s\n", ebuf);
            return 1;
          }
          const u_char * pkt;
          while((pkt = pcap_next(pcap_handle, &pcap_header))) {
            pArgs = PyTuple_New(1);
            pValue = PyInt_FromLong(pcap_header.len); // PCAP
            if (!pValue) {
                Py_DECREF(pArgs);
                fprintf(stderr, "Cannot convert argument\n");
                return 1;
            }
            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                if(PyErr_Occurred()) PyErr_Print();
                fprintf(stderr,"Call failed\n");
                Py_DECREF(pFunc);
                return 1;
            }
          }
        }
        else {
            if (PyErr_Occurred()) PyErr_Print();
            fprintf(stderr, "Cannot find function \"process\"\n");
        }
        Py_XDECREF(pFunc);
    }
    else {
        fprintf(stderr, "Failed to load dictionary\n");
        return 1;
    }
    Py_Finalize();
    return 0;
}

void sigproc()
{   
     signal(SIGINT, sigproc);
     printf("SIGINT received: Exiting...\n");
     exit(0);
}
 


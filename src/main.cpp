#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include "client.h"
#include "server.h"

// I want to share Client and Server implementation in one repository, so there will be flags to run binary
// --server and --client
// --server have no GUI
// Client shall be run with --client flag or without any flag
int main(int const argc, char* argv[])
{
    bool is_client{true};

    // TODO consider checking this as first flag
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--server") == 0)
        {
            is_client = false;
        }
    }
    if (is_client)
    {
        run_client();
    }
    else
    {
        run_server();
    }
}

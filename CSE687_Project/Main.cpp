#include "ThreadManager.h"
#include "SocketHelper.h"

int main(void)
{
    ThreadManager lcTM;
    SocketHelper lcSocket;

    // Local vector that will contain all of the result strings
    std::vector<std::string> resultVector;

    // Thread manager is being passed in as a reference
    lcSocket.Receive(lcTM);

    //resultVector is being passed in as a reference
    resultVector = lcTM.startProcessing();

    lcSocket.Send(resultVector);

    return 0;
}
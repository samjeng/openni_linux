#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IMG_WIDTH 640
#define IMG_HEIGHT 480
#define IMG_FPS 30
#define SERVER_PORT 5566
#define CLIENT_PORT 5567
#define MAXNAME 1024
#define PKT_SIZE 51200
#define DELAY 10000

using namespace std;
using namespace xn;

int main( int argc, char* argv[] )
{
    // 1. Prepare OpenNI context and depth generator
    Context mContext;
    mContext.Init();

    XnMapOutputMode mapMode;
    mapMode.nXRes = IMG_WIDTH;
    mapMode.nYRes = IMG_HEIGHT;
    mapMode.nFPS = IMG_FPS;

    DepthGenerator mDepthGen;
    mDepthGen.Create( mContext );
    mDepthGen.SetMapOutputMode( mapMode );

    int socket_fd;
    int length;
    int nbytes;
    char buf[BUFSIZ];
    struct sockaddr_in myaddr;
    struct sockaddr_in client_addr;
    char *data1;
    char *data2;
    char *data3;
    char *data4;
    char *data5;
    char *data6;
    char *data7;
    char *data8;
    char *data9;
    char *data10;
    char *data11;
    char *data12;
   
    data1 = (char*)malloc(PKT_SIZE*sizeof(char));
    data2 = (char*)malloc(PKT_SIZE*sizeof(char));
    data3 = (char*)malloc(PKT_SIZE*sizeof(char));
    data4 = (char*)malloc(PKT_SIZE*sizeof(char));
    data5 = (char*)malloc(PKT_SIZE*sizeof(char));
    data6 = (char*)malloc(PKT_SIZE*sizeof(char));
    data7 = (char*)malloc(PKT_SIZE*sizeof(char));
    data8 = (char*)malloc(PKT_SIZE*sizeof(char));
    data9 = (char*)malloc(PKT_SIZE*sizeof(char));
    data10 = (char*)malloc(PKT_SIZE*sizeof(char));
    data11 = (char*)malloc(PKT_SIZE*sizeof(char));
    data12 = (char*)malloc(PKT_SIZE*sizeof(char));

    // 2. Prepare UDP socket 
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        cout << "socket failed" << endl;
        return 1;
    }

    // 3. Set up address
    memset(&myaddr, 0, sizeof(myaddr));
    memset(&client_addr, 0, sizeof(client_addr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(SERVER_PORT);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(socket_fd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
        cout << "bind socket failed" << endl;
        return 1;
    }

    mContext.StartGeneratingAll();

    DepthMetaData mDepthMD;

    while ( !xnOSWasKeyboardHit() )
    {
        if ((nbytes = recvfrom(socket_fd, &buf, MAXNAME, 0, (struct sockaddr*)&client_addr, (socklen_t *)&length)) < 0) {
            cout << "could not read datagram" << endl;
            continue;
        }

        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(CLIENT_PORT);
        inet_aton(argv[1], &client_addr.sin_addr);

        cout << "Received data from " << inet_ntoa(client_addr.sin_addr) << " : " << htons(client_addr.sin_port) << endl;
        cout << buf << endl;
        while ( !xnOSWasKeyboardHit() )
        {
            mContext.WaitOneUpdateAll(mDepthGen);
            mDepthGen.GetMetaData(mDepthMD);
            memcpy(data1, mDepthMD.Data(), PKT_SIZE);
            memcpy(data2, mDepthMD.Data() + PKT_SIZE/2, PKT_SIZE);
            memcpy(data3, mDepthMD.Data() + PKT_SIZE, PKT_SIZE);
            memcpy(data4, mDepthMD.Data() + PKT_SIZE + PKT_SIZE/2, PKT_SIZE);
            memcpy(data5, mDepthMD.Data() + 2 * PKT_SIZE, PKT_SIZE);
            memcpy(data6, mDepthMD.Data() + 2 * PKT_SIZE + PKT_SIZE/2, PKT_SIZE);
            memcpy(data7, mDepthMD.Data() + 3 * PKT_SIZE, PKT_SIZE);
            memcpy(data8, mDepthMD.Data() + 3 * PKT_SIZE + PKT_SIZE/2, PKT_SIZE);
            memcpy(data9, mDepthMD.Data() + 4 * PKT_SIZE, PKT_SIZE);
            memcpy(data10, mDepthMD.Data() + 4 * PKT_SIZE + PKT_SIZE/2, PKT_SIZE);
            memcpy(data11, mDepthMD.Data() + 5 * PKT_SIZE, PKT_SIZE);
            memcpy(data12, mDepthMD.Data() + 5 * PKT_SIZE + PKT_SIZE/2, PKT_SIZE);
            length = sizeof(client_addr);
            sendto( socket_fd, data1, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data2, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data3, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data4, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data5, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data6, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data7, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data8, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data9, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data10, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data11, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
            usleep(DELAY);
            sendto( socket_fd, data12, PKT_SIZE, 0, (struct sockaddr*)&client_addr, length);
        }
    }

    mContext.StopGeneratingAll();

    mContext.Release();

    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
    free(data6);
    free(data7);
    free(data8);
    free(data9);
    free(data10);
    free(data11);
    free(data12);
    return 0;
}


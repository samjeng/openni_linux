#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define IMG_WIDTH 640
#define IMG_HEIGHT 480
#define SERVER_PORT 5566
#define CLIENT_PORT 5567
#define MAX_DATA 1024
#define PKT_SIZE 51200

using namespace std;
using namespace cv;

int main( int argc, char* argv[] )
{
    int socket_fd;
    int size;
    int frame_size = IMG_WIDTH*IMG_HEIGHT*2;
    char data[MAX_DATA] = {0};
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
    char *data_all;
    data_all = (char*)malloc(IMG_WIDTH*IMG_HEIGHT*2*sizeof(char));
    struct sockaddr_in myaddr;
    struct sockaddr_in server_addr;
    struct hostent *hp;

    if ( argc < 3 ) {
        cout << "No parameter" << endl;
        return 1;
    }

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        cout << "socket failed" << endl;
        return 1;
    }

    memset(&myaddr, 0, sizeof(myaddr));
    memset(&server_addr, 0, sizeof(server_addr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(CLIENT_PORT);
    if (bind(socket_fd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
        cout << "bind socket failed" << endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    hp = gethostbyname(argv[1]);
    if (hp == 0) {
        cout << "could not obtain address" << endl;
        return 1;
    }
    memcpy(hp->h_addr_list[0], (caddr_t)&server_addr.sin_addr, hp->h_length); 
    strncpy(data, argv[2], MAX_DATA); 

    size = sizeof(server_addr);
    if (sendto(socket_fd, data, sizeof(data), 0, (struct sockaddr*)&server_addr, size) == -1) {
        cout << "sendto server error" << endl;
        return 1;
    } 
    
    while ( true )
    {
        recvfrom(socket_fd, data1, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data2, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data3, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data4, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data5, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data6, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data7, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data8, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data9, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data10, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data11, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        recvfrom(socket_fd, data12, PKT_SIZE, 0, (struct sockaddr*)&server_addr, (socklen_t *)&size);
        memcpy(data_all, data1, PKT_SIZE);
        memcpy(data_all + PKT_SIZE, data2, PKT_SIZE);
        memcpy(data_all + 2 * PKT_SIZE, data3, PKT_SIZE);
        memcpy(data_all + 3 * PKT_SIZE, data4, PKT_SIZE);
        memcpy(data_all + 4 * PKT_SIZE, data5, PKT_SIZE);
        memcpy(data_all + 5 * PKT_SIZE, data6, PKT_SIZE);
        memcpy(data_all + 6 * PKT_SIZE, data7, PKT_SIZE);
        memcpy(data_all + 7 * PKT_SIZE, data8, PKT_SIZE);
        memcpy(data_all + 8 * PKT_SIZE, data9, PKT_SIZE);
        memcpy(data_all + 9 * PKT_SIZE, data10, PKT_SIZE);
        memcpy(data_all + 10 * PKT_SIZE, data11, PKT_SIZE);
        memcpy(data_all + 11 * PKT_SIZE, data12, PKT_SIZE);
        Mat imgDepth( IMG_HEIGHT, IMG_WIDTH, CV_16UC1, ( void* )data_all );
        Mat img8bitDepth;
        imgDepth.convertTo( img8bitDepth, CV_8U, 255.0 / 5000 );
        imshow( "Depth view", img8bitDepth );

        waitKey( 1 );
    }

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
    free(data_all);
    return 0;
}

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace xn;
using namespace cv;

int main( int argc, char* argv[] )
{
    Context mContext;
    mContext.Init();

    DepthGenerator mDepthGen;
    mDepthGen.Create( mContext );

    ImageGenerator mImageGen;
    mImageGen.Create( mContext );

    mContext.StartGeneratingAll();
    while ( true )
    {
        mContext.WaitAndUpdateAll();

        DepthMetaData depthData;
        mDepthGen.GetMetaData( depthData );
        Mat imgDepth( depthData.FullYRes(), depthData.FullXRes(), CV_16UC1, ( void* )depthData.Data() );
        Mat img8bitDepth;
        imgDepth.convertTo( img8bitDepth, CV_8U, 255.0 / 5000 );
        imshow( "Depth view", img8bitDepth );

        ImageMetaData colorData;
        mImageGen.GetMetaData( colorData );
        Mat imgColor( colorData.FullYRes(), colorData.FullXRes(), CV_8UC3, ( void* )colorData.Data() );
        Mat imgBGRColor;
        cvtColor( imgColor, imgBGRColor, CV_RGB2BGR );
        imshow( "Color view", imgBGRColor );

        waitKey( 1 );
    }
    mContext.StopGeneratingAll();
    mContext.Release();
    return 0;
}

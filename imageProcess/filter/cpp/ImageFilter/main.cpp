#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>

using namespace cv;

void setGaussianKernel(Mat kernel, float sigma)
{
    int mean =kernel.rows/2;
    float sum =0;
    float midVal = 2.0f*sigma*sigma;
    for (int r=0; r<kernel.rows; r++) {
        for (int c=0; c<kernel.cols; c++) {
            float value = exp((pow(r-mean,2.0f) + pow(c-mean, 2.0f))/midVal)
                                      /(midVal*M_1_PI);
            kernel.at<float_t>(r,c) = value;
            sum += value;
        }
    }
    
    for (int r=0; r<kernel.rows; r++) {
        for (int c=0; c<kernel.cols; c++) {
            kernel.at<float_t>(r,c) /= sum;
        }
    }
}

/** @function main */
int main ( int argc, char** argv )
{
    /// Declare variables
    Mat src, dst1, dst2;
    
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    
    int c;
    
    /// Load an image
    src = imread( argv[1] );
    
    if( !src.data ) { return -1; }
    
    
    /// Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;
    /// Loop - Will filter the image with different kernel sizes each 0.5 seconds
    int ind = 1;
    while( true )
    {
        /// Press 'ESC' to exit the program
        
        /// Update kernel size for a normalized box filter
        kernel_size = 2*ind+1;
        kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/(float)(kernel_size*kernel_size);
        setGaussianKernel(kernel, ind);
        /// Apply filter
        
        filter2D(src, dst1, src.depth(), kernel, anchor, delta, BORDER_DEFAULT );
        GaussianBlur(src, dst2, Size(kernel_size, kernel_size), ind);
        
        imshow( "filter2D Demo 2", dst2 );
        imshow("filter2D Demo 1", dst1);
        c = waitKey(0);
        
        if((char)c == 27 ) { break; }
        
        kernel.release();
        dst1.release();
        dst2.release();
        ind++;
    }
    
    return 0;
}
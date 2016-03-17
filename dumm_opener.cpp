/*
 * function that opens .dumm files from the chlorophyll fluorescence camera in TrayScan
 * 
 * input: path to image (char *)
 * output: Mat in CV_16U
 *
 * Author: Alexander Ivakov
 * Email: alexander.ivakov@anu.edu.au
 */

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>
#include <bitset>

using namespace cv;
using namespace std;

Mat dumm_opener(char * imgpath) {

FILE * f = fopen(imgpath,"rb");
if ( ! f )
{
    printf("bad path : %s\n",imgpath);
    throw 0;
}
int dims[4];
fread(dims,4,4,f);

short int pixels[dims[0]*dims[1]];
short int buf;

fread(pixels,dims[3],dims[0]*dims[1],f);
fclose(f);

Mat img;
img = Mat(Size(dims[0], dims[1]), CV_16U,pixels);

    if (img.empty()) 
     {
          cout << "Image cannot be loaded..!!" << endl;
          
          throw 0;
     }
     
Mat img2;
img.convertTo(img2, CV_16U, 2^(16-dims[2]));
/*
     namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"            /* Optional code to display the image
     imshow("MyWindow", img); //display the image which is stored in the 'img' in the "MyWindow" window

     waitKey(0); //wait infinite time for a keypress

     destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
*/
    return img2;
}

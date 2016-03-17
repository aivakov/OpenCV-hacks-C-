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
    //create a gui window:
    
    //Mat img = imread("C:/15.dumm", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'

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

    if (img.empty()) //check whether the image is loaded or not
     {
          cout << "Error : Image cannot be loaded..!!" << endl;
          //system("pause"); //wait for a key press
          throw 0;
     }
     
Mat img2;
img.convertTo(img2, CV_16U, 2^(16-dims[2]));
/*
     namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
     imshow("MyWindow", img); //display the image which is stored in the 'img' in the "MyWindow" window

     waitKey(0); //wait infinite time for a keypress

     destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
*/
    return img2;
}

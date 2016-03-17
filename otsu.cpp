/*
 * Thresholding using the Otsu two-class method in OpenCV is currently only implemented for 8-bit images (in the threshold() function)
 * 
 * This is a function that does Otsu thresholding on 16-bit or higher bit-depth images (single channel)
 * Iterates through all pixel intensity values between the minimum and maximum in the image and finds the value the minimises the intra-class variance
 * 
 * Takes a single channel image (Mat)
 * Returns the Otsu threshold value (int)
 * Use this value with the threshold()function to get your binary mask
 * 
 * Author: Alexander Ivakov
 * alexander.ivakov@anu.edu.au
 */

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
using namespace cv;


int otsu(Mat img){
    double min;
    double max;
    
    minMaxLoc(img, &min, &max);
            
    vector<double> levels;
        
    for(int i=(int)min; i<(int)max; i++){
        Mat mask;
        Mat invmask;
        inRange(img, Scalar(0), Scalar(i), mask);
        bitwise_not (mask, invmask);
        vector<double> mean1;
        vector<double> sdev1;
        vector<double> mean2;
        vector<double> sdev2;
        meanStdDev(img, mean1, sdev1, mask);
        meanStdDev(img, mean2, sdev2, invmask);
        
        int w1 = countNonZero(mask);
        int w2 = countNonZero(invmask);
        double w12 = (double)w1/(361920);                           //361920 is the number of pixels in the image (added manually), still need to implement this 
        double w22 = (double)w2/(361920);
        levels.push_back(w12*pow(sdev1[0],2)+w22*pow(sdev2[0],2));
        
    }
    
    int minpos = 0;
    double currentmin = levels[0];
    for(int k=1; k<levels.size(); k++){
        if(levels[k] < currentmin){
            currentmin = levels[k];
            minpos = k;
        }
    }
    
    return (int)min + minpos;
}
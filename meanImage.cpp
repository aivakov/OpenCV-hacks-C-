/*
 * Function to compute an average image from a vector of single channel Mat images
 * 
 * Input: stack of images as a vector<Mat>
 * 
 * start, finish = can indicate a subset of the stack to average (from start to finish)
 * 
 * returns the average image as a 32bit Mat
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

Mat meanImage(vector<Mat> src, int start, int finish){
    
    int rows = src[0].rows;
    int cols = src[0].cols;
    Mat average(rows, cols, CV_32F);
    for(int i=start; i<finish; i++){
        
        Mat div(rows, cols, CV_32F);
        Mat image32f(rows, cols, CV_32F);
        src[i].convertTo(image32f, CV_32F);
        divide(image32f, 21, div);
        add(average, div, average);
    }
    
    return average;
}
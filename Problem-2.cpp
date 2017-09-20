//Pranay Pourkar
// Mobile No. 7758857755
//email pranay.pourkar@gmail.com
//2nd year ,Electrical & Electronics Engineering.
//Visvesvaraya National Institute of Technology ,Nagpur.
//Problem 2
#include<opencv2/highgui/highgui.hpp>
#include<cv.h>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
//define window
namedWindow("img",CV_WINDOW_AUTOSIZE);


Mat output,blurr,hsv;

//read the input image jellyfish.jpg
Mat img = imread("/home/pranay/opencv/jellyfish.jpg",CV_LOAD_IMAGE_COLOR);

  for (int i=1; i<7; i=i+2)
   { 
      //smooth the image in the "img" and save it to "blurr"
      blur(img, blurr, Size(i,i));
   }

//change colour space
cvtColor(blurr,hsv,COLOR_BGR2HSV);

//threshold the image
inRange(hsv, Scalar(121, 25, 131), Scalar(255, 255, 255), output); 

//apply dilation to image
  dilate( output, output,getStructuringElement(MORPH_ELLIPSE, Size( 1, 1)) ); 


vector<vector<Point> > contours; 
//find contours in output image
findContours(output, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); 

 
/// Get the moments
vector<Moments> mu( contours.size());
for( int i = 0; i < contours.size(); i++ )
{ 
mu[i] = moments( contours[i], false );
} 

int j=0;
/// Get the mass centers:
vector<Point2f> mc( contours.size());
for( int i = 0; i < contours.size(); i++ )
{ 
mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00);
j++;
}


for(int i = 0; i < j-1; i++)
    {         
         if( contourArea(contours[i]) > 10 )
        {  
         //check for nan
         if (!isnan(mc[i].x)) 
        {         
            if (!isnan(mc[i].y))
           { 
            //draw rectangle on detected jellyfish
            Rect r0= boundingRect(Mat(contours[i])); 
            rectangle(img,r0,Scalar(0,255,0),2); 
            //put red cross mark
            putText(img, "x", Point(mc[i].x,mc[i].y), FONT_HERSHEY_COMPLEX, 0.5, Scalar(0,0,255), 2);     
           }  
        }
        }
    }
//show the image
imshow("img",img);
waitKey(0); 
     
return 0;
}




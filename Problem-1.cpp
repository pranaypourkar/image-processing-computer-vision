
//Problem 1
//source - Viola Jones algorithm is used

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<cv.h>
#include<iostream>
#include<math.h>


using namespace cv;
using namespace std;

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);    
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}


 
int main( )
{
    float a[2][2],b[2][1];
    Mat A,B,x;

    Mat image1,image2,rot1,rot2,rot3;
    //load input image oscarSelfie.jpg
    image1 = imread("/home/pranay/opencv/detect/oscarSelfie.jpg", CV_LOAD_IMAGE_COLOR);  
    image2 = image1.clone();
    
    namedWindow( "window1", 1 );  
    imshow( "window1", image2 );

    //degree positive rotate anticlockwise by 15 degrees
    rot1 = rotate(image2,15);


    // Load Face cascade (.xml file)
    CascadeClassifier face_cascade;
    face_cascade.load( "/home/pranay/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_alt2.xml" );
   
    // load eye cascade (.xml file)
    CascadeClassifier eyes_cascade; 
    eyes_cascade.load("/home/pranay/opencv-2.4.9/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml");
 
    // Detect faces
    vector<Rect> faces;
    face_cascade.detectMultiScale( rot1, faces, 1.1, 5, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );  //grayscale image , scale factor,minNeighbors,1.1 2 , 1.3 5
 
    // Draw circles on the detected faces
    for( int i = 0; i < faces.size(); i++ )
    {

       if(i!=0 && i!=3){
       
       //values 62.01146990647685,142.9761224217467,... are the elements of matrix r ( in rotate function) 
       float b[2][1]={{faces[i].x + 62.01146990647685}, {faces[i].y - 142.9761224217467}};
       float a[2][2] = {{ 0.9659258262890683, 0.2588190451025207},{-0.2588190451025207, 0.9659258262890683}};
        A = Mat(2,2 ,CV_32FC1, a);
        B = Mat(2,1, CV_32FC1, b);
       
        //apply transformation on rotated image to get co-ordinates in original image 
        x = A.inv() * B;

        faces[i].x=x.at<float>(0,0);
        faces[i].y=x.at<float>(1,0);
       
       
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
       //draw ellipse on detected face
        ellipse( image1, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
         }
    }
  


    rot2 = rotate(image2,-10);//negative angle rotate image by 10 degree clockwise


    // Load Face cascade (.xml file)
    face_cascade.load( "/home/pranay/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_alt2.xml" );
 
    // Detect faces
    face_cascade.detectMultiScale( rot2, faces, 1.1, 5, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );  //grayscale image , scale factor,minNeighbors,1.1 2 , 1.3 5
 
    // Draw circles on the detected faces
    for( int i = 0; i < faces.size(); i++ )
    {
     
       float b[2][1]={{faces[i].x - 61.0884210014971}, {faces[i].y + 84.24384714021619}};
       float a[2][2] = {{ 0.984807753012208, -0.1736481776669303},{0.1736481776669303, 0.984807753012208}};
        A = Mat(2,2 ,CV_32FC1, a);
        B = Mat(2,1, CV_32FC1, b);
        x = A.inv() * B;

        //access first and second element of x
        faces[i].x=x.at<float>(0,0);
        faces[i].y=x.at<float>(1,0);
       
          //draw ellipse on detected face
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( image1, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        
    }   

   
    for( int i = 0; i < faces.size(); i++ )
  {
   
     Mat faceROI = image2( faces[i] );

    vector<Rect> eyes;
    // detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
   if(i==3){
    for( int j = 0; j < eyes.size(); j++ )
     {    
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( image1, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        
      if(j==0){    
     //RGB value at the location of the centroid of Ellen’s eyes
       Point2d c; 
   //apply formula
   c.x=((faces[i].x+ eyes[j].x + eyes[j].width*0.5) + (faces[i].x + eyes[j+1].x + eyes[j+1].width*0.5))/2; 
   c.y=((faces[i].y + eyes[j].y + eyes[j].width*0.5) + (faces[i].y + eyes[j+1].y + eyes[j+1].width*0.5))/2; 
   Vec3b pixel = image1.at<Vec3b>((int)c.y,(int)c.x); 
        //print values
	cout << "B component:" << (unsigned int)pixel[0] << endl;   
	cout << "Y component:" << (unsigned int)pixel[1] << endl; 
	cout << "R component:" << (unsigned int)pixel[2] << endl;    
     }
     }
     }
  }

    imshow( "Detected Face", image1 );
     
    waitKey(0);                   
    return 0;
}

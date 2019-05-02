
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int main()
{
	Mat image_eyes;
	//image_eyes = imread("eyes.jpg",0);
	Mat heart;
	heart = imread("1200px-Heart_corazón.svg.png");

	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout<<"camera problem";
	}
	while(true)
	{
		Mat frame;
		cap.read(frame);
	cv::Ptr<cv::cuda::CascadeClassifier> cascade = cv::cuda::CascadeClassifier::create("haarcascade_eye.xml");
	cuda::GpuMat d_image,g_image;
	cuda::GpuMat d_buff;
	d_image.upload(frame);
	cv::cuda::cvtColor(d_image, g_image, cv::COLOR_BGR2GRAY);
	cascade->setScaleFactor(1.01);
	cascade->detectMultiScale(g_image, d_buff);
	std::vector<Rect> detection ;
	cascade->convert( d_buff, detection);
	if (detection.empty())

	{
		std::cout<<"no detection"<<std::endl;

	}
	//cout << "Width : " << frame.size().width << endl;
	//cout << "Height: " << frame.size().height << endl;
	Mat img(frame.size().height,frame.size().width,CV_8UC3,Scalar(0,0,0));
	///std::vector<Rect> io,p;
	Mat funny(frame.size().height,frame.size().width,CV_8UC3,Scalar(0,0,0));
	for (int i =0;i< detection.size();++i)
	{
		std::cout<<detection[i].tl()<<std::endl;
		//int *a = detection[i].tl();
		//std::cout<<a;
		Point center_of_rect = (detection[i].br() + detection[i].tl())*0.5;
    	//heart.copyTo(frame(cv::Rect((center_of_rect),center_of_rect,heart.cols, heart.rows)));
    	//std::cout<<center_of_rect;
    		
    	circle(img,center_of_rect,10,Scalar(0,0,255));
		circle(funny,center_of_rect,35,Scalar(115,50,100),-20);
		//std::cout<<io[i]<<std::endl;
	//	rectangle(frame,detection[i],Scalar(0,0,0),1);
		//rectangle(img,detection[i],Scalar(255,255,255),-5);
	}
	std::cout<<std::endl<<std::endl;
	Mat im;
	add(frame,funny,im);
	//imshow("add",im);
	imshow("result",im);
	//imshow("frame",img);
	//imshow("funnny",funny);

	waitKey(50);
	}


	return 0;

}

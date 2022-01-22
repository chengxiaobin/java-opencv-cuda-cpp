#include <iostream>
#include <string>
#include <bitset>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/cudabgsegm.hpp"
#include "opencv2/cudalegacy.hpp"
#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
using namespace cv::cuda;

extern "C" char* function(const char* input,int filenameleng) {
	char result[4096] = "0";
	memset(result,0, 4096);
	memcpy(result, input, filenameleng);
	std::string fileName;
	const char* str = result;
	fileName.append(str, filenameleng);
	
	Mat h_image = imread(fileName, 0);
	if (h_image.empty())
	{
		cout << "can not open image: "+ fileName << endl;
	}
	GpuMat d_edge, d_image;
	Mat h_edge;
	d_image.upload(h_image);
	cv::Ptr<cv::cuda::CannyEdgeDetector> canny_edge = cv::cuda::createCannyEdgeDetector(2.0, 100.0, 3, false);
	canny_edge->detect(d_image, d_edge);
	d_edge.download(h_edge);
	int index = fileName.find_last_of(".");
	string newFileName = fileName.replace(index, filenameleng - index, "-new.jpg");
	char ch[4096];
	strcpy_s(ch, newFileName.c_str());
	cv::imwrite(fileName, h_edge);
	return ch;
}
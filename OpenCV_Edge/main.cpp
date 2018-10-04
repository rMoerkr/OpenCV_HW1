 	
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;

int main() {
	Mat pic(40, 50, CV_8UC3, Scalar(0, 0, 255));
	Mat picPlus(40, 50, CV_8UC3, Scalar(0, 0, 255));
	Mat picMine(40, 50, CV_8UC3, Scalar(0, 0, 255));
	int R[4][5] = { { 247,67,32,187,240 }, {122, 41, 21, 16, 154}, { 52, 35, 79, 21, 93},{ 27, 22, 35, 154, 75} };
	int G[4][5] = { {14,145,132,25,40},{212,221,121,54,14},{132,235,178,19,14} ,{122,122,133,54,47} };
	int B[4][5] = { {17,44,32,127,240},{22,231,21,156,124},{32,35,78,21,194},{127,22,33,54,45} };
	for (int i = 0; i < pic.rows; i++) {
		for (int j = 0; j < pic.cols; j++) {
			int imat = (int)(i / 10);
			int jmat = (int)(j / 10);
			pic.at<cv::Vec3b>(i, j)[0] = B[imat][jmat];
			pic.at<cv::Vec3b>(i, j)[1] = G[imat][jmat];
			pic.at<cv::Vec3b>(i, j)[2] = R[imat][jmat];
			picPlus.at<cv::Vec3b>(i, j)[0] = min(B[imat][jmat] + 32, 255);
			picPlus.at<cv::Vec3b>(i, j)[1] = min(G[imat][jmat] + 32, 255);
			picPlus.at<cv::Vec3b>(i, j)[2] = min(R[imat][jmat] + 32, 255);
			picMine.at<cv::Vec3b>(i, j)[0] = max(B[imat][jmat] - 20, 0);
			picMine.at<cv::Vec3b>(i, j)[1] = max(G[imat][jmat] - 20, 0);
			picMine.at<cv::Vec3b>(i, j)[2] = max(R[imat][jmat] - 20, 0);
		}
	}
	//cout << pic << endl;
	Mat lena = imread("lena.jpg");
	imshow("pic", pic);
	imshow("picPlus", picPlus);
	imshow("picMine", picMine);
	waitKey(0);
}
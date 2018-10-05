
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<vector>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	cout << "import level:" << endl;
	int level;
	cin >> level;
	Mat pic(400, 500, CV_8UC3, Scalar(0, 0, 255));
	Mat picPlus(400, 500, CV_8UC3, Scalar(0, 0, 255));
	Mat picMinus(400, 500, CV_8UC3, Scalar(0, 0, 255));
	Mat picLevel(400, 500, CV_8UC3, Scalar(0, 0, 255));
	Mat picLevel2(400, 500, CV_8UC3, Scalar(0, 0, 255));
	vector<int[3]> vec(level);//儲存出現頻率的向量
	int sum[3] = { 0,0,0 };
	int BGR[3][4][5] = {
		{ {17,44,32,127,240},	{22,231,21,156,124},	{32,35,78,21,194},		{127,22,33,54,45} } ,
		{ {14,145,132,25,40},	{212,221,121,54,14},	{132,235,178,19,14} ,	{122,122,133,54,47} } ,
		{ {247,67,32,187,240 }, {122,41,21, 16, 154},	{52,35,79,21,93},		{27,22,35,154,75} }
	};
	int LevelNumber[3][4];
	for (int i = 0; i < pic.rows / 100; i++) {
		for (int j = 0; j < pic.cols / 100; j++) {
			for (int k = 0; k < 3; k++) {//顔色空間
				for (int im = 0; im < 100; im++) {
					for (int jm = 0; jm < 100; jm++) {
						pic.at<cv::Vec3b>(i * 100 + im, j * 100 + jm)[k] = BGR[k][i][j];
						picPlus.at<cv::Vec3b>(i * 100 + im, j * 100 + jm)[k] = min(BGR[k][i][j] + 32, 255);
						picMinus.at<cv::Vec3b>(i * 100 + im, j * 100 + jm)[k] = max(BGR[k][i][j] - 20, 0);
						picLevel.at<cv::Vec3b>(i * 100 + im, j * 100 + jm)[k] = ((int)(BGR[k][i][j] / (255 / level))) * (255/level);
					}
				}
				vec[(int)((BGR[k][i][j] / (255 / level)))][k]++;
				sum[k]++;
			}
		}
	}
	for (int i = 0; i < pic.rows / 100; i++) {
		for (int j = 0; j < pic.cols / 100; j++) {
			for (int k = 0; k < 3; k++) {//顔色空間
				for (int im = 0; im < 100; im++) {
					for (int jm = 0; jm < 100; jm++) {
						picLevel2.at<cv::Vec3b>(i * 100 + im, j * 100 + jm)[k] = 
							((vec[((int)picLevel.at<cv::Vec3b>(i * 100, j * 100)[k] / (255 / level))][k]) *255 /sum[k]);
					}
				}
			}
		}
	}
	for (int i = 0; i < level; i++) {
		cout << "level " << i << endl;
		cout << "    B" << vec[i][0] << endl;
		cout << "    G" << vec[i][1] << endl;
		cout << "    R" << vec[i][2] << endl;
	}
	cv::imshow("pic", pic);
	cv::imshow("picPlus", picPlus);
	cv::imshow("picMinus", picMinus);
	cv::imshow("picLevel", picLevel);
	cv::imshow("picLevel2", picLevel2);
	cv::waitKey(0);
}
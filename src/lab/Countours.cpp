#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

int main()
{
	// ��������� ���� ��� �����������
	const char* srcWinName = "src", *contourWinName = "contour", *grayWinName = "grey", *binaryWinName = "binary";
	namedWindow(srcWinName, 1);
	namedWindow(grayWinName, 1);
	namedWindow(binaryWinName, 1);
	namedWindow(contourWinName, 1);

	// ������������ ��������� ����������
	Mat src = imread("images/apple.jpg", 1);
	if (src.data == 0)
	{
		printf("Incorrect image name or format.\n");
		return 1;
	}

	// ��������� ��ﳿ ��������� ����������
	Mat copy = src.clone();

	// ��������� �������������� ���������� ���
	// ������������� ��������� ���������� �
	// ������ �����
	Mat gray, grayThresh;
	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray, grayThresh, 120, 255, CV_THRESH_BINARY);

	// ����� �������
	std::vector<std::vector<Point>> contours;
	findContours(grayThresh, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	// ����������� �������
	Scalar color(0, 255, 0);
	drawContours(copy, contours, -1, color, 2);

	// ���������� ����������
	std::vector<int> compression_params{ CV_IMWRITE_JPEG_QUALITY , 75 };
	imwrite("images/apple_contour.jpg", copy, compression_params);

	// ����������� ���������
	imshow(srcWinName, src);
	imshow(grayWinName, gray);
	imshow(binaryWinName, grayThresh);
	imshow(contourWinName, copy);

	// ���������� ���������� ����-��� ������
	waitKey(0);

	// ���������� �������
	gray.release();
	grayThresh.release();
	copy.release();
	src.release();
	return 0;
}
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

cv::Mat rgb2gray(cv::Mat rgb);

cv::Mat	imagebinary(cv::Mat image,int threshold);

cv::Mat histequalize(cv::Mat image);

cv::Mat histvisual(cv::Mat image);

void rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk); 
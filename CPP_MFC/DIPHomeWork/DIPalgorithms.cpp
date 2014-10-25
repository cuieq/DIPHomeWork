#include "stdafx.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <vector>
using namespace std;

// convert RGB image to Gray image
cv::Mat rgb2gray(cv::Mat rgb)
{
	cv::Mat channels[3];
	cv::split(rgb,channels);
	cv::Mat grayimage = channels[0]*0.114 + channels[1]*0.587 + channels[2]*0.299;
	return grayimage;
}

cv::Mat	imagebinary(cv::Mat image,int threshold)
{
	cv::Mat gray=rgb2gray(image);
	cv::Mat img_binary=gray.clone();
	int nrows=gray.rows;
	int ncols=gray.cols;
	for(int row=0;row < nrows ;row++){
		uchar* data=gray.ptr<uchar>(row);
		uchar* data_out=img_binary.ptr<uchar>(row);
		for(int col=0;col < ncols;col++){
			if (data[col] > threshold)
				data_out[col]=255;
			else
				data_out[col] = 0;
		}
	}
	return img_binary;
}

cv::Mat  HistCum(cv::Mat hist)
{
	cv::Mat cumSum(hist.rows, hist.cols, CV_32FC1, cv::Scalar(0));
	float sumTmp = 0;
	int rows = hist.rows;
	int cols = hist.cols;
	for (int i = 0; i<rows; i++){
		float* pDatahist = hist.ptr<float>(0);
		float* pDatasum = cumSum.ptr<float>(0);
		sumTmp += pDatahist[i];
		pDatasum[i] = sumTmp;
	}
	return cumSum;
}

cv::Mat histCalc(cv::Mat channel)
{
	cv::Mat img_hist(256, 1, CV_32FC1, cv::Scalar(0));
	for (int i = 0; i < channel.rows; i++){
		for (int j = 0; j < channel.cols; j++){
			UINT8 pix_tmp = channel.at<uchar>(i, j);
			float* Pdata = img_hist.ptr<float>(0);
			Pdata[pix_tmp]++;
		}
	}
	return img_hist;
}

cv::Mat equalizeChannel(cv::Mat channel, cv::Mat cumSum)
{
	for (int i = 0; i < channel.rows; i++){
		uchar* pData = channel.ptr<uchar>(i);
		float* pDatasum = cumSum.ptr<float>(0);
		for (int j = 0; j < channel.cols; j++){
			pData[j] = (int)(pDatasum[pData[j]] * 255.0 / (channel.rows*channel.cols));
		}
	}
	return channel;
}

cv::Mat histvisual(cv::Mat image)
{
    cv::Mat bgr_planes[3];
    cv::split(image, bgr_planes);
	int cols = bgr_planes[0].cols;
	int rows = bgr_planes[0].rows;
    int histSize=256;
    cv::Mat b_hist,g_hist,r_hist;
	b_hist = histCalc(bgr_planes[0]);
	g_hist = histCalc(bgr_planes[1]);
	r_hist = histCalc(bgr_planes[2]);
    int hist_w=512;int hist_h=220;
    int bin_w=cvRound((double)hist_w/histSize);
    cv::Mat histImage(hist_h,hist_w,CV_8UC3,cv::Scalar(0,0,0));

	float* pDataB = b_hist.ptr<float>(0);
	float* pDataG = g_hist.ptr<float>(0);
	float* pDataR = r_hist.ptr<float>(0);
	double minmaxInI = 0.0;
	double* minValB = &minmaxInI;
	double* maxValB = &minmaxInI;
	double* minValG = &minmaxInI;
	double* maxValG = &minmaxInI;
	double* minValR = &minmaxInI;
	double* maxValR = &minmaxInI;
	minMaxIdx(b_hist, minValB, maxValB);
	minMaxIdx(g_hist, minValG, maxValG);
	minMaxIdx(r_hist, minValR, maxValR);
    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, cv::Point( bin_w*(i-1), hist_h*(1.0-pDataB[i-1] / *maxValB) ) ,
			cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i) * hist_h / *maxValB)),
                         cv::Scalar( 255, 0, 0), 2, 8, 0  );
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1) * hist_h / *maxValG)),
			cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i) * hist_h / *maxValG)),
                         cv::Scalar( 0, 255, 0), 2, 8, 0  );
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1) * hist_h / *maxValG)),
			cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i) * hist_h / *maxValG)),
                         cv::Scalar( 0, 0, 255), 2, 8, 0  );
    }
    return histImage;
}


cv::Mat histequalize(cv::Mat image)
{
    cv::Mat image_equalized;
    cv::Mat bgr_planes[3];
    cv::split(image, bgr_planes);
	int rows = bgr_planes[0].rows;
	int cols = bgr_planes[0].cols;
    cv::Mat b_hist,g_hist,r_hist;
	b_hist = histCalc(bgr_planes[0]);
	g_hist = histCalc(bgr_planes[1]);
	r_hist = histCalc(bgr_planes[2]);
	cv::Mat cumSum_b=HistCum(b_hist);
    cv::Mat cumSum_g=HistCum(g_hist);
	cv::Mat cumSum_r=HistCum(r_hist);
	bgr_planes[0] = equalizeChannel(bgr_planes[0], cumSum_b);
	bgr_planes[1] = equalizeChannel(bgr_planes[1], cumSum_g);
	bgr_planes[2] = equalizeChannel(bgr_planes[2], cumSum_r);
	cv::merge(bgr_planes, 3, image_equalized);
	return image_equalized;
}

void rgb2cmyk(cv::Mat& image, std::vector<cv::Mat>& cmyk) {
	cv::Mat bgr_planes[3];
	cv::split(image,bgr_planes);
	for (int i = 0; i < 4; i++) {
        cmyk.push_back(cv::Mat(image.size(), CV_8UC1));
    }
	int nrow=image.rows;
	int ncol=image.cols;
	for (int i=0;i<nrow;i++){
		for(int j=0;j<ncol;j++){
			float r = (int)bgr_planes[2].at<uchar>(i, j) / 255.;
            float g = (int)bgr_planes[1].at<uchar>(i, j) / 255.;
            float b = (int)bgr_planes[0].at<uchar>(i, j) / 255.;
            float k = std::min(std::min(1- r, 1- g), 1- b);         
 
            cmyk[0].at<uchar>(i, j) = (1 - r - k) / (1 - k) * 255.;
            cmyk[1].at<uchar>(i, j) = (1 - g - k) / (1 - k) * 255.;
            cmyk[2].at<uchar>(i, j) = (1 - b - k) / (1 - k) * 255.;
            cmyk[3].at<uchar>(i, j) = k * 255.;
        }
    }
}

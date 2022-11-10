//
//  main.cpp
//  test
//
//  Created by 최진용 on 2022/11/08.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    //사용할 메인 이미지
    Mat src = imread("/Users/choejin-yong/Desktop/2semester/opencv/test/Small.png", 1);
    imshow("SourceImage",src);
//저주파 처리--------------------------------------------------------------------------------------------
    Mat noise_img;
    Mat noiseMedian3, noiseMedian5, noiseMean3, noiseMean5;
    Mat softMedian3, softMedian5, softMean3, softMean5;
    
    //노이즈 파일을 만들기 위해서 기본 이미지 복사
    noise_img = src.clone();
    
    //랜덤한 노이즈 생성
    for (int i = 0; i < 1000; i++)
        {
            int x = rand() % noise_img.rows;
            int y = rand() % noise_img.cols;
            int c = rand() % 256;

            noise_img.at<Vec3b>(x, y)[0] = c;
            noise_img.at<Vec3b>(x, y)[1] = c;
            noise_img.at<Vec3b>(x, y)[2] = c;
        }
    
    //3x3인 마스크 생성
    Mat meanfilter3x3 = Mat::ones(3, 3, CV_32F) / 9;
    //5x5인 마스크 생성
    Mat meanfilter5x5 = Mat::ones(5, 5, CV_32F) / 25;

//이미지 부드럽게 하는 meanfilter
    filter2D(src, softMean3, -1, meanfilter3x3, Point(-1, -1), 0, 4);
    filter2D(src, softMean5, -1, meanfilter5x5, Point(-1, -1), 0, 4);
//노이즈 제거하는 meanfilter
    filter2D(noise_img, noiseMean3, -1, meanfilter3x3, Point(-1, -1), 0, 4);
    filter2D(noise_img, noiseMean5, -1, meanfilter5x5, Point(-1, -1), 0, 4);
    
    
//이미지 부드럽게 하는 median
    //사이즈3
    medianBlur(src, softMedian3, 3);
    //사이즈5
    medianBlur(src, softMedian5, 5);
    
//노이즈 제거 median
    //사이즈3
    medianBlur(noise_img, noiseMedian3, 3);
    //사이즈5
    medianBlur(noise_img, noiseMedian5, 5);

    
    
//고주파 처리----------------------------------------------------------------------------------------------
    
    //이미지 선언
    Mat blur_img, gray_img, laplacian_img, finished_laplacian_img;
    
    //가우시안 필터를 이용해서 노이즈 제거(사이즈 3x3)
    GaussianBlur(src, blur_img, Size(3,3), 0);
    //가우시안 필터를 이용한 이미지를 gray로 컬러 변경후 gray_img로 저장
    cvtColor(blur_img, gray_img, COLOR_BGR2GRAY);
    
    //gray_img를 laplacian img로 변경, 3x3사이즈 커널 사이즈)
    Laplacian(gray_img, laplacian_img, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    //라플라시안 이미지를 처리한 이미지를, 픽셀로 처리한것을 다시 변환해서 finished_laplacian_img로 변경)
    convertScaleAbs(laplacian_img, finished_laplacian_img);
    
    
//결과 이미지 도출--------------------------------------------------------------------------------------
    //결과 화면 도출
    imshow("NoiseImage", noise_img);
    imshow("softMean3",softMean3);
    imshow("softMean5",softMean5);
    
    imshow("noiseMean3",noiseMean3);
    imshow("noiseMean5",noiseMean5);
    
    imshow("softMedian3", softMedian3);
    imshow("softMedian5", softMedian5);
    
    imshow("noiseMedian3", noiseMedian3);
    imshow("noiseMedian5", noiseMedian5);
    
    imshow("Gaussian", blur_img);
    imshow("Laplacian", finished_laplacian_img);
    waitKey(0);

    return 0;
}

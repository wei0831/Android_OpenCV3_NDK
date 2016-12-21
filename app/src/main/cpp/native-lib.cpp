#include <jni.h>
#include <opencv2/opencv.hpp>

void toGray(cv::Mat& input, cv::Mat& output) {
    cv::cvtColor(input, output, CV_RGBA2GRAY);
}

void cannyOperator(cv::Mat& input, cv::Mat& output){
    cv::Canny(input, output, 75, 150, 3, true);
}

extern "C"
JNIEXPORT void JNICALL
Java_net_wei0831_opencv_1init_MainActivity_covertEdge(JNIEnv *env, jobject instance,
                                                      jlong matAddrRgba,
                                                      jlong matAddrGray,
                                                      jlong matAddrEdge) {

    cv::Mat& mRgba = *(cv::Mat*)matAddrRgba;
    cv::Mat& mGray = *(cv::Mat*)matAddrGray;
    cv::Mat& mEdge = *(cv::Mat*)matAddrEdge;

    toGray(mRgba, mGray);
    cannyOperator(mGray, mEdge);
}

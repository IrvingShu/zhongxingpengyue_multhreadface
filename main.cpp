// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.



    This face detector is made using the classic Histogram of Oriented
    Gradients (HOG) feature combined with a linear classifier, an image pyramid,
    and sliding window detection scheme.  The pose estimator was created by
    using dlib's implementation of the paper:
        One Millisecond Face Alignment with an Ensemble of Regression Trees by
        Vahid Kazemi and Josephine Sullivan, CVPR 2014
    and was trained on the iBUG 300-W face landmark dataset.

    Also, note that you can train your own models using dlib's machine learning
    tools.  See train_shape_predictor_ex.cpp to see an example.




    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.
*/

#include <iostream>
#include <fstream>
#include <QString>
#include <QCoreApplication>
#include <sys/time.h>
#include <time.h>

#include "classifier.h"
#include "facedetector.h"
#include "worker.h"

using namespace caffe;
using namespace dlib;

// ----------------------------------------------------------------------------------------
void split(const string& src, const string& separate_character, std::vector<string> &dest)
{
    int separate_characterLen = separate_character.size();//分割字符串长度，这样就可以支持多字 符串的分隔符
    int lastPosition = 0, index = -1;
    while (-1 != (index = src.find(separate_character, lastPosition)))
    {
        dest.push_back(src.substr(lastPosition, index - lastPosition));
        lastPosition = index + separate_characterLen;
    }
    string lastString = src.substr(lastPosition);
    if (!lastString.empty())
    dest.push_back(lastString);

}


//-----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    struct timeval t_start,t_end;
    long cost_time = 0;
    //get start time
    gettimeofday(&t_start, NULL);
    long start = ((long)t_start.tv_sec)*1000+(long)t_start.tv_usec/1000;
    Worker worker;
    worker.Working();
    gettimeofday(&t_end, NULL);
    long end = ((long)t_end.tv_sec)*1000+(long)t_end.tv_usec/1000;
    cost_time = end - start;
    std::cout << "cost_time: " << cost_time << std::endl;
    return a.exec();
    /*
    //face detector file
    string shape_predictor_model = "./model/shape_predictor_68_face_landmarks.dat";

    //face recognization file
    string model_file = "./model/triplet_deploy.prototxt";
    string trained_file = "./model/_iter_175000.caffemodel";
    std::ifstream testImgFile("./data/datalist.txt");

    string IMGPATH = "./data/";

    //face recognization
    string imgName;
    int N = 6000;

    FaceDetector faceDetector(shape_predictor_model);
    Classifier classifier(model_file, trained_file);

    for(int i=0; i<N && std::getline(testImgFile, imgName); i++)
    {
        struct timeval t_start,t_end;
        long cost_time = 0;

        std::vector<string> destImgName;
        split(imgName, ":", destImgName);

        cv::Mat img1 = cv::imread(IMGPATH + destImgName[0]);
        cv::Mat img2 = cv::imread(IMGPATH + destImgName[1]);


        if(img1.empty() && img2.empty()){
            continue;
        }else if(img1.empty() && !img2.empty())
        {
            continue;
        }else if(!img1.empty() && img2.empty())
        {
            continue;
        }

        //get start time
        gettimeofday(&t_start, NULL);
        long start = ((long)t_start.tv_sec)*1000+(long)t_start.tv_usec/1000;
        std::vector<cv::Mat> imgFaceVector1 = faceDetector.getFaceImg(IMGPATH + destImgName[0]);
        std::vector<cv::Mat> imgFaceVector2 = faceDetector.getFaceImg(IMGPATH + destImgName[1]);

        if(imgFaceVector1.size()==0 && imgFaceVector2.size()==0){
            float distance = classifier.getImgDistance(img1, img2);
            std::cout <<  imgName<<" " << distance << " ";
        }else if(imgFaceVector1.size()==0 && imgFaceVector2.size() != 0)
        {
            float distance = classifier.getImgDistance(img1, img2);
            std::cout <<  imgName<<" " << distance << " ";

        }else if(imgFaceVector1.size()!=0 && imgFaceVector2.size() ==0)
        {
            float distance = classifier.getImgDistance(img1, img2);
            std::cout <<  imgName<<" " << distance << " ";
        }else if(imgFaceVector1.size()==1 && imgFaceVector2.size()==1)
        {

            //getImgDistance
            float distance = classifier.getImgDistance(imgFaceVector1[0], imgFaceVector2[0]);
            std::cout <<  imgName<<" " << distance << " ";

        }else{
            float distance = classifier.getImgDistance(img1, img2);
            std::cout <<  imgName<<" " << distance << " ";
        }
        gettimeofday(&t_end, NULL);
        long end = ((long)t_end.tv_sec)*1000+(long)t_end.tv_usec/1000;
        cost_time = end - start;
        std::cout << cost_time << std::endl;
    }

    testImgFile.close();
    */
    //return 0;
}

// ----------------------------------------------------------------------------------------


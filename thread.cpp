#include "thread.h"

extern std::vector<float> imgFeature0;
extern std::vector<float> imgFeature1;

Thread::Thread()
{

}

Thread::Thread(int threadIndex)
{
    this->threadIndex = threadIndex;
}

void Thread::run()
{
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
        this->pause.lock();
        //std::cout << this->threadIndex << std::endl;

        std::vector<string> destImgName;
        split(imgName, ":", destImgName);

        cv::Mat img = cv::imread(IMGPATH + destImgName[this->threadIndex]);

        if(img.empty()){
            continue;
        }
        //get start time
        std::vector<cv::Mat> imgFaceVector = faceDetector.getFaceImg(IMGPATH + destImgName[this->threadIndex]);

        if(imgFaceVector.size()!=1){
             if(this->threadIndex == 0)
             {
                imgFeature0 = classifier.getFeature(img);
             }
             else if(this->threadIndex == 1){
                imgFeature1 = classifier.getFeature(img);
             }
        }
        else if(imgFaceVector.size()==1)
        {
            if(this->threadIndex == 0)
            {
               imgFeature0 = classifier.getFeature(imgFaceVector[0]);
            }
            else if(this->threadIndex == 1){
               imgFeature1 = classifier.getFeature(imgFaceVector[0]);
            }
        }
       //this->pause.unlock();
        emit finishedImgFeatureSig(imgName);
    }
}


// ----------------------------------------------------------------------------------------
void Thread::split(const string& src, const string& separate_character, std::vector<string> &dest)
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


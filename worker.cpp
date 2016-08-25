#include "worker.h"
#include <QWaitCondition>
std::vector<float> imgFeature0;
std::vector<float> imgFeature1;

Worker::Worker()
{
    this->finishImgNum = 0;

    this->thread0 = new Thread(0);
    this->thread1 = new Thread(1);

    connect(this->thread0,SIGNAL(finishedImgFeatureSig(const string&)),this, SLOT(finishedImgFeatureSlot(const string&)), Qt::DirectConnection );
    connect(this->thread1,SIGNAL(finishedImgFeatureSig(const string&)),this, SLOT(finishedImgFeatureSlot(const string&)), Qt::DirectConnection );
    f.open("./result.txt");
}

Worker::~Worker(){
    if(this->thread0){delete this->thread0; this->thread0 = NULL; this->thread1 = NULL;}
    f.close();
}

void Worker::finishedImgFeatureSlot(const std::string &img)
{
    //std::cout << std::endl;//if no node, died
    this->f << std::endl;
    if(this->finishImgNum != 1){
        this->finishImgNum += 1;
    }else{
        this->f << img << " " <<getEucDistance(imgFeature0, imgFeature1) << std::endl;
        this->finishImgNum = 0;
        this->thread0->pause.unlock();
        this->thread1->pause.unlock();
    }

}

float Worker::getEucDistance(std::vector<float> &feature1, std::vector<float> &feature2)
{
    float distance = 0.0;
    if(feature1.size() == feature2.size())
    {
        for(int i=0; i < feature1.size(); i++)
        {
            distance += pow(feature1[i] - feature2[i],2);
        }
        distance = sqrt(distance);

    }else{
       std::cout << "feature1 and feature2 demension equll" << std::endl;
    }
    return distance;
}

void Worker::Working()
{
    //start thread
    this->thread0->start();
    this->thread1->start();
    this->thread0->wait();
    this->thread1->wait();

}



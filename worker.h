#ifndef WORKER_H
#define WORKER_H
#include "thread.h"
#include <QObject>
#include <iostream>
#include <fstream>

class Worker : public QObject
{
Q_OBJECT
public:
    Worker();
    ~Worker();
    void Working();
    void split(const string& src, const string& separate_character, std::vector<string> &dest);
    float getEucDistance(std::vector<float> &feature1, std::vector<float> &feature2);
private:
    Thread *thread0;
    Thread *thread1;
    int finishImgNum;
    std::ofstream f;
public slots:
    void finishedImgFeatureSlot(const string&);

};

#endif // WORKER_H

#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QMutex>

#include "classifier.h"
#include "facedetector.h"

class Thread : public QThread
{
    Q_OBJECT
private:
    int threadIndex;

public:
    Thread();
    Thread(int n);
    void run();\
    void split(const string& src, const string& separate_character, std::vector<string> &dest);
    QMutex pause;
signals:
    void finishedImgFeatureSig(const string&);
};

#endif // THREAD_H

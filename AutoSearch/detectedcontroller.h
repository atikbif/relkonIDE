#ifndef DETECTEDCONTROLLER_H
#define DETECTEDCONTROLLER_H

#include "searchcontroller.h"

// паттерн синглтон для хранения параметров последнего успешного поиска контроллера

#include <QObject>
#include <QMutex>

class DetectedController: public SearchController
{

public:
    static DetectedController& Instance()
    {
        static DetectedController singleton;
        return singleton;
    }

    void updateData(const SearchController &contr);

private:
    DetectedController();                                          // Private constructor
    ~DetectedController();
    DetectedController(const DetectedController&);                 // Prevent copy-construction
    DetectedController& operator=(const DetectedController&);      // Prevent assignment
};

#endif // DETECTEDCONTROLLER_H

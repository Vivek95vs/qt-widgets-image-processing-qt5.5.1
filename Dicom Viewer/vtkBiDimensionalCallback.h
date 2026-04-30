#ifndef VTKBIDIMENSIONALCALLBACK_H
#define VTKBIDIMENSIONALCALLBACK_H

#include "vtkCommand.h"
#include <vtkBiDimensionalWidget.h>
#include <vtkBiDimensionalRepresentation2D.h>

class vtkBiDimensionalCallback : public vtkCommand
{
public:
    static vtkBiDimensionalCallback* New();

    virtual void Execute(vtkObject* caller, unsigned long, void*);
    vtkBiDimensionalCallback();
};


#endif // VTKBIDIMENSIONALCALLBACK_H

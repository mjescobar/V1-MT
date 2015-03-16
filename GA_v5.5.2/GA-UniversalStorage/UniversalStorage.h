
/* 
 * File:   UniversalStorage.h
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 *
 * Created on November 8, 2012, 10:51 PM
 */

#ifndef UNIVERSALSTORAGE_H
#define UNIVERSALSTORAGE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "sys/types.h"
#include "sys/sysinfo.h"

class UniversalStorage {
public:
//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------
                    UniversalStorage(const UniversalStorage& orig);
                    UniversalStorage();  
  virtual          ~UniversalStorage();  
  UniversalStorage &operator=(const UniversalStorage UniversalStorageP);
//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------
  UniversalStorage(int DataDimensionsP, int* DataDimensionsSizesP);
//------------------------------------------------------------------------------
//Operations Related to Data Managing-------------------------------------------
//------------------------------------------------------------------------------
  void  FreeDimensions(int CurrentDimensionP, void* ArrayP);  
  void* FillDimensions(int CurrentDimensionP);  
  void  CopyDimensions(int CurrentDimensionP, void* ArraySourceP, void* &ArrayDestinationP);
  void* GetData();
//------------------------------------------------------------------------------
//Operations Related to Fields Vector-------------------------------------------
//------------------------------------------------------------------------------  
  int               GetFieldSize();
  void              AddStorage(int DataDimensionsP, int* DataDimensionsSizesP);
  void              DeleteStorage(int PositionP);
  void              FreeStorage(int PositionP);
  void              Shift();
  UniversalStorage* GetLast(); 
  UniversalStorage* GetPosition(int PositionP); 
private:
  int                           DataDimensions;
  int                           FieldsBuffer;
  int*                          DataDimensionsSizes;
  void*                         Data;
  std::vector<UniversalStorage> Fields;
};

#endif /* UNIVERSALSTORAGE_H */

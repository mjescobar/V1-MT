/* 
 * File:   UniversalStorage.cpp
 * Author: Pedro F. Toledo <pedrotoledocorrea@gmail.com>
 * 
 * Created on November 8, 2012, 10:51 PM
 */

#include "UniversalStorage.h"

#define free(p) free(p);p=NULL;  

//------------------------------------------------------------------------------
//Standard methods--------------------------------------------------------------
//------------------------------------------------------------------------------

UniversalStorage::UniversalStorage(const UniversalStorage& orig) {
  DataDimensions = orig.DataDimensions;
  FieldsBuffer   = orig.FieldsBuffer;
  if(orig.DataDimensionsSizes!=NULL){
    DataDimensionsSizes = (int*)malloc(sizeof(int)*DataDimensions);
    for(int i=0;i<DataDimensions;i++){
      DataDimensionsSizes[i] = orig.DataDimensionsSizes[i];
    }
  }
  else{
    DataDimensionsSizes = NULL;
  }
  Data = NULL;  
  if(orig.Data!=NULL){
    CopyDimensions(0, orig.Data, Data);
  }
  Fields = orig.Fields;
}

UniversalStorage::UniversalStorage(){
  DataDimensions      = -1;
  DataDimensionsSizes = NULL;
  FieldsBuffer        = 50;
  Data                = NULL;
  Fields.reserve(FieldsBuffer);
}

UniversalStorage::~UniversalStorage() {
  FreeDimensions(0,Data);
  if(DataDimensionsSizes!=NULL){
    free(DataDimensionsSizes);
  }
}

UniversalStorage &UniversalStorage::operator=(const UniversalStorage UniversalStorageP){
  DataDimensions  = UniversalStorageP.DataDimensions;
  FieldsBuffer  = UniversalStorageP.FieldsBuffer;
  DataDimensionsSizes  = UniversalStorageP.DataDimensionsSizes;
  if(UniversalStorageP.Data!=NULL){
    CopyDimensions(0,UniversalStorageP.Data,Data);
  }
  else{
    Data = NULL;
  }
  Fields = UniversalStorageP.Fields;
  return *this;
}

//------------------------------------------------------------------------------
//Constructors------------------------------------------------------------------
//------------------------------------------------------------------------------

UniversalStorage::UniversalStorage(int DataDimensionsP, int* DataDimensionsSizesP){
  DataDimensions = DataDimensionsP;
  FieldsBuffer   = 50;
  Data           = NULL;
  if(DataDimensionsSizesP != NULL){
    DataDimensionsSizes = (int*)malloc(sizeof(int)*DataDimensions);
    for(int i=0;i<DataDimensions;i++){
      DataDimensionsSizes[i] = DataDimensionsSizesP[i];
    }
    Data = FillDimensions(0);
  }
  else{
    DataDimensionsSizes = DataDimensionsSizesP;
  }
  Fields.reserve(FieldsBuffer);
}

//------------------------------------------------------------------------------
//Operations Related to Data Managing-------------------------------------------
//------------------------------------------------------------------------------

void UniversalStorage::FreeDimensions(int CurrentDimensionP, void* ArrayP){
  if(CurrentDimensionP+1<DataDimensions){
    for(int i=0;i<DataDimensionsSizes[CurrentDimensionP];i++){
      if(ArrayP != NULL){
        FreeDimensions(CurrentDimensionP+1, ((void**)ArrayP)[i]);
      }
    }
  }
  if(ArrayP != NULL){
    free(ArrayP);
  }
}

void* UniversalStorage::FillDimensions(int CurrentDimensionP){
  void* Array;
  if(CurrentDimensionP+1>=DataDimensions){
    Array = malloc(sizeof(double)*DataDimensionsSizes[CurrentDimensionP]);
    for(int i=0;i<DataDimensionsSizes[CurrentDimensionP];i++){
      ((double*)Array)[i] = 0;
    }
  }
  else{
    Array = malloc(sizeof(void*)*DataDimensionsSizes[CurrentDimensionP]);
    for(int i=0;i<DataDimensionsSizes[CurrentDimensionP];i++){
      ((void**)Array)[i] = FillDimensions(CurrentDimensionP+1);
    }
  }
  return Array;
}

void UniversalStorage::CopyDimensions(int CurrentDimensionP, void* ArraySourceP, void* &ArrayDestinationP){
  if(CurrentDimensionP == 0 && ArrayDestinationP != NULL){
    FreeDimensions(0,ArrayDestinationP);
  }
  if(CurrentDimensionP+1>=DataDimensions){
    ArrayDestinationP = (void*)malloc(sizeof(double)*DataDimensionsSizes[CurrentDimensionP]);
    for(int i=0;i<DataDimensionsSizes[CurrentDimensionP];i++){
      ((double*)ArrayDestinationP)[i] = ((double*)ArraySourceP)[i];
    }
  }
  else{
    ArrayDestinationP = (void*)malloc(sizeof(void*)*DataDimensionsSizes[CurrentDimensionP]);
    for(int i=0;i<DataDimensionsSizes[CurrentDimensionP];i++){
      CopyDimensions(CurrentDimensionP+1, ((void**)ArraySourceP)[i], ((void**)ArrayDestinationP)[i]);
    }
  }
}

void* UniversalStorage::GetData(){
  return Data;
}

//------------------------------------------------------------------------------
//Operations Related to Fields Vector-------------------------------------------
//------------------------------------------------------------------------------

int UniversalStorage::GetFieldSize(){
  return Fields.size();
}

void UniversalStorage::AddStorage(int DataDimensionsP, int* DataDimensionsSizesP){
  if(((int)Fields.size())+1>=FieldsBuffer){
    FieldsBuffer *= 2;
    Fields.reserve(FieldsBuffer);
  }
  Fields.push_back(UniversalStorage(DataDimensionsP, DataDimensionsSizesP));
}

void UniversalStorage::DeleteStorage(int PositionP){
  Fields[PositionP].Fields.erase(Fields.begin());
}

void UniversalStorage::FreeStorage(int PositionP){
  Fields[PositionP].FreeDimensions(0,Data);
}

UniversalStorage* UniversalStorage::GetLast(){
  int position = Fields.size()-1;
  return &(Fields[position]);
}

UniversalStorage* UniversalStorage::GetPosition(int PositionP){
  return &(Fields[PositionP]);
}

void UniversalStorage::Shift(){
  for(int i=1;i<(int)Fields.size();i++){
    Fields[0].Fields[i-1] = Fields[0].Fields[i];
  }
  Fields[0].Fields.pop_back();
}

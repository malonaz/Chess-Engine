// -*- C++ -*-
#include "bishop.h"
#include "square.h"
#include "utils.h"


bool Bishop::move(Square* sqr_source_ptr, Square* sqr_dest_ptr){
  Square* path[8];

  if (!sqr_source_ptr->getPath(sqr_dest_ptr, path, id))
    return false;

  for (int i = 1; path[i] != sqr_dest_ptr; i++)
    if (!path[i]->isEmpty())
      return false;
  
  return true;
  
}
  

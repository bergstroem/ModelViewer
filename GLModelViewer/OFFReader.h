//
//  OFFReader.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-22.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_OFFReader_h
#define ModelViewer_OFFReader_h

#include <istream>
#include "Mesh.h"

namespace OFFReader {
    Mesh read(std::istream& stream);
}

#endif

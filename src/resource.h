//
//  resource.h
//  Mandelbrot
//
//  Created by Kevin Hoàng on 10.09.22.
//

#ifndef resource_h
#define resource_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Loads a file from the resources directory
FILE *load_resource_file(const char *filename, const char *mode);

#endif /* resource_h */

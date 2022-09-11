//
//  shader.h
//  Mandelbrot
//
//  Created by Kevin Hoàng on 09.09.22.
//

#ifndef shader_h
#define shader_h

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdlib.h>
#include <stdio.h>

#include "resource.h"

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif /* shader_h */

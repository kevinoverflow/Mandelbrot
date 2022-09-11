//
//  shader.c
//  Mandelbrot
//
//  Created by Kevin Hoàng on 09.09.22.
//

#include "shader.h"

GLuint LoadShaders(const char *vertex_file, const char *fragment_file)
{
    /* Create the shaders */
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    /* Read the Vertex Shader code from the file */
    FILE *VertexShaderFile = load_resource_file(vertex_file, "r");

    char *VertexShaderCode;
    long VertexShaderLenght;

    fseek(VertexShaderFile, 0, SEEK_END);
    VertexShaderLenght = ftell(VertexShaderFile);
    fseek(VertexShaderFile, 0, SEEK_SET);

    VertexShaderCode = malloc(VertexShaderLenght);
    if (!VertexShaderCode)
    {
        printf("Failed to create buffer\n");
        return -1;
    }

    fread(VertexShaderCode, 1, VertexShaderLenght, VertexShaderFile);
    fclose(VertexShaderFile);

    /* Read the Fragment Shader code from the file */
    FILE *FragmentShaderFile = load_resource_file(fragment_file, "r");

    char *FragmentShaderCode;
    long FragmentShaderLenght;

    fseek(FragmentShaderFile, 0, SEEK_END);
    FragmentShaderLenght = ftell(FragmentShaderFile);
    fseek(FragmentShaderFile, 0, SEEK_SET);

    FragmentShaderCode = malloc(FragmentShaderLenght);
    if (!FragmentShaderCode)
    {
        printf("Failed to create buffer\n");
        return -1;
    }

    fread(FragmentShaderCode, 1, FragmentShaderLenght, FragmentShaderFile);
    fclose(FragmentShaderFile);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    /* Compile Vertex Shader */
    printf("Compiling shader: %s\n", vertex_file);
    const char *VertexShaderPtr = VertexShaderCode;
    glShaderSource(VertexShaderId, 1, &VertexShaderPtr, NULL);
    glCompileShader(VertexShaderId);

    /* Check Vertex Shader */
    glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        char *ErrorMessage = malloc(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderId, InfoLogLength, NULL, ErrorMessage);
        printf("%s\n", ErrorMessage);
    }

    /* Compile Fragment Shader */
    printf("Compiling shader: %s\n", fragment_file);
    const char *FragmentShaderPtr = FragmentShaderCode;
    glShaderSource(FragmentShaderId, 1, &FragmentShaderPtr, NULL);
    glCompileShader(FragmentShaderId);

    glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        char *ErrorMessage = malloc(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderId, InfoLogLength, NULL, ErrorMessage);
        printf("%s\n", ErrorMessage);
    }

    /* Link the program */
    printf("Linking program\n");
    GLuint ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);

    /* Check the program */
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &Result);
    if (InfoLogLength > 0)
    {
        char *ErrorMessage = malloc(InfoLogLength + 1);
        glGetShaderInfoLog(ProgramId, InfoLogLength, NULL, ErrorMessage);
        printf("%s\n", ErrorMessage);
    }

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);

    return ProgramId;
}

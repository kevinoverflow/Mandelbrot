#ifndef MB_SHADER_H
#define MB_SHADER_H

#include "GL/glew.h"

class Shader {
public:
	void init();

	void load(GLenum shaderType, const char* shaderFile);

	void link();

	void attach();

	void detach();

	void destroy();

	GLint getUniformLocation(const char* name);

	void setUniform(const char* name, GLfloat v0);

	void setUniform(const char* name, GLfloat v0, GLfloat v1);

	void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2);

	void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

private:
	GLuint program;
};

#endif  // MB_SHADER_H
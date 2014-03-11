#include "shader.h"
#include <algorithm>


Shader::Shader()
{
	pos_loc = -1;
	color_loc = -1;
	texcoord_loc = -1;
	normal_loc = -1;
	matrix_loc = -1;
	sample_loc= -1;
}



char* Shader::file_read(const char* filename)
{
	FILE* input = fopen(filename, "rb");
	if(input == NULL) return NULL;

	if(fseek(input, 0, SEEK_END) == -1) return NULL;
	long size = ftell(input);
	if(size == -1) return NULL; 
	if(fseek(input, 0, SEEK_SET) == -1) return NULL;

	char *content = (char*) malloc ((size_t)size+1);

	fread(content, 1, (size_t)size, input);
	if(ferror(input)){
		free(content);
		return NULL;
	}

	fclose(input);
	content[size] = '\0';
	return content;
}

GLuint Shader::CreateShader(GLenum shaderType, const char* fileData)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &fileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(shaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

void Shader::CompileProgram()
{
		this->Program = glCreateProgram();
	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(this->Program, shaderList[iLoop]);

	glLinkProgram(Program);

	GLint status;
	glGetProgramiv (this->Program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->Program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->Program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(this->Program, shaderList[iLoop]);
}

void Shader::add(GLenum shaderType, const char* filename)
{
	shaderList.push_back(CreateShader(shaderType, file_read(filename)));
}

void Shader::deleteShaders()
{
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

void Shader::useProgram()
{
	glUseProgram(this->Program);
}

GLint Shader::getUniformLoc(GLchar *varname)
{
	return glGetUniformLocation(this->Program, varname);
}

GLint Shader::getAttributeLocation(std::string varName)
{
	return glGetAttribLocation(this->Program, varName.c_str());
	
}


void Shader::initShaderVars()
{

	pos_loc = getAttributeLocation("position");
	color_loc = getAttributeLocation("color");
	texcoord_loc = getAttributeLocation("texcoord");
	normal_loc = getAttributeLocation("normal");
	matrix_loc = getUniformLoc("projection");
	sample_loc= getUniformLoc("gtexture");
}

void Shader::enableShaderAttribs()
{
	glEnableVertexAttribArray(pos_loc);
	glEnableVertexAttribArray(color_loc);
	glEnableVertexAttribArray(normal_loc);
	glEnableVertexAttribArray(texcoord_loc);
}

void Shader::disableShaderAttribs()
{
	glDisableVertexAttribArray(pos_loc);
	glDisableVertexAttribArray(color_loc);
	glDisableVertexAttribArray(normal_loc);
	glDisableVertexAttribArray(texcoord_loc);
}

int Shader::positionAttrib()
{
	return pos_loc;
}
int Shader::colorAttrib()
{
	return color_loc;
}
int Shader::normalAttrib()
{
	return normal_loc;
}
int Shader::texcoordAttrib()
{
	return texcoord_loc;
}
int Shader::matrixUniform()
{
	return matrix_loc;
}
int Shader::sampleUniform()
{
	return sample_loc;
}
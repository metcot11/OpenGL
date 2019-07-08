#include "Shader.h"

#include <iostream>
#include <fstream>
//library to open files using c++
#include <string>
#include <sstream>

#include "Renderer.h"

// Compiling a shader from a external source

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = PassShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID)); // moment that the shader is bound
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	//                (address of the uniform, the variables of the vec4 object)

}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));

}


ShaderProgramSource Shader::PassShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	//opens the file

	enum class Shader_Type { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
	// Creating a enum to set the mode of the Shader

	std::stringstream ss[2];
	// To store the two shaders that are inside of the Basic file

	Shader_Type type = Shader_Type::NONE;
	//seting the default state to be none

	// going through the lines of the .txt file 
	std::string line;
	while (getline(stream, line)) //while we don't run out of lines
	{
		if (line.find("#shader") != std::string::npos) // checks to see if the line contains the string "shader"
		{                                     //npos is 'invalid string position'
			if (line.find("vertex") != std::string::npos)
			{
				//Set the mode to vertex
				type = Shader_Type::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				//Set the mode to fragment
				type = Shader_Type::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}                 // add the '\n' character to the end of the line 
	}
	return { ss[0].str(), ss[1].str() }; // returning the shaders as ShaderProgramSource structs
}


//Wrinting Shaders
unsigned int Shader::CompileShader(unsigned int type, const std::string source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	// Converting a C++ string(source) to a raw sting(src). Returns a pointer to the beginning of the source string 
	//const char* src = &source[0]; It does the same

	// Specifies the source of the shader
	glShaderSource(id, 1, &src, nullptr);
	//            (shader,count, string, length)
	/*
	Shader :: Specifies the handle of the shader object whose source code is to be replaced.
	Count :: How many source codes are being specified
	String :: Pointer to the pointer to the string
	Length :: Specifies an array of string lengths
	*/

	glCompileShader(id);

	// display status in case of error
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//char message[length]; can not allocate char array with a variable 
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "compile shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string fragmentShader)
{
	unsigned int program = glCreateProgram();
	//Returns a unsigned int
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	//Creating the vertex shader
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	//Creating the fragment shader

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	// Attaching the shaders to the program 
	glLinkProgram(program);
	// Linking
	glValidateProgram(program);
	// Validating

	// As the shaders were already stored inside the program executable it's recomendable
	// to delete the intermidiant shaders 
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UnLocationCache.find(name) != m_UnLocationCache.end())
		return m_UnLocationCache[name];
	//Defining the uniform
	// Variables stored in the CPU that can be used by the GPU
	GLCall( int location = glGetUniformLocation(m_RendererID, name.c_str()));
	// returns the location of the uniform (Program, Uniform)
	if (location == -1)
		std::cout << "Warning uniform " << name << " doesn't exist!" << std::endl;

	m_UnLocationCache[name] = location;
	 return location;
}

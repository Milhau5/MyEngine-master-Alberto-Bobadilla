/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __MEDEFINITIONS_H_
#define __MEDEFINITIONS_H_

// Include standard headers
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>

#ifdef EXP_STL
#	define MyEngineDLL __declspec(dllexport)
#	define EXPIMP_TEMPLATE
#else
#	define MyEngineDLL __declspec(dllimport)
#	define EXPIMP_TEMPLATE extern
#endif

namespace MyEngine
{
typedef std::string String;
typedef glm::vec2 vector2;
typedef glm::vec3 vector3;
typedef glm::vec4 vector4;
typedef glm::mat4 matrix4;
typedef unsigned int uint;
typedef glm::quat quaternion;

#define SafeDelete(p){ if(p) { delete p; p = nullptr; } }
////https://stackoverflow.com/questions/10240161/reason-to-pass-a-pointer-by-reference-in-c/20188970#20188970
//template<typename T>
//void SafeDelete(T*& p)
//{
//	if(p != nullptr)
//	{
//		delete p;
//		p = nullptr;
//	} 
//}
#define PI 3.14159265358979323846
#define IDENTITY 1.0f
#define MEIDENTITY matrix4(1.0f)

#define MEBLACK vector3(0.0f, 0.0f, 0.0f)
#define MEWHITE vector3(1.0f, 1.0f, 1.0f)
#define MEGRAY vector3(0.3f, 0.3f, 0.3f)

#define MERED vector3(1.0f, 0.0f, 0.0f)
#define MEMAGENTA vector3(1.0f, 0.0f, 1.0f)
#define MEBROWN vector3(0.6f,0.3f,0.0f)

#define MEGREEN vector3(0.0f, 1.0f, 0.0f)
#define MEGREENDARK vector3(0.0f, 5.0f, 0.0f)
#define MELIME vector3(0.33f,0.90f,0.33f)

#define MEBLUE vector3(0.0f, 0.0f, 1.0f)
#define MECYAN vector3(0.0f,1.0f,1.0f)

#define MEYELLOW vector3(1.0f, 1.0f, 0.0f)
#define MEORANGE vector3(1.0f,0.5f,0.0f)
#define MEVIOLET vector3(0.54f,0.16f,0.88f)
#define MEPURPLE vector3(0.50f,0.0f,0.50f)

#define MEDEFAULT vector3(-1.0f, -1.0f, -1.0f)

#define MEAXISX vector3(1.0f, 0.0f, 0.0f)
#define MEAXISY vector3(0.0f, 1.0f, 0.0f)
#define MEAXISZ vector3(0.0f, 0.0f, 1.0f)

//-----------------------------------------------------------------------------------------------------------
// Enumerations
//-----------------------------------------------------------------------------------------------------------
enum MEOptions
{
	NO = 0,
	YES = 1,
	ASK = 2,
	OPENGL2X = 3,
	OPENGL3X = 4,
	DIRECTX = 5
};
enum MEErrors
{
	ERROR_FREE = 0,
	ERROR_FILE_MISSING = 1,
	ERROR_CONTEXT = 2,
	ERROR_MEMORY = 3,
	ERROR_GENERAL = 4,
	ERROR_NAME = 5,
	ERROR_NOT_INITIALIZED = 6,
	ERROR_FILE = 7,
	DONE = 8,
	RUNNING = 9,
};
enum MEAXIS
{
	NONE = 0,
	XY = 1,
	XZ = 2,
	YZ = 4,
};
enum MERENDER
{
	SOLID = 1,
	WIRE = 2,
};


}

#endif //__MEDEFINITIONS_H__
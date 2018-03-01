#pragma once
#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdio.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define BUFFER_OFFSET(i) ((char *)NULL + (i)) 
#define DEBUG(x,y) std::cout<<x<<"\t"<<y<<std::endl;
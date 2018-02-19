#pragma once
#include <iostream>
#define DEBUG(x,y) {std::cout<<x<<"\t"<<y<<"\n";}
#define SAFE_DELETE(x) { if(x != nullptr) delete x;}
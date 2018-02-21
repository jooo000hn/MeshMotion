#include "GlobalVariables.h"

GlobalVariables *GlobalVariables::_instance = nullptr;

GlobalVariables::GlobalVariables()
{
	group1Dir = ".\\Data\\Group1\\";
	testASF = "01.asf";
	testAMC = "01_01.amc";

	group2Dir = ".\\Data\\Group2\\";
	testASF2 = "02.asf";
}
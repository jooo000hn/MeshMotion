#include "GlobalVariables.h"

GlobalVariables *GlobalVariables::_instance = nullptr;

GlobalVariables::GlobalVariables()
{
	dataDir = ".\\Data\\Group1\\";
	testASF = "01.asf";
	testAMC = "01_01.amc";

}
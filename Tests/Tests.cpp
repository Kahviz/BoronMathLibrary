#include "Tests.h"

#include "BoronMath.h"

#include "BoronTest.h"

void Tests::doTests() {
	//Variables
    GPUInt3 gpuInt3_1{1,2,3};
    GPUInt3 gpuInt3_2{2,2,2};

	//GPU
    EXPECTVALUE(gpuInt3_1.x, 1);
    EXPECTVALUE(gpuInt3_1.y, 2);
    EXPECTVALUE(gpuInt3_1.z, 3);

    EXPECTVALUE(gpuInt3_1.x + gpuInt3_2.x, 3);
    EXPECTVALUE(gpuInt3_1.y + gpuInt3_2.y, 4);
    EXPECTVALUE(gpuInt3_1.z + gpuInt3_2.z, 5);
}
cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BoronMathLibrary")

add_executable(BoronMathLibrary 
	#CPU
	BoronMathLibrary.cpp
	BoronMathLibrary.h
	BoronMath/BoronMath.h
	
	BoronMath/SIMD/Vector3/Vector3.h
	BoronMath/SIMD/Vector4/Vector4.h
	BoronMath/SIMD/Color255/Color255.h
	BoronMath/SIMD/Matrix4x4/Matrix4x4.h
	BoronMath/SIMD/Int2/Int2.h
	BoronMath/Variables.h

	#Functions
	BoronMath/SIMD/Functions/TransformVector.h
	BoronMath/SIMD/Functions/LoadVector.h
	BoronMath/SIMD/Functions/StoreComponent.h
	BoronMath/SIMD/Functions/TransformNormal.h
	BoronMath/SIMD/Functions/LoadInt.h
	BoronMath/SIMD/Functions/Matrix4x4Functions.h 
	BoronMath/SIMD/Functions/Utils.h

	#GPU
	BoronMath/GPU/GPUVector2/GPUVector2.h
	BoronMath/GPU/GPUInt3/GPUInt3.h
	BoronMath/GPU/GPUVector3/GPUVector3.h 
	BoronMath/GPU/GPUVector4/GPUVector4.h 
	BoronMath/GPU/GPUMatrix4x4/GPUMatrix4x4.h

	#Functions
	BoronMath/GPU/Functions/StoreGPUComponent.h
	BoronMath/GPU/Functions/LoadGPUInt.h 
	BoronMath/GPU/Functions/TransformGPUNormal.h
)

target_include_directories(BoronMathLibrary PRIVATE 
	../SIMD/
	BoronMath/
	GPU/
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BoronMathLibrary PROPERTY CXX_STANDARD 20)
endif()

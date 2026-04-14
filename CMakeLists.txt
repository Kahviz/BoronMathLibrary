cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("UntilitedMathLibrary")

add_executable(UntilitedMathLibrary 
	#CPU
	UntilitedMathLibrary.cpp
	UntilitedMathLibrary.h
	UntilitedMath/UntilitedMath.h

	UntilitedMath/SIMD/Vector3/Vector3.h
	UntilitedMath/SIMD/Vector4/Vector4.h
	UntilitedMath/SIMD/Color255/Color255.h
	UntilitedMath/SIMD/Matrix4x4/Matrix4x4.h
	UntilitedMath/SIMD/Int2/Int2.h
	UntilitedMath/Variables.h

	#Functions
	UntilitedMath/SIMD/Functions/TransformVector.h
	UntilitedMath/SIMD/Functions/LoadVector.h
	UntilitedMath/SIMD/Functions/StoreComponent.h
	UntilitedMath/SIMD/Functions/TransformNormal.h
	UntilitedMath/SIMD/Functions/LoadInt.h
	UntilitedMath/SIMD/Functions/Matrix4x4Functions.h 
	UntilitedMath/SIMD/Functions/Utils.h

	#GPU
	UntilitedMath/GPU/GPUVector2/GPUVector2.h
	UntilitedMath/GPU/GPUInt3/GPUInt3.h
	UntilitedMath/GPU/GPUVector3/GPUVector3.h 
	UntilitedMath/GPU/GPUVector4/GPUVector4.h 
	UntilitedMath/GPU/GPUMatrix4x4/GPUMatrix4x4.h

	#Functions
	UntilitedMath/GPU/Functions/StoreGPUComponent.h
	UntilitedMath/GPU/Functions/LoadGPUInt.h UntilitedMath/GPU/Functions/TransformGPUNormal.h
)

target_include_directories(UntilitedMathLibrary PRIVATE 
	../SIMD/
	UntilitedMath/
	GPU/
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UntilitedMathLibrary PROPERTY CXX_STANDARD 20)
endif()

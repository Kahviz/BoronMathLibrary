# CMakeList.txt : CMake project for UntilitedMathLibrary, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("UntilitedMathLibrary")

add_executable(UntilitedMathLibrary 
	UntilitedMathLibrary.cpp
	UntilitedMathLibrary.h
	UntilitedMath/UntilitedMath.h
	UntilitedMath/SIMD/Vector3/Vector3.h
	UntilitedMath/SIMD/Vector4/Vector4.h
	UntilitedMath/SIMD/INT3/Int3.h
	UntilitedMath/SIMD/Color255/Color255.h
	UntilitedMath/SIMD/Matrix4x4/Matrix4x4.h
	UntilitedMath/Functions/Matrix4x4Functions.h 
	UntilitedMath/Functions/Utils.h
	UntilitedMath/Variables.h
	UntilitedMath/Functions/StoreComponent.h
	UntilitedMath/Functions/TransformNormal.h
	UntilitedMath/Functions/LoadInt.h
	UntilitedMath/SIMD/Int2/Int2.h
	UntilitedMath/Functions/TransformVector.h
	UntilitedMath/Functions/LoadVector.h
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UntilitedMathLibrary PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

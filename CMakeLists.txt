cmake_minimum_required(VERSION 2.6)
PROJECT(TestOscpack)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# separate versions of NetworkingUtils.cpp and UdpSocket.cpp are provided for Win32 and POSIX
# the IpSystemTypePath selects the correct ones based on the current platform

IF(WIN32)
 set(IpSystemTypePath oscpack/ip/win32)
 set(LIBS ${LIBS} Ws2_32 winmm)
ELSE(WIN32)
 set(IpSystemTypePath oscpack/ip/posix)
ENDIF(WIN32)
if(UNIX AND NOT APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

ADD_LIBRARY(oscpack

oscpack/ip/IpEndpointName.h
oscpack/ip/IpEndpointName.cpp

oscpack/ip/NetworkingUtils.h
${IpSystemTypePath}/NetworkingUtils.cpp
${IpSystemTypePath}/NetworkingUtils.h

oscpack/ip/UdpSocket.h
oscpack/ip/AbstractUdpSocket.h
${IpSystemTypePath}/UdpSocket.cpp
${IpSystemTypePath}/UdpSocket.h

oscpack/ip/PacketListener.h
oscpack/ip/TimerListener.h

oscpack/osc/SmallString.h
oscpack/osc/OscTypes.h
oscpack/osc/OscTypesTraits.h
oscpack/osc/OscDebug.h
oscpack/osc/OscTypes.cpp
oscpack/osc/OscHostEndianness.h
oscpack/osc/OscException.h
oscpack/osc/OscPacketListener.h
oscpack/osc/MessageMappingOscPacketListener.h
oscpack/osc/OscReceivedElements.h
oscpack/osc/OscReceivedElements.cpp
oscpack/osc/OscPrintReceivedElements.h
oscpack/osc/OscPrintReceivedElements.cpp
oscpack/osc/OscOutboundPacketStream.h
oscpack/osc/OscOutboundPacketStream.cpp
oscpack/osc/OscUtilities.h

)

set_target_properties(oscpack PROPERTIES CXX_STANDARD 14)
target_include_directories(oscpack PUBLIC .)


ADD_EXECUTABLE(OscDump examples/OscDump.cpp)
TARGET_LINK_LIBRARIES(OscDump oscpack ${LIBS})
target_include_directories(OscDump PUBLIC .)
set_target_properties(OscDump PROPERTIES CXX_STANDARD 14)
if(OSCPACK_BUILD_EXAMPLES)
ADD_EXECUTABLE(OscUnitTests tests/OscUnitTests.cpp)
TARGET_LINK_LIBRARIES(OscUnitTests oscpack ${LIBS})

ADD_EXECUTABLE(OscSendTests tests/OscSendTests.cpp)
TARGET_LINK_LIBRARIES(OscSendTests oscpack ${LIBS})

ADD_EXECUTABLE(OscReceiveTest tests/OscReceiveTest.cpp)
TARGET_LINK_LIBRARIES(OscReceiveTest oscpack ${LIBS})


ADD_EXECUTABLE(OscDump examples/OscDump.cpp)
TARGET_LINK_LIBRARIES(OscDump oscpack ${LIBS})

ADD_EXECUTABLE(SimpleReceive examples/SimpleReceive.cpp)
TARGET_LINK_LIBRARIES(SimpleReceive oscpack ${LIBS})

ADD_EXECUTABLE(SimpleSend examples/SimpleSend.cpp)
TARGET_LINK_LIBRARIES(SimpleSend oscpack ${LIBS})
endif()

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

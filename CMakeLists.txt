CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )
PROJECT ( AchSplit )

SET ( VERSION_MAJOR "1" )
SET ( VERSION_MINOR "0" )
SET ( VERSION_PATCH "0" )

INCLUDE_DIRECTORIES ("include")
FILE ( GLOB SRC "src/*.cpp" )


IF ( WIN32 )

        SET ( CMAKE_CXX_FLAGS  "-DSFML_STATIC -s" )
        SET ( CMAKE_EXE_LINKER_FLAGS  "-mwindows -static-libgcc -static-libstdc++ -static -Wl,-Bstatic" )
        SET ( CMAKE_LINK_LIBS sfml-audio-s sfml-graphics-s sfml-window-s sfml-system-s winmm opengl32 gdi32 freetype glew jpeg opengl32 openal32 pthread FLAC vorbisfile vorbisenc vorbis ogg m jansson )

ELSEIF ( UNIX )

        SET ( CMAKE_RESOURCE  "" )
        SET ( CMAKE_CXX_FLAGS  "-s" )
        SET ( CMAKE_EXE_LINKER_FLAGS  "-static-libgcc -static-libstdc++" )
        SET ( CMAKE_LINK_LIBS sfml-audio sfml-graphics sfml-window sfml-system m jansson )

ENDIF ( )


ADD_EXECUTABLE ( AchSplit ${SRC} )
TARGET_LINK_LIBRARIES ( AchSplit  ${CMAKE_LINK_LIBS} )

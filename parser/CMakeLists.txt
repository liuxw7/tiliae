CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
PROJECT (parser)
SET (CMAKE_VERBOSE_MAKEFILE 1)

FIND_PROGRAM (LLVM_CONFIG_PATH NAME "llvm-config" HINTS "${CLANG_ROOT}/bin")

IF (NOT LLVM_CONFIG_PATH)
        MESSAGE(FATAL_ERROR "llvm-config not found -- ${LLVM_CONFIG_PATH}")
ENDIF()

MESSAGE (STATUS "Found LLVM_CONFIG_PATH as ${LLVM_CONFIG_PATH}")


# This function saves the output of the llvm-config command with the given
# switch to the variable named VARNAME.
#
# Example usage: llvm_config(LLVM_CXXFLAGS "--cxxflags")
function(llvm_config VARNAME switch)
        set(CONFIG_COMMAND "${LLVM_CONFIG_PATH}" "${switch}")

        execute_process(
                COMMAND ${CONFIG_COMMAND}
                RESULT_VARIABLE HAD_ERROR
                OUTPUT_VARIABLE CONFIG_OUTPUT
        )

        if (HAD_ERROR)
                string(REPLACE ";" " " CONFIG_COMMAND_STR "${CONFIG_COMMAND}")
                message(STATUS "${CONFIG_COMMAND_STR}")
                message(FATAL_ERROR "llvm-config failed with status ${HAD_ERROR}")
        endif()

        # replace linebreaks with semicolon
        string (REGEX REPLACE "[ \t]*[\r\n]+[ \t]*" ";" CONFIG_OUTPUT ${CONFIG_OUTPUT})

        # make result available outside
        set(${VARNAME} ${CONFIG_OUTPUT} PARENT_SCOPE)

        # Optionally output the configured value
        message(STATUS "llvm_config(${VARNAME})=>${CONFIG_OUTPUT}")

        # cleanup
        unset(CONFIG_COMMAND)
endfunction(llvm_config)


llvm_config(LLVM_CXXFLAGS "--cxxflags")
llvm_config(LLVM_LDFLAGS "--ldflags")
llvm_config(LLVM_LIBS "--libs")
llvm_config(LLVM_LIBDIR "--libdir")
llvm_config(LLVM_INCLUDE_DIR "--includedir")
llvm_config(LLVM_SYSTEM_LIBS "--system-libs")


add_definitions(${LLVM_CXXFLAGS})
add_definitions (-std=c++11)
include_directories(${LLVM_INCLUDE_DIR})
link_directories(${LLVM_LIBDIR})

# TODO
include_directories("/home/iwasz/workspace/llvm/tools/clang/include")
include_directories("/home/iwasz/workspace/llvm/build/tools/clang/include/")


add_executable (${CMAKE_PROJECT_NAME} main.cc)

target_link_libraries(${CMAKE_PROJECT_NAME}
        ${LLVM_LDFLAGS}
        clangAnalysis
        clangApplyReplacements
        clangARCMigrate
        clangAST
        clangASTMatchers
        clangBasic
        clangCodeGen
        clangDriver
        clangDynamicASTMatchers
        clangEdit
        clangFormat
        clangFrontend
        clangFrontendTool
        clangIndex
        clangLex
        clangParse
        clangQuery
        clangRename
        clangRewrite
        clangRewriteFrontend
        clangSema
        clangSerialization
        clangStaticAnalyzerCheckers
        clangStaticAnalyzerCore
        clangStaticAnalyzerFrontend
        clangTidy
        clangTidyGoogleModule
        clangTidyLLVMModule
        clangTidyMiscModule
        clangTidyModernizeModule
        clangTidyReadabilityModule
        clangTidyUtils
        clangTooling
        clangToolingCore
        ${LLVM_LIBS}
        ${Boost_LIBRARIES}
        rt
        dl
        tinfo
        pthread
        z
        m
    )

#target_link_libraries(${CMAKE_PROJECT_NAME}
#        ${LLVM_LDFLAGS}
#        clang
#        ${LLVM_LIBS}
#        ${Boost_LIBRARIES}
#    )









#SET (LLVM_USED_LIBS clangTooling)


##target_link_libraries(decl
##  clangBasic
##  clangCodeGen
##  clangDriver
##  clangFrontend
##  clangTooling
##  )
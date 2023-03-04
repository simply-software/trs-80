#! /bin/bash

# Given:
#   $1 = a target path, which begins with the path in $2
#   $2 = a base path
#
# Returns a string which is $1's path relative to $2.
#
# Example:
#    relative_path "/home/Jay/projects/src/common/algorithms" "/home/Jay/projects/src"
#
#    returns "common/algorithms"
#
relative_path() {
	RESULT=$(echo ${2} | sed "s|${1}||")
	echo ${RESULT:1}
}

# Compiles each .cpp in the CURRENT WORKING DIRECTORY into a separate
# executable and puts the resulting binaries in the "obj" subdirectory.
# Upon successful compilation, runs each executable until either an
# executable returns non-zero or all executables have been run.
#
# Returns 1 if all .cpp files compile successfully and all binaries
# return 0 (success), otherwise returns 0.  Trivially returns 0 if
# there are no .cpp files in the directory.
#
compile_and_run_tests() {
    mkdir obj 2>/dev/null
    rm obj/* 2>/dev/null
	LIBNAME=$(basename $(dirname $PWD))
	REL_PATH=$(relative_path ${RUNDIR} ${PWD})
	echo "${1}Running tests in ${REL_PATH}..."
    for FILE in `find . -maxdepth 1 -name "*.cpp"`; do
        FILE=$(basename ${FILE})
        OUT_FILE=$(echo ${FILE} | sed 's/.cpp/.exe/')

        echo "${1}  Compiling $FILE..."
        g++ ${FILE} ${CCFLAGS} -o obj/${OUT_FILE} ../obj/lib${LIBNAME}.a
        if [ $? -eq 1 ]; then
            return 0
        fi
    done

    cd obj
    for FILE in `find . -maxdepth 1 -name "*.exe"`; do
		TESTNAME=`echo $(basename $FILE) | sed s/\.exe//`
        echo "${1}  Running $TESTNAME..."
        ./${FILE}
        if [ $? -ne 0 ]; then
			cd ..
            return 0
        fi
    done
    cd ..
    return 1
}

# Compiles -- but does NOT link -- all .cpp files in the CURRENT WORKING
# DIRECTORY.  All object files are placed in the "obj" subdirectory.
#
# Returns 1 on success, 0 on failure.
#
# Uses CCFLAGS environment variable as additional parameters to the
# compilation step.
#
compile() {
	if [ "$(find . -maxdepth 1 -name "*.cpp")" == "" ]; then
		return 1
	fi

    mkdir obj 2>/dev/null
    rm obj/* 2>/dev/null
    for FILE in `find . -maxdepth 1 -name "*.cpp"`; do
        FILE=$(basename ${FILE})
        OUT_FILE=$(echo ${FILE} | sed 's/.cpp/.o/')

        echo "${1}Compiling $FILE..."
        g++ -c ${FILE} ${CCFLAGS} -o obj/${OUT_FILE}
        if [ $? -eq 1 ]; then
            return 0
        fi
    done
    return 1
}

# Links all .o files in the "obj" subdirectory of the CURRENT WORKING
# DIRECTORY to a static library.  The library is named "lib<cwd_name>.a"
# and is placed in the "obj" subdirectory.
#
# Returns 1 on success, 0 on failure.
#
# Uses LINKFLAGS environment variable as additional parameters to the
# linker step.
#
link_library() {
    if [ -d obj ]; then
        OBJ_FILES=$(find obj -name "*.o")
        if [ "${OBJ_FILES}" != "" ]; then
            LIBNAME=lib$(basename $PWD).a

            echo "${1}Linking ${LIBNAME}..."
            ar -cvq obj/${LIBNAME} ${OBJ_FILES} >/dev/null
            if [ $? -eq 1 ]; then
                return 0
            fi
        fi
    fi
    return 1
}

# Makes doxygen documentation in the "docs" subdirectory of the
# CURRENT WORKING DIRECTORY if there is a doxygen config file in
# the current working directory, otherwise does nothing.
#
# The "docs" subdirectory is created if it does not exist.
#
# Returns 1 on success, 0 on failure.  No doxygen file present
# is considered success by default.
#
make_documentation() {
    DOXY_FILE=$(find . -maxdepth 1 -name "*.doxygen")
    if [ "$DOXY_FILE" = "" ]; then
        return 1
    fi

    DOC_NAME=$(echo $(basename ${DOXY_FILE}) | sed "s/.doxygen//")
    echo "${1}Making documentation for ${DOC_NAME}..."
    mkdir docs 2>/dev/null
    doxygen $DOXY_FILE >/dev/null
    if [ $? -eq 1 ]; then
        return 0
    fi
    return 1
}

# Recursively performs all build operations first in all
# subdirectories of the current working directory, and lastly
# in the current working directory itself.
#
# Currently, "all build operations" means:
#   * Making documentation, if a doxygen config file is present;
#   * Compiling all .cpp files to .o files;
#   * Building a static library (.a file) from all .o files
#
# Returns 1 on success, 0 on failure.
process_directory() {
    for DIR in `ls`; do
        if [[ -d ${DIR} && ${DIR} != "obj" && ${DIR} != "docs" && ${DIR} != "test" ]]; then
            local CURRENT_DIR=${PWD}
            cd ${DIR}
            process_directory "$1  "
            RC=$?
            cd ${CURRENT_DIR}
            if [ ${RC} -eq 0 ]; then
                return 0
            fi
        fi
    done

	if [ "$(basename $PWD)" != "test" ]; then
		REL_PATH=$(relative_path ${RUNDIR} ${PWD})
	    echo "${1}Building ${REL_PATH}..."
	    make_documentation "$1  "
    	if [ $? -eq 1 ]; then
        	compile "$1  "
	        if [ $? -eq 1 ]; then
    	        link_library "$1  "
        	fi
	    fi
	fi
    return $?
}

# Recursively finds, builds, and runs all tests in all subdirectories
# of the current working directory, and lastly in the current
# working directory itself.
#
# Returns 1 if all tests pass (or no tests were found), or 0 if at
# least one test fails.
run_all_tests() {
	ALL_FILES=$(ls)
    for DIR in ${ALL_FILES}; do
        if [[ -d ${DIR} && ${DIR} != "obj" && ${DIR} != "docs" ]]; then
            local CURRENT_DIR=${PWD}
            cd ${DIR}
            run_all_tests "$1  "
            RC=$?
            cd ${CURRENT_DIR}
            if [ ${RC} -eq 0 ]; then
                return 0
            fi
        fi
    done

    if [ "$(basename ${PWD})" = "test" ]; then
        compile_and_run_tests "$1"
        if [ $? -eq 0 ]; then
            return 0
        fi
    fi
    return 1
}

BASEDIR="/home/Jay/trs-80/src"
RUNDIR=${PWD}
CCFLAGS="-ggdb3 -std=c++17 -I ${BASEDIR}"
process_directory ""
run_all_tests ""
exit $?

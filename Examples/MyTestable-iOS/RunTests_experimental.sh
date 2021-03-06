#!/bin/sh

# If we aren't running from the command line, then exit
if [ "$GHUNIT_CLI" = "" ] && [ "$GHUNIT_AUTORUN" = "" ]; then
  exit 0
fi

export DYLD_ROOT_PATH="$SDKROOT"
export DYLD_FRAMEWORK_PATH="$CONFIGURATION_BUILD_DIR"
export IPHONE_SIMULATOR_ROOT="$SDKROOT"

export MallocScribble=YES
export MallocPreScribble=YES
export MallocGuardEdges=YES
export MallocStackLogging=YES
export MallocStackLoggingNoCompact=YES

export NSDebugEnabled=YES
export NSZombieEnabled=YES
export NSDeallocateZombies=NO
export NSHangOnUncaughtException=YES
export NSAutoreleaseFreedObjectCheckEnabled=YES

export DYLD_FRAMEWORK_PATH="$CONFIGURATION_BUILD_DIR"

TEST_TARGET_EXECUTABLE_PATH="$TARGET_BUILD_DIR/$EXECUTABLE_PATH"

if [ ! -e "$TEST_TARGET_EXECUTABLE_PATH" ]; then
  echo ""
  echo "  ------------------------------------------------------------------------"
  echo "  Missing executable path: "
  echo "     $TEST_TARGET_EXECUTABLE_PATH."
  echo "  The product may have failed to build or could have an old xcodebuild in your path (from 3.x instead of 4.x)."
  echo "  ------------------------------------------------------------------------"
  echo ""
  exit 1
fi

# From $IPHONE_SIMULATOR_ROOT we figure out what the path to the simulator binary is
# /Developer4/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator4.3.sdk
# /Developer/Platforms/iPhoneSimulator.platform/Developer/Applications/iPhone\ Simulator.app/Contents/MacOS/iPhone\ Simulator 

export IPHONE_SIMULATOR_APPLICATION="$IPHONE_SIMULATOR_ROOT/../../Applications/iPhone Simulator.app/Contents/MacOS/iPhone Simulator"

"$IPHONE_SIMULATOR_APPLICATION" -SimulateApplication $TEST_TARGET_EXECUTABLE_PATH
#RUN_CMD="$IPHONE_SIMULATOR_APPLICATION -SimulateApplication $TEST_TARGET_EXECUTABLE_PATH"

#RUN_CMD="$TEST_TARGET_EXECUTABLE_PATH -RegisterForSystemEvents"

#echo "Running: $RUN_CMD"
#"$RUN_CMD"
RETVAL=$?

unset DYLD_ROOT_PATH
unset DYLD_FRAMEWORK_PATH
unset IPHONE_SIMULATOR_ROOT

if [ -n "$WRITE_JUNIT_XML" ]; then
  MY_TMPDIR=`/usr/bin/getconf DARWIN_USER_TEMP_DIR`
  RESULTS_DIR="${MY_TMPDIR}test-results"

  if [ -d "$RESULTS_DIR" ]; then
	`$CP -r "$RESULTS_DIR" "$BUILD_DIR" && rm -r "$RESULTS_DIR"`
  fi
fi

exit $RETVAL

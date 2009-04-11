//
//  GHTestSuite.h
//  GHUnit
//
//  Created by Gabriel Handford on 1/25/09.
//  Copyright 2009. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//

#import "GHTestGroup.h"

/*!
 Test suite is an alias for test group.
 
 A test case is an instance of a test case class with test methods.
 A test is a id<GHTest> which represents a target and a selector.
 A test group is a collection of tests; A collection of id<GHTest> (GHTest or GHTestGroup).
 
 For example, if you have 2 test cases, GHTestCase1 (with some test methods) and GHTestCase2 (with some test methods), 
 your test suite might look like:
 
"Tests" (GHTestSuite)
	GHTestGroup (collection of tests from GHTestCase1)
		- (void)testA1 (GHTest with target GHTestCase1 + testA1)
		- (void)testA2 (GHTest with target GHTestCase1 + testA2)
	GHTestGroup (collection of tests from GHTestCase2)
		- (void)testB1; (GHTest with target GHTestCase2 + testB1)
		- (void)testB2; (GHTest with target GHTestCase2 + testB2)  
 
 */
@interface GHTestSuite : GHTestGroup {

}

/*! 
 Create test suite with test cases.
 @param name Label to give the suite
 @param testCases Array of init'ed test case classes
 @param delegate
 */
- (id)initWithName:(NSString *)name testCases:(NSArray *)testCases delegate:(id<GHTestDelegate>)delegate;

/*! 
 Create test suite with tests.
 @param name Label to give the suite
 @param tests Array of id<GHTest> 
 @param delegate
 */
- (id)initWithName:(NSString *)name tests:(NSArray/*of id<GHTest>*/ *)tests delegate:(id<GHTestDelegate>)delegate;

/*!
 Creates a suite of all tests.
 Will load all classes that subclass from GHTestCase, SenTestCase or GTMTestCase (or register test case class).
 */
+ (GHTestSuite *)allTests;

/*!
 Create test suite of all tests.
 @param flatten If flatten is YES, returns a test suite with all tests grouped in a single suite.
 */
+ (GHTestSuite *)allTests:(BOOL)flatten;

/*!
 Create suite of tests with filter.
 This is useful for running a single test or all tests in a single test case.
 
 For example,
 'GHSlowTest' -- Runs all test method in GHSlowTest
 'GHSlowTest/testSlowA -- Only runs the test method testSlowA in GHSlowTest
 
 @param testFilter Test filter
 @result Runner
 */
+ (GHTestSuite *)suiteWithTestFilter:(NSString *)testFilter;

@end
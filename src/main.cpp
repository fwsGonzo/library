/**
 * Library tests
 * 
**/
extern void test_maths();
extern void test_compression();
extern void test_sockets();
extern void test_opengl_support();
extern void test_opengl_window();
extern void test_opengl_bonerig();

#include <iostream>

#include "dequeue.hpp"
#include <deque>
#include <cassert>

class TestClass
{
public:
	TestClass()
	{
		//std::cout << "TestClass constructor" << std::endl;
	}
	~TestClass()
	{
		//std::cout << "TestClass destructor" << std::endl;
	}
};

int main(void)
{
	test::deque<TestClass> testClass;
	
	for (int i = 0; i < 20; i++)
	{
		testClass.emplace_back();
	}
	std::cout << "SIZE:    " << testClass.size() << std::endl;
	
	/// testing deque<int>
	test::deque<int> testInt;
	
	/// testing back
	std::cout << "Pushing back to testInt - size: " << testInt.size() << std::endl;
	for (int i = 0; i < 20; i++)
	{
		testInt.push_back(i);
    assert(testInt.back() == i);
	}
	std::cout << "New size: " << testInt.size() << std::endl;
	
	std::cout << "Popping from back from testInt - size: " << testInt.size() << std::endl;
	while (testInt.size())
		testInt.pop_back();
	std::cout << "New size: " << testInt.size() << std::endl;
	
	/// testing front
	std::cout << "Testing push_front" << std::endl;
	
	for (int i = 0; i < 20; i++)
	{
		testInt.push_front(i);
		assert(testInt.front() == i);
	}
	
	std::cout << "Testing pop_front (size: " << testInt.size() << ")" << std::endl;
  
	for (int i = 0; i < 20; i++)
	{
    assert(testInt.front() == 19-i);
    ///
    testInt.pop_front();
    ///
    if (testInt.size())
      assert(testInt.front() == 18-i);
    else
      assert(testInt.empty());
	}
  // size must be 0
  assert(testInt.size() == 0);
  // must be empty
  assert(testInt.empty());
  
  /// resize ///
  std::cout << "Testing resize (size: " << testInt.size() << ")" << std::endl;
  testInt.resize(40, 999);
  
  std::cout << "After resize n=40 v=999 (size: " << testInt.size() << ")" << std::endl;
  std::cout << "Value at front: " << testInt.front() << ", back: " << testInt.back() << std::endl;
  
  /// clear ///
  std::cout << "Testing clear - size: " << testInt.size() << std::endl;
  testInt.clear();
  std::cout << "After clear - size: " << testInt.size() << std::endl;
  
  
	return EXIT_SUCCESS;
	
	/////////////////////////////////////////////////////////
	std::cout << "//                 //" << std::endl;
	std::cout << "// Framework tests //" << std::endl;
	std::cout << "//                 //" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_maths();
	return EXIT_FAILURE;
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: lzo2 compression" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_compression();
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: glfw3 window & GL context" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_opengl_support();
	test_opengl_window();
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: OpenGL animated bone rig" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_opengl_bonerig();
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: Sockets" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_sockets();
	
	/////////////////////////////////////////////////////////
	std::cout << "//                 //" << std::endl;
	std::cout << "// Tests completed //" << std::endl;
	std::cout << "//                 //" << std::endl;
	/////////////////////////////////////////////////////////
	
	getchar();
	return EXIT_SUCCESS;
}

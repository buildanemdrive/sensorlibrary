#include <iostream>
#include <CUnit/Basic.h>
#include "sensorlibrary.h"
using namespace std;

void simpleTest(void) {
	// Run as fast as we can
	int length = 50;
	bem_reading_t sample[50];
	int returnVal = bem_get_sample(sample, 50);
	CU_ASSERT(returnVal == 0);
	CU_ASSERT(sample[0].reading != 0);
	for (int i = 0; i < 50; i++) {
		printf("%5i; %10i %10i\n", sample[i].reading, sample[i].time.tv_sec, sample[i].time.tv_usec);
	}

}

int main(int argc, char**argv) {
	CU_pSuite pSuite = NULL;
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("Suite_1", NULL, NULL);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "Simple Test", simpleTest)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	//CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

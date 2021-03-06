const char *MODEL_NAME                             = "Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz";
const unsigned int PHYSICAL_CHIPS                  = 1;
const unsigned int CORE_PER_CHIP                   = 6;
const unsigned int SMT_LEVEL                       = 2;
const unsigned int CACHE_PER_CORE                  = 9216;
const unsigned int seq_cores[]                     = {0,2,4,6,8,10,1,3,5,7,9,11};
const unsigned int rr_cores[]                      = {0,2,4,6,8,10,1,3,5,7,9,11};
const unsigned int test_hw_thr_cnts_fine_grain[]   = {1,2,4,6,12};
const unsigned int test_hw_thr_cnts_coarse_grain[] = {1,2,4,6,12};

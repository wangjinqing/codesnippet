 unsigned int rdm()
 {
     struct timeval tpstart;
     gettimeofday(&tpstart, NULL);
     srand(tpstart.tv_usec);
     return (unsigned int)(4561.0 * rand() / (RAND_MAX + 0.0));
  }

# Speed_Tests

This project contains all the necessary code to test 
multiple functions and compare how long they run.

My philosophy for testing is that if it takes 
less than a second it is not a meaning full test.

So for functions that don't take long just add one more 
zero at the end of the maxLoopCount variable until the 
times are inline with a reasonable testing time.

Once you have your testing times set you can run this
and see the results. like this


|Test | Start    | Stop     | Durations        |

|000x | HH:MM:SS | HH:MM:SS | YYY:DDD:HH:MM:SS |

|==============================================|

|0004 | 05:11:20 | 05:11:48 | 000:000:00:00:28 |

|0005 | 05:11:48 | 05:12:31 | 000:000:00:00:43 |

|0006 | 05:12:31 | 05:13:10 | 000:000:00:00:39 |


If your wondering why start with test 4?
Tests 1,2, and 3 were way slower than 4, 5, and 6,
and I was still tweaking the code for 4, 5, and 6.
So I commented out tests 1, 2, and 3.

 

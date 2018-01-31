#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

/*********
	A program to understand the Time related classes and templates supported in C++ 11.

	The time related functions in C++ 11 are a part of the chrono header,
	and primarily consist of the clock, time_point and the duration classes.
	
clocks:
A clock consists of a starting point (or epoch) and a tick rate. 

	system_clock			wall clock time from the system-wide realtime clock 
	steady_clock			monotonic clock that will never be adjusted 
	high_resolution_clock	the clock with the shortest tick period available 

time_point:
			a point in time (class template)
			A time point is a duration of time that has passed since the epoch of specific clock.

	

duration:
A duration consists of a span of time, defined as some number of ticks of some time unit.

	template <class Rep, class Period = ratio<1> >
	class duration;
				
	Rep
		An arithmetic type, or a class emulating an arithmetic type, to be used as the type for the internal count.
	Period
		A ratio type that represents the period in seconds.
		
The following convenience typedefs of instantiations of duration are also defined in this namespace:
type			Representation								Period
=========================================================================
hours			signed integral type of at least 23 bits	ratio<3600,1>
minutes			signed integral type of at least 29 bits	ratio<60,1>
seconds			signed integral type of at least 35 bits	ratio<1,1>
milliseconds	signed integral type of at least 45 bits	ratio<1,1000>
microseconds	signed integral type of at least 55 bits	ratio<1,1000000>
nanoseconds		signed integral type of at least 64 bits	ratio<1,1000000000>

**********/


int main()
{
//  typedef std::ratio<std::chrono::system_clock::period::num, std::chrono::system_clock::period::den> suppTime;
//  The 'using' format provides the new syntax instead of using typedef

// 	chrono::system_clock::period is of type 'std::ratio' that defines the time precision supported in the system.

    using suppTime = std::ratio<std::chrono::system_clock::period::num, std::chrono::system_clock::period::den>;
    std::cout << "Supported Time Precision: (" << suppTime::num << "/" << suppTime::den <<") " << std::endl;


///////////////////////// duration	(template_class)

	std::chrono::milliseconds millSec(36000);		//36000 milliseconds
	std::chrono::microseconds microSec = millSec;	//36000000 microseconds
	std::chrono::nanoseconds nanoSec = microSec;	//36000000000 nanoseconds

	// A direct assignment would lead to a lower precision and truncation, 
	// hence an explicit cast is required
    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(millSec);
	
	// count() returns the number of elements stored in the duration.
	std::cout << "milliseconds: " << millSec.count()  << std::endl;
	std::cout << "microseconds: " << microSec.count() << std::endl;
	std::cout << "nanoseconds:  " << nanoSec.count()  << std::endl;
	std::cout << "seconds:      " << sec.count()  	  << std::endl;
    
    // The std::duration is a template class also allows to create user defined duration types
    // Create user defined types for duration day.

							// std::ratio can be defined with just numerator, with the default denominator of 1
	using usrDay    = std::chrono::duration<double, std::ratio<1> >;    // number of days stored as a double.
	using usrWeek   = std::chrono::duration<double, std::ratio<7> >;	// number of days in a week, stored as a double.
	using usrMonth  = std::chrono::duration<double, std::ratio<30,1> >;	// number of days in a month, stored as a double.
    using usrYear   = std::chrono::duration<double, std::ratio<365,1> >; // number of days in an year, stored as a double.

    usrWeek week(1);
    usrDay day = week;
    usrMonth month = week;
    usrYear year = week;

    std::cout << "1 week: " << week.count() << std::endl;
    std::cout << "1 week: " << day.count() << " days"  << std::endl;
    std::cout << "1 week: " << month.count() << " month(s) " << std::endl;
    std::cout << "1 week: " << year.count() << " year(s)" << std::endl;

    usrMonth mon(3);
    usrWeek wk = mon;
    usrDay dy = mon;
    usrYear yr = mon; 

    std::cout << "3 month: " << mon.count() << std::endl;
    std::cout << "3 month: " << dy.count() << " days"  << std::endl;
    std::cout << "3 month: " << wk.count() << " week(s) " << std::endl;
    std::cout << "3 month: " << yr.count() << " year(s)" << std::endl;
	
	// You can apply arithmetic on the duration values created.
	
	usrWeek w(3);
    usrDay d(10);
    d += w;
//	usrDay d = w + std::chrono::duration_cast<usrDay>(10);
	std::cout << "3 weeks + 10 days: " << d.count()  << " days " << std::endl;

///////////////////////// time_point (template_class)
	
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now(); 	// Get the current time point
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);	// Convert the system_clock time to time_t format
	
	std::cout << "Current system_clock time: " << std::put_time( std::localtime(&currentTime), "%F - %T %p") << std::endl;
	
	std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
	std::cout << "Hello C++ 11" << std::endl;
	std::chrono::steady_clock::duration dr = std::chrono::steady_clock::now() - t0;
	
    //	std::cout << "Printing using cout took: " << std::chrono::duration_cast<std::chrono::microseconds>(dr).count() << std::endl;
	std::cout << "Printing using cout took: " << dr.count() << std::endl;
	
	t0 = std::chrono::steady_clock::now();
	std::cerr << "Hello C++ 11" << std::endl;
	dr = std::chrono::steady_clock::now() - t0;
	std::cout << "Printing using cerr took: " << dr.count() << std::endl;
	
	return 0;
}

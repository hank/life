#include <cstdlib>
#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace ba = boost::accumulators;

int main()
{
    ba::accumulator_set<double, ba::stats<ba::tag::mean,
    ba::tag::moment<2> > > acc;
    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);
    std::cout << "Mean: " << ba::mean(acc) << std::endl;
    std::cout << "2nd Moment: " << ba::moment<2>(acc) << std::endl;
    return EXIT_SUCCESS;
    
}

#include <iostream>
#include <string>
#include <boost/proto/proto.hpp>
#include <boost/typeof/std/ostream.hpp>

namespace proto = boost::proto;

proto::terminal< std::ostream & >::type cout_ = { std::cout };

template< typename Expr >
void evaluate( const Expr& expr)
{
   proto::default_context ctx;
   proto::eval(expr, ctx);
}

int main()
{
   evaluate( cout_ << "hello" << ", " << "world\n");
   return 0;
}

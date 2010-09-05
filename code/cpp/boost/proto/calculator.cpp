#include <iostream>
#include <vector>
#include <boost/proto/proto.hpp>

namespace proto = boost::proto;

template< int I >
struct placeholder {};

struct calculator_context
  : proto::callable_context< calculator_context const >
{
   std::vector<double> args;

   typedef double result_type;

   template<int I>
   double operator()(proto::tag::terminal, placeholder<I>) const
   {
      return this->args[I];
   }
};


proto::terminal<placeholder<0> >::type const _1 = {{}};
proto::terminal<placeholder<1> >::type const _2 = {{}};

int main()
{
   calculator_context ctx;
   ctx.args.push_back(45);
   ctx.args.push_back(50);

   double d = proto::eval( (_2 - _1) / _2 * 100, ctx);

   std::cout << d << std::endl;
}

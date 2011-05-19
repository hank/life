#include <iostream>
#include <vector>
#include <boost/proto/proto.hpp>

namespace proto = boost::proto;

template< typename Expr >
struct calculator;

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

struct calculator_domain
  : proto::domain< proto::generator<calculator> >
{};

struct calculator
   : proto::extends< Expr, calculator< Expr >, calculator_domain>
{
   typedef proto::extends< Expr, calculator< Expr >, calculator_domain>
      base_type;

   calculator(const Expr& expr = Expr())
      : base_type(expr)
   {}

   typedef double result_type;

   double operator() (double a1 = 0, double a2 = 0) const
   {
      calculator_context ctx;
      ctx.args.push_back(a1);
      ctx.args.push_back(a2);
      return proto::eval(*this, ctx);
   }
};


template< int I >
struct placeholder {};

calculator< proto::terminal<placeholder<0> > >::type const _1 = {{}};
calculator< proto::terminal<placeholder<1> > >::type const _2 = {{}};

int main()
{
   calculator_context ctx;
   ctx.args.push_back(45);
   ctx.args.push_back(50);

   double d = proto::eval( (_2 - _1) / _2 * 100, ctx);

   std::cout << d << std::endl;
}

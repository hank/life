-module(shop2).
-export([total/1]).
-import(lists, [map/2, sum/1]).
-import(shop, [cost/1]).

total(L) -> sum([cost(What) * N || {What, N} <- L]).

-module(exercise2).
-export([sum/1, sum/2, makelist/1, makerevlist/1]).

% Evaluating Expressions
sum(N) when N > 0 -> N + sum(N - 1);
sum(0) -> 0.

sum(N,M) when N < M -> N + sum(N + 1, M);
sum(N,M) when N == M -> M;
sum(_,_) -> {error, unknown}.

% Creating Lists
makelist(N) when N > 1 -> makelist(N-1) ++ [N];
makelist(1) -> [1].

makerevlist(N) when N > 1 -> [N] ++ makerevlist(N-1);
makerevlist(1) -> [1].


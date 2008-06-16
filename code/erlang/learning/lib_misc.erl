-module(lib_misc).
-compile(export_all).

sum(L) -> sum(L, 0).
sum([], N) -> N;
sum([H|T], N) -> sum(T, H+N).

for(Max, Max, F) -> [F(Max)];
for(I, Max, F) -> [F(I)|for(I+1, Max, F)].

% Quicksort
qsort([]) -> [];
qsort([Pivot|T]) -> qsort([X || X <- T, X < Pivot])
                    ++ [Pivot] ++
                    qsort([Y || Y <- T, Y >= Pivot]).

% Pythagorean Triplets
pythag(N) ->
	[ {A,B,C} ||
		A <- lists:seq(1,N),
		B <- lists:seq(1,N),
		C <- lists:seq(1,N),
		A+B+C =< N,
		A*A + B*B =:= C*C
	].

perms([]) -> [ [] ];
perms(L)  -> [ [H|T] || H <- L, T <- perms(L--[H])].

max(X,Y) when X > Y -> X;
max(_,Y) -> Y.

filter(F,[H|T]) -> 
	case F(H) of
		true -> [H|filter(F, T)];
		false -> filter(F, T)
	end;
filter(_, []) -> [].

% Use of an accumulator
odds_and_evens(L) ->
	odds_and_evens(L, [], []).

odds_and_evens([H|T], Odds, Evens) ->
	case (H rem 2) of
		1 -> odds_and_evens(T, [H|Odds], Evens);
		0 -> odds_and_evens(T, Odds, [H|Evens])
	end;
odds_and_evens([], Odds, Evens) -> {lists:reverse(Odds), lists:reverse(Evens)}.

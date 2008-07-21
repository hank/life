-module(mylists).
-compile(export_all).

sum([H|T]) -> H + sum(T);
sum([])    -> 0.

map(_, []) -> [];
map(F, [H|T])  -> [F(H)|map(F, T)].

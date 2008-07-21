-module(area_server0).
-export([start/0, area/2]).

start() -> spawn(fun loop/0).

area(Pid, WhatWhat) -> rpc(Pid, WhatWhat).

rpc(Pid, Request) ->
  Pid ! {self(), Request},
  receive
    {Pid, Response} -> Response
  end.

loop() ->
  receive
    {From, {rectangle, Width, Ht}} ->
      From ! {self(), Width * Ht},
      loop();
    {From, {circle, R}} ->
      From ! {self(), R * R * 3.14159},
      loop();
    {From, Other} ->
      From ! {self(), {error, Other}},
      loop()
  end.

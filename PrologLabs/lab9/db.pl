%%%%%%%%%
%   1   %
%%%%%%%%%

sum_up(N, D) :-
  Sum is 0,
  ( D >= N ->
    format('The result is ~w ~n', [D]) ;
    sum(N, D, Sum)
  ).

sum(N, D, Sum) :-
  N =< 0,
  format('The sum is ~w ~n', [Sum]).

sum(N, D, Sum) :-
  N > 0,
  Res is N + Sum,
  New is N - D,
  sum(New, D, Res).


%%%%%%%%%
%   2   %
%%%%%%%%%

pow(A, N, X) :-
  ( N >= 0 ->
    power(A, N, 1, X) ;
    negative_power(A, N, 1, X)
  ).

power(A, N, Res, X) :-
  N = 0,
  X is Res.

power(A, N, Res, X) :-
  N > 0,
  Tmp is A * Res,
  New is N - 1,
  power(A, New, Tmp, X).

negative_power(A, N, Res, X) :-
  N = 0,
  X is Res.

negative_power(A, N, Res, X) :-
  N < 0,
  Tmp is 1 / A * Res,
  New is N + 1,
  negative_power(A, New, Tmp, X).

%%%%%%%%%%%%%%%%%%%%%%%%

is_even(X) :-
  Y is X // 2,
  X =:= Y * 2.

pow2(A, N, X) :-
  ( is_even(N) ->
    pow_even(A, N, 1, 1, X) ;
    pow_odd(A, N, 1, 1, X)
  ).

pow_even(A, N, Rese, Reso, X) :-
  N = 0,
  X is Rese.

pow_even(A, N, Rese, Reso, X) :-
    N > 0,
    New is N // 2,
    pow_odd(A, New, Reso, XX),
    X is XX * XX.

pow_odd(A, N, Rese, Reso, X) :-
  N = 1,
  X is Reso.

pow_odd(A, N, Rese, Reso, X) :-
  N > 1,
  Tmp is A * Reso,
  New is N - 1,
  format('~w ~n', [Tmp]),
  ( is_even(New) ->
    pow_even(A, New, Rese, Tmp, X) ;
    pow_odd(A, New, Rese, Tmp, X)
  ).


%%%%%%%%%
%   3   %
%%%%%%%%%

sum_line(N) :-
  s_line(N, 0).

s_line(0, Sum) :-
  format('The sum is ~w', [Sum]).

s_line(N, Sum) :-
  N > 0,
  Res is N + Sum,
  New is N - 1,
  s_line(New, Res).


%%%%%%%%%
%   4   %
%%%%%%%%%
% pi ** 2 / 6 =:= 1.6449340668482264
% Calculate Pi^2 / 6 with N iterations
calc(N) :-
  calculate(N, 1, 0).

calculate(N, N, Res) :-
  format('The result is ~w ~n', [Res]).

calculate(N, K, Res) :-
  K =< N,
  Tmp is 1 / K ** 2 + Res,
  New is K + 1,
  calculate(N, New, Tmp).

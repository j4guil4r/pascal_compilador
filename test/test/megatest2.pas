program MegaProgram;
var
  n, i: integer;
  fib1, fib2: longint;
  limit: unsignedint;
  isPrimeFlag: boolean;

function isPrime(num: integer): boolean;
var
  i: integer;
begin
  if num <= 1 then
  begin
    isPrime := false;
  end
  else
  begin
    isPrime := true;
    i := 2;
    while i * i <= num do
    begin
      if num mod i = 0 then
      begin
        isPrime := false;
        i := num;
      end;
      i := i + 1;
    end;
  end;
end;

procedure printPrimes(limit: integer);
var
  i: integer;
begin
  for i := 2 to limit do
  begin
    if isPrime(i) then
    begin
      writeln(i);
    end;
  end;
end;

function fibonacci(n: integer): longint;
var
  a, b, temp: longint;
  i: integer;
begin
  if n <= 0 then
  begin
    fibonacci := 0;
  end
  else
  begin
    if n = 1 then
    begin
      fibonacci := 1;
    end
    else
    begin
      a := 0;
      b := 1;
      for i := 2 to n do
      begin
        temp := a + b;
        a := b;
        b := temp;
      end;
      fibonacci := b;
    end;
  end;
end;

procedure printFibonacci(count: integer);
var
  i: integer;
begin
  for i := 0 to count-1 do
  begin
    writeln(fibonacci(i));
  end;
end;

function isPalindrome(num: longint): boolean;
var
  original, reversed, digit: longint;
begin
  original := num;
  reversed := 0;
  while num > 0 do
  begin
    digit := num mod 10;
    reversed := reversed * 10 + digit;
    num := num div 10;
  end;
  isPalindrome := original = reversed;
end;

begin
  limit := 30;
  printPrimes(limit);

  printFibonacci(15);

  fib1 := fibonacci(10);
  fib2 := fibonacci(15);
  writeln(isPalindrome(fib1));
  writeln(isPalindrome(fib2));

  n := 20;
  isPrimeFlag := isPrime(n);
  if isPrimeFlag then
  begin
    writeln(1);
  end
  else
  begin
    writeln(0);
  end;

  i := 0;
  while i < 5 do
  begin
    writeln(i);
    i := i + 1;
  end;

  for i := 1 downto 0 do
  begin
    writeln(i);
  end;
end.
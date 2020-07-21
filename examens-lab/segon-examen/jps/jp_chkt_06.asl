func esmult3(n:int) : bool
  return n %3 == 0;
endfunc

func main()
  var a1,a2,a3: array [10] of int
  var b1,b2: array [10] of bool

  var n,m,s : int
  var x,y : char

  n = filter a1 into b1 using esmult3;
  m = n + filter a2 into b2 using esmult3; 
  s = m * filter a3 into b1 using esmult3 + 4; 

  x = filter a1 into b2 using esmult3;
  if filter a2 into b1 using esmult3 and
      y != filter a1 into b2 using esmult3 then
     s = 0;
  endif
endfunc

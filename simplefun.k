extern test(a);
extern prova(x[] size);
def func(x y)
  while x < y
  in
    x = x + 1:
    test(x)    
  end
;

def main()
  var x[10] = {1,2,3,4,5,6,7,8,9,10}
  in
    prova(x, 10)
  end 
;
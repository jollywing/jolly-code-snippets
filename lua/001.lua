
-- do not need ';' to end a statement
-- function in lua can return more than one values
function foo(a, b, c)
   -- only the variable decorated with 'local' is local variable
   -- otherwise, it is a global variable
   -- In this example, foo, r1, r2 are all global variables
   local sum = a * b
   return sum, c
end

-- parallel assignment
-- "" equals ''?
-- if fool returns only one value, r2 will be nil.
r1, r2 = foo(1, '123', "hello")
-- even though a number is quoted with '' or "",
-- it will be interpreted as a number when it meet arithmetic operators
-- However, a string can not joined a number with '+'
-- Then how to express a number string??
r1, r2 = r1 + 100, r2
print(r1, r2)

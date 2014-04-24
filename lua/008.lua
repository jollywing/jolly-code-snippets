
-- a lua file is a chunk
-- each statement may ends with ';'

--[[
This is a block commented.
In booleans, only false and nil are false, other are all true, include 0 and ''
--]]

function fact(n)
   if n == 0 then
      return 1
   else
      return n * fact(n - 1)
   end
end

print("Enter a number:")
a = io.read("*number")
print(fact(a))
-- .. join strings
print(10 .. 10 .. 10 .. 'hello')

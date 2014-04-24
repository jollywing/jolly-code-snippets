
-- metatable

function add(t1, t2)
   -- '#' get the length of table
   assert(#t1 == #t2)
   local length = #t1
   for i = 1, length do
      t1[i] = t2[i] + t1[i]
   end
   return t1
end

-- overload the operator +
t1 = setmetatable({1, 2, 3}, {__add = add})
t2 = setmetatable({20, 30, 40}, {__add = add})
t1 = t1 + t2

for i = 1, #t1 do
   print(t1[i])
end

